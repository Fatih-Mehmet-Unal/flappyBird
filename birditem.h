#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

/**
 *  The BirdItem class is derived from QObject and QGraphicsPixmapItem.
 */
class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    //! Q_PROPERTY macro is used to define custom properties.
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    //! Constructor that creates a BirdItem object taking a QPixmap as a parameter.
    explicit BirdItem(QPixmap pixmap);

    //! Access functions for the rotation property.
    qreal rotation() const;
    void setRotation(qreal newRotation);

    //! Access functions for the y property.
    qreal y() const;
    void setY(qreal newY);

    //! Function to make the bird move upwards.
    void shootUp();

    //! Function to ensure the bird falls to the ground if necessary.
    void fallToGroundNecessary();

    //! Function to initiate flying behavior.
    void startFlying();

    //! Function to freeze the bird in place.
    void freezeInPlace();

signals:

public slots:
    //! Slot to rotate the bird to a specified angle over a given duration with a specified easing curve.
    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);

private:
    //! Enumeration to represent wing positions.
    enum WingPosition
    {
        Up,
        Middle,
        Down
    };

    //! Function to update the bird's pixmap based on its wing position.
    void updatePixmap();

    //! Variables to store wing position, rotation, y-coordinate, and animations.
    WingPosition wingPosition;
    bool wingDirection;
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation *yAnimation;
    QPropertyAnimation *rotationAnimation;
    qreal groundPosition;
};

#endif // BIRDITEM_H
