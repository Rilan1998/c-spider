#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<queue>
//#include<WinSock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")//链接Ws2_32.lib这个库

bool StartCatch(string url);
class CHttp {
public:
	CHttp();
	~CHttp();
	bool InitNet();//初始化网络
	bool AnalyseUrl(string url);//解析网页
	bool Connect();//连接服务器
	bool FetchHtml(string &html);//获取网页
	bool AnalyseHtml();//解析网页
	bool Download(string url, string filename);//下载资源
private:
	string m_host;//主机名
	string m_object;//资源路径
	SOCKET m_socket;//套接字
};