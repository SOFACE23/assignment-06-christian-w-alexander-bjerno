//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  // try the block of code
  try
  {
    // Boost creats io context.
    boost::asio::io_context io_context;

    // creats a pointer, to the socket with the acceptet data.
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    // when true creats a socket with io context and then
    // the acceptor accepts the socket.
    while (true)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      // massage, about the usage.
      std::string message = make_daytime_string();

      // if its not an error it will return the result of
      // the socket and the message that has been enteret.
      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  // if some mistakes/bugs, has come through in the end.
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}