#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QObject>
#include <QPoint>
#include <string>

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
