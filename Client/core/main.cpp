#include "client.hpp"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Client client;
    client.Connect("127.0.0.1", 1234);
    client.Start();
    client.Stop();
    return app.exec();
}