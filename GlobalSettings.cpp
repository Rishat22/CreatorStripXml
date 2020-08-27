#include "GlobalSettings.h"

GlobalSettings::GlobalSettings()
	: m_maxItemsSize(40),
	  m_itemStep(50),
	  m_itemColor(QColor(165, 45, 45))
{

}

GlobalSettings& GlobalSettings::get()
{
	static GlobalSettings s_GlobalSettings;
	return s_GlobalSettings;
}

QColor GlobalSettings::itemColor()
{
	return m_itemColor;
}

size_t GlobalSettings::maxItemsSize()
{
	return m_maxItemsSize;
}

size_t GlobalSettings::itemStep()
{
	return m_itemStep;
}

int GlobalSettings::modulusOfStep(const int value)
{
	auto& globalSettings = GlobalSettings::get();
	return static_cast<int>(value / (int)globalSettings.itemStep()) * globalSettings.itemStep();
}

QPoint GlobalSettings::modulusOfStep(const QPoint value)
{
	return QPoint(modulusOfStep(value.x()), modulusOfStep(value.y()));
}
