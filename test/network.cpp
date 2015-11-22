#include <iostream>
#include <fstream>
#include <sstream>
#include "network.h"

std::string parse_stream(std::istream &stream)
{
        std::string line;
        while(std::getline(stream, line))
        {
                if (!line.length())
                {
                        std::ostringstream ss;
                        ss << stream.rdbuf();
                        return ss.str();
                }
        }
        return std::string();
}

//void handler(const boost::system::error_code &ec)  {
//  std::cout << "5 s." << std::endl;
//}

std::string NetworkLayer::fetch_url(const std::string &url)
{
    //boost::asio::io_service io_service;

    std::ifstream file(url.c_str(), std::ifstream::in);

    return parse_stream(file);
}
