//
// Created by jaken on 16-11-16.
//

#ifndef TINYSPIDER_FINDLINK_HPP
#define TINYSPIDER_FINDLINK_HPP

#include <boost/regex.hpp>
#include <vector>


    class findlink {

    public:
        static void getlinkinpage(const std::string & message,std::vector<std::string> & veclink);

    private:
        //static bool checkpagetype(std::string & message);
        const static boost::regex srcandhref;

        const static boost::regex typematch;

    };




#endif //TINYSPIDER_FINDLINK_HPP
