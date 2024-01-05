#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

/** PillarItem class is derived from QObject and QGraphicsItemGroup.
 */
class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

    //! Q_PROPERTY macro is used to define the x property.
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    //! Constructor for creating a PillarItem object.
    explicit PillarItem();

    //! Destructor for cleaning up resources when the PillarItem is destroyed.
    ~PillarItem();

    //! Access function for the x property.
    qreal x() const;

    //! Function to freeze the pillar in place.
    void freezeInPlace();

signals:
    //! Signal emitted when a collision with the bird is detected.
    void collideFail();

public slots:
    //! Slot to set the x coordinate of the pillar.
    void setX(qreal x);

private:
    //! Function to check if the pillar collides with the bird.
    bool collidesWithBird();

    //! Pointers to QGraphicsPixmapItems representing the top and bottom parts of the pillar.
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;

    //! Animation for the x-coordinate movement of the pillar.
    QPropertyAnimation *xAnimation;

    //! Initial y position of the pillar.
    int yPosition;

    //! Variable to store the current x coordinate of the pillar.
    qreal m_x;

    //! Flag indicating whether the bird has passed the pillar.
    bool pastBird;
};

#endif // PILLARITEM_H
