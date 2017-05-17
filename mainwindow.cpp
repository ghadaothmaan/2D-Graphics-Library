#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <bits/stdc++.h>
#include <QMouseEvent>
#include <algorithm>
#include <QMouseEvent>
#include <QPaintEvent>
#include <bits/stdc++.h>
#include <QPoint>
#include <QImage>
#include <QWindow>
#include <QScreen>
#include <QDataStream>
#include <QFile>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //   this->setStyleSheet("background-color: white;");
        QImage img(16,16,QImage::Format_RGB32);
        QPainter p(&img);
        p.fillRect(img.rect(), Qt::black);

        QBrush* brush;

        QRect rect = img.rect().adjusted(1,1,-1,-1);

        brush = new QBrush(QColor(255, 204, 204));
        p.fillRect(rect, *brush);
        ui->backgroundColor->setItemData(1, QPixmap::fromImage(img), Qt::DecorationRole);

        brush = new QBrush(QColor(204, 255, 204));
        p.fillRect(rect, *brush);
        ui->backgroundColor->setItemData(2, QPixmap::fromImage(img), Qt::DecorationRole);

        brush = new QBrush(QColor(255, 255, 204));
        p.fillRect(rect, *brush);
        ui->backgroundColor->setItemData(3, QPixmap::fromImage(img), Qt::DecorationRole);

        setMouseTracking(true);

}

int chosen = -1;
int nPoints = 1;
double PI = 3.14;
QPoint points[10];

vector <int> allDrawings [1000];
int drawingNum = 0;

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent){
    points[click++] =  mouseEvent->pos();
    if (click == nPoints){
        allDrawings[drawingNum].push_back(chosen);
        allDrawings[drawingNum].push_back(nPoints);
        for (int i = 0; i < nPoints; i++){
            allDrawings[drawingNum].push_back(points[i].x());
            allDrawings[drawingNum].push_back(points[i].y());
        }
        ++drawingNum;
        update();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::write(QString filename)
{

    ofstream file;
    file.open("data.txt");

    file << drawingNum << endl;
    for (int i = 0; i < drawingNum; i++){
        file << allDrawings[i].size() << endl;
        for (int j = 0; j < allDrawings[i].size(); j++)
            file << allDrawings[i][j] << ' ';
        file << endl;
    }

    file.close();
}

void MainWindow::read(QString filename)
{

    ifstream file;
    file.open("data.txt");

    file >> drawingNum;
    for (int i = 0; i < drawingNum; i++){
        int n, x;
        file >> n;
        for (int j = 0; j < n; j++){
            file >> x;
            allDrawings[i].push_back(x);
        }
    }

    update();
    file.close();

}



void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter qp(this);
    QPen pen (Qt::blue, 2, Qt::SolidLine);
    qp.setPen(pen);


    if (click){

        for (int i = 0; i < 1000; i++){
            if (allDrawings[i].size() == 0) continue;
            chosen = allDrawings[i][0];
            if (chosen == -1) continue;
            nPoints = allDrawings[i][1];
            int k = 0;
            for (int j = 2; j < allDrawings[i].size(); j+=2){
                QPoint p;
                p.setX(allDrawings[i][j]);
                p.setY(allDrawings[i][j+1]);
                points[k] = p;
                ++k;
            }

            if (chosen == 0)
                drawPolarCircle(&qp, 100, points[0].x(), points[0].y(), pen);
            else if (chosen == 1)
                drawIPolar(&qp, points[0].x(), points[0].y(), 150, pen);
            else if (chosen == 2)
                drawMidpointCircle(&qp, 50, points[0].x(), points[0].y(), pen);
            else if (chosen == 3)
                drawCartesianCircle(&qp, 75, points[0].x(), points[0].y(), pen);
            else if (chosen == 4)
                drawDDALine(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 5)
                drawLine(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 6)
                drawParametricLine(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 7)
                drawfirstDegreeCurve(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 8)
                drawSecondDegreeCurve(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), points[2].x(), points[2].y(), pen);
            else if (chosen == 9)
                drawBezierCurve(&qp, points[0], points[1], points[2], points[3], pen);
            else if (chosen == 10)
                drawHermiteCurve(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 11)
                drawSpline(&qp, points, nPoints, pen);
            else if (chosen == 12)
                convexFill(&qp, points, nPoints);
            else if (chosen == 13)
                floodFill(&qp, points[0].x(), points[0].y());
            else if (chosen == 14)
                pointClippingRectangle(&qp, points[0].x(), points[0].y(), pen);
            else if (chosen == 15)
                lineRectangleClipping(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 16)
                pointCircleClipping(&qp, points[0].x(), points[0].y(), pen);
            else if (chosen == 17)
                lineCircleClipping(&qp, points[0].x(), points[0].y(), points[1].x(), points[1].y(), pen);
            else if (chosen == 18)
                lineRectangleClippingVariable(&qp, points[0], points[1], points[2], points[3], pen);
            click = 0;
        }
    }

}

