//
// Created by jaken on 16-11-16.
//

#include "../include/findlink.hpp"
#include <iostream>

//const boost::regex findlink::typematch=boost::regex("[\\d\\D]+<body.*\\>[\\d\\D]+</body\\>[\\d\\D]+");
//match html file.
const boost::regex findlink::srcandhref=boost::regex("(?:(?:src)|(?:href))\\s?=\\s?[\"\']?([-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|])[\"\']?\\s?");





void findlink::getlinkinpage(const std::string &message, std::vector<std::string> & veclink) {

    std::string data = message;




        boost::sregex_iterator end;
        for (boost::sregex_iterator iter(std::cbegin(data), std::cend(data), srcandhref); iter != end; ++iter) {
            veclink.emplace_back((*iter)[1]);


    }
}//match the regular expressions,and collect the url from a new page,then write them to the vector.