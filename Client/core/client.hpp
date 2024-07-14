#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include "udpclient.hpp"
#include "qtwindow.hpp"

class MyData {
public:
    int myInt;
    std::string myString;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int = 0) {
        ar & myInt;
        ar & myString;
    }
};

class Client
{
public:
    Client();
    void Connect(std::string address, int port);
    void Start();
    void Stop();
    void identification();
    void UdpHandle(int port_listen, int port_send);
    std::string unserialize(const std::string& message);
    void CheckReadyConnectAndRunUdpHandle(int port);
    std::atomic<bool> readyconnect{false}; 
    std::string serialize(std::string message);
    std::string Read();
    int port_listen;
    int port_send;
    Qtwindow widow;

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    int value;

    void ReadHandler();
    void WriteHandler();
};