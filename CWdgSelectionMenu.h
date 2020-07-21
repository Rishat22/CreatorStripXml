#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H
#include <QBoxLayout>
#include <QWidget>

class CWdgSelectionMenu : public QWidget
{
    Q_OBJECT
public:
    CWdgSelectionMenu(QWidget *parent = nullptr);
signals:
    void addElementToScene();
private:
    QStringList& fillTypeItemsFilst();
    void addComboBoxWithTypeItems(const QStringList& typeItemsList, QBoxLayout* layoutToInsert);
    void addCreateElementsButton(QBoxLayout* layoutToInsert);
private:
    QStringList m_typeItemsList;
};

#endif // CWDGSELECTIONMENU_H
