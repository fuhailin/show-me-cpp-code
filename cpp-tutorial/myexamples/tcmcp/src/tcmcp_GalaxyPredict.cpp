#include "tcmcp_GalaxyPredict.h"

void tcmcp_GalaxyPredictClient::createConnect(map<STR_ip_port_suffix, connectNode<GalaxyPredictClient>>& pool, const string& ip, const int port)
{
    CREATE_CONNECT_TFramedTransport_TBinaryProtocol(GalaxyPredictClient);
}
/*
****************************************************
*****---tcmcp function list implementations.---*****
****************************************************
*/
int tcmcp_GalaxyPredictClient::tcmcp_predict(PredictRes& _return, const PredictReq& req)
{
    USE_tcmcp_NOT_POD(GalaxyPredictClient, predict, (_return, req));
}