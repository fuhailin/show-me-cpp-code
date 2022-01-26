#include "gcommon.h"
#include "logger.h"

namespace gcommon
{
    char* now(void)
    {
        struct  tm      *ptm;
        struct  timeb   stTimeb;
        static  char    szTime[24];

        ftime(&stTimeb);
        ptm = localtime(&stTimeb.time);
        snprintf(szTime, sizeof(szTime), "%4d-%02d-%02d %02d:%02d:%02d.%03d",
                1900+ptm->tm_year, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
        szTime[23] = 0;
        return szTime;
    }

    string getIp() 
    {
        char name[256];
        gethostname(name, sizeof(name));
        struct hostent* host = gethostbyname(name);
        char szBuf[16];
        const char* ret = inet_ntop(host->h_addrtype, host->h_addr_list[0], szBuf, sizeof(szBuf));
        if (nullptr == ret) 
        {
            return "";
        }
        return szBuf;
    }

    bool readConf2Json(string path, json& conf)
    {
        std::ifstream infile(path);
        if (!infile.is_open()) 
        {
            return false;
        }

        infile >> conf;
        infile.close();
        return true;
    }


    void TestDeleteHandler(ZKErrorCode errcode, const std::string& path, void* context) {
        if (errcode == kZKSucceed) {
            logger->info("TestDeleteHandler-[kZKSucceed] path={}", path);
        } else if (errcode == kZKError) {
            logger->error("TestDeleteHandler-[kZKError] path={}", path);
        } else if (errcode == kZKNotExist) {
            logger->error("TestDeleteHandler-[kZKNotExist] path={}", path);
        } else if (errcode == kZKNotEmpty) {
            logger->error("TestDeleteHandler-[kZKNotEmpty] path={}", path);
        }
        logger->info("exit the handler ");
    }
};