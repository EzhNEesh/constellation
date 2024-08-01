#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <string>

class BinaryReader : public QObject
{
    Q_OBJECT

public:
    explicit BinaryReader(QObject *parent);
    void readBinary(const QString &filePath);
    ~BinaryReader();

signals:
    void paintPoints(const std::vector<QPoint> &newPoints);
    void fileNotOpen(const QString &errorMessage);
};

#endif // BINARYREADER_H
