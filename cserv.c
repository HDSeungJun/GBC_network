#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(char * msg);

int clnt_cnt=0;				// 서버에 접속한 클라이언트의 소켓 관리를 위한 변수와 배열 
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	pthread_mutex_init(&mutx, NULL);		// 뮤텍스 생성 
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);	// 소켓 생성 

	memset(&serv_adr, 0, sizeof(serv_adr));		// 초기화  
	serv_adr.sin_family=AF_INET; 				// 주소 체계를 IPv4 인터넷 프로토콜에 적용하는 주소체계
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);	// IP주소를 클라이언트로 입력받은 주소로 배정 
	serv_adr.sin_port=htons(atoi(argv[1]));		// port번호를 클라이언트로 입력받은 port 번호로 배정 
	
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)		// 주소 할당 
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)	// 연결 요청 대기 상태 확인 
		error_handling("listen() error");
    
    printf("Welcome to GBC Network Server!\n");
	
	while(1)
	{
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);	// 연결 허용 
		
		pthread_mutex_lock(&mutx);			// 뮤텍스 잠금 (간섭으로 인한 혼란 방지)
		clnt_socks[clnt_cnt++]=clnt_sock;	// 새로운 연결이 형성될 때마다 변수와 배열 정보를 등록 
		pthread_mutex_unlock(&mutx);		// 뮤텍스 잠금 해제 
	
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);	// 추가된 클라이언트에 서비스를 제공하기 위한 쓰레드 생성 
		pthread_detach(t_id);	//쓰레드 종료 (메모리 소멸)
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);	// close socket
	return 0;
}
	
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char msg[BUF_SIZE];
	
	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)	// 데이터 수신 
		send_msg(msg, str_len);		// send message 
	
	pthread_mutex_lock(&mutx)	
	for(i=0; i<clnt_cnt; i++)   // remove disconnected client
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}
void send_msg(char * msg, int len)   // send to all
{
	int i;
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);	// 데이터 송신 
	pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}