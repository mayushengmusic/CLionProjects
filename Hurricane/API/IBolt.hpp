//
// Created by jaken on 10/24/17.
//

#ifndef HURRICANE_IBOLT_HPP
#define HURRICANE_IBOLT_HPP

#include "ITask.hpp"

namespace hurricane{
    namespace bolt{

        class IBolt:public base::ITask{
        public:
            virtual void Prepare(base::outputCollector& outputCollector) = 0;
            virtual void Cleanup() = 0;
            virtual void Execute(const base::Values & values) = 0;
            virtual IBolt * clone() const = 0;
        };
    }
}
#endif //HURRICANE_IBOLT_HPP
