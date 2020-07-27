#ifndef STRIPITEM_H
#define STRIPITEM_H

#include <string>
#include <QRect>

struct Interaction
{
    Interaction(const std::string& actionName, const std::string& trigger)
	: action(actionName), trigger(trigger) {}
    std::string action;
    std::string trigger;
};

struct StripItem
{
public:
    StripItem() {}
public:
    std::string name;
    Interaction interaction;
    QRect stripRect;
    int FontCoefficient;

};
#endif // STRIPITEM_H
