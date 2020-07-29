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

bool CStripLoader::save(const std::string& strFileName)
{
	CXmlNode* pDoc = NewDocument(strFileName);
	bool bRes = SaveDocument();

	return bRes;
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
