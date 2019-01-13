#ifndef MNGFILESERVER_H
#define MNGFILESERVER_H

#include <QTcpServer>

namespace Mango{

class MngRecvFileSocket;

class MngFileServer : public QTcpServer // Das kann verbindungen entgegennehmen
{
    Q_OBJECT
public:
    MngFileServer(quint16 port, const QString &stdDir, QObject *parent);     // verbindungen auf port xyz
protected:
    void incomingConnection(qintptr handle); // überschriebene Funktion, die bei hereinkommender Verbindung aufgerufen wird
signals:
    void newConnection(MngRecvFileSocket *); // es gibt eine neue verbindung
private:
    QString stdDirectory;
    quint16 port = 0;
};
}
#endif // MNGFILESERVER_H
