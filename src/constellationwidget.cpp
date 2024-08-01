#include <QPainter>
#include <QFile>
#include <QXmlStreamReader>

#include "constellationwidget.h"

ConstellationWidget::ConstellationWidget(const QString &xmlFilePath, QWidget *parent = nullptr) : QWidget(parent){
    QFile file(xmlFilePath);
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader sr(&file);
        do {
            sr.readNext();
            if (!sr.isEndElement() && sr.name().toString() == "Point") {
                float X = sr.attributes().value('X').toFloat();
                float Y = sr.attributes().value('Y').toFloat();
                markers.push_back(QPoint(X, Y));
            }
        } while (!sr.atEnd());
        if (sr.hasError()) {
            qDebug() << "Error:" << sr.errorString();
        }
        file.close();
    }
}

void ConstellationWidget::updatePoints(const std::vector<QPoint> &newPoints) {
    for (auto &newStar : newPoints) {
        stars.push_back(newStar);
        if (stars.size() > 16000) {
            stars.pop_front();
        }
    }
    update();
}

void ConstellationWidget::paintEvent(QPaintEvent *event) {
    int cur_height = height();
    int cur_width = width();
    QWidget* parentNode = parentWidget();

    resize(parentNode->width(), parentNode->height());

    QPainter painter;
    painter.begin(this);
    for (auto& star : stars) {
        painter.drawPoint((star.x() / 300. + 0.5) * float(cur_width), (star.y() / 300. + 0.5) * float(cur_height));
    }

    painter.setPen("red");
    for (auto& marker : markers) {
        painter.drawLine((marker.x() / 300. + 0.5) * float(cur_width) + 1,
                         (marker.y() / 300. + 0.5) * float(cur_height) + 1,
                         (marker.x() / 300. + 0.5) * float(cur_width) - 1,
                         (marker.y() / 300. + 0.5) * float(cur_height) - 1);
        painter.drawLine((marker.x() / 300. + 0.5) * float(cur_width) + 1,
                         (marker.y() / 300. + 0.5) * float(cur_height) - 1,
                         (marker.x() / 300. + 0.5) * float(cur_width) - 1,
                         (marker.y() / 300. + 0.5) * float(cur_height) + 1);
    }
    painter.end();
}

ConstellationWidget::~ConstellationWidget() {}
