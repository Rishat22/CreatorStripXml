#include "CItemInfoGetter.h"
#include <UUserPolicies/CStripItem.h>
#include <UUserPolicies/CActionItem.h>
#include <UUserPolicies/CMouseButtonItem.h>

CItemInfoGetter::CItemInfoGetter()
{

}

std::vector<std::string> CItemInfoGetter::getListWithTypeNames()
{
	std::vector<std::string> listWithTypeNames;
	UUserPolicies::CStripItem stripItem;
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

std::vector<std::string> CItemInfoGetter::getListWithTriggers()
{
	std::vector<std::string> listWithActionNames;
	UUserPolicies::CMouseButtonItem mouseItem;
	for(auto typeItemIndex = 0; typeItemIndex <= (int)mouseItem.LastElement(); typeItemIndex++)
	{
		std::string itemName;
		if(mouseItem.GetNameById(typeItemIndex, itemName))
		{
			listWithActionNames.push_back(std::move(itemName));
		}
	}
	return listWithActionNames;
}
