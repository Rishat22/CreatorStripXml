#include "CItemInfoGetter.h"
#include <Galaxy/CStripItem.h>
#include <Galaxy/CActionItem.h>

CItemInfoGetter::CItemInfoGetter()
{

}

std::vector<std::string> CItemInfoGetter::getListWithTypeNames()
{
	std::vector<std::string> listWithTypeNames;
	UVisualTools::CStripItem stripItem;
	for(auto typeItemIndex = 0; typeItemIndex <= (int)stripItem.LastElement(); typeItemIndex++)
	{
		std::string itemName;
		if(stripItem.GetNameById(typeItemIndex, itemName))
		{
			listWithTypeNames.push_back(std::move(itemName));
		}
	}
	return listWithTypeNames;
}

std::vector<std::string> CItemInfoGetter::getListWithActionNames()
{
	std::vector<std::string> listWithActionNames;
	UUserPolicies::CActionItem actionItem;
	for(auto typeItemIndex = 0; typeItemIndex <= (int)actionItem.LastElement(); typeItemIndex++)
	{
		std::string itemName;
		if(actionItem.GetNameById(typeItemIndex, itemName))
		{
			listWithActionNames.push_back(std::move(itemName));
		}
	}
	return listWithActionNames;
}
