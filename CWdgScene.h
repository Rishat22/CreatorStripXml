#ifndef CWDGTOWIN_H
#define CWDGTOWIN_H

#include <StableDeclaration.h>
#include <CStripItemConfig.h>
#include <QWidget>

constexpr size_t maxItemsSize = 30;
using namespace UUserPolicies;

class CWdgScene : public QWidget
{
    Q_OBJECT
public:
	explicit CWdgScene(QWidget *parent = nullptr);
	std::list<CStripItemConfig> GetStripItemsParams();
	void setElementsToScene(std::list<CStripItemConfig>& stripItemsConfigs);
signals:

public slots:
	void addElementToScene(const CStripItemConfig& stripItem);
private:
	void addGridToScene();
	void fillMatrixItemPos();
	QPoint getCenterPoint();
	void clearScene();
private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
	std::vector<std::vector<QPoint>> m_matrixPosOfItem;
	std::map<CGraphicsItem*, CStripItemConfig> m_stripItems;
};

#endif // CWDGTOWIN_H
