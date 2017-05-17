#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *mouseEvent);

    void write(QString filename);
    void read(QString filename);

    void drawPolarCircle(QPainter *qp, int radius, int xc, int yc, QPen pen);
    void drawCartesianCircle(QPainter *qp, int radius, int xc, int yc, QPen pen);
    void drawMidpointCircle(QPainter *qp, int radius, int xc, int yc, QPen pen);
    void drawIPolar(QPainter *qp, int xc, int yc, int radius, QPen pen);
    void drawLine(QPainter *qp, int x1, int y1, int x2, int y2, QPen pen);
    void drawDDALine(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen);
    void drawParametricLine(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen);

    void drawHermiteCurve(QPainter *qp, int x0, int y0, int x1, int y1, QPen pen);
    void drawBezierCurve(QPainter *qp, QPoint p0, QPoint p1, QPoint p2, QPoint p3, QPen pen);
    void drawfirstDegreeCurve(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen);
    void drawSecondDegreeCurve(QPainter *qp, int x0, int xHalf, int x1, int y0, int yHalf, int y1, QPen pen);
    void drawSpline(QPainter *qp, QPoint p[], int n, QPen pen);

    void convexFill(QPainter *qp, QPoint p[], int n);
    void floodFill(QPainter *qp, int x, int y);

    void pointClippingRectangle(QPainter *qp, int x, int y, QPen pen);
    void lineRectangleClipping(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen);
    void lineRectangleClippingVariable(QPainter *qp, QPoint p0, QPoint p1, QPoint p2, QPoint p4, QPen pen);
    void pointCircleClipping(QPainter *qp, int x, int y, QPen);
    void lineCircleClipping(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen);

    int click = 0;

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_fontComboBox_activated(const QString &arg1);

    void on_circle_currentIndexChanged(int index);

    void on_line_currentIndexChanged(int index);

    void on_curve_currentIndexChanged(int index);

    void on_filling_currentIndexChanged(int index);

    void on_rectangleClipping_currentIndexChanged(int index);

    void on_circleClipping_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_backgroundColor_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
