#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTransform>
#include <vector>

class Snake : public QWidget {
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);

protected:
    // Qt Event Overrides
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    // Assignment Methods
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();

    // Game State Variables
    bool inGame;
    int timerId;
    int dots;
    qreal angle; 
    qreal speed;

    // Entity Coordinates (Using qreal for continuous, non-grid movement)
    std::vector<qreal> x;
    std::vector<qreal> y;
    qreal apple_x;
    qreal apple_y;

    // Graphical Assets
    QImage dot;
    QImage head;
    QImage apple;
};