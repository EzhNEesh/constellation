#ifndef CONSTELLATIONWIDGET_H
#define CONSTELLATIONWIDGET_H

#include <QWidget>
#include <QString>
#include <deque>

class ConstellationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConstellationWidget(const QString &_xmlFilePath, QWidget *parent);
    void readXml();
    ~ConstellationWidget();

private:
    QString xmlFilePath;
    std::deque<QPoint> stars;
    std::vector<QPoint> markers;
    void paintEvent(QPaintEvent *event);

signals:
    void xmlFileNotExist(const QString &errorMessage);
    void xmlFileHasError(const QString &errorMessage);

public slots:
    void updatePoints(const std::vector<QPoint> &newPoints);
};

#endif // CONSTELLATIONWIDGET_H
