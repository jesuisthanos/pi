#ifndef DK_H
#define DK_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class dk;
}

class dk : public QWidget
{
    Q_OBJECT

public:
    explicit dk(QWidget *parent = nullptr);
    ~dk();

private slots:
    void receivedData();
    void connected();
    void disconnected();
    void socketError(QAbstractSocket::SocketError);
    void switchPressed();


private:
    Ui::dk *ui;
    QTcpSocket *socket;
};

#endif // DK_H
