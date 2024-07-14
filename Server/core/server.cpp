#include "server.hpp"

Server::Server(boost::asio::io_service& io_service, unsigned short port) :
    io_service_(io_service),
    acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    start_accept();
}

std::string Server::unserialize(const std::string& message) {
    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);
    std::string myString;
    archive >> myString;
    return myString;
}

std::string Server::serialize(std::string message) {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << message;
    return archive_stream.str();
}

void Server::send_string(std::string message, std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    boost::system::error_code error;
    std::string serialized_message = serialize(message);
    serialized_message += "\n";
    boost::asio::write(*socket, boost::asio::buffer(serialized_message), error);
    if (error) {
        std::cerr << "Error sending message: " << error.message() << std::endl;
    }
}

std::string Server::receive_string(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    boost::asio::streambuf message_buffer;
    boost::system::error_code error;
    boost::asio::read_until(*socket, message_buffer, '\n', error);
    if (error) {
        std::cerr << "Error reading message: " << error.message() << std::endl;
    }
    std::string message = boost::asio::buffer_cast<const char*>(message_buffer.data());
    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
    std::string un_str = unserialize(message);
    un_str.pop_back();
    return un_str;
}

void Server::start_accept() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_service_);
    acceptor_.async_accept(*socket, std::bind(&Server::handle_accept, this, socket, std::placeholders::_1));
    std::cout << "Waiting for incoming connections..." << std::endl;
}

void Server::handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code& error) {
    if (!error) {
        std::cout << "New connection from " << socket->remote_endpoint().address().to_string() << std::endl;
        std::thread{&Server::handle_client, this, socket}.detach();
        connected_sockets_.push_back(socket);
    }
    else {
        std::cerr << "Error accepting connection: " << error.message() << std::endl;
    }

    start_accept();
}

void Server::handle_client(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    send_request_identification(socket);
    while (true) {
        boost::system::error_code error;
        std::string message = receive_string(socket);
        std::cout << "Message from " << client_identifiers_[socket].first << " = " << std::endl << message << std::endl;
        if (message == "list") {
            std::string list = "List of connected clients:\n";
            for (auto& client : client_identifiers_) {
                list += client.second.first + '\n';
            }
            send_string(list, socket);
        }
        else if (message == "connect") {
            bool pseudo_choice = false;
            send_string("Choose a user to connect:\n", socket);
            while(pseudo_choice != true) {
                std::string str_pseudo = receive_string(socket);
                for (auto& client : client_identifiers_) {
                    if (client.second.first == str_pseudo) {
                        send_string("OK\n", socket);
                        std::string final_message = std::to_string(client.second.second);
                        if (client_identifiers_.size() == 1) {
                            final_message = final_message + " " + std::to_string(client_identifiers_[socket].second+1) + "\n";
                        } else {
                            final_message = final_message + " " + std::to_string(client_identifiers_[socket].second) + "\n";
                        }
                        connected += 1;
                        std::cout << "final_message = " << final_message << std::endl;
                        send_string(final_message, socket);
                        std::cout << "is send" << std::endl;
                        pseudo_choice = true;
                        break;
                    }
                }
                if (pseudo_choice == false)
                    send_string("Choose a valid user to connect\n", socket);
            }
        }
        else {
            send_string("Unknown command\n", socket);
        } 
    }
}

void Server::send_request_identification(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    send_string("Please enter your identifier:\n", socket);
    std::string response = receive_string(socket);
    store_client_identifier(socket, response);

}

void Server::store_client_identifier(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const std::string& identifier) {
    client_identifiers_[socket].first = identifier;
    client_identifiers_[socket].second = (rand () % 8000 + 1000) + plus_rand;
    std::cout << "Size of client_identifiers_ = " << client_identifiers_.size() << std::endl;
    plus_rand += 1;
    std::cout << "Connected clients:" << std::endl;
    for (auto& client : client_identifiers_) {
        std::cout << client.second.first << std::endl;
        std::cout << client.second.second << std::endl;
    }
}