#include "udpclient.hpp"
#include <iostream>
#include "C:\msys64\mingw64\include\opus\opus.h"

UdpClient::UdpClient(const QHostAddress& address, quint16 port, QObject* parent)
    : QObject(parent), _address(address), _port(port) {
    QObject::connect(&_socket, &QUdpSocket::readyRead, this, &UdpClient::onReadyRead);
}

void UdpClient::sendMessage() {
    std::vector<unsigned char> encodedData = _audio.EnregistreAndEncode(std::vector<unsigned char>(_audio.SIZEBUFF * _audio.CHANNEL));
    QByteArray message(reinterpret_cast<const char *>(encodedData.data()), static_cast<int>(encodedData.size()));
    _socket.writeDatagram(message, _address, _port);
}

void UdpClient::listen(int port) {
    _socket.bind(QHostAddress::Any, port, QUdpSocket::ShareAddress);
}

void UdpClient::onReadyRead() {
    while (_socket.hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(_socket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _socket.readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        std::vector<unsigned char> encodedData(buffer.begin(), buffer.end());
        _audio.DecodeAndPlay(encodedData);
    }
}