void MainWindow::drawLine (QPainter *qp, int x1, int y1, int x2, int y2, QPen pen){

    pen.setWidth(10);
    qp->setPen(pen);
    qp->drawPoint (x1, y1);
    qp->drawPoint(x2, y2);
    pen.setWidth(2);
    pen.setColor(Qt::black);
    qp->setPen(pen);

    int dx, dy, pk, x, y, d = 1;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) < abs(dy)){ // |slope| < 1

        if (y1 > y2){
            swap (y2, y1);
            swap (x2, x1);
            dx*=-1;
            dy*=-1;
        }

        if (x2 < x1){
            dx*=-1;
            d = -1;
        }

        pk =  2 * dx - dy;
        x = x1;
        y = y1;

        while (y < y2){

            if (pk <= 0)
                pk+= 2 *  dx;
            else {
                pk+= (2 * dx - 2 * dy);
                x+=d;
            }

            qp->drawPoint(x, y);
            ++y;

        }

        qp->drawPoint(x2, y2);

    }


    else {

        if (x1 > x2){
            swap (x2, x1);
            swap (y2, y1);
            dx*=-1;
            dy*=-1;
        }

        if (y1 > y2){
            dy*=-1;
            d = -1;
        }

        pk = 2 * dy - dx;
        x = x1;
        y = y1;


        qp->drawPoint(x, y);

        while (x < x2){

            if (pk < 0) {
                pk += 2 * dy;
            } else {
                pk += (2 * dy - 2 * dx);
                y+=d;
            }


            qp->drawPoint(x, y);

            ++x;

        }

        qp->drawPoint(x2, y2);


    }
}

void MainWindow::drawDDALine(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen)
{
    int dx = xe - xs, dy = ye - ys;
    qp->drawPoint(xs, ys);
    double slope;
    //slope < 1
    if (abs(dx) >= abs(dy)) {
        slope = (double) dy / (double) dx;

        /*if (xs > xe) {
             swap(xs, xe);
             swap(ys, ye);
             }*/

        int x = xs, xincr = dx > 0 ? 1 : -1; // we increase x 1 unit at a time
        double y = ys, yincr = (double)slope*xincr;
        while (x != xe) {
            x += xincr; y += yincr;
            qp->drawPoint(x, round(y));
        }
    }

    else {
        slope = (double) dx / (double) dy;

        /*if (ys > ye) {
             swap(xs, xe);
             swap(ys, ye);
             }*/

        int y = ys, yincr = dy > 0 ? 1 : -1;
        double x = (double)xs, xincr = (double)slope*yincr;
        while (y != ye) {
            x += xincr; y += yincr;
            qp->drawPoint(round(x), y);
        }
    }
}

//TODO: fix other slope
void MainWindow::drawParametricLine(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen)
{
    pen.setColor(Qt::red);
    qp->setPen(pen);

    int dx = abs(xe - xs);
    int dy = abs(ye - ys);
    double slope;
    if (dy <= dx) {
        slope = (double) dy / dx; // must cast to double

        if (xs > xe) {
            swap(xs, xe);
            swap(ys, ye);
        }

        for (int x = xs; x <= xe; x++) {
            int y = round(ys + (x - xs)*slope);
            qp->drawPoint(x, y);
        }
    }
    else {
        slope = (double) dx / dy;
        if (ys > ye) {
            swap(xs, xe);
            swap(ys, ye);
        }

        for (int y = ys; y <= ye; y++) {
            int x = round(xs + (y - ys)*slope);
            qp->drawPoint(x, y);
        }
    }
}



