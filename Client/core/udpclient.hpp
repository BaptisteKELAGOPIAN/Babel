#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "audio.hpp"
#include <QObject>
#include <QUdpSocket>
#include <QCoreApplication>
#include <QTimer>
#include "C:\msys64\mingw64\include\opus\opus.h"

class UdpClient : public QObject {
    Q_OBJECT

public:
    UdpClient(const QHostAddress& address, quint16 port, QObject* parent = nullptr);
    void sendMessage();
    void listen(int port);
    virtual ~UdpClient(){};

private slots:
    void onReadyRead();

private:
    Audio _audio;
    QUdpSocket _socket;
    QHostAddress _address;
    quint16 _port;
};

#endif // UDPCLIENT_H