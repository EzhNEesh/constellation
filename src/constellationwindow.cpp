#include <thread>
#include <QVBoxLayout>
#include <QMessageBox>

#include "constellationwindow.h"

ConstellationWindow::ConstellationWindow(QWidget *parent,
                                         const QString &xmlFilePath,
                                         const QString &binaryPath)
    : QDialog(parent)
{
    setMinimumSize(300, 300);
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    constellationWidget = new ConstellationWidget(xmlFilePath, this);
    bReader = new BinaryReader(this);

    QObject::connect(bReader, &BinaryReader::paintPoints,
                     constellationWidget, &ConstellationWidget::updatePoints);

    QObject::connect(bReader, &BinaryReader::fileNotOpen,
                     this, &ConstellationWindow::showErrorMessageBox);

    QObject::connect(bReader, &BinaryReader::invalidData,
                     this, &ConstellationWindow::showErrorMessageBox);

    QObject::connect(constellationWidget, &ConstellationWidget::xmlFileNotExist,
                     this, &ConstellationWindow::showErrorMessageBox);

    QObject::connect(constellationWidget, &ConstellationWidget::xmlFileHasError,
                     this, &ConstellationWindow::showErrorMessageBox);

    constellationWidget->readXml();
    mainLayout->addWidget(constellationWidget);
    std::thread readerThread([this, binaryPath](){ bReader->readBinary(binaryPath); });
    readerThread.detach();
}

void ConstellationWindow::showErrorMessageBox(const QString &errorMessage) {
    QMessageBox *errorMessageBox = new QMessageBox();
    errorMessageBox->setText(errorMessage);
    errorMessageBox->setAttribute(Qt::WA_DeleteOnClose);
    errorMessageBox->show();
}

ConstellationWindow::~ConstellationWindow() {}
