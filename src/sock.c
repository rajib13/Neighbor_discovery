#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <linux/wireless.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>


#include "sock.h"



void die(const char *msg) {
  printf(msg);
  exit(1);
}

/* ifp = output parameter: contains info about the wlan interface
   ready to be used in send/recv - creates socked, configures it in
   promiscuous mode, gets MAC addr and MTU of wlan, gets the interface
   index, and binds the socket to the wlan interface */
void init(struct Ifconfig * ifp) {
  if (ifp == NULL)
    return;
  struct Ifconfig ifc;

  /* create first the socket */
  /* raw version, construct the header as per Barbeau and Kranakis */
  /*ifc.sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));*/

  /* dgram version, header constructed by the library (see man 7 packet) */
  ifc.sockd = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));

  if (ifc.sockd < 0) {
    printf("Error opening raw socket\n");
    exit(1);
  }

  /* find the network device index */
  struct ifreq ifr;
  strcpy(ifr.ifr_name, "wlan0");
  if (ioctl(ifc.sockd, SIOGIFINDEX, &ifr) < 0)
    die("Error getting interface index\n");

  ifc.ifindex = ifr.ifr_ifindex;

  /* find the interface MAC address */
  if (ioctl(ifc.sockd, SIOCGIFHWADDR, &ifr) < 0)
    die("Can't get net interface addr\n");

  if (ifr.ifr_hwaddr.sa_family!=ARPHRD_ETHER) {
    die("not an Ethernet interface");
  }

  /* save the MAC addr */
  memcpy(ifc.mac, ifr.ifr_hwaddr.sa_data, MACADDRLEN);

  /* get the MTU */
  if (ioctl(ifc.sockd, SIOCGIFMTU, &ifr) < 0)
    die("Error getting the MTU\n");
  ifc.mtu = ifr.ifr_mtu;

  /* set promiscuous mode for the socket */
  struct packet_mreq mr;
  memset(&mr, 0, sizeof(mr));
  mr.mr_ifindex = ifc.ifindex;
  mr.mr_type = PACKET_MR_PROMISC;
  setsockopt(ifc.sockd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr));
  
	
  /* bind socket to interface */
  struct sockaddr_ll sll;
  memset(&sll, 0, sizeof(sll));  /* set struct to 0 */
  sll.sll_family = AF_PACKET;
  sll.sll_ifindex = ifc.ifindex;
  sll.sll_protocol = htons(ETH_P_ALL);
  if (bind(ifc.sockd, (struct sockaddr*) &sll, sizeof(sll)) < 0)
    die("Cannot bind the socket to the wlan interface\n");

  *ifp = ifc; /* returns the socket and interface info */
}  

/* close socket, set structure pointed to by parameter ifp to zero.
ifp can be NULL in which case no action is taken */
void destroy(struct Ifconfig * ifp) {
  if (ifp == NULL)
    return;
  close(ifp->sockd);
  memset(ifp, 0, sizeof(struct Ifconfig));
}

