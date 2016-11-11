#ifndef OPENAPICLIENT_H
#define OPENAPICLIENT_H

#if defined(NDEBUG)
#define dPrintL
#define dPrint(format,...)
#define dPrint1(var)
#define dPrintA(var)
#else
#include <sstream>//for std::ostringstream
#include<Windows.h>//for OutputDebugStringA
#define dPrintL  {std::ostringstream oss; oss<<"["<<__FILE__<<":"<<__LINE__<<"]  ";OutputDebugStringA(oss.str().c_str());}//print current file and line
#define dPrint(format,...) dPrintL{char buf[256]; sprintf(buf, format "\n", ##__VA_ARGS__);OutputDebugStringA(buf);}
#define dPrint1(var)  dPrintL{std::ostringstream oss;oss<<#var<<" = "<<var<<std::endl; OutputDebugStringA(oss.str().c_str());}//print varilable name = value
#define dPrintA(var) dPrintL{char buf[256]; sprintf(buf,#var" @ %p\n", var);OutputDebugStringA(buf);}//print a pointer
#endif



#include "json/json_util.h"

#  if defined(OPENAPI_LIB)

#ifndef XRSA_KEY_BITS
#define XRSA_KEY_BITS (1024)
#endif

#include "http/http_client.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <time.h>

#pragma comment (lib, "libs/libcurl.lib")
#pragma comment (lib, "libs/libeay32.lib")
#pragma comment (lib, "libs/ssleay32.lib")
#    define OPENAPI//   __declspec(dllexport)
#  else
#    define OPENAPI //  __declspec(dllimport)
#pragma comment (lib, "openapi/Openapi.lib")
#  endif

using namespace std;

/** STL map default sort order by key **/
typedef map<string, string> StringMap;

/**
 * @brief The OpenapiClient class
 */
class OpenapiClient {
public:
	OpenapiClient();
		//const string &appId,
  //                const string &privateKey,
  //                const string &url = default_url,
  //                const string &charset = default_charset,
  //                const string &alipayPublicKey = string());

public:

    static const string default_charset;
    //static const string default_url;
    static const string default_sign_type;
    static const string default_version;

    static const string KEY_APP_ID;
    static const string KEY_METHOD;
    static const string KEY_CHARSET;
    static const string KEY_SIGN_TYPE;
    static const string KEY_SIGN;
    static const string KEY_TIMESTAMP;
    static const string KEY_VERSION;
    static const string KEY_BIZ_CONTENT;

public:
	string appId;
    string privateKey;
    string signType;
    string version;
    string charset;
    string url;
    string alipayPublicKey;

public:
    string invoke(const string &method, const string &content, const StringMap &extendParamMap = StringMap());
    JsonMap invoke(const string &method, const JsonMap &contentMap, const StringMap &extendParamMap = StringMap());


private:
    /**
     *
     * STL map default sort order by key
     *
     * STL map 默认按照key升序排列
     * 这里要注意如果使用的map必须按key升序排列
     *
     */
    string buildContent(const StringMap &contentPairs);
    string analyzeResponse(const string &responseStr);

public:
    static string base64Encode(const unsigned char *bytes, int len);
    static bool base64Decode(const string &str, unsigned char *bytes, int &len);

    static string rsaSign(const string &content, const string &key);
    static bool rsaVerify(const string &content, const string &sign, const string &key);

public:
    string getAppId();

    string getSignType();

    string getVersion();

    string getCharset();

    string getUrl();

    string getAlipayPublicKey();

public:
	OPENAPI	 	string createNewTrade(string itemName, float itemPrice);
	 	int queryTrade();
	 	int cancelTrade();
	//friend  OpenapiClient* createNewClient();
	int readConfigFile();
private:
	JsonMap contentMap;
};
OPENAPI 	 OpenapiClient* createNewClient();
#endif // OPENAPICLIENT_H
