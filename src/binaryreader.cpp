#include <fstream>
#include <inttypes.h>

#include "binaryreader.h"

BinaryReader::BinaryReader(QObject *parent) : QObject(parent) {}

void BinaryReader::readBinary(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (file.is_open()) {
        __INT16_TYPE__ x;
        __INT16_TYPE__ y;
        std::vector<QPoint> points;
        while (file.read((char*)&x, sizeof(__INT16_TYPE__)) && file.read((char*)&y, sizeof(__INT16_TYPE__))) {
            points.push_back(QPoint(x / 100, y / 100));
            if (points.size() == 1000) {
                emit paintPoints(points);
                points.clear();
                // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            }
        }
        if (points.size() > 0) {
            emit paintPoints(points);
        }
    }
}

BinaryReader::~BinaryReader() {}
