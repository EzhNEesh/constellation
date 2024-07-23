#ifndef CONSTELLATIONWIDGET_H
#define CONSTELLATIONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFile>
#include <QtXml>
#include <QApplication>
#include <QString>
#include <deque>

class ConstellationWidget : public QWidget
{
public:
    explicit ConstellationWidget(const QString &, QWidget *);
    // void readMarkers();
    ~ConstellationWidget();

private:
    std::deque<QPoint> stars;
    std::vector<QPoint> markers;
    void paintEvent(QPaintEvent *event);

public slots:
    void updatePoints(const std::vector<QPoint> &newPoints);
};

#endif // CONSTELLATIONWIDGET_H
