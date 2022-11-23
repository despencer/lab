#ifndef _MASTER_HH_
#define _MASTER_HH_

namespace gazebo
{
  class Master
  {

    public: Master();
    public: virtual ~Master();
    public: void Run();
    private: void OnRead(const std::string &_data);

  };
}

#endif