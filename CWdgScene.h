#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

//ToDo move to forvard declaration
#include <StableDeclaration.h>
#include <CStripItemConfig.h>
#include <CGraphicsItem.h>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QWidget>

constexpr size_t maxItemsSize = 30;
using namespace UUserPolicies;

class CStripScene: public QGraphicsScene
{
	Q_OBJECT
public:
	CStripScene(QObject* pParent = NULL) : QGraphicsScene::QGraphicsScene()
	{
	}
	virtual ~CStripScene(void) {}
signals:
	void ItemMouseReleased(CGraphicsItem*);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
	{
		CGraphicsItem* pItem = dynamic_cast<CGraphicsItem*>(itemAt(mouseEvent->scenePos(), QTransform()));
		emit ItemMouseReleased(pItem);
		QGraphicsScene::mouseReleaseEvent(mouseEvent);
	}
};

class CWdgScene : public QWidget
{
    Q_OBJECT
public:
	explicit CWdgScene(QWidget *parent = nullptr);
	std::list<CStripItemConfig> GetStripItemsParams();
	void setElementsToScene(std::list<CStripItemConfig>& stripItemsConfigs);
signals:
	void selectedItemConfig(const CStripItemConfig&);
public slots:
	void addElementToScene(const CStripItemConfig& stripItem);
private slots:
	void ItemMouseReleased(CGraphicsItem* graphicsItem);
private:
	void addGridToScene();
	void fillMatrixItemPos();
	QPoint getCenterPoint();
	void clearScene();
private:
	CStripScene* m_scene;
    QGraphicsView* m_view;
	std::vector<std::vector<QPoint>> m_matrixPosOfItem;
	std::map<CGraphicsItem*, CStripItemConfig> m_stripItems;
};

#endif // CWDGTOWIN_H
