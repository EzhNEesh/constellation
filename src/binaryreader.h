#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QObject>
#include <QWidget>
#include <QObject>
#include <QPoint>
#include <string>
#include <fstream>
#include <inttypes.h>

// #include <chrono>
// #include <thread>

class BinaryReader : public QObject
{
    Q_OBJECT

public:
    explicit BinaryReader(QObject *);
    void readBinary(const std::string &);
    ~BinaryReader();

signals:
    void paintPoints(const std::vector<QPoint> &);
};

#endif // BINARYREADER_H
