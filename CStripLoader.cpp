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

std::list<StripItem> CStripLoader::load(const std::string& strFileName)
{
	return std::list<StripItem>();
}

bool CStripLoader::XmlNodeBegin(void)
{
	return true;
}

bool CStripLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	return false;
}

