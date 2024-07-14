#include "client.hpp"
#include <QTimer>
#include <future>


Client::Client()
    : socket_(io_context_), value(0)
{
    // widow.init();
}

int start(int port_listen, int port_send) {
    int argc = 1;
    QCoreApplication app(argc, {});

    std::string ip_address = "127.0.0.6";

    QHostAddress address(QString::fromStdString(ip_address));
    quint16 qport = static_cast<quint16>(port_listen);

    UdpClient client(address, qport);

    client.listen(port_send);
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        client.sendMessage();
    });
    timer.start(1);

    return app.exec();
}

void Client::identification()
{
    std::string message = Read();
    std::cout << message << std::endl;
    WriteHandler();
}

void Client::Connect(std::string address, int port)
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(address), port);
    socket_.connect(endpoint);
    std::cout << "Connected to server!" << std::endl;
    identification();
}

void Client::Start()
{
    while(1) {
        WriteHandler();
        ReadHandler();
    }
}

void Client::Stop()
{
    io_context_.stop();
}

std::string Client::unserialize(const std::string& message) {
    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);
    std::string myString;
    archive >> myString;
    return myString;
}

std::string Client::serialize(std::string message) {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << message;
    return archive_stream.str();
}

void sendMessagePeriodically(UdpClient& client) {
    std::cout << "Sending message..." << std::endl;
    client.sendMessage();
}

void Client::UdpHandle(int port_listen, int port_send)
{
    start(port_listen, port_send);
}

void Client::ReadHandler()
{
    std::string string = Read();
    std::cout << "Received message: " << string << std::endl;
    if (string == "OK") {
        std::string alone = Read();
        std::istringstream iss(alone);
        std::string port_listen, port_send;
        iss >> port_listen >> port_send;
        std::cout << "port_listen : " << port_listen << std::endl;
        std::cout << "port_send : " << port_send << std::endl;

        int int_port_listen = std::stoi(port_listen);
        int int_port_send = std::stoi(port_send);

        std::cout << "i have to liste on port : " << int_port_listen << std::endl;
        std::cout << "i have to send on port : " << int_port_send << std::endl;
        UdpHandle(int_port_listen, int_port_send);
    }
}

std::string Client::Read()
{
    boost::system::error_code error;
    boost::asio::streambuf buff;
    boost::asio::read_until(socket_, buff, '\n', error);
    if (error) {
        std::cerr << "Error reading message: " << error.message() << std::endl;
        return "";
    }
    std::string my_str = boost::asio::buffer_cast<const char*>(buff.data());
    my_str.erase(std::remove(my_str.begin(), my_str.end(), '\n'), my_str.end());
    std::string un_str = unserialize(my_str);
    un_str.pop_back();
    return un_str;
}

void Client::WriteHandler()
{
    std::string message;
    std::getline(std::cin, message);
    message += "\n";
    std::string serialized_message = serialize(message);
    serialized_message += "\n";
    boost::asio::write(socket_, boost::asio::buffer(serialized_message));
}