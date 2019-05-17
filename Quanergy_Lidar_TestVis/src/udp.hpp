/*
 * udp.hpp
 *
 *  Created on: 17 May 2018
 *      Author: Yun Wu
 *  log:
 *  	2018-05-17 create the udp class
 */

#ifndef SRC_HEADERS_UDP_HPP_
#define SRC_HEADERS_UDP_HPP_

#include "common.hpp"
#include "socket.hpp"

#define UDP_BUFFER_SIZE 4096

class udp{
public:
    pthread_t udpserver_id=0;
    pthread_t udpclient_id=0;
    pthread_mutex_t udpAccessMuxid;
    bool server_onoff=false;
    udp();
    udp(char *ipaddr_tx);
    udp(int pn_tx, char *ipaddr_tx);
    udp(int pn_tx, char *ipaddr_tx, char *d_tx, int t_size);
    udp(int pn_rx, char *ipaddr_rx, int r_size);
    ~udp();
    int getRxPort();
    int getTxPort();
    int getRxDataSize();
    int getTxDataSize();
    char *getRxIP();
    char *getTxIP();
    char *getRxData();
    char *getTxData();
    void setServerOnOff(bool flag);
    void setRxPort(int p);
    void setTxPort(int p);
    void setRxIP(char *ip);
    void setTxIP(char *ip);
    void setRxDataW(char *d);
    void setTxDataW(char *d);
    void setRxDataR();
    void setTxDataR();
    void setRxDataSize(int len);
    void setTxDataSize(int len);
    void *rx();
    void *tx();
    void *rx2();
    void *tx2();
private:
    int port_num_rx=9527;
    int port_num_tx=9527;
    char ip_addr_tx[128]={};
    char ip_addr_rx[128]={};
protected:
    int data_size_rx = 0;
    int data_size_tx = 0;
    char *data_rxw = NULL;
    char *data_txw = NULL;
    char *data_rxr = NULL;
    char *data_txr = NULL;
};
void *udp_server_thread(void *p);
void *udp_client_thread(void *p);


#endif /* SRC_HEADERS_UDP_HPP_ */
