#include <iostream>
#include <thread>
#include <chrono>
#include "gazebo/util/LogRecord.hh"
#include "gazebo/common/Console.hh"
#include "gazebo/transport/TransportIface.hh"
#include "Master.hh"

bool setupServer()
{
  gzLogInit("test-", "gzserver.log");
  gazebo::util::LogRecord::Instance()->Init("gzserver");

  gzlog << "gazebo::setupServer started\n";
  std::string host = "";
  unsigned int port = 0;

  gazebo::transport::get_master_uri(host, port);

  gazebo::Master* g_master = new gazebo::Master();
  g_master->Init(port);
  gzlog << "gazebo::setupServer ready to start master thread\n";
  g_master->RunThread();

  gzlog << "gazebo::setupServer finished\n";
  std::cout << "Can kill me now" << std::endl;
  while(1)
    std::this_thread::sleep_for(std::chrono::seconds(5));
  return true;
}

int main()
{
 std::cout << "main started" << std::endl;
 setupServer();
 return 0;
}