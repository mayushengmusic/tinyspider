//
// Created by jaken on 16-12-31.
//
#include "../include/linkbufformultithread.h"


safebuf::safebuf():LinkQueue(),LinkSet(){
}


void safebuf::insertlink(std::vector<std::string> links) {
    std::lock_guard<std::mutex> lk(mutexforboth);
    for(auto &link: links)
    if(LinkSet.count(link)==0)
    {
        LinkQueue.push(link);
        LinkSet.insert(link);
    }
}

const std::string safebuf::getandpoplink() {
    std::string back;
    std::lock_guard<std::mutex> lk(mutexforboth);
    if(LinkQueue.empty())
        return std::string("NULL");
    else
    {
       back =  LinkQueue.top();
       LinkQueue.pop();
    }

    return back;

}

