# Chapter 1: 네트워크 프로그래밍과 소켓의 이해

## 01-1: 네트워크 프로그래밍과 소켓의 이해 

- 네트워크 프로그래밍: 네트워크로 연결되어 있는 서로 다른 두 컴퓨터가 데이터를 주고받을 수 있도록 하는 것 (소켓을 통해서 주고 받기 때문에 소켓 프로그래밍이라고 하기도 함)

    - 소켓: 네트워클르 통한 두 컴퓨터의 연결을 의미
    - TCP 소켓 

- 전화 받는 소켓의 구현(소켓을 전화기에 비유)
    - 전화기로 비유를 들지만 소켓은 받는 소켓과 거는 소켓이 따로 있음. 
    - 받는 용도의 소켓 
    - 필요한 socket 함수 (<sys/socket.h> 필요)
    -  서버 소켓(리스닝 소켓)

    1. `int socket(int domain, int type, int protocol);`
        - 비유에 적용하면 소켓은 전화기이다. 
        - 소켓을 생성하는 함수 
        - 성공 시 파일 디스크립터, 실패 시 -1 반환 

    2. `int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);`
        - 비유에 적용하면 bind 함수 호출을 통하여 전화번호를 할당하는 것이다.
        - 소켓에 IP와 포트번호 할당
        - 성공 시 0, 실패 시 -1 반환

    3. `int listen(int sockfd, int backlog);`
        - 비유에 적용하면 케이블 연결 
        - 소켓이 연결요청 가능한 상태가 되게 하는 함수
        - 성공시 0, 실패 시 -1 반환
    
    4. `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
        - 비유에 적용하면 수화기를 드는 것 
        - 연결요청에 대한 수락 
        - 성공 시 파일 디스크립터, 실패 시 -1 반환 

- 전화 거는 소켓의 구현 
    - 클라이턴트 소켓 

    -  `int connect(int sockfd, strcut sockaddr *serv_addr, socklen_t addrlen);`
        - 비유에 적용하면 전화를 거는 함수 
        - 성공 시 0, 실패 시 -1 반환 
    - 클라이언트 소켓에서는 socket 함수 호출을 통해 소켓 생성, connect 함수 호출을 통해 섭로의 연결 요청 과정만 존재 

---

## 01-2: 리눅스 기반 파일 조작하기 

-  리눅스는 소켓을 파일의 일종으로 구분 

- 저 수준 파일 입출력과 파일 디스크립터 
    - 저 수준: 표준에 상관없이 운영체제가 독립적으로 제공하는... = 리눅스에서 제공하는 함수 
    - 파일 디스크립터: 시스템으로부터 할당 받은 파일 또는 소켓에 부여된 정수 

    |파일 디스크립터|대상|
    |------|---|
    |0|표준 입력|
    |1|표준 출력|
    |2|표준 에러|

- 파일 열기 
    - `int open(const char *path, int flag)`;
        - flag: 오픈 모드 
        - 성공 시 파일 디스크립터, 실패 시 -1 반환 

- 파일 닫기
    - `int  close(int fd);`
        - 성공 시 0, 실패 시 -1 반환 
        - fd: 닫고자 하는 파일 디스크립터 전달 

- 파일에 데이터 쓰기
    - `ssize_t write(int fd, const void *buf, size_t nbytes);`
        -ssize_t: signed int
        - 성공 시 전달한 바이트 수, 실패 시 -1 반환 

- 파일에 저장된 데이터 읽기 
    - `ssize_t read(int fd, void *buf, size_t nbytes);`
        - 성공 시 수신한 바이트 수 (파일 끝을 만나면 0)
        - 실패 시 -1 반환 

- 파일 디스크립터와 소켓 

---

## 01-3: 윈도우 기반으로 구현하기 

- 윈도우 소켓 = 윈속(winsock) 
- 윈도우 소켓을 위한 헤더와 라이브러리 설정 
    - 헤더파일 `winsock2.h` 필요 
    - `ws2_32.lib` 라이브러리 링크

- 윈속의 초기화 
    - `int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);`
        - wVersionRequested: 프로그래뭐가 사용할 윈속의 버전정보 
            - MAKEWORD()를 통해 전달 (버전 주의) 
        - lpWSAData: WSADATA라는 구조체 변수의 주소값 
        - 성공 시 0, 실패 시 0이 아닌 에러코드 값 반환 

    - `int WSACleanup(void);`
        - 성공 시 0, 실패 시 SOCKET_ERROR 반환 
        - 윈속 라이브러리 해제 

---

## 01-4: 윈도우 기반의 소켓관련 함수와 예쩨 

- `SOCKET socket(int af, int type, int protocol);`
    - 성공 시 소켓 핸들, 실패 시 INVALID_SOKET 반환 

- `int bind(SOCKET s, const struct sockaddr *name, int namelen);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환 

