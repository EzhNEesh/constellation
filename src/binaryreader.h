#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QObject>
#include <QPoint>
#include <string>

class BinaryReader : public QObject
{
    Q_OBJECT

public:
    explicit BinaryReader(QObject *parent);
    void readBinary(const std::string &filePath);
    ~BinaryReader();

signals:
    void paintPoints(const std::vector<QPoint> &newPoints);
};

#endif // BINARYREADER_H
