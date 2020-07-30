#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H

#include <StableDeclaration.h>
#include <QWidget>

class CWdgSelectionMenu : public QWidget
{
	Q_OBJECT
public:
	CWdgSelectionMenu(QWidget *parent = nullptr);
signals:
	void addElementToScene(const StripItem& stripItem);
	void saveData(const std::string& strFileName);
private slots:
	void createGraphicsItem();
private:
	QStringList getListByType(const TypeItemParam typeParam);
	QLayout* createComboBox(const TypeItemParam typeParam, const QString& textDescription);
	void fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet);
	QComboBox* createComboBox(const QStringList& typeItemsList);
	QLabel* createDescription(const QString &textDescription);
	void addCreateElementsButton(QBoxLayout* layoutToInsert);
	void addSaveButton(QBoxLayout* layoutToInsert);
private:
	std::map<TypeItemParam, QString> m_itemParams;
};

#endif // CWDGSELECTIONMENU_H
