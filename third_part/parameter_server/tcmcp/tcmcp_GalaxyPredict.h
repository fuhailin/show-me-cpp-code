#ifndef _TCMCP_GalaxyPredict_H_
#define _TCMCP_GalaxyPredict_H_

#include "ThriftClientMultiConnectPlug.h"
#include "thrift/GalaxyPredictorThrift/GalaxyPredict.h"

class tcmcp_GalaxyPredictClient
    : public CThriftClinetMultiConnectPlug<GalaxyPredictClient> {
 public:
  tcmcp_GalaxyPredictClient(const string zkHost, const string zkPath,
                            const int connectNumber,
                            const int timeout = 1000 * 10,
                            const double checkTimes = 1.0)
      : CThriftClinetMultiConnectPlug<GalaxyPredictClient>(
            zkHost, zkPath, connectNumber, timeout, checkTimes) {}

 private:
  void createConnect(
      map<STR_ip_port_suffix, connectNode<GalaxyPredictClient>>& pool,
      const string& ip, const int port);

 public:
  int tcmcp_predict(PredictRes& _return, const PredictReq& req);
};
#endif  //_TCMCP_GalaxyPredict_H_