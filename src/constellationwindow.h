#ifndef CONSTELLATIONWINDOW_H
#define CONSTELLATIONWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QString>

#include "constellationwidget.h"
#include "binaryreader.h"

class ConstellationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConstellationWindow(QWidget *parent = nullptr,
                                 const QString &xmlFilePath="32.xml",
                                 const QString &binaryPath="iq_qam32.bin");
    ~ConstellationWindow();

private slots:
    void showErrorMessageBox(const QString &errorMessage);
};

#endif // CONSTELLATIONWINDOW_H
