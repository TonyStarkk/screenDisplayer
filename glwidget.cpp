#include "glwidget.h"
#include <GLUT/glut.h>
#include <vector>
#include <iostream>

using namespace std;

GLWidget::GLWidget(QWidget *parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL() {
    glClearColor(1, 0.2, 0.2, 1);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    // 4 bytes per pixel (RGBA), 1x1 bitmap
    vector< unsigned char > pixels( 1 * 1 * 4 );
    glReadPixels
        (
        10, glutGet( GLUT_WINDOW_HEIGHT ) - 10,
        1, 1,
        GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]
        );

    cout << "r: " << (int)pixels[0] << endl;
    cout << "g: " << (int)pixels[1] << endl;
    cout << "b: " << (int)pixels[2] << endl;
    cout << "a: " << (int)pixels[3] << endl;
    cout << endl;
    glRotatef(0.5, 1, 1, 1);
    glutWireTeapot(0.6);
}

void GLWidget::resizeGL(int w, int h) {

}
