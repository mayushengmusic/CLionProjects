//
// Created by jaken on 10/24/17.
//
#include "ITask.hpp"
#ifndef HURRICANE_ISPOUT_HPP
#define HURRICANE_ISPOUT_HPP
namespace hurricane{

    namespace spout{
        class ISpout : public base::ITask{
        public:
            virtual void open(base::outputCollector& outputCollector) = 0;
            virtual void Close() = 0;
            virtual void Execute() = 0;
            virtual ISpout * Close() const = 0;
        };
    }


}
#endif //HURRICANE_ISPOUT_HPP
