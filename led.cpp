#include "led.h"
#include "ui_led.h"

LED::LED(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LED)
{
    ui->setupUi(this);

    QLabel * serverState = new QLabel;

    m_pi = new QTcpServer(this);

    if (!m_pi->listen(QHostAddress::Any, 14396)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 50885
    {
        // Si le serveur n'a pas été démarré correctement
        serverState->setText(QObject::tr("Le serveur n'a pas pu être démarré. Raison :<br />") + m_pi->errorString());
    }
    else {
        // Si le serveur a été démarré correctement
        serverState->setText(QObject::tr("Le serveur a été démarré sur le port <strong>") + QString::number(m_pi->serverPort()) + QObject::tr("<strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(m_pi, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }
}

LED::~LED()
{
    delete ui;
}

void LED::newConnection()
{
    QTcpSocket *const newSocket = m_pi->nextPendingConnection();
    clients.push_back(newSocket);
    QString addr = newSocket->peerAddress().toString();

    connect(newSocket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(newSocket, SIGNAL(disconnected()), this, SLOT(disconnectClient()));
}

void LED::receivedData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(socket);
    quint16 code;

    if (socket->bytesAvailable() < static_cast<int>(sizeof(quint16)))  // On n'a pas reçu la taille du  message en entier
        return;

    in >> code;  // Si on a reçu la taille du message en entier, on la récupère
    if (code == 1)  // on
    {
        ui->led->setText("BẬT");
    }
    else {  // code = 0 = off
        ui->led->setText("TẮT");
    }
}

void LED::disconnectClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr)  // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
    {
        return;
    }

    clients.removeOne(socket);

    socket->deleteLater();
}
