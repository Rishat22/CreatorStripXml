#ifndef STRIPITEM_H
#define STRIPITEM_H

#include <string>
#include <QRect>

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
public:
    std::string name;
    Interaction interaction;
	QRect rect;
	int fontCoefficient;

};
#endif // STRIPITEM_H
