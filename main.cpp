#include <iostream>
#include "stdlib.h"

#define _DEBUG

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "openapi/openapi_client.h"

using namespace std;

/** ++++++++++++++++++++++++++++++++++++++++++++++++ **/
/** 此处替换为开发者在支付宝开放平台申请的应用ID **/
string appId = "2016092100566055";

/** 此处替换为开发者使用openssl生成的rsa私钥 **/
string pKey = "-----BEGIN RSA PRIVATE KEY-----\n"
"MIICXgIBAAKBgQDtc69kjie / mUEkMh9 + EgjaoLM4obeDowu + if2pz9ZfTQMD3hz7"
"wkBMwdemH0YPK / NescNclTmkieHPY8U / GlYNyfIRK / AlVqvNK72DIFuy6SJZdzS5"
"OcMhhOqhjwU / wwOT0DTZ + o2xKvZPaWmq + pNpnSEvdJhFklt + LmliML++KwIDAQAB"
"AoGBAM / vFFJsIeaon + DAe898n4BEZW1cQEXoC6rJT / baaBGAcPl8Eclta71Lqjpw"
"/ Hrgs / filv + GNboefD2OUvZVa7BroOm9y7RwwlAfJSUWcNpOVtt11B1j + B4 + yoaV"
"4JpSxMITo5PI4l + eWkN2AX7NLaMZRgGXNOQkatjE84NW4KoxAkEA + l5oLs5EoMXu"
"XnX0dwh8KrKA / 0PpNCsnAtRLC2drZP4Wh3KOG97JguBw5CzV87wMag5Ao3XWQ7pS"
"wUr + qAsopwJBAPLK54HE / KjFa1ELDRtCvdgwFcqQVLo + 3tkDmxLKf4lNpqRiKWnN"
"lVpxYINgsU + xC5vubC8lb29kvVY + MT4D6t0CQFgiL456cdIemuCJqTrVs8 / b8mjp"
"YQhKQHtQe / JRv45Xm1qmyruo20rE8zh / R / l6suwKhFqGOpyw1DzSx34kH3UCQQDj"
"8b2iZyfy585WezKl6mZERvjegd0aMpaUVj9MSBOu + 9k9Me / BpsLW8 + Tx02EE + ap1"
"jkXBibrycTkVdDRVDeZ9AkEAvbx5uZxG2vVexJMDTdo3BcWgXw7N + 6TN28weFBfA"
"HjOPNP2GBfrX7WonrHVttrZr5zKkGIJ1nlyOr3tNxnRCLQ ==\n"
		"-----END RSA PRIVATE KEY-----";

/** 支付宝公钥，用来验证支付宝返回请求的合法性 **/
string aliPubKey = "-----BEGIN PUBLIC KEY-----\n"
"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDIgHnOn7LLILlKETd6BFRJ0GqgS2Y3mn1wMQmyh9zEyWlz5p1zrahRahbXAfCfSqshSNfqOmAQzSHRVjCqjsAw1jyqrXaPdKBmr90DIpIxmIyKXv4GGAkPyJ/6FTFY99uhpiq0qadD/uSzQsefWo0aTvP/65zi3eof7TcZ32oWpwIDAQAB\n"
        "-----END PUBLIC KEY-----";

/** 注：appid，私钥，支付宝公钥等信息建议不要写死在代码中 **/
/** 这些信息应以配置等方式保存，此处写在代码中只是为了示例的简便 **/
/** ++++++++++++++++++++++++++++++++++++++++++++++++ **/


/** some examples **/
JsonMap getPrecreateContent();

