//
// Created by jaken on 16-12-31.
//
#include <string>
#include <queue>
#include <boost/regex.hpp>
#include <mutex>
#include <iostream>

#ifndef TINYSPIDER_LINKBUFFORMULTITHREAD_H
#define TINYSPIDER_LINKBUFFORMULTITHREAD_H
struct compare {
    bool operator()(std::string &a, std::string &b) {
        boost::regex pic("[\\D\\d]+?\\.(?:jpg)|(?:jpeg)$");
        return !boost::regex_match(a,pic);

    }};


class safebuf{
public:
    explicit safebuf();
    safebuf &operator=(safebuf &) = delete;
    void insertlink(std::vector<std::string> links);
    const std::string getandpoplink(int threadid);



private:
    std::priority_queue<std::string,std::deque<std::string>,compare> LinkQueue;
    std::set<std::string> LinkSet;
    mutable std::mutex mutexforboth;
};




#endif //TINYSPIDER_LINKBUFFORMULTITHREAD_H
