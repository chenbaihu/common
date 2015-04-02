#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int udp_bind(const char * ip, unsigned short port,char * errbuf)
{
    int listenfd = -1;

	listenfd = socket(AF_INET,SOCK_DGRAM,0);
	if ( listenfd < 0 )
	{
		snprintf(errbuf,1024,"open socket error[%d][%s]",errno,strerror(errno));
		return -1;
	}

	int iReuseAddrFlag = 1;
	int ret = setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(char*)&iReuseAddrFlag,sizeof(iReuseAddrFlag));
	if(ret < 0)
	{
		snprintf(errbuf,1024,"open setsocopt error[%d][%s]",errno,strerror(errno));
        close(listenfd);
        listenfd = -1;
		return -1;
	}
	struct sockaddr_in  servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port        = htons(port);
	ret = bind(listenfd,(struct sockaddr*) &servaddr,sizeof(servaddr) );
	if(ret < 0)
	{
		snprintf(errbuf,1024,"bind[%s:%d] error[%d][%s]",ip,port,errno,strerror(errno));
        close(listenfd);
		listenfd = -1;
		return -1;
	}

	return listenfd;

}