void MainWindow::drawHermiteCurve(QPainter *qp, int x0, int y0, int x1, int y1, QPen pen)
{
    qp->drawPoint(x0, y0);
    double dt = (double) 1 / 1000, slope1 = 500, slope2 = 500,
            alpha1 = slope2 - (2 * x1) + slope1 + (2 * x0),         // alpha1 = slope2 - 2x1 + slope1 + 2x0
            beta1 = (3 * x1) - slope2 - (2 * slope1) - (3 * x0),    // beta1 = 3x1 - slope2 - 2slope1 - 3x0
            alpha2 = slope2 - (2 * y1) + slope1 + (2 * y0),
            beta2 = (3 * y1) - slope2 - (2 * slope1) - (3 * y0);

    for (double t = 0; t <= 1; t += dt){
        double x = (alpha1 * pow(t, 3)) + (beta1 * pow(t, 2)) + (slope1 * t) + x0;
        double y = (alpha2 * pow(t, 3)) + (beta2 * pow(t, 2)) + (slope1 * t) + y0;

        qp->drawPoint(round(x), round(y));
    }
}

void MainWindow::drawBezierCurve(QPainter *qp, QPoint p0, QPoint p1, QPoint p2, QPoint p3, QPen pen)
{
    pen.setBrush(Qt::red);
    qp->setPen(pen);

    double dt = 1.0 / 1000,
            alphax = (-1 * p0.x()) + (3 * p1.x()) + (-3 * p2.x()) + p3.x(),
            betax = (3 * p0.x()) + (-6 * p1.x()) + (3 * p2.x()),
            gammax = (-3 * p0.x()) + (3 * p1.x()),
            sigmax = p0.x(),

            alphay = (-1 * p0.y()) + (3 * p1.y()) + (-3 * p2.y()) + p3.y(),
            betay = (3 * p0.y()) + (-6 * p1.y()) + (3 * p2.y()),
            gammay = (-3 * p0.y()) + (3 * p1.y()),
            sigmay = p0.y();

    for (double t = 0; t <= 1; t += dt) {

        double x = (alphax * pow(t, 3)) + (betax * pow(t, 2)) + (gammax * t) + sigmax,
                y = (alphay * pow(t, 3)) + (betay * pow(t, 2)) + (gammay * t) + sigmay;

        qp->drawPoint(round(x), round(y));
    }
}

void MainWindow::drawfirstDegreeCurve(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen)
{
    drawParametricLine(qp, xs, ys, xe, ye, pen);
}

void MainWindow::drawSecondDegreeCurve(QPainter *qp, int x0, int y0, int xHalf, int yHalf, int x1, int y1, QPen pen)
{

    qp->drawPoint(x0, y0);
    pen.setBrush(Qt::yellow);
    qp->setPen(pen);
    double dt = (double)1 / 1000,
            alpha1 = (2 * x1) - (4 * xHalf) + (2 * x0),
            beta1 = (4 * xHalf) - x1 - (3 * x0),
            alpha2 = (2 * y1) - (4 * yHalf) + (2 * y0),
            beta2 = (4 * yHalf) - y1 - (3 * y0);
    for (double t = 0; t <= 1; t += dt) {
        double x = (alpha1 * pow(t, 2)) + (beta1 * t) + x0,
                y = (alpha2 * pow(t, 2)) + (beta2 * t) + y0;
        qp->drawPoint(round(x), round(y));
    }
}

void mul(int A[4][4], double B[4], double C[4]) { //Multiply Hermite Matrix By Vector
    for (int i = 0; i < 4; i++) {
        C[i] = 0;
        for (int j = 0; j < 4; j++)
            C[i] += A[i][j] * B[j];
    }
}

