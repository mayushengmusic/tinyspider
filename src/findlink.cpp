//
// Created by jaken on 16-11-16.
//

#include "../include/findlink.hpp"
#include <iostream>

const boost::regex findlink::typematch=boost::regex("[\\d\\D]+<html.*\\>[\\d\\D]+</html\\>[\\d\\D]+");
//match html file.
const boost::regex findlink::srcandhrefwithmark=boost::regex("(?:(?:src)|(?:href))\\s?=\\s?([\'\"]{1})(.+?)\\1");
const boost::regex findlink::srcandhrefwithoutmark=boost::regex("(?:(?:src)|(?:href))\\s?=\\s?([^[\"\']]+?)\\s");

bool findlink::checkpagetype(std::string &message) {
    return boost::regex_match(message,typematch);
}


void findlink::getlinkinpage(const std::string &message, std::vector<std::string> & veclink) {

    std::string data = message;

    if(checkpagetype(data)) {


        boost::sregex_iterator end;
        for (boost::sregex_iterator iter(std::cbegin(data), std::cend(data), srcandhrefwithmark); iter != end; ++iter) {
            veclink.emplace_back((*iter)[2]);
        }
        for (boost::sregex_iterator iter(std::cbegin(data), std::cend(data), srcandhrefwithoutmark); iter != end; ++iter) {
            veclink.emplace_back((*iter)[1]);
        }

    }
}//match the regular expressions,and collect the url from a new page,then write them to the vector.