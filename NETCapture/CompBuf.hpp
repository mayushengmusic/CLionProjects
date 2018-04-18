//
// Created by jaken on 16-12-17.
//


#include <mutex>
#include <memory.h>

#include "packet.hpp"
#ifndef NETCAPTURE_COMPBUF_HPP
#define NETCAPTURE_COMPBUF_HPP

class CompBuf{
public:
    CompBuf();
    struct packet * getelem();

    void insertelem(struct packet *const elemp);

private:
    std::mutex mutexforback;
    std::mutex mutexforlink;
    struct packet * link;
    struct packet * back;

};

CompBuf::CompBuf() {
    link = new packet;
    memset(link,0,sizeof(struct packet));
    link->size = 0;
    link->next = new packet;
    memset(link->next,0,sizeof(struct packet));
    back = link -> next;
    back->size = 0;
    back->next = nullptr;
}


void CompBuf::insertelem(struct packet *const elemp) {


    std::lock_guard<std::mutex> lk(mutexforback);
    back->next = elemp;
    back = elemp;
    back->next = nullptr;

}

struct packet* CompBuf::getelem() {
    std::lock_guard<std::mutex> lk(mutexforlink);
    if(link->next->next == nullptr)
        return nullptr;
    struct packet * ret = link;
    link = link -> next;
    ret -> next = nullptr;
    return ret;

}

#endif //NETCAPTURE_COMPBUF_HPP
