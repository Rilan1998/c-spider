#include "spider.h"

int main()
{
    cout << "Hello World!" << endl;
    string url="http://www.baidu.com";
    
    //创建文件夹
    CreateDirectory(L"./img",NULL);

    //开始抓取
    StartCatch(url);
}


bool StartCatch(string url) {
    queue<string> q;
    q.push(url);

    while (!q.empty())
    {
        CHttp http;
        //取出url
        string current=q.front();
        q.pop();
        //初始化网络
        http.InitNet();
        //解析url
        http.AnalyseUrl(current);
        //连接服务器
        http.Connect();
        //获取网页
        string html;
        http.FetchHtml(html);
        cout << html << endl;
    }
    return true;
}

CHttp::CHttp()
{
}

CHttp::~CHttp()
{
}

bool CHttp::InitNet()
{
    WSADATA wd;
    if(WSAStartup(MAKEWORD(2,2),&wd))
        return false;
    if(LOBYTE(wd.wVersion)!=2||HIBYTE(wd.wVersion != 2))
        return false;

    //创建套接字
    m_socket=socket(AF_INET,SOCK_STREAM,0);
    if (m_socket == INVALID_SOCKET)
        return false;
    return false;
}

bool CHttp::AnalyseUrl(string url)
{
    //tolower(url);//全部转为小写
    if (string::npos == url.find("http://"))//string:npos是个特殊值，说明查找没有匹配
        return false;
    if(url.length()<=7)
        return false;
    int pos=url.find('/', 7);
    if (pos == string::npos) {
        m_host = url.substr(7);
        m_object = "/";
    }
    else {
        m_host = url.substr(7, pos-7);//第二个参数表示要截取多少个字符
        m_object = url.substr(pos);
    }
    if (m_host.empty())
        return false;
    return true;
}

bool CHttp::Connect()
{
    hostent *p=gethostbyname(m_host.c_str());
    if (!p)
        return false;
    sockaddr_in sa;
    memcpy(&sa.sin_addr, p->h_addr,4);//内存拷贝
    sa.sin_family = AF_INET;//ipv4
    sa.sin_port = htons(80);//将主机字节顺序转换为网络字节顺序

    if (SOCKET_ERROR == connect(m_socket, (sockaddr*)&sa, sizeof(sa)))
        return false;//连接失败
    return true;
}

bool CHttp::FetchHtml(string& html)
{
    //get请求制作
    string info;
    info = info + "GET " + m_object+" HTTP/1.1\r\n";
    info = info + "Host: " + m_host + "\r\n";
    info = info + "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.100 Safari/537.36\r\n";
    //chrome://version/ 查看用户代理
    info = info + "Connection:Close\r\n\r\n";
    
    //发送请求
    if (SOCKET_ERROR == send(m_socket, info.c_str(), info.length(), 0))
        return false;

    //接收
    char ch = 0;
    int m_recv = 0;//实际接收的数据
    while (m_recv = recv(m_socket, &ch, sizeof(ch), 0) > 0){
        html = html + ch;
    }
    return true;
}

bool CHttp::AnalyseHtml()
{
    return true;
}

bool CHttp::Download(string url, string filename)
{
    return true;
}
