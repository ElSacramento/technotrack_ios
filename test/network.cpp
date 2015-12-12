#include <iostream>
#include <fstream>
#include <sstream>
#include "network.h"
#include "cpprest/http_client.h"
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

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

std::string NetworkLayer::fetch_url(const std::string &url)
{
    // Create http_client to send the request.
    http_client client(U(url));
    std::string result = "";

    auto request = client.request(methods::GET);
    //request.set_body();
    auto resp = request.then([=, &result](http_response response) mutable
    {
        concurrency::streams::container_buffer<std::string> bufferStream;
        auto bytesRead = response.body().read_to_end(bufferStream).get();
        //printf("Received response status code:%u\n", response.status_code());
        //printf("Received response:%s\n", bufferStream.collection().c_str()); // string with json
        //printf("Received bytesRead:%lu\n", bytesRead); //number of read bytes
        result = bufferStream.collection();
    });
    resp.wait();
    return result;

  //  std::ifstream file(url.c_str(), std::ifstream::in);

//    return parse_stream(file);
}

