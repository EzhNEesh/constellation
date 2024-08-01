#include <fstream>
#include <inttypes.h>
#include <QDebug>
#include "binaryreader.h"

BinaryReader::BinaryReader(QObject *parent) : QObject(parent) {}

void BinaryReader::readBinary(const QString &filePath) {
    std::ifstream file(filePath.toStdString(), std::ios::binary);

    if (file.is_open()) {
        __INT16_TYPE__ x;
        __INT16_TYPE__ y;
        std::vector<QPoint> points;

        while (file.read((char*)&x, sizeof(__INT16_TYPE__)) && file.read((char*)&y, sizeof(__INT16_TYPE__))) {
            points.push_back(QPoint(x / 100, y / 100));
            if (points.size() == 1000) {
                emit paintPoints(points);
                points.clear();
            }
        }
        if (file.bad()) {
            file.close();
            emit invalidData("Invalid data in binary file");
        }

        if (points.size() > 0) {
            emit paintPoints(points);
        }
    } else {
        emit fileNotOpen("Could not open binary file " + filePath);
    }
}

BinaryReader::~BinaryReader() {}
