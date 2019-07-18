#include "dk.h"
#include "ui_dk.h"

dk::dk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dk)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(ui->ledSwitch, SIGNAL(clicked()), this, SLOT(switchPressed()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnecteds()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

}

dk::~dk()
{
    delete ui;
}

void dk::receivedData()
{

}

void dk::connected()
{

}

void dk::disconnected()
{

}

void dk::socketError(QAbstractSocket::SocketError)
{

}

void dk::switchPressed()
{
    if (ui->ledSwitch->text() == "BẬT")
    {
        ui->ledSwitch->setText("TẮT");
    }
    else {
        ui->ledSwitch->setText("BẬT");
    }
}
