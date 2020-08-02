#ifndef STRIPITEM_H
#define STRIPITEM_H

#include <string>
#include <QRect>

enum class TypeItemParam
{
	Action,
	Trigger,
	Name,
	FontCoifficient
};

struct Interaction
{
	Interaction() = default;
    Interaction(const std::string& actionName, const std::string& trigger)
	: action(actionName), trigger(trigger) {}
    std::string action;
    std::string trigger;
};


struct StripItem
{
public:
	StripItem() = default;
	bool operator < ( const StripItem& compareStripItem)
	{
		if(rect.x() == compareStripItem.rect.x())
		{
			return rect.y() < compareStripItem.rect.y();
		}
		return rect.x() < compareStripItem.rect.x();
	}
	bool setDataByType(const TypeItemParam type, const std::string& paramData)
	{
		bool result = true;
		switch (type)
		{
			case TypeItemParam::Name:
			{
				name = paramData;
				break;
			}
			case TypeItemParam::Action:
			{
				interaction.action = paramData;
				break;
			}
			case TypeItemParam::Trigger:
			{
				interaction.trigger = paramData;
				break;
			}
			default:
			{
				result = false;
				break;
			}
		}
		return result;
	}
public:
    std::string name;
    Interaction interaction;
	QRect rect;
	int fontCoefficient;

};
#endif // STRIPITEM_H