double dot(double A[4], double B[4]) {
    double sum = 0;
    for (int i = 0; i < 4; i++)
        sum += A[i] * B[i];
    return sum;
}

void DrawCurve_Hermite(QPainter* qp, QPoint p1, QPoint t1, QPoint p2, QPoint t2) {
    double x, y;
    double dt = 1.0 / 10000;

    int basisMatrix[4][4] = { { 2, 1, -2, 1 },{ -3, -2, 3, -1 },{ 0, 1, 0, 0 },{ 1, 0, 0, 0 } };
    double vx[4] = { p1.x(), t1.x(), p2.x(), t2.x() };
    double vy[4] = { p1.y(), t1.y(), p2.y(), t2.y() };
    double gx[4], gy[4];

    mul(basisMatrix, vx, gx);
    mul(basisMatrix, vy, gy);

    for (double t = 0; t <= 1; t += dt) {
        double vt[4] = { t*t*t, t*t, t, 1 };
        x = dot(gx, vt);
        y = dot(gy, vt);
        qp->drawPoint(round(x), round(y));
    }
}


void MainWindow::drawSpline(QPainter *qp, QPoint p[], int n, QPen pen)
{

    double c = 1/100.0;
    double c1 = 1 - c;
    QPoint T0(c1 *(p[2].x() - p[0].x()), c1*(p[2].y() - p[0].y()));
    for (int i = 2; i < n - 1; i++){
        QPoint T1 (c1*(p[i+1].x()-p[i-1].x()), c1*(p[i+1].y()-p[i-1].y()));
        (qp, p[i-1], T0, p[i], T1, pen);
        DrawCurve_Hermite(qp, p[i-1], T0, p[i], T1);
        T0 = T1;
    }
    //drawSecondDegreeCurve(qp, p[0].x(), p[0].y(), p[1].x(), p[1].y(), p[2].x(), p[2].y(), pen);

}



void draw8Points (QPainter *qp, int xc, int yc, int a, int b, QPen pen){

    qp->setPen(pen);

    qp->drawPoint(xc+a, yc+b);
    qp->drawPoint(xc-a, yc+b);
    qp->drawPoint(xc+a, yc-b);
    qp->drawPoint(xc-a, yc-b);
    qp->drawPoint(xc+b, yc+a);
    qp->drawPoint(xc-b, yc+a);
    qp->drawPoint(xc+b, yc-a);
    qp->drawPoint(xc-b, yc-a);

}

void MainWindow::drawPolarCircle(QPainter *qp, int radius, int xc, int yc, QPen pen){

    double dtheta = 1.0 / radius;

    for (double i = 0; i < PI / 4; i += dtheta) {
        int x = radius * cos(i);
        int y = radius * sin(i);
        draw8Points(qp, xc, yc, round(x), round(y), pen);
    }

}

void MainWindow::drawCartesianCircle(QPainter *qp, int radius, int xc, int yc, QPen pen)
{
    int x = 0, y = radius;
    while (x <= y) {
        draw8Points(qp, xc, yc, x, y, pen);
        x++; y = sqrt((radius * radius) - (x * x));
    }
}

void MainWindow::drawMidpointCircle(QPainter *qp, int radius, int xc, int yc, QPen pen)
{
    int x = 0, y = radius;
    draw8Points(qp, xc, yc, x, y, pen);
    while (x <= y) {
        double d = pow((x + 1), 2) + pow((y - 0.5), 2) - (radius * radius);
        if (d < 0) {
            x++;
        }
        else {
            x++;
            y--;
        }
        draw8Points(qp, xc, yc, x, y, pen);
    }
}

void MainWindow::drawIPolar(QPainter *qp, int xc, int yc, int radius, QPen pen)
{


    double x = radius, y = 0;
    double dtheta = 1.0/radius;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    draw8Points(qp, xc, yc, radius, 0, pen);
    while (x > y){
        double x1 = x*cdtheta - y*sdtheta;
        y = x*sdtheta + y*cdtheta;
        x = x1;
        draw8Points(qp, xc, yc, round(x), round(y), pen);
    }
}


struct Entry {
    int xmin, xmax;
};