- `int listen(SOCKET s, int backlog);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환 

- `SOCKET accept(SOCKET s, struct sockaddr *addr, int *addrlen);`
    - 성공 시 소켓 핸들, 실패 시 INVALID_SOCKET 반환 

- `int conncet(SOCKET s, const struct sockaddr *name, int namelen);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환 

- `int closesocket(SOCKET s);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환 

- 윈도우에서의 파일 핸들과 소켓 핸들 
    - 윈도우에서의 핸들 == 리눅스에서의 파일 디스크립터 
    - 파일 핸들과 소켓 핸들을 구분함 

- 윈도우 기반 입출력 함수 
    - `int send(SOCKET s, const char *buf, int len, int flags);`
        - s: 소켓의 핸들 값 
        - flag: 데이터 전송 시 적용할 다양한 옵션 정보 
        - 성공 시 전송된 바이트 수, 실패시 SOCKET_ERROR 반환 
        - 리눅스의 write 함수 
    - `int recv(SOCKET s, const char *buf, int len, int flags);`
        - 성공 시 수신한 바이트 수 (EOF = 0), 실패 시 SOCKET_ERROR 반환 
        - 리눅스의 read 함수 

---

# Chapter 2: 소켓의 타입과 프로토콜의 설정 

## 02-1: 소켓의 프로토콜과 그에 따른 데이터 전송 특성 

- 프로토콜: 컴퓨터 상호간의 대화에 필요한 통신규약 

- 소켓의 생성 
    - `int socket(int domain, int type, int protocol);`
        - domain: 프로토콜 체계 정보
        - type: 소켓의 데이터 전송방식 
        - protocol: 프로토콜 정보 

- 프로토콜 체계: 소켓이 사용할 프로토콜의 부류정보 
    - PF_INET: IPv4
    - PF_INETy6: IPv6
    - PF_LOCAL: 로컬 통신 
    - PF_PACKET: Low level 소켓 
    - PF_IPX: IPX 노벨 프로토콜 체계 

- 소켓의 타입 
    - 연결지향형 소켓 (SOCK_STREAM)
        - 특징:
            - 중간에 데이터가 소멸되지 않고 목적지로 전송 
            - 전송 순서대로 수신
            - 전송되는 데이터의 경계 X 
            - 소켓 대 소켓의 연결은 반드시 1대 1
        
        - 신뢰성 잇는 순차적인 바이트 기반의 연결지향 데이터 전송 방식의 소켓 
    
    - 비 연결지향형 소켓 (SOCK_DGRAM)
        - 특징: 
            - 전송된 순서와 상관없이 가장 빠른 전송 지향 
            - 데이터 손실, 파손의 우려가 있음
            - 데이터의 경계 존재 
            - 한번에 전송할 수 있는 데이터 크기 제한 

        - 신뢰성과 순차적 데이터 전송을 보장하지 안흔, 고속의 데이터 전송을 목적으로 하는 소켓 

- 프로토콜의 최종 선택 
    - 하나의 프로토콜 체계 안에 데이터 전송방식이 동일한 프로토콜이 둘 이상 존재한는 경우 필요 

---

## 02-2: 윈도우 기반에서 이해 및 확인하기 

- `SOCKET socket(int af, int type, int protocol);`
    - 성공 시 소켓 핸들(정수), 실패 시 INVALID_SOCKET(하나의 상수) 반환 

---

# Chapter 3: 주소체계와 데이터 정렬 
## 03-1: 소켓에 할당되는 IP 주소와 PORT 번호 

- 인터넷 주소: IPv4, IPv6 

- 클래스 별 네트워크 주소와 호스트 주소의 경계 
    - A class: 0 ~ 127 (0b0으로 시작)
    - B class: 128 ~ 191 (0b10으로 시작)
    - C class: 192 ~ 223 (0b110으로 시작)

- 소켓의 구분에 활용되는 PORT 번호 
    - 소켓 구분에 사용됨 (동일한 PORT번호 X)
    - PORT 번호를 활용하여 데이터를 소켓에 적절히 분배하여 전달 
    - TCP 소켓과 UDP 소켓 

- 데이터 전달을 위해서는 IP 주소뿐만 아니라 PORT 번호 까지 필요하다.

---

## 03-2: 주소정보의 표현 

- IPv4 기반의 주소표현을 위한 구조체 

```c
struct sockaddr_in  // bind 함수 주소정보 전달 용도 
{
    sa_family_ t    sin_family;     // 주소체계   
    unit16_t        sin_port;       // 16비트 TCP/UDP PORT 번호 
    struct in_addr  sin_addr;       // 32비트 IP주소 
    char            sin_zeor[8]     // 사용되지 않음 (0으로 채워져 있어야 함)
}

