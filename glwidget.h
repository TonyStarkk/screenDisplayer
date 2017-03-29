#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>
#include <Qtimer>

class GLWidget : public QGLWidget
{
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;
};

#endif // GLWIDGET_Hfind
