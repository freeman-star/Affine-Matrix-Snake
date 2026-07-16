#include "Snake.h"
#include <QPainter>
#include <QRandomGenerator>
#include <cmath>

Snake::Snake(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: black;");
    resize(1080, 1080); // Standard field size
    
    // Resize vectors to hold up to 100 body segments
    x.resize(100);
    y.resize(100);
    
    loadImages();
    initGame();
}

void Snake::loadImages() {
    // 1. Load the raw image files
    dot.load("dot.jpg");
    head.load("head.jpg");
    apple.load("apple.jpg");

    // 2. Define uniform target size (70x70 pixels)
    int targetSize = 70;

    // 3. Scale all images to exactly the target size
    dot = dot.scaled(targetSize, targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    head = head.scaled(targetSize, targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    apple = apple.scaled(targetSize, targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void Snake::initGame() {
    dots = 3;
    angle = 0.0;  // Start facing right (0 degrees)
    speed = 50.0; 


    for (int z = 0; z < dots; z++) {
        x[z] = 560 - (z * speed); 
        y[z] = 560;
    }

    locateApple();
    timerId = startTimer(200); 
    inGame = true;
}

void Snake::locateApple() {
    apple_x = QRandomGenerator::global()->bounded(10, 950);
    apple_y = QRandomGenerator::global()->bounded(10, 950);
}

void Snake::move() {
    // 1. Shift the body: each segment moves to the position of the segment ahead of it
    for (int z = dots; z > 0; z--) {
        x[z] = x[z - 1];
        y[z] = y[z - 1];
    }

    // 2. Calculate translation components based on current rotation angle
    qreal rad = angle * M_PI / 180.0;
    qreal dx = speed * std::cos(rad);
    qreal dy = speed * std::sin(rad);

    // 3. Apply the Affine Transformation Matrix to the Head
    QTransform T;
    T.translate(dx, dy); 

    // Multiply the current head coordinates by the translation matrix to get the new state
    T.map(x[0], y[0], &x[0], &y[0]);
}

void Snake::checkCollision() {
    for (int z = dots; z > 0; z--) {
        if ((z > 4) && (std::abs(x[0] - x[z]) < 30) && (std::abs(y[0] - y[z]) < 30)) {
            inGame = false;
        }
    }
    if (y[0] >= 1080 || y[0] < 0 || x[0] >= 1080 || x[0] < 0) {
        inGame = false;
    }

    if (!inGame) {
        killTimer(timerId);
    }
}

void Snake::timerEvent(QTimerEvent *event) {
    if (inGame) {
        int hitBoxSize = 70; 
        
        if (std::abs(x[0] - apple_x) < hitBoxSize && std::abs(y[0] - apple_y) < hitBoxSize) {
            dots++;
            locateApple();
        }

        checkCollision();
        move();
    }
    
    repaint(); 
}

void Snake::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    if (inGame) {
        painter.drawImage(apple_x, apple_y, apple);
        
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                // To rotate the head image visually to match the trajectory, 
                // apply a transformation matrix to the QPainter itself
                painter.save();
                painter.translate(x[z], y[z]);
                painter.rotate(angle);
                painter.drawImage(-head.width() / 2, -head.height() / 2, head);
                painter.restore();
            } else {
                painter.drawImage(x[z], y[z], dot);
            }
        }
    } else {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "Game Over");
    }
}

void Snake::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    // Left and Right arrows steer the snake's angle
    if (key == Qt::Key_Left) {
        angle -= 15.0; // Steer left by 15 degrees
    } else if (key == Qt::Key_Right) {
        angle += 15.0; // Steer right by 15 degrees
    } 
    // Up and Down arrows dynamically control the speed
    else if (key == Qt::Key_Up) {
        speed += 2.0; // Accelerate
    } else if (key == Qt::Key_Down) {
        if (speed > 2.0) {
            speed -= 2.0; // Brake (prevents stopping completely or reversing)
        }
    }
}