#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

#include <StableDeclaration.h>
#include <CStripItemConfig.h>
#include <CGraphicsScene.h>
#include <QWidget>

using namespace UUserPolicies;

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
	void addItemToScene(const CStripItemConfig& stripItem);
	void overwriteItemFromScene(const CStripItemConfig& stripItem);
	void deleteItemFromScene(const CStripItemConfig& stripItem);
private slots:
	void itemMouseReleased(CGraphicsItem* graphicsItem);
private:
	void addGridToScene();
	void fillMatrixItemPos();
	QPoint getCenterPoint();
	void clearScene();
private:
	CGraphicsScene* m_scene;
    QGraphicsView* m_view;
	std::vector<std::vector<QPoint>> m_matrixPosOfItem;
	std::map<CGraphicsItem*, CStripItemConfig> m_stripItems;
};

#endif // CWDGTOWIN_H
