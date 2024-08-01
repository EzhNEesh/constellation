#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new QWidget();
    centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    centralWidget->setMaximumSize(450, 150);
    mainLayout = new QGridLayout(centralWidget);

    filePathLabel = new QLabel("Enter the path to the markers file");
    filePathLabel->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    mainLayout->addWidget(filePathLabel, 0, 0);

    filePathInput = new QLineEdit();
    filePathInput->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
    mainLayout->addWidget(filePathInput, 0, 1);

    drawGraphButton = new QPushButton("Draw");
    drawGraphButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(drawGraphButton, 1, 0);

    setCentralWidget(centralWidget);
    connect(drawGraphButton, &QPushButton::released, this, &MainWindow::openGraphWindow);
}

void MainWindow::openGraphWindow() {
    ConstellationWindow *constellationWindow = new ConstellationWindow(this->filePathInput->text(), this);
    constellationWindow->setAttribute(Qt::WA_DeleteOnClose);
    constellationWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