struct in_addr  
{
    in_addr_t   s_addr; // 32비트 IPv4 인터넷 주소  
}
```

---

## 03-3: 네트워크 바이트 순서와 인터넷 주소 변환 

- 바이트 순서와 네트워크 바이트 순서 
    - 빅 엔디안: 상위 바이트 값을 작은 번지수에 저장하는 방식 
    - 리틀 엔디안: 상위 바이트 값을 큰 번지수에 저장하는 방식 

- 네트워크 바이트 순서 = 빅 엔디안 방식으로 통일!

- 바이트 순서의 변환 
    - 바이트 순서의 변환을 돕는 함수 
        - `unsigned short htons(unsigned short);` : short형 데이터를 호스트 바이트 순서에서 네트워크 바이트 순서로 변환 
        - `unsigned short ntohs(unsigned short);` : short형 데이터를 네트워크 바이트 순서에서 호스트 바이트 순서로 변환 
        - `unsigned long htonl(unsigned short);` : long
        - `unsigned long htohl(unsigned short);` : long

---

## 03-4: 인터넷 주소의 초기화와 할당 

- 문자열 정보를 네트워크 바이트 순서의 정수로 변환하기 
    - `in_addr_t inet_addr(const char *string);`
        - 문자열로 표현된 IP주소를 32비트 정수형으로 변환하는 함수
        - 성공 시 빅 엔디안으로 표현된 32비트 정수 값, 실패 시 INADDR_NONE 반환 

    - `int inet_aton(const cahr *string, struct in_addr *addr);`
        - int_addr()과 같은 역할 
        - `string`을 변환하여 `in_addr`에 저장 
        - 성공 시 1, 실패 시 0을 반환 

    - `char *inet_ntoa(struct in_addr adr);`
        - 네트워크 바이트 순서로 정렬된 IP주소를 문자열 형태로 변환(십진수)
        - 성공 시 변환된 무자열 주소의 값, 실패 시 -1 반환 

- 인터넷 주소의 초기화 

```c
struct sockaddr_in addr;
char *serv_ip="211.217.168.13";         // IP 주소 문자열 선언
char *serv_port="9190";                 // PORT 번호 문자열 선언 
memset(&addr, 0, sizeof(addr));         // 구조체 변수 addr의 모든 멤버 0으로 초기화 
addr.sin_addr.s_addr=inet_addr(serv_ip);// 문자열 기반의 IP 주소 초기화 
addr.sin_port=htons(atoi(serv_port));   // 문자열 기반의 PORT 번호 초기화 
```

- 클라이언트의 주소정보 초기화 
    - sockaddr_in 구조체 변수를 선언해서 이를 연결할 서버 소켓의 IP와 PORT qjsghfh chrlghkgksekdma connect 함수 호출

- INADDR ANY
    - 매번 서버의 IP 주소를 입력하는 것이 귀찮을 때 

```c
struct sockaddr_in addr;        
char *serv_port="9190";               
memset(&addr, 0, sizeof(addr));         
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=inet_addr(INADDR_ANY);
addr.sin_port=htons(atoi(serv_port));   
```

- 소켓에 인터넷 주소 할당하기 
    - bind() 함수를 사용하여 할당
    - `int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);`
        - sockfd: 주소정보를 할당할 소켓의 파일 디스크립터
        - myaddr: 할당하고자 하는 주소정보를 지니는 구조체 변수의 주소 값
        - 두 번째 인자로 전달된 구조체 변수의 길이정보

```c 
bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
```

---

## 03-5: 윈도우 기반으로 구현하기 

- 윈도우에서 소켓에 인터넷 주소 할당하기 

```c
SOCKET servSock;
struct sockaddr_in servAddr;
char *servPort="9109";

