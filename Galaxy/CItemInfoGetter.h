#ifndef CITEMINFOGETTER_H
#define CITEMINFOGETTER_H
#include <string>
#include <vector>

class CItemInfoGetter
{
public:
	CItemInfoGetter();
	std::vector<std::string> getListWithTypeNames();
	std::vector<std::string> getListWithActionNames();
};

#endif // CITEMINFOGETTER_H
