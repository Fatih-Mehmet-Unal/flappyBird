#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // Set up the user interface.
    ui->setupUi(this);

    // Create a new game scene and define its dimensions.
    scene = new Scene(this);
    scene->setSceneRect(-250, -300, 500, 600);

    // Add a background image to the scene.
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(QPixmap(":/Images/background.png"));
    scene->addItem(backgroundItem);
    //This line puts the background we added in the center of the scene
    backgroundItem->setPos(-backgroundItem->boundingRect().center());

    // Set the created scene for the graphics view.
    ui->graphicsView->setScene(scene);

    // Add a bird to the scene.
    scene->addBird();
}

Widget::~Widget()
{
    // Clean up the UI.
    delete ui;
}

void Widget::on_startGameButton_clicked()
{
    // Start the game when the "Start" button is clicked.
    scene->startGame();
}
