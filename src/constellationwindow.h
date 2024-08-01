#ifndef CONSTELLATIONWINDOW_H
#define CONSTELLATIONWINDOW_H

#include <QWidget>
#include <QDialog>

#include "constellationwidget.h"
#include "binaryreader.h"

class ConstellationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConstellationWindow(const QString &xmlFilePath="32.xml", QWidget *parent = nullptr);
    ~ConstellationWindow();
};

#endif // CONSTELLATIONWINDOW_H
