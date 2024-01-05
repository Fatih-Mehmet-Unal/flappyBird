#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>


/** This is a constructor for the Scene class, initializing member variables and setting up the pillar creation timer.
 */
Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}, gameOn(false), score(0), bestScore(0)
{
    // Set up the timer for creating and updating pillars.
    setUpPillarTimer();
}

//This method allows adding bird to the scene.
void Scene::addBird()
{

    bird=new BirdItem(QPixmap(":/Images/bird_red_up.png"));
    addItem(bird);
}
// Set up a timer for creating and updating pillars at regular intervals.
void Scene::setUpPillarTimer()
{
    // Create a QTimer object associated with this scene.
    timer = new QTimer(this);

    // Connect the timer's timeout signal to create a new PillarItem.
    connect(timer, &QTimer::timeout, [=]() {
        // Create a new PillarItem.
        PillarItem *pillarItem = new PillarItem();

        // Connect the collideFail signal to handle collision failures.
        connect(pillarItem, &PillarItem::collideFail, [=]() {
            // Stop the timer and handle game over conditions.
            timer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });

        // Add the created PillarItem to the scene.
        addItem(pillarItem);
    });
}



//This method allows to starting the game by using some other class's methods.
void Scene::startGame()
{
    //Bird
    bird->startFlying();

    //Pillars
    if(!timer->isActive()){
        cleanPillars();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        timer->start(800);
    }

}


//This method freeze bird and pillars if game is over.
void Scene::freezeBirdAndPillarsInPlace()
{   //freeze bird
    bird->freezeInPlace();
    //freeze pillars
    QList<QGraphicsItem *>sceneItems=items();
    foreach (QGraphicsItem * item, sceneItems) {
        PillarItem * pillar=dynamic_cast<PillarItem*>(item);
        if(pillar){
            pillar->freezeInPlace();
        }

    }
}
//This method returns the score in the game.This is getter method.
int Scene::getScore() const
{
    return score;
}
//This method sets the new score .This is setter method.
void Scene::setScore(int newScore)
{
    score = newScore;
}

// Getter method to retrieve the current game status.
bool Scene::getGameOn() const
{
    return gameOn;
}

// Setter method to update the game status.
void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

//This method allows to incrementing score and if current score is bigger than bestScore ,it arranges score as new bestScore.
void Scene::incrementScore()
{
    score++;
    if(score>bestScore){
        bestScore=score;

        qDebug() <<"Score :" << score;
        qDebug() <<"Best Score :" <<bestScore;
    }
}
//This method shows the  game over picture and score best score on the scene when the game is over.
void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/Images/gameOver.png"));
    addItem(gameOverPix);

    const QPointF offset(100, 120);
    //Sets the position of the game over pixmap.
    gameOverPix->setPos(QPointF(0, 0) - offset);

    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = QString("<p> Score: %1 </p><p> Best Score: %2 </p>").arg(score).arg(bestScore);
    QFont mFont("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::red);
    addItem(scoreTextItem);
    //Sets the position of the text item as center of the scene.
    const QPointF textItemPos = QPointF(0, 0) - QPointF(scoreTextItem->boundingRect().width() / 2, scoreTextItem->boundingRect().height() / 2);
    scoreTextItem->setPos(textItemPos);
}

//This method hides the game over picture  and the score best score and is called when the game starts
void Scene::hideGameOverGraphics()
{
    if (gameOverPix && items().contains(gameOverPix)) {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if (scoreTextItem && items().contains(scoreTextItem)) {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

//This method allows clean the pillars when the game starts.
void Scene::cleanPillars()
{
    QList<QGraphicsItem*>sceneItems=items();
    foreach (QGraphicsItem * item, sceneItems) {
        PillarItem *pillar=dynamic_cast<PillarItem*>(item);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }

    }
}

// Respond to the space key press event to make the bird shoot up if the game is ongoing.
void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

// Respond to the left mouse button press event to make the bird shoot up if the game is ongoing.
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