// 서버 소켓 생성 
servSock = socket(PF_INET, SOCK_STREAM, 0);

// 주소정보 초기화 
memset(&servAddr, 0, sizeof(servAddr));         
servAddr.sin_family=AF_INET;
servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
servAddr.sin_port=htons(atoi(servPort));  

// 주소ㅈ어보 할당 
bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr));
```

- WSAStringToAddress % WSAAdrdressToString
    - inet_ntoa, inet_addr 함수와 기능이 같으나 다양한 프로토콜에 적용이 가능 
    
    - `INT WSAStringToAddress(LPTSTR AddressString, INT AddressFamily, LPWSAPROTOCL_INFO lpProtocolInfo, LPSOCKADDR lpAddress, LPINT lpAddressLength);`

        - 성공 시 0, 실패 시 SOCKET_ERROR 반환 
        - AddressString: IP와 PORT 번호를 담고 있는 문자열의 주소 값
        - AddressFamily: 첫 번째 인자로 전달된 주소정보가 속하는 주소체계 정보 
        - lpProtocolInfo: 프로토콜 프로바이더 설정 (NULL)
        - lpAddress: 주소정보를 담은 구조체 변수의 주소 값
        - lpAddressLength: 네 번째 인자로 전달된 주소 값의 변수 크기를 담고 있는 변수의 주소 값

    -  `INT WSAAddressToString(LPSOCKADDR lpAddress, DWORD dwAddressLength, LPWSAPROTOCL_INFO lpProtocolInfo, LPTSTR lpszAddressString, LPWORLD lpdwAddressStringLength);`

        - 성공 시 0, 실패 시 SOCKET_ERROR 반환

---

# Chapter 4: TCP 기반 서버/ 클라이언트 1

## 04-1: TCP와 UDP에 대한 이해 

- TCP/IP 프로토콜 스택 

- ![TCP/IP프로토콜스택](https://img1.daumcdn.net/thumb/R800x0/?scode=mtistory2&fname=https%3A%2F%2Ft1.daumcdn.net%2Fcfile%2Ftistory%2F194DAA384F97E42D11)

    - 네 개의 계층으로 나뉨 (계층화)

- LINK 계층: LAN, WAN, MAN과 같은 네트워크 표준과 관련된 프로토콜을 정의하는 영역 

- IP 계층: 목적지로 데이터를 전송하기 위한 경로 결정 (Internet Protocol)
    - 비 연결지향적이며 신뢰할 수 없는 프로토콜 
    - 오류발생에 대한 대비 X

- TCP/UDP 계층: IP 계층에서 알려준 경로정보를 바탕으로 데이터의 실제 송수신 담당 (전송 계층)
    - TCP: 신뢰성 있는 데이터의 전송 담당. IP의 단점을 보완(재전송)
        - 확인절차를 걸쳐서 신뢰성 없는 IP에 신뢰성을 부여한 프로토콜 

APPLICATION 계층: 클라이언트와 서버 간의 데이터 송수신에 대한 약속을 정하는 계층 

---

## 04-2: TCP 기반 서버, 클라이언트 구현 

- TCP 서버에서의 기본적인 함수 호출 순서 
    - socket() -> bind() -> listen() -> accept -> read()/write() -> close()

- TCP 클라이언트의 기본적인 함수 호출 순서 
    - socket() -> connect() -> read()/write() -> close()

- TCP 기반 서버, 클라이언트 함수호출 관계 

![함수호출관계](https://postfiles.pstatic.net/MjAxOTAzMjRfMTEy/MDAxNTUzNDA3MjE0NTg0.Irj-pz4bmXU9oOfjl4XlGbiKcVnGNxlLYCuYLQcozXMg.zuyg2mHXJD7Joca3Stv5nbBhCD7RdfR6J5p7Sv5cvcEg.PNG.ihp0001/image.png?type=w773)
    
---

## 04-3: Iterative 서버, 클라이언트 구현 

- Iterative 서버의 구현 : 계속해서 들어오는 클라이언트의 연결요청을 수락하기 위해서 

![Iterative](https://lh3.googleusercontent.com/proxy/NaFmjnf_WWoG8jI1rqJO-2FYmme-WEIndv5fPTwRi3vVFdRG3rv9g3SpIQ3j42x-MFWk2KxftoqTBfFpAv-FPcoMz9_c7JTAHD8DMMGQ6egtVVQT6v2io2XZlZnfYFN6HJuAHjIyCIfXMwCWdG16wWW0AYiopkQa6yq0iqEruFtclNfAQbWhqwA5L6j2E0RM6SuZZaFRb5sl1p0775z2XkoX4WM_8vL84_TdWAWebWq2w9T3p6QYR3PQ9LqMYlNWnH53JxuoZ711GnRGhqQsKtLJ71aa4bHrEBnj)

- Iterative 에코 서버, 에코 클라이언트 
    - 프로그램 기본 동작방식 
        1. 서버는 한 순간에 하나의 클라이언트와 연결되어 에코 서비스 제공 
        2. 총 다섯 개의 클라이언트에게 순차적으로 서비스 제공하고 종료
        3. 클라이언트는 프로그램 사용자로부터 문자열 데이터를 입력받아 서버에 전송 
        4. 서버는 전송받은 데이터를 클라이언트에 재전송 (에코)
        5. 에코는 클라이언트가 Q를 입력할 때까지 계속 

- 에코 클라이언트의 문제점: 문자열 길이가 길 때 여러 개의 조각으로 나눠서 클라이언트에 전송, 이 과정에서 모든 조각이 클라이언트에게 전송되지 않았음에도 불구하고 클라이언트는 read 함수를 호출할 수 있음 

---

## 04-4: 윈도우 기반으로 구현하기 
- 윈도우 기반의 에코 서보와 에코 클라이언트 

---

# Chapter 5: TCP 기반 서버/클라이언트 2

## 05-1: 에코 클라이언트의 완벽 구현 
- 에코 클라이언트 문제의 해결책: 데이터 크기를 미리 알고 있으므로 데이터 크기를만큼 수신할 때까지 read 함수 호출 
- 어플리케이션 프로토콜의 정의 

---

## 05-2: TCP의 이론적인 이야기 

- TCP 소켓에 존재하는 입출력 버퍼 
    - 입출력 버퍼는 TCP 소켓 각각에 대 별도로 존재
    - 입출력 버퍼는 소켓 생성시 자동으로 생성 
    - 소켓을 닫아도 출력버퍼에 남아있는 데이터는 계속 전송
    - 소켓을 닫으면 입력버퍼에 남아있는 데이터 소멸 

- TCP의 내부 동작 원리1: 상대 소켓과의 연결
- TCP의 내부 동작 원리2: 상대 소켓과의 데이터 송수신 
- TCP의 내부 동작 원리3: 상대 소켓과의 연결 종료 

---

## 05-3: 윈도우 기반으로 구현하기 

---

# Chapter 6: UDP 기반 서버/클라이언트
## 06-1: UDP에 대한 이해 

- UDP 소켓의 특성: 신뢰할 수 없는 전송방법을 제공하지만 간결한 구조로 설계 되어 있음.(성능이 좋음)
    - 흐름제어가 없음 

- UDP의 내부 동작원리:

![UDP](https://t1.daumcdn.net/cfile/tistory/225E4B4255C1B74621)

- UDP의 효율적 사용 

---

## 06-2: UDP 기반 서버.클라이언트의 구현 

- UDP에서의 서버와 클라이언트는 연결되어 있지 않다.
- UDP에서는 서버건 클라이언트건 하나의 소켓만 있으면 된다.
- UDP 기반의 데이터 입출력 함수 
    - `ssize_t sendto(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen);`
        - 성공 시 전송된 바이트 수, 실패 시 -1 반환 

    - `ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);`
        - 성공 시 수신한 바이트 수, 실패 시 -1 반환 

- UDP 기반의 에코 서버와 에코 클라이언트 
- UDP 클라이언트 소켓의 주소 정보 할당: sendto 함수 호출 이전, bind 함수를 호출하여 할당

---

## 06-3: UDP의 데이터 송수신 특성과 UDP에서의 connect 함수 호출 

- 데이터의 경계가 존재하는 UDP 소켓: 입출력함수의 호출횟수가 큰 의미를 가짐(입력, 출력 함수 호출 횟수 동일)

- connected UDP 소켓, unconnected UDP 소켓 
    - unconnected 소켓: 목적지 정보 등록 X
    - connected 소켓: 목적지 정보 등록 O

- connected UDP 소켓 생성 
    - `connect(sock, (struct sockaddr*)&adr, sizeof(adr));`

---

## 06-4: 윈도우 기반으로 구현하기 
- `int sendto(SOCKET s, const char* buf, int len, int flags, const struct sockaddr* to, int tolne);`
    - 성공 시 전송된 바이트 수, 실패 시 SOCKET_ERROR 반환 
- `int recvfrom(SOCKET s, char *buf, int len, int flags, struct sockaddr *from, int *fromlen);`
    - 성공 시 수신한 바이트 수, 실패 시 SOCKET_ERROR 반환 

----

# Chapter 7: 소켓의 우아한 연결종료
## 07-1: TCP 기반의 Half-close

- 일반적인 연결종료의 문제점: 연결종료 후 데이터 수신과 관련된 함수의 호출 자체 불가능 
    - 문제점 해결을 위해 일부만 종료 (Half-close)

- 소켓과 스트림 
    - 스트림: 소켓을 통해 호스트가 연결되어 상호 간의 데이터 송수신이 가능한 상태 

- 우아한 종료를 위한 shutdown 함수(Half-close)
    - `int shutdown(int sock, int howto);`
        - 성공 시 0, 실패 시 -1 반환
        - howto: 종료 방법 

## 07-2: 윈도우 기반으로 구현하기 
- `int shutdown(SOCKET sock, int howto);`
    - 성공시 0, 실패 시 SOCKET_ERROr 반환 

---

# Chapter 8: 도메인 이름과 인터넷 주소 
## 08-1: Domain Name System

- 도메인 이름이란? IP주소는 기억하기 쉽지 않으므로 IP 주소 대신에 좋은 형태의 도메인 이름을 부여함.

- DNS 서버: 도메인 이름을 IP 주소로 변환 담당 

---

## 08-2: IP주소와 도메인 이름 사이의 변환 

- 프로그램상에서 도메인 이름을 쓸 필요가 있는가? 
    - 주소정보가 바뀔 때마다 IP 주소와 PORT번호를 바꿔 컴파일 하려면 너무 번거로움 => Domain name 사용

- 도메인 이름을 이용해서 IP주소 얻어오기 
    - `struct hostent *gethostbyname(const char *hostname);`
        - 성공 시 hostent 구조체 변수의 주소 값, 실패 시 NULL 포인터 반환 

```c
struct hostent
{
    char *h_name;       // official name 
    char **h_aliases;   // alias list
    int h_addrtype;     // host address type
    int h_length;       // address length
    char **h_addr_list  // address list
}
```

- IP 주소를 이용해서 도메인 정보 얻어오기 
    - `struct hostent *gethostbyaddr(const char *addr, socklen_t len, int family);`

---

## 08-3: 윈도우 기반으로 구현하기 

- `struct hostent *gethostbyname(const char *name);`
- `struct hostent *gethostbyaddr(const char *addr, int len, int type);`

---
# Chapter 9: 소켓의 다양한 옵션 
## 09-1: 소켓의 옵션과 입출력 버퍼의 크기

- 소켓의 다양한 옵션 

![소켓옵션](https://img1.daumcdn.net/thumb/R720x0.q80/?scode=mtistory2&fname=http%3A%2F%2Fcfile2.uf.tistory.com%2Fimage%2F256DF5375299D6062A3FFE)

- getsockopt & setsockopt
    - `int getsockopt(int sock, int level, int optname, void *optval, sockelen_t *optlne);`
        - 성공 시 0, 실패 시 -1 반환 

    - `int setsocketopt(int sock, int level, int optname, const void *optval, sockeln_t optlen);`
        - 성공 시 0, 실패 시 -1 반환 

- SO_SNDBUF & SO_RCVBUF

---

## 09-2: SO_REUSEADDR

- 주소 할당 에러 발생 

- Time-wait 상태

![Time-wait](https://lh3.googleusercontent.com/proxy/lRmRZWZL6Noqrl_vi5SXhPmE51IiF_CF9_1eGvZUdX_VH3nUs4AU-ppMzpLqbGfDRyIJ0Wb_IH4dCyRFyZstkqWZneAcy-xx-BEGizPZEEatbgScTEXSjmXz8cT7o1x33qubmMdyOK4XwjeZr3W92AXIz8CJhSk5)

- 주소의 재할당 

![Time-wait](https://lh3.googleusercontent.com/proxy/a_HrI7_tpjwXPhzk5Id9IT1PGX43hLcovxKZKgfdVHTyXfhzE_1LX9qGRHfzKOpdbbVnKWXu2OWX5ER4Hvm82G7L7I_je0h32dnK9wm9KcsbJ8U5Ok8obktm5VZbPavR3Hz3iZFNl8nff6t8lidhrEcv_Stnqv1FhA)

---

## 09-3: TCP_NODELAY

- Nalge 알고리즘: 네트워크 상에서 돌아다니는 패킷들의 흘러넘침을 막기 위 고안된 알고리즘 
    - 전송한 데이터에 대한 ACK를 받아야만 다음 데이터 전송 가능 

## 09-4: 윈도우 기반으로 구현하기 
- `int getsockopt(SOCKET sock, int level, int optname, char *optval, int *optlen);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환

- `int setsocket(SOCKET sock, int level, int optname, char *optval, int *optlen);`
    - 성공 시 0, 실패 시 SOCKET_ERROR 반환 
