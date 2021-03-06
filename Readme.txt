来源：https://github.com/ArthasModern/AlipayOpenapiCpp

支付宝的VS2015 C++接入代码。
重新编译了openssl-1.0.2i和最新版curl。
主函数演示了预支付生成二维码，和查询。



原readme：
该项目为C++项目，包含访问支付宝开放平台（Openapi）网关的源码；

/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/

工程中有两个项目文件：
Openapi.pro为QtCreater项目文件，可用QtCreater打开；
Openapi.sln为VS（2008版）项目文件，可用VS打开；

注：该项目源码依赖C\C++标准库（STL）以及几个开源的第三方库（cJSON，libcurl，openssl）；
开发者可以在其它支持C\C++的平台（linux等）编译适配；

/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/

项目主要源码包含在目录“/openapi”中；

1）主工具类 -- ./openapi/openapi_client 
---- 访问支付宝开放平台（openapi）网关的工具类；
---- 外部主要依赖该类访问支付宝网关；
---- 具体使用示例可参见main.cpp中的源码及注释；

2）其它依赖的工具类：
HttpClient -- ./openapi/http/http_client
---- 该工具类提供Http（Https）网络通信的功能；
---- 该工具类依赖第三方库libcurl

JsonUtil -- ./openapi/json/json_util
---- 该工具类提供Json串与C++对象之间的转换功能；
---- 该工具类依赖第三方库cJSON；

openssl & libcurl -- ./libs/
---- 这两个第三方库已经编译成静态库（windows平台）;
---- 其它平台的静态库，开发者可自行下载源码进行编译；

/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/

集成/调试之前的准备工作：

1）入住支付宝开放平台，申请应用并获得应用ID（appId）；

2）本地生成rsa密钥对，并上传公钥到支付宝开放平台相应的应用下，
   并保存好自己的私钥（privateKey -- 严格保密）；
   rsa密钥生成方式参看支付宝开放平台官方文档；
   注：C++使用的是标准格式的rsa私钥，不是pkcs8格式的；
	
3）各个具体业务接口参数组装模式具体参看Openapi官方文档；

4）支付宝开放平台文档中心：https://doc.open.alipay.com/


