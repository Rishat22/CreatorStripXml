#ifndef CWDGSELECTIONMENU_H
#define CWDGSELECTIONMENU_H

#include <QWidget>

class CWdgSelectionMenu : public QWidget
{
    Q_OBJECT
public:
    explicit CWdgSelectionMenu(QWidget *parent = nullptr);

signals:
    void AddElementToScene();
private:
    void AddCreateElementsButton(QLayout* layoutToInsert);
};

#endif // CWDGSELECTIONMENU_H
