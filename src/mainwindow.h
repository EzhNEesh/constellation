#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>

#include "constellationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QLabel *filePathLabel;
    QLineEdit *filePathInput;
    QPushButton *drawGraphButton;

private slots:
    void openGraphWindow();
};
#endif // MAINWINDOW_H