#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<queue>
//#include<WinSock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")//����Ws2_32.lib�����

bool StartCatch(string url);
class CHttp {
public:
	CHttp();
	~CHttp();
	bool InitNet();//��ʼ������
	bool AnalyseUrl(string url);//������ҳ
	bool Connect();//���ӷ�����
	bool FetchHtml(string &html);//��ȡ��ҳ
	bool AnalyseHtml();//������ҳ
	bool Download(string url, string filename);//������Դ
private:
	string m_host;//������
	string m_object;//��Դ·��
	SOCKET m_socket;//�׽���
};