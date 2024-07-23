#ifndef CONSTELLATIONWINDOW_H
#define CONSTELLATIONWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>

#include "constellationwidget.h"
#include "binaryreader.h"

class ConstellationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConstellationWindow(QString xmlFilePath="32.xml", QWidget *parent = nullptr);
    ~ConstellationWindow();
};

#endif // CONSTELLATIONWINDOW_H
