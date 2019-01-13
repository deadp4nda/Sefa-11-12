#ifndef MONGOCONNECTION_H
#define MONGOCONNECTION_H

#include <QTcpSocket>
#include "mangolib_global.h"
#include <thread>
#include <memory>
#include <QDataStream>

namespace Mango{
class MangoConnection : public QTcpSocket // socket, das senden und empfangen von Anweisungen möglich macht. (toyota)
{
    Q_OBJECT
public:
    MangoConnection(const QHostAddress &toIp,quint16 port = 0, MngThManager *parent = nullptr); // Konstruktor auf der verbindenden Seite(kriegt adresse+port+pointer zum Manager, der super ist.)
    MangoConnection(qintptr handle,MngThManager *parent = nullptr); // auf der passiven Seite, kriegt socket-handle
    bool send(const SafeByteArray); // versenden von Anweisung
signals:
    void newInput(const SafeByteArray); // anweisung kommt rein
private slots:
    void handleReadyRead(); // wird vom System aufgerufen,wenn anweisung reinkommt.
private:
    QHostAddress foreignHost; // adresse vom anderen Computer
    quint16 atPort = 0;         // an port xyz
    QDataStream stream;         // EIN DATENSTROM! eigentlich  nicht mehr gebraucht, aber ein jeder mag legacy-code
    MngThManager *parentManager;// der parentmanager für eventuelle direkte Callbacks
};
}
#endif // MONGOCONNECTION_H
