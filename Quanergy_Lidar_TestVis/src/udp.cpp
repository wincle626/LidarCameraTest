/*
 * udp.cpp
 *
 *  Created on: 17 May 2018
 *      Author: Yun Wu
 *  log:
 *  	2018-05-17 create udp class functions
 */


#include "udp.hpp"

// constructor
udp::udp(){

}
udp::udp(char *ipaddr_tx){
    this->port_num_tx = 9527;
    strcpy(this->ip_addr_tx, ipaddr_tx);
    this->port_num_rx = 9527;
    strcpy(this->ip_addr_rx, (char*)"127.0.0.1");
    this->data_size_rx = 0;
    this->data_size_tx = 0;
    this->data_rxw = NULL;
    this->data_txw = NULL;
    this->data_rxr = NULL;
    this->data_txr = NULL;
#ifdef PRINT_DEFAUT_SETTING
    std::cout << "TX IP: " << this->ip_addr_tx << std::endl;
    std::cout << "TX Port: " << this->port_num_tx << std::endl;
    std::cout << "TX Data: " << this->data_txw << std::endl;
    std::cout << "RX Port: " << this->port_num_rx << std::endl;
#endif
}
udp::udp(int pn_tx, char *ipaddr_tx){
    this->port_num_tx = pn_tx;
    strcpy(this->ip_addr_tx, ipaddr_tx);
    this->port_num_rx = pn_tx;
    strcpy(this->ip_addr_rx, (char*)"127.0.0.1");
    this->data_size_rx = 0;
    this->data_size_tx = 0;
    this->data_rxw = NULL;
    this->data_txw = NULL;
    this->data_rxr = NULL;
    this->data_txr = NULL;
#ifdef PRINT_DEFAUT_SETTING
    std::cout << "TX IP: " << this->ip_addr_tx << std::endl;
    std::cout << "TX Port: " << this->port_num_tx << std::endl;
    std::cout << "TX Data: " << this->data_txw << std::endl;
    std::cout << "RX Port: " << this->port_num_rx << std::endl;
#endif
}
udp::udp(int pn_tx, char *ipaddr_tx, char *d_tx, int t_size){
    this->port_num_tx = pn_tx;
    strcpy(this->ip_addr_tx, ipaddr_tx);
    this->port_num_rx = pn_tx;
    strcpy(this->ip_addr_rx, (char*)"127.0.0.1");
    this->data_size_rx = t_size;
    this->data_size_tx = t_size;
    this->data_rxw = NULL;
    this->data_txw = (char*) realloc(this->data_txw, t_size*sizeof(char));
    this->data_rxr = NULL;
    this->data_txr = (char*) realloc(this->data_txr, t_size*sizeof(char));
    memcpy(this->data_txw, d_tx, t_size*sizeof(char));
#ifdef PRINT_DEFAUT_SETTING
    std::cout << "TX IP: " << this->ip_addr_tx << std::endl;
    std::cout << "TX Port: " << this->port_num_tx << std::endl;
    std::cout << "TX Data: " << this->data_txw << std::endl;
    std::cout << "TX Data Length: " << this->data_size_tx << std::endl;
#endif
}
udp::udp(int pn_rx, char *ipaddr_rx, int r_size){
    this->port_num_tx = pn_rx;
    strcpy(this->ip_addr_tx, ipaddr_rx);
    this->port_num_rx = pn_rx;
    strcpy(this->ip_addr_rx, ipaddr_rx);
    this->data_size_rx = r_size;
    this->data_size_tx = r_size;
    this->data_rxw = (char *) realloc(this->data_rxw, r_size*sizeof(char));
    memset( this->data_rxw, '\0', sizeof(char)*r_size );
    this->data_txw = NULL;
    this->data_rxr = (char *) realloc(this->data_rxr, r_size*sizeof(char));
    memset( this->data_rxr, '\0', sizeof(char)*r_size );
    this->data_txr = NULL;
#ifdef PRINT_DEFAUT_SETTING
    std::cout << "RX IP: " << this->ip_addr_rx << std::endl;
    std::cout << "RX Port: " << this->port_num_rx << std::endl;
    std::cout << "RX Data: " << this->data_rxw << std::endl;
    std::cout << "RX Data Length: " << r_size << std::endl;
#endif
}

// destructor
udp::~udp(){

}

// return the port number
int udp::getRxPort(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->port_num_rx;
}
int udp::getTxPort(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->port_num_tx;
}

// return the IP address
char *udp::getRxIP(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->ip_addr_rx;
}
char *udp::getTxIP(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->ip_addr_tx;
}

// return the rx/tx data
char *udp::getRxData(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->data_rxr;
}
char *udp::getTxData(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->data_txr;
}

int udp::getRxDataSize(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->data_size_rx;
}

