#include <boost/asio.hpp>
// declare boost archive

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "server.hpp"

int main(int argc, char* argv[]) {
    unsigned short port = 1234;
    
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }
    boost::asio::io_service io_service;

    Server server(io_service, port);

    io_service.run();

    return 0;
}