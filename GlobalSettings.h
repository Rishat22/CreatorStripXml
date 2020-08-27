#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H
#include <QRectF>
#include <QColor>

class GlobalSettings
{
public:
	GlobalSettings(const GlobalSettings&) = delete;
	GlobalSettings & operator = (const GlobalSettings&) = delete;
	static GlobalSettings& get();
	QColor itemColor();
	size_t maxItemsSize();
	size_t itemStep();
	static int modulusOfStep(const int value);
	static QPoint modulusOfStep(const QPoint value);
private:
	GlobalSettings();
	size_t m_maxItemsSize;
	size_t m_itemStep;
	QColor m_itemColor;
};
#endif // GLOBALSETTINGS_H
