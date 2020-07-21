#ifndef CGRAPHICSITEM_H
#define CGRAPHICSITEM_H
#include <QGraphicsItem>
#include <QBrush>

constexpr size_t adjustMouseResize = 5;
enum class ResizeMode
{
    top,
    bottom,
    left,
    right,
    topRight,
    topLeft,
    bottomRight,
    bottomLeft,
};

class CGraphicsItem : public QGraphicsItem
{
public:
    explicit CGraphicsItem(const QRect& size, const QColor color);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void resizeItem(QGraphicsSceneMouseEvent* event);
    void moveItem(QGraphicsSceneMouseEvent* event);
    size_t modulusOfStep(const size_t value);
private:
    QRectF m_itemRect;
    QBrush m_itemBrush;
    ResizeMode m_resizeMode;
    bool m_isMoveMode;
    size_t m_initPos;
    size_t itemStep;
};

#endif // CGRAPHICSITEM_H