void InitEntries(Entry table[])
{
    for (int i = 0; i<600; i++)
    {
        table[i].xmin = INT_MAX;
        table[i].xmax = INT_MIN;
    }
}

void ScanEdge(QPoint v1, QPoint v2, Entry table[])
{
    if (v1.y() == v2.y())return;
    if (v1.y()>v2.y())swap(v1, v2);
    double minv = (double)(v2.x() - v1.x()) / (v2.y() - v1.y());
    double x = v1.x();
    int y = v1.y();
    while (y<v2.y())
    {
        if (x<table[y].xmin)table[y].xmin = (int)ceil(x);
        if (x>table[y].xmax)table[y].xmax = (int)floor(x);
        y++;
        x += minv;
    }
}

void DrawSanLines(QPainter *qp, Entry table[])
{
    for (int y = 0; y<600; y++)
        if (table[y].xmin<table[y].xmax)
            for (int x = table[y].xmin; x <= table[y].xmax; x++)
                qp->drawPoint(x, y);
}

void MainWindow::convexFill(QPainter *qp, QPoint p[], int n)
{
    Entry *table = new Entry[600];
    InitEntries(table);
    QPoint v1 = p[n - 1];
    for (int i = 0; i<n; i++)
    {
        QPoint v2 = p[i];
        ScanEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawSanLines(qp, table);
    delete table;
}

void MainWindow::floodFill(QPainter *qp, int x, int y)
{

   QPixmap qPix = QPixmap::grabWindow(this->winId(), x, y, 1, 1);
   QImage image(qPix.toImage());
   QColor color(image.pixel(0,0));
   QPen pen (color);
   pen.setWidth(6);
   qp->setPen(pen);
   qp->drawPoint(100, 100);

}


void MainWindow::pointClippingRectangle(QPainter *qp, int x, int y, QPen pen)
{
    int windowX1 = 100;
    int windowY1 = 300;
    int windowX2 = 400;
    int windowY2 = 100;

    drawLine(qp, windowX1, windowY2, windowX2, windowY2, pen);
    drawLine(qp, windowX1, windowY2, windowX1, windowY1, pen);
    drawLine(qp, windowX1, windowY1, windowX2, windowY1, pen);
    drawLine(qp, windowX2, windowY2, windowX2, windowY1, pen);

    pen.setWidth(4);
    qp->setPen(pen);
    if (x >= windowX1 && y <= windowY1 && x <= windowX2 && y >= windowY2)
        qp->drawPoint(x, y);

}

void MainWindow::lineRectangleClipping(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen)
{
    int windowX1 = 600;
    int windowY1 = 300;
    int windowX2 = 900;
    int windowY2 = 100;

    drawLine(qp, windowX1, windowY2, windowX2, windowY2, pen);
    drawLine(qp, windowX1, windowY2, windowX1, windowY1, pen);
    drawLine(qp, windowX1, windowY1, windowX2, windowY1, pen);
    drawLine(qp, windowX2, windowY2, windowX2, windowY1, pen);

    //xs and ys
    if (ys < windowY2){ //top
        xs = (ys*xe - ye*xs - windowY2*xe + windowY2*xs)/(ys-ye);
        ys = windowY2;
    }
    if (xs > windowX2){ //right
        ys = (ye*xs - ye*windowX2 - ys*xe + ys*windowX2)/(xs-xe);
        xs = windowX2;
    }

    if (ys > windowY1){ //down
        xs = (ys*xe - ye*xs - windowY1*xe + windowY1*xs)/(ys-ye);
        ys = windowY1;
    }

    if (xs < windowX1){ //left
        ys = (ye*xs - ye*windowX1 - ys*xe + ys*windowX1)/(xs-xe);
        xs = windowX1;
    }

    //xe ye
    if (ye < windowY2){ //top
        xe = (-1*ys*xe + ye*xs + windowY2*xe - windowY2*xs)/(ye-ys);
        ye = windowY2;
    }
    if (xe > windowX2){ //right
        ye = (-1*ye*xs + ye*windowX2 + ys*xe - ys*windowX2)/(xe-xs);
        xe = windowX2;
    }

    if (ye > windowY1){ //down
        xe = (-1*ys*xe + ye*xs + windowY1*xe - windowY1*xs)/(ye-ys);
        ye = windowY1;
    }

    if (xe < windowX1){ //left
        ye = (-1*ye*xs + ye*windowX1 + ys*xe - ys*windowX1)/(xe-xs);
        xe = windowX1;
    }
    drawLine(qp, xs, ys, xe, ye, pen);

}

void MainWindow::lineRectangleClippingVariable(QPainter *qp, QPoint p0, QPoint p1, QPoint p2, QPoint p3, QPen pen)
{
    int windowX1 = p0.x();
    int windowY1 = p0.y();
    int windowX2 = p1.x();
    int windowY2 = p1.y();

    bool swaped = false;
    if (windowX1 > windowX2){
        swap(windowX1, windowX2);
        swap(windowY1, windowY2);
        swaped = 1;
    }
    if (windowY1 < windowY2) swap (windowY1, windowY2);

    int xs = p2.x();
    int ys = p2.y();
    int xe = p3.x();
    int ye = p3.y();

    drawLine(qp, windowX1, windowY2, windowX2, windowY2, pen);
    drawLine(qp, windowX1, windowY2, windowX1, windowY1, pen);
    drawLine(qp, windowX1, windowY1, windowX2, windowY1, pen);
    drawLine(qp, windowX2, windowY2, windowX2, windowY1, pen);

    //xs and ys
    if (ys < windowY2){ //top
        xs = (ys*xe - ye*xs - windowY2*xe + windowY2*xs)/(ys-ye);
        ys = windowY2;
    }
    if (xs > windowX2){ //right
        ys = (ye*xs - ye*windowX2 - ys*xe + ys*windowX2)/(xs-xe);
        xs = windowX2;
    }

    if (ys > windowY1){ //down
        xs = (ys*xe - ye*xs - windowY1*xe + windowY1*xs)/(ys-ye);
        ys = windowY1;
    }

    if (xs < windowX1){ //left
        ys = (ye*xs - ye*windowX1 - ys*xe + ys*windowX1)/(xs-xe);
        xs = windowX1;
    }

    //xe ye
    if (ye < windowY2){ //top
        xe = (-1*ys*xe + ye*xs + windowY2*xe - windowY2*xs)/(ye-ys);
        ye = windowY2;
    }
    if (xe > windowX2){ //right
        ye = (-1*ye*xs + ye*windowX2 + ys*xe - ys*windowX2)/(xe-xs);
        xe = windowX2;
    }

    if (ye > windowY1){ //down
        xe = (-1*ys*xe + ye*xs + windowY1*xe - windowY1*xs)/(ye-ys);
        ye = windowY1;
    }

    if (xe < windowX1){ //left
        ye = (-1*ye*xs + ye*windowX1 + ys*xe - ys*windowX1)/(xe-xs);
        xe = windowX1;
    }
    drawLine(qp, xs, ys, xe, ye, pen);
}


void MainWindow::pointCircleClipping(QPainter *qp, int x, int y, QPen pen)
{
        int windowXC = 600;
        int windowYC = 300;
        drawPolarCircle(qp, 100, windowXC, windowYC, pen);

        pen.setWidth(4);
        qp->setPen(pen);

        if ((x - windowXC) * (x - windowXC) + (y - windowYC) * (y - windowYC) <= 10000)
            qp->drawPoint(x, y);
}

void MainWindow::lineCircleClipping(QPainter *qp, int xs, int ys, int xe, int ye, QPen pen)
{

    qp->setPen(pen);

    int windowXC = 600;
    int windowYC = 300;
    int r = 100;
    drawPolarCircle(qp, 100, windowXC, windowYC, pen);

    long long dx = xe - xs;
    long long dy = ye - ys;
    long long k = (dx*ys - dy*xs)/dx; //y = mx + k
    long long a, b, c, d, x1, x2, y1, y2;

    a = dx*dx + dy*dy;
    b = 2*dx*dy*k - 2*dx*dx*windowXC - 2*windowYC*dx*dy;
    c = dx*dx*(windowXC*windowXC - 2*windowYC*k + windowYC*windowYC - r*r + k*k);
    d = b*b - 4*a*c;


    if (d < 0) x1 = -100000, x2 = -100000;
    else if (d == 0) x1 = (b*-1)/(2*a), x2 = -100000;
    else x1 = (-1*b - sqrt(d))/(2*a*1.0), x2 = (-1*b + sqrt(d))/(2*a*1.0);

    if (x1 == -100000 && x2 == -100000) return;

    y1 = dy*x1 + dx*k;
    y2 = dy*x2 + dx*k;

    y1/=dx;
    y2/=dx;

    if(x2 == -100000) qp->drawPoint(x1, y1);

    else{

        if (xs > xe){
            swap(xs, xe);
            swap(ys, ye);
        }
        if (x1 > x2){
            swap(x1, x2);
            swap(y1, y2);
        }

        if ((xs - windowXC) * (xs - windowXC) + (ys - windowYC) * (ys - windowYC) <= r*r)
            x1 = xs, y1 = ys;
        if ((xe - windowXC) * (xe - windowXC) + (ye - windowYC) * (ye - windowYC) <= r*r)
            x2 = xe, y2 = ye;
        //  drawLine(qp, x1, y1, x2, y2, pen);
        qp->drawLine(x1, y1, x2, y2);
    }

}


void MainWindow::on_circle_currentIndexChanged(int index)
{
    if (index == 1){ //polar
        nPoints = 1;
        chosen = 0;
    } else if (index == 4){ //cartesian
        nPoints = 1;
        chosen = 3;
    }else if (index == 3){ //midpoint
        nPoints = 1;
        chosen = 2;
    }else if (index == 2){ //iterative polar
        nPoints = 1;
        chosen = 1;
    }
}

void MainWindow::on_line_currentIndexChanged(int index)
{
    if (index == 1){//DDA
        nPoints = 2;
        chosen = 4;
    }
    else if (index == 2){ //midpoint
        nPoints = 2;
        chosen = 5;
    } else if (index == 3){ //parametric
        nPoints = 2;
        chosen = 6;
    }
}

void MainWindow::on_curve_currentIndexChanged(int index)
{
    if (index == 1){ //1st degree
        nPoints = 2;
        chosen = 7;
    }else if (index == 2){ //2nd degree
        nPoints = 3;
        chosen = 8;
    }else if (index == 4){ //Bezier
        nPoints = 4;
        chosen = 9;
    }else if (index == 3){ //Hermite
        nPoints = 2;
        chosen = 10;
    } else if (index == 5){
        nPoints = 6;
        chosen = 11;
    }
}

void MainWindow::on_filling_currentIndexChanged(int index)
{
    if (index == 1){ //convex fill
        nPoints = 5;
        chosen = 12;
    } else if (index == 2){ //flood fill
        nPoints = 1;
        chosen = 13;
    }
}

void MainWindow::on_rectangleClipping_currentIndexChanged(int index)
{
    if (index == 1){
     //   drawRectangleWindow();
        nPoints = 1;
        chosen = 14;
    } else if (index == 2){
        nPoints = 2;
        chosen = 15;
    } else if (index == 3){
        nPoints = 4;
        chosen = 18;
    }
}

void MainWindow::on_circleClipping_currentIndexChanged(int index)
{
    if (index == 1){
        nPoints = 1;
        chosen = 16;
    } else if (index == 2){
        nPoints = 2;
        chosen = 17;
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 1){
        write("/home/maryam/Qt projects/test1/data.txt");
    } else if (index == 2){
        read("/home/maryam/Qt projects/test1/data.txt");
        update();
    }
}

void MainWindow::on_backgroundColor_currentIndexChanged(int index)
{

    if (index == 1){
        this->setStyleSheet("background-color: rgb(255, 204, 204);");
    } else if (index == 2)
        this->setStyleSheet("background-color: rgb(204, 255, 204);");
    else if (index == 3)
        this->setStyleSheet("background-color:");
    update();

}
