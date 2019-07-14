#ifndef __SOCK_H
#define __SOCK_H

/* length of MAC adress of the wlan card */
#define MACADDRLEN 6

/* wlan info */
typedef struct Ifconfig {
  int sockd;  /* socket descriptor */
  int ifindex;  /* net interface index, needed in bind */
  int mtu;
  unsigned char mac[MACADDRLEN];
} Ifconfig;

/* functions */

/* ifp = output parameter: contains info about the wlan interface
   ready to be used in send/recv - creates socked, configures it in
   promiscuous mode, gets MAC addr and MTU of wlan, gets the interface
   index, and binds the socket to the wlan interface */
void init(struct Ifconfig *ifp);

/* writes message msg to the console and terminates the program */
void die(const char *msg);

/* close socket, set structure pointed to by parameter ifp to zero.
ifp can be NULL in which case no action is taken */
void destroy(struct Ifconfig * ifp);
  
#endif

