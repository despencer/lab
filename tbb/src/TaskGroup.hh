#ifndef GAZEBO_TRANSPORT_TASKGROUP_HH_
#define GAZEBO_TRANSPORT_TASKGROUP_HH_

#include <iostream>
#include <boost/function.hpp>
#include <tbb/tbb.h>

namespace gazebo {
  namespace transport {
    class TaskGroup
    {
      public: ~TaskGroup() noexcept
              {
                // Wait for running tasks to finish
                this->taskGroup.wait();
              }

      public: template<class Functor, class... Args> void run(Args&&... args)
      {
        std::cout << "TaskGroup::run called, this=" << this << "\n";
        this->taskGroup.run(Functor(std::forward<Args>(args)...));
      }

      private: tbb::task_group taskGroup;
    };

  }
}

#endif