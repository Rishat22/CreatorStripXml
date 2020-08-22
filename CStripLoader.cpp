#include "CStripLoader.h"
#include <string>

CStripLoader::CStripLoader()
{

}

void CStripLoader::setData(const std::list<CStripItemConfig>& stripItemsList)
{
	m_stripsConfigList = stripItemsList;
}

std::list<CStripItemConfig> CStripLoader::load(const std::string& strFileName)
{
	m_stripsConfigList.clear();
	CXmlHandler::Load(strFileName);
	return m_stripsConfigList;
}

//ToDo need to fix hardcore saving.
bool CStripLoader::save(const std::string& strFileName)
{
	CXmlNode* document = NewDocument(strFileName);
	CXmlNode* itemsNode = NewNode("Items", document);
	for(const auto& itemConfig : m_stripsConfigList)
	{
		CXmlNode* itemNode = NewNode("Item", itemsNode);
		saveName(itemNode, itemConfig);
		saveParams(itemNode, itemConfig);
		saveInteractions(itemNode, itemConfig);
	}
	bool bRes = SaveDocument();

	return bRes;
}

void CStripLoader::saveName(CXmlNode* parentNode, const CStripItemConfig& itemConfig)
{
	CXmlNode* itemNameNode = NewNode(itemConfig.Item().GetTag(CBaseItem::Name), parentNode);
	itemNameNode->SetValue(itemConfig.Item().GetData(CBaseItem::Name));
}

void CStripLoader::saveParams(CXmlNode* parentNode, const CStripItemConfig& itemConfig)
{
	CXmlNode* itemParamsNode = NewNode("Params", parentNode);
	for(auto paramIndex = 0; paramIndex < itemConfig.ParamNum(); paramIndex++)
	{
		CStripItemParamItem itemParam;
		if(!itemConfig.GetParamByIndex(paramIndex, itemParam))
		{
			continue;
		}
		CXmlNode* itemXNode = NewNode(itemParam.GetTag(CBaseItem::Name), itemParamsNode);
		//	ToDo mb use: itemConfig.S32ValueById()
		itemXNode->SetValue(itemParam.GetData());
	}
}

void CStripLoader::saveInteractions(CXmlNode* parentNode, const CStripItemConfig& itemConfig)
{
	CXmlNode* itemInteractionsNode = NewNode("Interactions", parentNode);
	const auto& interactions = itemConfig.GetCInteractions();
	for(const auto interaction : interactions.Interactions())
	{
		CXmlNode* triggerNode = NewNode(interaction.CTrigger().GetTag(CBaseItem::Name), itemInteractionsNode);
		triggerNode->SetValue(interaction.CTrigger().GetData());
		CXmlNode* actionNode = NewNode(interaction.CAction().GetTag(CBaseItem::Name), itemInteractionsNode);
		actionNode->SetValue(interaction.CAction().GetData());
	}
}

bool CStripLoader::XmlNodeBegin(void)
{
	const size_t topNodeIndex = 0;
	if(m_vStrOfNodes[topNodeIndex] == "Items")
	{
		if(m_vStrOfNodes[topNodeIndex +1] == "Item")
		{
			if(m_vStrOfNodes[topNodeIndex + 2] == "")
			{
				m_stripsConfigList.emplace_back();
			}
		}
	}
	return true;
}

bool CStripLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	bool bRes = false;
	if(m_stripsConfigList.empty())
	{
		return false;
	}
	const auto topNodeIndex = 0;
	if(m_vStrOfNodes[topNodeIndex] == "Items")
	{
		if(m_vStrOfNodes[topNodeIndex + 1] == "Item")
		{
			if(m_vStrOfNodes[topNodeIndex + 2] == "Interactions")
			{
				bRes = m_stripsConfigList.back().GetInteractions().SetData(m_vStrOfNodes[topNodeIndex + 3], strNodeValue);
			}
			else if(m_vStrOfNodes[topNodeIndex + 2] == "Params")
			{
				if(!m_vStrOfNodes[topNodeIndex + 3].empty())
				{
					bRes = m_stripsConfigList.back().AddParam(m_vStrOfNodes[topNodeIndex + 3], strNodeValue);
					if(!bRes)
					{
						printf("Wrong strip item param : %s \n", strNodeValue.data());
					}
				}
			}
			else
			{
				bRes = m_stripsConfigList.back().SetItemData(m_vStrOfNodes[topNodeIndex + 2], strNodeValue);
				if(!bRes)
				{
					printf("Wrong strip item data : %s \n", strNodeValue.data());
				}
			}
//
		}
	}
	if(bRes == false)
	{
		printf("Error loading strip configuration. \n");
		printf("Value = %s \n", strNodeValue.data());
	}
	return bRes;
}

