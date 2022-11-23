#ifndef _CONNECTION_HH_
#define _CONNECTION_HH_

#ifndef BOOST_BIND_GLOBAL_PLACEHOLDERS
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#endif

#include <iostream>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/tuple/tuple.hpp>
#include <tbb/tbb.h>
#include "TaskGroup.hh"

namespace gazebo {
  namespace transport {

    class Connection;
    typedef boost::shared_ptr<Connection> ConnectionPtr;

    class ConnectionReadTask
    {
      public: ConnectionReadTask(
                  boost::function<void (const std::string &)> _func,
                  const std::string &_data) :
                func(_func),
                data(_data)
              {
              }

      /// \brief Execute the data callback
      public: void operator()() const
              {
                    std::cout << "tbb::task run new" << std::endl;
                    this->func(this->data); 
              }

      /// \brief The boost function pointer
      private: boost::function<void (const std::string &)> func;

      /// \brief The data to send to the boost function pointer
      private: std::string data;
    };

    class Connection :
      public boost::enable_shared_from_this<Connection>
    {
      public: Connection();
      public: virtual ~Connection();

      public: template<typename Handler>
               void OnReady(Handler _handler)
              {
                  std::cout << "Connection::OnReady called" << std::endl;
                  this->taskGroup.run<ConnectionReadTask>(_handler, "abcdef");
              }

      private: TaskGroup taskGroup;
    };

  }
}

#endif