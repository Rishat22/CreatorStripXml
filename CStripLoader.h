#ifndef CSTRIPLOADER_H
#define CSTRIPLOADER_H
#include <USerialization/CXmlHandler.h>
#include <StableDeclaration.h>

using namespace USerialization;
class CStripLoader : public CXmlHandler
{

public:
	CStripLoader();

public:
	void setData(const std::list<StripItem>& stripItemsList);
	bool save(const std::string& strFileName);
	std::list<StripItem> load(const std::string& strFileName);

	bool XmlNodeBegin(void);
	bool XmlNodeDecode(const std::string& strNodeValue);
private:
	void saveParams(CXmlNode* parentNode, const StripItem& item);
	void saveInteractions(CXmlNode* parentNode, const StripItem& item);
private:
	std::list<StripItem> m_stripItemsList;
};

#endif // CSTRIPLOADER_H
