#pragma once

//#include "stdlib.h"
//#include <iostream>
#include <sstream>//for std::ostringstream
#include<Windows.h>//for OutputDebugStringA

#if defined(NDEBUG)
#define dPrintL
#define dPrint(format,...)
#define dPrint1(var)
#define dPrintA(var)
#else
#define dPrintL  {std::ostringstream oss; oss<<"["<<__FILE__<<":"<<__LINE__<<"]  ";OutputDebugStringA(oss.str().c_str());}//print current file and line
#define dPrint(format,...) dPrintL{char buf[256]; sprintf(buf, format "\n", ##__VA_ARGS__);OutputDebugStringA(buf);}
#define dPrint1(var)  dPrintL{std::ostringstream oss;oss<<#var<<" = "<<var<<std::endl; OutputDebugStringA(oss.str().c_str());}//print varilable name = value
#define dPrintA(var) dPrintL{char buf[256]; sprintf(buf,#var" @ %p\n", var);OutputDebugStringA(buf);}//print a pointer
#endif


#define PAIRCNT 10

using namespace std;
class WeixinPayAPI
{
private:
	string appid = "wxd930ea5d5a258f4f",
		mch_id = "10000100",
		key = "123456",//user password
		notifyURL = "#",
		device_info = "1000",//not in use in this case
		tradeType = "NATIVE",
		unifiedorderURL = "https://api.mch.weixin.qq.com/pay/unifiedorder",
		orderqueryURL = "https://api.mch.weixin.qq.com/pay/orderquery",
		closeorderURL = "https://api.mch.weixin.qq.com/pay/closeorder",
		deviceIP,nonce_str, sign, body, out_trade_no, total_fee; //need to be filled for each trade
	struct KeyValuePair
	{
		string key;
		string *value;
	};
	KeyValuePair pairs[PAIRCNT] = {
		{"appid",	&appid}, // application ID
		{"body",	&body}, // product description
		{"mch_id",	&mch_id}, //merchant id
		{"nonce_str",&nonce_str}, //random str
		{"notify_url",&notifyURL }, // call back url
		{"out_trade_no",&out_trade_no }, // trade number
		{"sign",&sign}, //signature
		{"spbill_create_ip",&deviceIP}, // device IP
		{"total_fee",&total_fee }, //total fee
		{"trade_type",&tradeType} //trade type = NATIVE
	};
public:
	WeixinPayAPI();
	~WeixinPayAPI();
	std::string getstr();
	std::string sendRequest();
private:
	int loadConfig();
	int getIP();
	int getTradeNoAndNonce_str();
	int signature();
};

