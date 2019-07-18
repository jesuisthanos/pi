#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class LED;
}

class LED : public QWidget
{
    Q_OBJECT

public:
    explicit LED(QWidget *parent = nullptr);
    ~LED();

private slots:
    void newConnection();
    void receivedData();
    void disconnectClient();

private:
    Ui::LED *ui;
    QTcpServer * m_pi;
    QList<QTcpSocket *> clients;
};

#endif // LED_H