int udp::getTxDataSize(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return this->data_size_tx;
}

// set the on switch of sever
void udp::setServerOnOff(bool flag){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    pthread_mutex_lock(&this->udpAccessMuxid);
    this->server_onoff = flag;
    pthread_mutex_unlock(&this->udpAccessMuxid);
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the port number
void udp::setRxPort(int p){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->port_num_rx = p;
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}
void udp::setTxPort(int p){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->port_num_tx = p;
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the rx IP address
void udp::setRxIP(char *ip){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    strcpy(this->ip_addr_rx, ip);
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the tx IP address
void udp::setTxIP(char *ip){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    strcpy(this->ip_addr_tx, ip);
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the transmiting data
void udp::setTxDataW(char *d){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->data_txw = (char*) realloc(this->data_txw, this->data_size_tx*sizeof(char));
    memcpy(this->data_txw, d, this->data_size_tx*sizeof(char));
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the received data
void udp::setRxDataW(char *d){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    //this->data_rxw = NULL;
    this->data_rxw = (char*) realloc(this->data_rxw, this->data_size_rx*sizeof(char));
    memcpy(this->data_rxw, d, this->data_size_rx*sizeof(char));
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the transmiting data
void udp::setTxDataR(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    //this->data_txr = NULL;
    this->data_txr = (char*) realloc(this->data_txr, this->data_size_tx*sizeof(char));
    memcpy(this->data_txr, this->data_txw, this->data_size_tx*sizeof(char));
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// set the received data
void udp::setRxDataR(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->data_rxr = (char*) realloc(this->data_rxr, this->data_size_rx*sizeof(char));
    memcpy(this->data_rxr, this->data_rxw, this->data_size_rx*sizeof(char));
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}


void udp::setRxDataSize(int len){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->data_size_rx = len;
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

void udp::setTxDataSize(int len){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    this->data_size_tx = len;
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
}

// receive data from specific UDP port
void *udp::rx(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other) , recv_len;
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    //si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_port = htons(this->getRxPort());
    if (inet_aton(this->getRxIP() , &si_me.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        perror("bind");
        exit(1);
    }

    //keep listening for data until the flag is off
#ifdef DEBUG
        std::cout << "Waiting for data..." << std::endl;
#endif
    int torevlen = this->getRxDataSize();
    char *toreceivedata = (char*) malloc(sizeof(char)*torevlen);
    int revlen = 0;
    while(torevlen>0){
        char data[UDP_BUFFER_SIZE];
        memset( data, '\0', sizeof(unsigned char)*UDP_BUFFER_SIZE );
        fflush(stdout);
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, data, UDP_BUFFER_SIZE, 0,
            (struct sockaddr *) &si_other, (socklen_t *)&slen)) == -1)
        {
            perror("recvfrom()");
            exit(1);
        }
        char* ip = inet_ntoa(si_other.sin_addr);
        int port = si_other.sin_port;
        this->setRxIP(ip);
        this->setRxPort(port);
#ifdef DEBUG
        //print details of the client/peer and the data received
        std::cout << "Received packet from " << ip
             << ":" << pn << std::endl;
        std::cout << "Data: " << data << std::endl;
#endif
        //pthread_mutex_lock(&this->udpAccessMuxid);
        //flag = this->server_onoff;
        //pthread_mutex_unlock(&this->udpAccessMuxid);
        if(recv_len>0){
            std::cout << "Receive Data Remain: " << torevlen << std::endl;
            std::cout << "Receive Data Size: " << recv_len << std::endl;
            //std::cout << "Receive Data: " << data << std::endl;
            memcpy(&toreceivedata[revlen],data,recv_len*sizeof(char));
            torevlen -= recv_len;
            revlen += recv_len;
        }
    }
    this->setRxDataW(toreceivedata);
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    close(s);
    return NULL;
}

// send data to specific IP address and port
void *udp::tx(){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(this->getTxPort());
    if (inet_aton(this->getTxIP() , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    //send the message
    this->setTxDataR();
    char *tosenddata = this->getTxData();
    int sendlen = this->getTxDataSize();
    int tosendlen = sendlen;

    while (tosendlen > 0)
    {
        char *data = NULL;
        fflush(stdout);
#ifdef DEBUG
    std::cout << "Send message ? (Enter) " << std::endl;
    getchar();
#endif
        if(tosendlen >= UDP_BUFFER_SIZE){
            data = (char*) realloc(data, UDP_BUFFER_SIZE*sizeof(char));
            memcpy(data,&tosenddata[sendlen-tosendlen],UDP_BUFFER_SIZE);
            if (sendto(s, data, UDP_BUFFER_SIZE , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                perror("sendto()");
                exit(1);
            }
        }
        else{
            data = (char*) realloc(data, tosendlen*sizeof(char));
            memcpy(data,&tosenddata[sendlen-tosendlen],tosendlen);
            if (sendto(s, data, tosendlen , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                perror("sendto()");
                exit(1);
            }
        }
        tosendlen -= UDP_BUFFER_SIZE;
        // usleep(10);
    }
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    close(s);
    std::cout << "exit function: " << __func__ << std::endl;
    return NULL;
}

// send data to specific IP address and port
void *udp::tx2(){

    UDPSocket sock;

    std::string servAddress = std::string(this->getTxIP()); // First arg: server address
    unsigned short servPort = (unsigned short)this->getTxPort();
    try {

        int tosendlen = this->getTxDataSize();
        int total_pack = 1 + (tosendlen - 1) / UDP_BUFFER_SIZE;

        //std::cout << total_pack << " send packages" << std::endl;

        /*int ibuf[1];
        ibuf[0] = total_pack;
        sock.sendTo(ibuf, sizeof(int), servAddress, servPort);*/

        int i;
        this->setTxDataR();
        char *tosenddata = this->getTxData();
        if(total_pack>1){
			for (i = 0; i < total_pack; i++){
				sock.sendTo( & tosenddata[i * UDP_BUFFER_SIZE],
						UDP_BUFFER_SIZE, servAddress, servPort);
				tosendlen = tosendlen - UDP_BUFFER_SIZE;
	        	//std::cout << i << "th sent package" << std::endl;
			}
			if(tosendlen>0){
				char buf[UDP_BUFFER_SIZE];
				memset(buf, '0', UDP_BUFFER_SIZE);
				memcpy(buf, &tosenddata[i * UDP_BUFFER_SIZE], tosendlen);
				sock.sendTo( buf, UDP_BUFFER_SIZE, servAddress, servPort);
				//std::cout << i << "th sent package" << std::endl;
			}
			/*sock.sendTo( & tosenddata[i * UDP_BUFFER_SIZE],
					tosendlen, servAddress, servPort);*/
        }else{
        	char buf[UDP_BUFFER_SIZE];
        	memcpy(buf, tosenddata, tosendlen);
			sock.sendTo( buf, UDP_BUFFER_SIZE, servAddress, servPort);
        }

    }catch (SocketException & e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    std::cout << "exit function: " << __func__ << std::endl;

    return NULL;
}

#define BUF_LEN 65540 // Larger than maximum UDP packet size

void *udp::rx2(){

    try {

        unsigned short servPort = this->getRxPort(); // First arg:  local port
        UDPSocket sock(servPort);

        char buffer[BUF_LEN]; // Buffer for echo std::string
        unsigned int recvMsgSize; // Size of received message
        std::string sourceAddress = std::string(this->getTxIP()); // Address of datagram source
        unsigned short sourcePort = servPort; // Port of datagram source

        /*do {
            recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
        } while (recvMsgSize > sizeof(int));
        int total_pack = ((int * ) buffer)[0];
        std::cout << "total size indicated by udp class: " << this->getRxDataSize() << std::endl;
        std::cout << "total size indicated by package header: " << total_pack << std::endl;*/
        int total_pack = 1 + (this->getRxDataSize() - 1) / UDP_BUFFER_SIZE;

        //std::cout << total_pack << " receive packages" << std::endl;

        char *longbuf = new char[UDP_BUFFER_SIZE * total_pack];
        for (int i = 0; i < total_pack; i++) {
            recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
            if (recvMsgSize != UDP_BUFFER_SIZE) {
                std::cerr << "Received unexpected size pack:" << recvMsgSize << std::endl;
                continue;
            }
            memcpy( & longbuf[i * UDP_BUFFER_SIZE], buffer, UDP_BUFFER_SIZE);
        	//if(i==total_pack-1)std::cout << i << "th received package" << std::endl;
        }
        this->setRxDataW(longbuf);
        free(longbuf);

    }catch (SocketException & e) {
        std::cerr << "got error: " << e.what() << std::endl;
        exit(1);
    }
    std::cout << "exit function: " << __func__ << std::endl;

    return NULL;
}

void *udp_server_thread(void *context){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
    ((udp *)context)->rx2();
#ifdef DEBUG
    std::cout << "the received data is: " << ((udp *)context)->getRxData() << std::endl;
#endif
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return NULL;
}

void *udp_client_thread(void *context){
#ifdef PRINT_FUNC
    std::cout << "enter function: " << __func__ << std::endl;
#endif
#ifdef DEBUG
    std::cout << "the transmitting data will be: " << ((udp *)context)->getTxData() << std::endl;
#endif
#ifdef DEBUG
    ((udp *)context)->setServerOnOff(false);
#endif
    ((udp *)context)->tx2();
#ifdef PRINT_FUNC
    std::cout << "exit function: " << __func__ << std::endl;
#endif
    return NULL;
}

