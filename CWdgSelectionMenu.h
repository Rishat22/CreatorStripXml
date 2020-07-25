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
    void addElementToScene();
private:
	void fillTypeItemsList();
	void fillActionNamesList();
	void fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet);
	QLayout* createComboBoxWithDescription(const QStringList& typeItemsList, const std::string& textDescription);
	QComboBox* createComboBox(const QStringList& typeItemsList);
	QLabel* createDescription(const std::string& textDescription);
    void addCreateElementsButton(QBoxLayout* layoutToInsert);
private:
	QStringList m_typeItemsList;
	QStringList m_actionNamesList;
};

#endif // CWDGSELECTIONMENU_H