int main1(int argc, char *argv[])
{

    /** 实例化OpenapiClient工具类 **/
    OpenapiClient openapiClient(appId,
                                pKey,
                                OpenapiClient::default_url,
                                OpenapiClient::default_charset,
                                aliPubKey);

    /** ++++++++++++++++++++++++++++++++++++++++++++++++ **/
    /** 各个具体业务接口参数组装模式具体参看Openapi官方文档 **/
    /** https://doc.open.alipay.com/ **/
    // demo1:当面付预下单示例

    string method = "alipay.trade.precreate";

    JsonMap contentMap = getPrecreateContent();

    /** ++++++++++++++++++++++++++++++++++++++++++++++++ **/

    /** ++++++++++++++++++++++++++++++++++++++++++++++++ **/
    /** 网关扩展参数，例如商户需要回传notify_url等，可以在extendParamMap中传入 **/
    /** 这是一个可选项，如不需要，可不传 **/
    /* StringMap extendParamMap;
    extendParamMap.insert(StringMap::value_type("notify_url", "http://api.test.alipay.net/atinterface/receive_notify.htm"));
    */

    /** ++++++++++++++++++++++++++++++++++++++++++++++++ **/

    /** 调用Openapi网关 **/
    JsonMap respMap;
    respMap = openapiClient.invoke(method, contentMap);
    /* 如果有扩展参数，则按如下方式传入
    respMap = openapiClient.invoke(method, contentMap, extendParamMap);
    */

    /** 解析支付宝返回报文 **/
    JsonMap::const_iterator iter = respMap.find("code");
    if (iter != respMap.end()) {
        string respCode = iter->second.toString();
        DebugLog("code:%s", respCode.c_str());
    } else {
        DebugLog("cannot get code from response");
		goto RET;
    }

    iter = respMap.find("msg");
    if (iter != respMap.end()) {
        string respMsg = iter->second.toString();
        DebugLog("msg:%s", respMsg.c_str());
		OutputDebugStringA(respMsg.append("\n").c_str());
    } else {
        DebugLog("cannot get msg from response");
		goto RET;
    }


	iter = respMap.find("qr_code");
	if (iter != respMap.end()) {
		string respMsg = iter->second.toString();
		DebugLog("qr_code:%s", respMsg.c_str());
		OutputDebugStringA(respMsg.append("\n").c_str());
		std::string  str = "C:\\Progra~1\\Intern~1\\iexplore ";
		str.append("http://api.qrserver.com/v1/create-qr-code/?data=").append(respMsg);
		str.append("&size = 100x100");
		//system(str.c_str());
		std::string str1 = "START ";
		str1.append(str);
		system(str1.c_str());
		Sleep(2000);
	}
	else {
		DebugLog("cannot get qr_code from response");
		goto RET;
	}
	//
	//precreate done
	//
	//start query
	method = "alipay.trade.query";

	bool success = false;
	int cnt = 60;
	do
	{
		respMap = openapiClient.invoke(method, contentMap);
		iter = respMap.find("trade_status");
		if (iter != respMap.end()) {
			string respMsg = iter->second.toString();
			DebugLog("Return code:%s", respMsg.c_str());
			//OutputDebugStringA(respMsg.append("\n").c_str());
			if(respMsg == "TRADE_SUCCESS")
				success = true;
			if (respMsg == "TRADE_CLOSED")
				cnt = 0;
		}
		else {
			DebugLog("cannot get code from response.");
		}
		cnt-=2;
		printf("Time left : %ds\n", cnt);
		Sleep(2000);
	} while (!success && cnt >0);

	if (success)
	{
		DebugLog("Trade done");
	}
	else
	{
		method = "alipay.trade.cancel";
		respMap = openapiClient.invoke(method, contentMap);
		iter = respMap.find("code");
		if (iter != respMap.end()) {
			string respMsg = iter->second.toString();
			DebugLog("Return code:%s", respMsg.c_str());
			//OutputDebugStringA(respMsg.append("\n").c_str());
			if (respMsg == "10000")
				DebugLog("Time out, Trade canceled.");
		}
		else {
			DebugLog("cannot get code from response");
		}
	}
RET:
    system("pause");
    return 0;
}


#include <time.h>
std::string getTradeNo()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[128];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);
	std::string retstr(buffer);
	printf("Trade No = %s\n", retstr.c_str());
	return retstr;

}

/**
 * 组装支付宝预下单业务请求
 */
JsonMap getPrecreateContent() {
    JsonMap contentMap;
    //contentMap.insert(JsonMap::value_type(JsonType("out_trade_no"), JsonType("20160606121229")));
	contentMap.insert(JsonMap::value_type(JsonType("out_trade_no"), JsonType(getTradeNo())));
    contentMap.insert(JsonMap::value_type(JsonType("total_amount"), JsonType(22.0)));
    contentMap.insert(JsonMap::value_type(JsonType("subject"), JsonType("iphone7")));
    return contentMap;
}
