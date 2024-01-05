#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include<QGraphicsScene>
#include <birditem.h>
#include "scene.h"
/** Constructor for PillarItem, creating top and bottom pillars with corresponding pixmap items.
*/
PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    pastBird(false)
{
    // Add top and bottom pillars to the item group.
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    // Set the initial positions of top and bottom pillars.
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width() / 2,
                                              topPillar->boundingRect().height() + 80));

    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width() / 2, 60));

    // Generate random y-position and x-position for the pillar item.
    yPosition = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPosition));

    // Create and start the x-position animation for horizontal movement.
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    xAnimation->start();

    // Connect the finished signal of xAnimation to remove the item from the scene and delete it.
    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });
}

//This is destructor of pillaritem class.
PillarItem::~PillarItem()
{
    //Clean up the topPillar and bottomPillar
    delete topPillar;
    delete bottomPillar;
}


// Getter method to retrieve the x-coordinate of the PillarItem.
qreal PillarItem::x() const
{
    return m_x;
}

// Stop the horizontal movement animation to freeze the PillarItem in place.
void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

// Setter method to update the x-coordinate of the PillarItem and handle collisions.
void PillarItem::setX(qreal x)
{
    m_x = x;

    // Check if the pillar has passed the bird and update the score.
    if (x < 0 && !pastBird) {
        pastBird = true;
        QGraphicsScene *mScene = scene();
        Scene *myScene = dynamic_cast<Scene *>(mScene);

        if (myScene) {
            myScene->incrementScore();
        }
    }

    // Check for collisions with the bird and emit the collideFail signal if a collision occurs.
    if (collidesWithBird()) {
        emit collideFail();
    }

    // Update the position of the PillarItem.
    setPos(QPointF(0, 0) + QPointF(x, yPosition));
}

// Check for collisions with the bird by examining colliding items with the top and bottom pillars.
bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem *> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach (QGraphicsItem *item, collidingItems) {
        BirdItem *birdItem = dynamic_cast<BirdItem *>(item);
        if (birdItem) {
            return true;
        }
    }
    return false;
}





