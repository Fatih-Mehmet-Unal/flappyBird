#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"

/** Scene class derived from QGraphicsScene.
 */
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    //! Constructor for creating a Scene object.
    explicit Scene(QObject *parent = nullptr);

    //! Function to add a bird to the scene.
    void addBird();

    //! Function to start the game.
    void startGame();

    //! Function to check if the game is currently running.
    bool getGameOn() const;

    //! Function to set the game state.
    void setGameOn(bool newGameOn);

    //! Function to increment the score.
    void incrementScore();

    //! Function to get the current score.
    int getScore() const;

    //! Function to set the score.
    void setScore(int newScore);

signals:

private:
    //! Functions for managing game graphics and state.
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();

    //! Timer for controlling game events.
    QTimer *timer;

    //! Pointer to the BirdItem representing the player's bird.
    BirdItem *bird;

    //! Flag indicating whether the game is currently running.
    bool gameOn;

    //! Variables to store the current score and best score.
    int score;
    int bestScore;

    //! QGraphicsItems for displaying game over graphics and score.
    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem *scoreTextItem;

protected:
    //! Override keyPressEvent and mousePressEvent for handling user input.
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
