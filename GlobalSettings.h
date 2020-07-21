#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H
#include <QRectF>

class GlobalSettings
{
public:
	GlobalSettings();
	static size_t itemStep();
	static int modulusOfStep(const int value);
	static QPoint modulusOfStep(const QPoint value);
private:
};

#endif // GLOBALSETTINGS_H
