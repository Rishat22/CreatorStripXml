#ifndef CSTRIPLOADER_H
#define CSTRIPLOADER_H
#include <USerialization/CXmlHandler.h>
#include <CStripItemConfig.h>
#include <StableDeclaration.h>

using namespace USerialization;
using namespace UUserPolicies;
class CStripLoader : public CXmlHandler
{

public:
	CStripLoader();

public:
	void setData(const std::list<CStripItemConfig>& stripItemsList);
	bool save(const std::string& strFileName);
	std::list<CStripItemConfig> load(const std::string& strFileName);

	bool XmlNodeBegin(void);
	bool XmlNodeDecode(const std::string& strNodeValue);
private:
	void saveName(CXmlNode* parentNode, const CStripItemConfig& itemConfig);
	void saveParams(CXmlNode* parentNode, const CStripItemConfig& itemConfig);
	void saveInteractions(CXmlNode* parentNode, const CStripItemConfig& itemConfig);
private:
	std::list<CStripItemConfig> m_stripsConfigList;
};

#endif // CSTRIPLOADER_H
