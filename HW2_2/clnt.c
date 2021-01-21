#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
	
#define BUF_SIZE 100
#define NAME_SIZE 20
	
void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);
	
char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];
	
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;	// 송수신용 thread 생성 
	void * thread_return;
	if(argc!=4) {	// argument 확인 
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	 }
	
	sprintf(name, "[%s]", argv[3]);
	sock=socket(PF_INET, SOCK_STREAM, 0);	//socket 생성
	
	memset(&serv_addr, 0, sizeof(serv_addr));		// 초기화  
	serv_addr.sin_family=AF_INET;					// 주소 체계를 IPv4 인터넷 프로토콜에 적용하는 주소체계
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);	// IP주소를 클라이언트로 입력받은 주소로 배정 
	serv_addr.sin_port=htons(atoi(argv[2]));		// port번호를 클라이언트로 입력받은 port 번호로 배정 
	  
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 	// 연결요청 
		error_handling("connect() error");
    
    printf("Welcome to GBC Network Client!\n");
	
	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);	// send용 thread 생성 
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);	// recieve용 thread 생성 
	pthread_join(snd_thread, &thread_return);		// snd_thread 종료될 때까지 기다리다가 종료시 자원 해제 
	pthread_join(rcv_thread, &thread_return); 		
	close(sock);  
	return 0;
}
	
void * send_msg(void * arg)   // send thread main
{
	int sock=*((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1) 
	{
		fgets(msg, BUF_SIZE, stdin);
		if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n")) 	// 종료 확인 
		{
			close(sock);
			exit(0);
		}
		sprintf(name_msg,"%s %s", name, msg);
		write(sock, name_msg, strlen(name_msg));	// 데이터 송신 
	}
	return NULL;
}
	
void * recv_msg(void * arg)   // read thread main
{
	int sock=*((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;
	while(1)
	{
		str_len=read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);	// 데이터 수신 
		if(str_len==-1) 
			return (void*)-1;
		name_msg[str_len]=0;
		fputs(name_msg, stdout);
	}
	return NULL;
}
	
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
