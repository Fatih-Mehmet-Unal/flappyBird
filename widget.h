#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

/** Widget class derived from QWidget.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    //! Constructor for creating a Widget object.
    Widget(QWidget *parent = nullptr);

    //! Destructor for cleaning up resources when the Widget is destroyed.
    ~Widget();

private slots:
    //! Slot for handling the start game button click event.
    void on_startGameButton_clicked();

private:
    //! Pointer to the UI object.
    Ui::Widget *ui;

    //! Pointer to the Scene object managing the game scene.
    Scene *scene;
};

#endif // WIDGET_H
