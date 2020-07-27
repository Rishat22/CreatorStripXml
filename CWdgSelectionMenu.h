#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H

#include <StableDeclaration.h>
#include <QWidget>
enum class StripItemParam
{
    Action,
    Name,
    FontCoifficient
};

class CWdgSelectionMenu : public QWidget
{
    Q_OBJECT
public:
    CWdgSelectionMenu(QWidget *parent = nullptr);
signals:
    void addElementToScene();
private slots:
    void createGraphicsItem();
private:
    QStringList getListByType(const StripItemParam typeParam);
    QLayout* createComboBox(const StripItemParam typeParam, const QString& textDescription);
	void fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet);
	QComboBox* createComboBox(const QStringList& typeItemsList);
    QLabel* createDescription(const QString &textDescription);
    void addCreateElementsButton(QBoxLayout* layoutToInsert);
private:
    std::map<StripItemParam, QString> m_itemParams;
};

#endif // CWDGSELECTIONMENU_H
