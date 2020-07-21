#include "GlobalSettings.h"

GlobalSettings::GlobalSettings()
{

}

size_t GlobalSettings::itemStep()
{
	return 50;
}

int GlobalSettings::modulusOfStep(const int value)
{
	return static_cast<int>(value / (int)itemStep()) * itemStep();
}

QPoint GlobalSettings::modulusOfStep(const QPoint value)
{
	return QPoint(modulusOfStep(value.x()), modulusOfStep(value.y()));
}
