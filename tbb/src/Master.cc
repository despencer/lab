#include <iostream>
#include <boost/bind.hpp>
#include "Master.hh"
#include "Connection.hh"

using namespace gazebo;

namespace gazebo
{

Master::Master()
{
}

Master::~Master()
{
}

void Master::Run()
{
 std::cout << "Master::Run called" << std::endl;
 transport::ConnectionPtr conn = transport::ConnectionPtr(new transport::Connection());
 using namespace boost::placeholders;
 conn->OnReady(
        boost::bind(&Master::OnRead, this, _1));

 std::cout << "Master::Run returns" << std::endl;
}

void Master::OnRead(const std::string &_data)
{
  std::cout << "Master::OnRead called with " << _data << std::endl;
}

}
