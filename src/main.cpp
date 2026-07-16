#include <QApplication>
#include "Snake.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Snake window;
    window.setWindowTitle("Affine Matrix Snake");
    window.show();
    
    return app.exec();
}