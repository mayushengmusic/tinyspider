#include <iostream>
#include <fstream>
#include <thread>
#include "../include/client_http.hpp"
#include "../include/findlink.hpp"
#include "../include/linkbufformultithread.h"

typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;


std::string string_process(std::string & original,std::string & domin)
{

    boost::regex http("http://.*");
    boost::regex doublesprit("//.*");

    boost::regex spliturl_http("http://(.+?)(/.*)");
    boost::regex spliturl_doublesprit("//(.+)(/.*)");

    boost::regex subsprit("/.*");

    if(boost::regex_match(original,http))
    {
        boost::smatch m2;
        if(!boost::regex_match(original,m2,spliturl_http)) {
            boost::smatch m;
            boost::regex subhttp("http://(.+)");
            boost::regex_match(original,m,subhttp);
            domin = m[1];
            return "/";
        }
        std::string portionone=m2[1];
        std::string portiontwo=m2[2];
        domin = portionone;
        return portiontwo;
    }
    if(boost::regex_match(original,doublesprit))
    {
        boost::smatch m2;
        if(!boost::regex_match(original,m2,spliturl_doublesprit)) {
            boost::smatch m;
            boost::regex subhttp("//(.+)");
            boost::regex_match(original,m,subhttp);

            domin = m[1];
            return "/";
        }
        std::string portionone=m2[1];
        std::string portiontwo=m2[2];
        domin = portionone;
        return portiontwo;
    }

    if(boost::regex_match(original,subsprit))
        return original;
    else
    {
        std::string spirt("/");
        return spirt+=original;
    }



}


int main(int argc,char **argv) {


    if(argc!=5)
    {
        std::cout<<"help:\n example: ./tinyspider www.meitulu.com/item/4446.html ./image/ jpg 4 \n 1.start url 2.filewritepath 3.wantedfiletype 4.threadnum\n";
        return 1;
    }

    std::string mainurl(argv[1]);
    std::string type(argv[3]);
    std::string writeloc(argv[2]);
    int threadnum=atoi(argv[4]);

    boost::regex split("(.*?)(/.*)");
    boost::smatch m1;
    if(!boost::regex_match(mainurl,m1,split))
    {
        std::clog<<" please input a corrent url:\n example: www.baidu.com/index.html\n";
        return 1;
    }
    std::string domin = m1[1];
    std::string loc = m1[2];

    HttpClient client(domin.c_str());
    auto r1 = client.request("GET",loc.c_str());

    std::stringstream ss;
    ss<<r1->content.rdbuf();

    std::vector<std::string> links;
    findlink::getlinkinpage(ss.str(),links);

    safebuf buf;
    buf.insertlink(links);
    std::atomic_int sleepcount(0);



   auto multprocesslambda = [&](int threadid){

       while(true)
       {

           std::string link = buf.getandpoplink(threadid);

           if(link=="NULL")
           {
               if(sleepcount==6*threadnum)
                   break;
               std::cout<<"sleep 5 seconds"<<std::endl;
               std::this_thread::sleep_for(std::chrono::seconds(5));
               sleepcount++;
               continue;
           }
           std::string typecheckstring(".*\\.");
           typecheckstring+=type;
           boost::regex typecheck(typecheckstring.c_str());
           if(boost::regex_match(link,typecheck))
           {

               std::string dominfromlink=domin;
               std::string locfromlink = string_process(link,dominfromlink);
               if(locfromlink=="NULL")
                   continue;


               std::stringstream ssforthread;
               static int id = 0;
               ssforthread<<threadid<<"_"<<id++<<"."<<type;
               std::string filepath=writeloc+ssforthread.str();

               try {
                   HttpClient clientforfile(dominfromlink.c_str());
                   auto r = clientforfile.request("GET", locfromlink.c_str());
                   std::fstream file(filepath.c_str(),std::ios_base::binary|std::ios_base::out);
                   file<<r->content.rdbuf();
               }catch (...)
               {
                   std::clog<<"broke link\n";
                   continue;
               }



           }
           else
           {

               std::string dominfromlink=domin;
               std::string locfromlink = string_process(link,dominfromlink);

               if(locfromlink=="NULL")
                   continue;

               if(dominfromlink!=domin)
                   continue;

               std::stringstream ssforchangepage;
               try{
               HttpClient clientinthread(dominfromlink.c_str());
               auto r = clientinthread.request("GET",locfromlink.c_str());
               ssforchangepage<<r->content.rdbuf();}
               catch (...)
               {
                   std::clog<<"broke link\n";
                   continue;
               }
               std::vector<std::string> linksforthread;
               linksforthread.reserve(1024);
               findlink::getlinkinpage(ssforchangepage.str(),linksforthread);
               if(!linksforthread.empty())
                   buf.insertlink(linksforthread);
           }

       }
   };

    std::vector<std::thread> threadcollect;
    for(int i=0;i<threadnum;i++)
    {
        threadcollect.emplace_back(multprocesslambda,i);
    }

    for(auto & x: threadcollect)
        x.join();

    return 0;
}