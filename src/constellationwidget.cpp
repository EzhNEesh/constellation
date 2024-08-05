#include <QPainter>
#include <QFile>
#include <QRegularExpression>
#include <QXmlStreamReader>

#include "constellationwidget.h"

ConstellationWidget::ConstellationWidget(const QString &_xmlFilePath, QWidget *parent = nullptr) : QWidget(parent){
    xmlFilePath = _xmlFilePath;
}

void ConstellationWidget::readXml() {
    QFile file(xmlFilePath);
    static QRegularExpression isFloat(QRegularExpression::anchoredPattern("-?\\d+\\.?\\d*"));

    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader sr(&file);
        do {
            sr.readNext();
            if (!sr.isEndElement() && sr.name().toString() == "Point") {
                QStringView Xstring = sr.attributes().value('X');
                QStringView Ystring = sr.attributes().value('Y');
                if (!isFloat.match(Xstring).hasMatch() || !isFloat.match(Ystring).hasMatch()) {
                    emit xmlFileHasError("Not float point data in xml");
                    break;
                }
                float X = Xstring.toFloat();
                float Y = Ystring.toFloat();
                markers.push_back(QPoint(X, Y));
            }
        } while (!sr.atEnd());
        if (sr.hasError()) {
            emit xmlFileHasError("Invalid data in xml file");
        }
        file.close();
    } else {
        emit xmlFileNotExist("Xml file " + xmlFilePath + " does not exist");
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
