#include "WeixinPayAPI.h"

WeixinPayAPI::WeixinPayAPI()
{
	signature();
}


WeixinPayAPI::~WeixinPayAPI()
{
}

int WeixinPayAPI::getIP()
{
	deviceIP = "12.12.12.12";
	return 0;
}
#include <time.h>
int WeixinPayAPI::getTradeNo()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[128];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);
	std::string retstr(buffer);
	out_trade_no = retstr;
	//printf("Trade No = %s\n", retstr.c_str());
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
	LOG0(stringSignTemp.c_str());
	char out[32];
	char *in = (char*)stringSignTemp.c_str();
	int l = stringSignTemp.length();
	GetMd5KeyString(in, l , out);
	sign = string((const char*)out);
	LOG0(sign.c_str());
	return 0;
}
int main(int argc, char *argv[])
{
	WeixinPayAPI *api = new WeixinPayAPI();
	return 0;
}