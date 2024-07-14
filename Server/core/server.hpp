#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <map>

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


class Server {
public:
    Server(boost::asio::io_service& io_service, unsigned short port);
    void start_accept();
    void handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code& error);
    void send_request_identification(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void store_client_identifier(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& identifier);
    void handle_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void send_string(std::string message, std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    std::string receive_string(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    std::string unserialize(const std::string& message);
    std::string serialize(std::string message);
    int plus_rand = 0;
    int connected = 0;
    int port = 1045;
    // define a tab of int 
    
private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::map<std::shared_ptr<boost::asio::ip::tcp::socket>, std::pair<std::string, int>> client_identifiers_;
    std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> connected_sockets_;
};

#endif // SERVER_HPP