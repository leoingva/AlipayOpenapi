#include "WeixinPayAPI.h"
#include "openapi/http/http_client.h"
WeixinPayAPI::WeixinPayAPI()
{
	getIP();
}


WeixinPayAPI::~WeixinPayAPI()
{
}


int WeixinPayAPI::getIP()
{
	deviceIP = "24.87.136.203";
	return 0;
}
#include <sstream>//for std::ostringstream
int WeixinPayAPI::getTradeNoAndNonce_str()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	char buf[64];
	sprintf(buf, "%4d%2d%2d%2d%2d%2d%3d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	out_trade_no = std::string(buf);
	dPrint1(out_trade_no);

	memset(buf, 0, 64);
	
	srand(time.wMilliseconds);
	sprintf(buf, "%4d%4d", rand(), rand());
	nonce_str = std::string(buf);
	dPrint1(nonce_str);
	return 0;
}
#include "md5.h"
int WeixinPayAPI::signature()
{
	string stringA = "";
	for (int i = 0; i < PAIRCNT; i++)
	{
		if (pairs[i].key == "sign") continue;
		stringA += pairs[i].key;
		stringA += "=";
		stringA += *pairs[i].value;
		stringA += "&";
	}

	string stringSignTemp;
	stringSignTemp = stringA += "key=";
	stringSignTemp += key;
	char out[33];
	char *in = (char*)stringSignTemp.c_str();
	int len = stringSignTemp.length();
	GetMd5KeyString(in, len , out);
	dPrint1(stringSignTemp);
	sign = string((const char*)out);
	dPrint1(sign);
	return 1;
}
std::string WeixinPayAPI::getstr()
{
	getTradeNoAndNonce_str();
	signature();
	string ret="<xml>";
	for (int i = 0; i < PAIRCNT; i++)
	{
		ret += "<";
		ret += pairs[i].key;
		ret += ">";
		ret += *pairs[i].value;
		ret += "</";
		ret += pairs[i].key;
		ret += ">";
	}
	ret += "</xml>";
	return ret;
}
std::string  WeixinPayAPI::sendRequest()
{

	string str = getstr();
	dPrint1(str);
	HttpClient httpClient;
	//string url = unifiedorderURL.append("?").append(str);
	string responseStr = httpClient.sendSyncRequest(unifiedorderURL, "<xml>sdfasdf</xml>");
	dPrint1(responseStr);
	return responseStr;
}
int main1(int argc, char *argv[])
{
	WeixinPayAPI api;
	api.sendRequest();
	system("pause");
	return 0;
}