#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);

private:
    Ui::MainWindow *m_ui;
    Game *game;
    QTimer tickerick;
    bool rup;
    bool rdown;
    bool lup;
    bool ldown;

public slots:
    void movePaddles();
};

#endif // MAINWINDOW_H
