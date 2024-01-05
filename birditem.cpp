#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>

/**This is the constructor of BirdItem class which initializes some values ​​in class birditem
 */
//and takes pixmap object from QPixmap class as parameter.
BirdItem::BirdItem(QPixmap pixmap):
    wingPosition(WingPosition::Up),
    wingDirection(0)

{
    // Set the pixmap for the current object.
    setPixmap(pixmap);

    // Create a QTimer for bird wings animation.
    QTimer *birdWingsTimer = new QTimer(this);

    // Connect the timeout signal of the timer to the updatePixmap slot using a lambda function.
    connect(birdWingsTimer, &QTimer::timeout, this, [=]() {
        updatePixmap();
    });

    // Start the bird wings timer with a timeout interval of 80 milliseconds.
    birdWingsTimer->start(80);

    // Set the initial ground position based on the scene position.
    groundPosition = scenePos().y() + 290;

    // Create a vertical position animation using QPropertyAnimation.
    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    // Create a rotation animation using QPropertyAnimation.
    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
}



//This method updates the bird's wing position.
void BirdItem::updatePixmap() {
    QString imagePath;

    switch (wingPosition) {
    case WingPosition::Middle:
        if (wingDirection) {
            // up
            imagePath = ":/Images/bird_red_up.png";
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        } else {
            // down
            imagePath = ":/Images/bird_red_down.png";
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }
        break;
    case WingPosition::Up:
        // middle
        imagePath = ":/Images/bird_red_middle.png";
        wingPosition = WingPosition::Middle;
        break;
    case WingPosition::Down:
        // middle
        imagePath = ":/Images/bird_red_middle.png";
        wingPosition = WingPosition::Middle;
        break;
    }

    setPixmap(QPixmap(imagePath));
}


//This method returns the bird's rotation.
qreal BirdItem::rotation() const
{
    return m_rotation;
}


//This method sets the new rotation for the bird.
void BirdItem::setRotation(qreal newRotation)
{
    if (m_rotation != newRotation) {
        m_rotation = newRotation;


        QTransform transform;
        transform.rotate(m_rotation);

        setTransform(transform);
    }
}

//This method returns the y coordinate of bird.
qreal BirdItem::y() const
{
    return m_y;
}

//This method sets the new Y coordinate for the bird.
void BirdItem::setY(qreal newY)
{
    moveBy(0,newY-m_y);
    m_y = newY;
}
//This method allows the bird to move up.
void BirdItem::shootUp()
{
    // Stop existing animations
    yAnimation->stop();
    rotationAnimation->stop();

    // Retrieve current Y position
    qreal curPosY = y();

    // Set up animation for upward movement
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height() / 8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    // Connect a lambda function to be executed when the animation finishes
    connect(yAnimation, &QPropertyAnimation::finished, [=]() {
        fallToGroundNecessary();
    });

    // Start the Y animation
    yAnimation->start();

    // Rotate the bird to a specified angle with a cubic easing curve
    rotateTo(-20, 200, QEasingCurve::OutCubic);
}



// Check if the bird is still in the air (above the ground).
void BirdItem::fallToGroundNecessary()
{
    // If the bird is flying, start the falling animation.

    if (y() < groundPosition) {

        // Stop any ongoing rotation (flapping wings) animation.
        rotationAnimation->stop();

        // Set up the falling animation: from current height to the ground over 1200 milliseconds.
        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);

        // Start the falling animation.
        yAnimation->start();

        // Rotate the bird to a 90-degree angle over 1100 milliseconds with smooth motion.
        rotateTo(90, 1100, QEasingCurve::InCubic);


    }
}


// This method starts the bird's flying animation, lifting it up, and rotates the bird to a 90-degree angle over 1200 milliseconds.
void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90, 1200, QEasingCurve::InQuad);
}

// This method stops the Y animation and rotation animation, freezing the bird item in its current position.
void BirdItem::freezeInPlace()
{
    // Stop the vertical position animation.
    yAnimation->stop();

    // Stop the rotation animation.
    rotationAnimation->stop();
}


// This method initiates a smooth rotation animation for the bird.
void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{

    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

