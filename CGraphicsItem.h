#ifndef CGRAPHICSITEM_H
#define CGRAPHICSITEM_H
#include <QGraphicsItem>
#include <QBrush>

class CGraphicsItem : public QGraphicsItem
{
public:
    explicit CGraphicsItem(const QRect& size, const QColor color);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool m_mousePressed;
    size_t itemStep;
    QRectF m_itemRect;
    QBrush m_itemBrush;
};

#endif // CGRAPHICSITEM_H
