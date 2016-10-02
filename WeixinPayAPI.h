#pragma once

#include "stdlib.h"
#include <iostream>

#include<Windows.h>
#define LOG0(str) {OutputDebugStringA(str);OutputDebugStringA("\n");}
#define LOG(format,...)  {char buf[256], *p = buf;va_list args;va_start(args, format);p += _vsnprintf(p, sizeof(buf) - 1, format, args);va_end(args);OutputDebugStringA(buf);OutputDebugStringA("\n");}


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
		deviceIP = "12.12.12.12",
		nonce_str, sign, body, out_trade_no, total_fee; //need to be filled for each trade
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
private:
	int loadConfig();
	int getIP();
	int getTradeNo();
	string getRandom();
	int signature();
};

