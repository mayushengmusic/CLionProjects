//
// Created by jaken on 17-10-9.
//

#include <vector>
#include <string>

#ifndef HURRICANE_ITASK_HPP
#define HURRICANE_ITASK_HPP
namespace hurricane {
    namespace base {
        class ITask {

        public:
            typedef std::vector<std::string> Fields;

            virtual ~ITask() {};

            virtual Fields DeclareFields() const = 0;

        };
    }
}

#endif //HURRICANE_ITASK_HPP
