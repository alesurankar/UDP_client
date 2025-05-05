#define _WIN32_WINNT 0x0601
#include <boost/asio.hpp>
#include <iostream>


class UdpClient 
{
public:
    UdpClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
        : 
        udp_socket_(io_context, boost::asio::ip::udp::v4()) 
    {
        udp_endpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(host), port);
    }

    void sendMessage(const std::string& message) 
    {
        udp_socket_.send_to(boost::asio::buffer(message), udp_endpoint_);
    }

    void receiveMessage() 
    {
        char buffer[1024];
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t len = udp_socket_.receive_from(boost::asio::buffer(buffer), sender_endpoint);
        std::cout << "Received: " << std::string(buffer, len) << std::endl;
    }

private:
    boost::asio::ip::udp::socket udp_socket_;
    boost::asio::ip::udp::endpoint udp_endpoint_;
};

int main() 
{
    boost::asio::io_context io_context;
    UdpClient client(io_context, "127.0.0.1", 1234);
    client.sendMessage("Hello, server!");
    client.receiveMessage();
    return 0;
}


//#define _WIN32_WINNT 0x0601
//#include <boost/asio.hpp>
//#include <boost/asio/ip/address_v4.hpp>
//#include <iostream>
//#include <array>
//#include <string>
//
//class UdpClient
//{
//public:
//    UdpClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
//        :
//        udp_socket_(io_context, boost::asio::ip::udp::v4()),
//        udp_endpoint_(boost::asio::ip::make_address(host), port)
//    {
//        startReceive();
//    }
//
//    void sendMessage(const std::string& message)
//    {
//        udp_socket_.async_send_to
//        (
//            boost::asio::buffer(message), udp_endpoint_,
//            [](const boost::system::error_code& ec, std::size_t bytes_sent)
//            {
//                if (!ec)
//                    std::cout << "Sent " << bytes_sent << " bytes\n";
//                else
//                    std::cerr << "Send failed: " << ec.message() << "\n";
//            });
//    }
//
//    void startReceive()
//    {
//        udp_socket_.async_receive_from
//        (
//            boost::asio::buffer(recv_buffer_), sender_endpoint_,
//            [this](const boost::system::error_code& ec, std::size_t bytes_recvd)
//            {
//                if (!ec)
//                {
//                    // Check for overflow
//                    if (bytes_recvd > recv_buffer_.size()) {
//                        std::cerr << "Warning: Message exceeds buffer size!" << std::endl;
//                    }
//                    std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_recvd) << "\n";
//                    startReceive(); // Loop to keep listening
//                }
//                else
//                {
//                    std::cerr << "Receive failed: " << ec.message() << "\n";
//                    // Optionally, handle error recovery here, like retrying
//                }
//            });
//    }
//
//private:
//    boost::asio::ip::udp::socket udp_socket_;
//    boost::asio::ip::udp::endpoint udp_endpoint_;
//    boost::asio::ip::udp::endpoint sender_endpoint_;
//    std::array<char, 1024> recv_buffer_;
//};
//
//int main()
//{
//    try
//    {
//        boost::asio::io_context io_context;
//        UdpClient client(io_context, "127.0.0.1", 1234);
//
//        client.sendMessage("Hello, server!");
//
//        io_context.run(); // Needed to process async handlers
//    }
//    catch (const std::exception& e)
//    {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return 0;
//}
//
