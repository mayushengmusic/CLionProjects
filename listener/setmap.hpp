//
// Created by jaken on 18-2-15.
//

#ifndef LISTENER_SETMAP_HPP
#define LISTENER_SETMAP_HPP
#include <string>
#include <unordered_set>
#include <fstream>

class fliter{
public:
    explicit fliter(const std::string & path):machine_set(),file_path(path) {
    }
    void init(){
        std::ifstream file(file_path.c_str());
        while(file.good())
        {
            static std::string machineid;
            std::getline(file,machineid);

            if(!machineid.empty())
                machine_set.insert(machineid);
        }
    }


    void check_write_file(const std::string &machineid){
        if(!check(machineid)) {
            write_file(machineid);
            machine_set.insert(machineid);
        }
    }



private:

    bool check(const std::string &machineid) noexcept {
        return machine_set.count(machineid)>0;
    }

    void write_file(const std::string &machineid){
        std::ofstream file(file_path.c_str(),std::ios::app);
        file<<machineid<<'\n';
    }


    std::unordered_set<std::string> machine_set;
    std::string file_path;

};
#endif //LISTENER_SETMAP_HPP
