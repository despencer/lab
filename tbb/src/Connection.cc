#include <iostream>
#include "Connection.hh"

using namespace gazebo;
using namespace transport;

Connection::Connection()
{
 std::cout << "Connection::Connection" << std::endl;
}

Connection::~Connection()
{
 std::cout << "Connection::~Connection" << std::endl;
}

