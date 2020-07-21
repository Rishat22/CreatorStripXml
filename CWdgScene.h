#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>

constexpr size_t maxItemCount = 50;

class CWdgScene : public QWidget
{
    Q_OBJECT
public:
	explicit CWdgScene(QWidget *parent = nullptr);
signals:

public slots:
	void addElementToScene();
private:
	void addGridToScene();
	void fillMatrixItemPos();
	QPoint getCenterPoint();
private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
	std::vector<std::vector<QPoint>> m_matrixPosOfItem;
};

#endif // CWDGTOWIN_H
