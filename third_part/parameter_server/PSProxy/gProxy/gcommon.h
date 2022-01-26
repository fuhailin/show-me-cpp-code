#ifndef _G_COMMON_H_
#define _G_COMMON_H_


#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>
#include <chrono>   
#include <iostream>
#include <unistd.h>
#include <netdb.h> 
#include <arpa/inet.h> 
#include <fstream>
#include <future>
#include <memory>
#include "nlohmann/json.hpp"
#include "zkclient.h"
#include "logger.h"

namespace gcommon
{
    using json = nlohmann::json;
    using namespace std;
    using namespace chrono;

    char* now(void);
    string getIp();
    bool readConf2Json(string path, json& conf);
    void TestDeleteHandler(ZKErrorCode errcode, const std::string& path, void* context);
    class showCostTime
    {
    public:
        showCostTime(int num = 0):
            m_num(num),
            m_start(std::chrono::system_clock::now()),
            m_strStart(now())
        {
        }
        ~showCostTime()
        {
            std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
            logger->info("[{}] start[{}] end[{}] cost {} (s) ",  m_num,
                        m_strStart.data(), now(), 
                        static_cast<double>((duration_cast<microseconds>(end-m_start)).count()) * microseconds::period::num / microseconds::period::den );
        }
    private:
        int m_num;
        std::chrono::system_clock::time_point m_start;
        std::string m_strStart;
    };
};

#endif //_G_COMMON_H_