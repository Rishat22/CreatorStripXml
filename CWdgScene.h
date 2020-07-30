#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

#include <StableDeclaration.h>
#include <StripItem.h>
#include <QWidget>

constexpr size_t maxItemsSize = 30;

class CWdgScene : public QWidget
{
    Q_OBJECT
public:
	explicit CWdgScene(QWidget *parent = nullptr);
	std::list<StripItem> GetStripItemsList();
signals:

public slots:
	void addElementToScene(const StripItem& stripItem);
private:
	void addGridToScene();
	void fillMatrixItemPos();
	QPoint getCenterPoint();
private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
	std::vector<std::vector<QPoint>> m_matrixPosOfItem;
	//Required sort by params pointer than by address.
	template<class T> struct ptr_less {
		bool operator()(T* lhs, T* rhs) {
			return *lhs < *rhs; }};
	std::map<CGraphicsItem*, StripItem, ptr_less<CGraphicsItem>> m_stripItems;
};

#endif // CWDGTOWIN_H
