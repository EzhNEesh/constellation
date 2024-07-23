#include "constellationwindow.h"

ConstellationWindow::ConstellationWindow(QString xmlFilePath, QWidget *parent) : QDialog(parent)
{
    this->setMinimumSize(300, 300);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    ConstellationWidget* constellationWidget = new ConstellationWidget(xmlFilePath, this);
    BinaryReader* bReader = new BinaryReader(this);

    QObject::connect(bReader, &BinaryReader::paintPoints,
                     constellationWidget, &ConstellationWidget::updatePoints);

    mainLayout->addWidget(constellationWidget);
    std::thread readerThread([bReader](){ bReader->readBinary("iq_qam32.bin"); });
    readerThread.detach();
}

ConstellationWindow::~ConstellationWindow()
{
    // delete ui;
}
