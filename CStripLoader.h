#ifndef CSTRIPLOADER_H
#define CSTRIPLOADER_H
#include <QObject>

class CStripLoader : public QObject
{
    Q_OBJECT
public:
	CStripLoader();

public slots:
	bool saveStripItem(const std::string& strFileName);
	//return (StripItem)Struc
	void loadStripItem(const std::string& strFileName);
};

#endif // CSTRIPLOADER_H
