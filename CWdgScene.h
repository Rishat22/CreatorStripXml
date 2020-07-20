#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>

constexpr auto gridStep = 50;

class CWdgScene : public QWidget
{
    Q_OBJECT
public:
	explicit CWdgScene(QWidget *parent = nullptr);
signals:

public slots:
	void AddElementToScene();
private:
    void AddGridToScene();

private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;

};

#endif // CWDGTOWIN_H
