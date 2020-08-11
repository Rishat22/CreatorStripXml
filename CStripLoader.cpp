#include "CStripLoader.h"
#include <StripItem.h>
#include <string>

CStripLoader::CStripLoader()
{

}

void CStripLoader::setData(const std::list<StripItem>& stripItemsList)
{
	m_stripItemsList = stripItemsList;
}

std::list<StripItem> CStripLoader::load(const std::string& strFileName)
{
	m_stripItemsList.clear();
	CXmlHandler::Load(strFileName);
	return std::list<StripItem>();
}

//ToDo need to fix hardcore saving.
bool CStripLoader::save(const std::string& strFileName)
{
	CXmlNode* document = NewDocument(strFileName);
	CXmlNode* itemsNode = NewNode("Items", document);
	for(const auto& item : m_stripItemsList)
	{
		CXmlNode* itemNode = NewNode("Item", itemsNode);
		CXmlNode* itemNameNode = NewNode("Name", itemNode);
		itemNameNode->SetValue(item.name);
		saveParams(itemNode, item);
		saveInteractions(itemNode, item);
	}
	bool bRes = SaveDocument();

	return bRes;
}

void CStripLoader::saveParams(CXmlNode* parentNode, const StripItem& item)
{
	CXmlNode* itemParamsNode = NewNode("Params", parentNode);
	CXmlNode* itemXNode = NewNode("X", itemParamsNode);
	itemXNode->SetValue(item.rect.x());
	CXmlNode* itemYNode = NewNode("Y", itemParamsNode);
	itemYNode->SetValue(item.rect.y());
	CXmlNode* itemWNode = NewNode("CustomWidth", itemParamsNode);
	itemWNode->SetValue(item.rect.width());
	CXmlNode* itemHNode = NewNode("CustomHeight", itemParamsNode);
	itemHNode->SetValue(item.rect.height());
}

void CStripLoader::saveInteractions(CXmlNode* parentNode, const StripItem& item)
{
	CXmlNode* itemInteractionsNode = NewNode("Interactions", parentNode);
	CXmlNode* triggerNode = NewNode("Trigger", itemInteractionsNode);
	const auto itemInteraction = item.interaction;
	triggerNode->SetValue(itemInteraction.trigger);
	CXmlNode* actionNode = NewNode("Action", itemInteractionsNode);
	actionNode->SetValue(itemInteraction.action);
}

bool CStripLoader::XmlNodeBegin(void)
{
	const S32 topNodeIndex = 0;
	if(m_vStrOfNodes[topNodeIndex] == "Items")
	{
		if(m_vStrOfNodes[topNodeIndex +1] == "Item")
		{
			if(m_vStrOfNodes[topNodeIndex + 2] == "")
			{
				m_stripItemsList.push_back(StripItem());
			}
		}
	}
	return true;
}

bool CStripLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	if(m_stripItemsList.empty())
	{
		return false;
	}
	const auto currentStripIndex = m_stripItemsList.size() - 1;
	const S32 topNodeIndex = 0;
	if(m_vStrOfNodes[topNodeIndex] == "Items")
	{
		if(m_vStrOfNodes[topNodeIndex + 1] == "Item")
		{
//			m_stripItemsList[currentStripIndex];
		}
	}
}

