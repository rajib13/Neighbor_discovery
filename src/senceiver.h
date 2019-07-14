#include <sys/socket.h>
#include <sys/types.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <fstream>
#include <mutex>

#include "sock.h"
#include "OLSRPacketFactory.h"
#include "OLSRHelloFactory.h"
#include "IPAddr.h"
#include "ConcreteOLSRPacketFactory.h"
#include "ConcreteOLSRHelloFactory.h"
#include "ConcreteIPUDPPacketFactory.h"
#include "OLSRHello.h"
#include "IPUDPPacketFactory.h"
//#include "definition.h"



using namespace std;

//Declaration of some global variables
int linkTableElement = 0;
int oneHopElement = 0;
int twoHopElement = 0;
int messageSeqNo = 1;
int pcktSeqNumber = 1;
int numberOfOneHopNeighbor = 0;
int g_i = 0;
std::mutex g_i_mutex;

unsigned char * buffer;

//To determine current time
string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

//To write log into a text file
void writeToLog(char * src, char* oneHopNeighMac, char* twoHopNeighMac)
{

  ofstream logFile ("log.txt", ios_base::app|ios_base::out); // for opening in append mode
  if (logFile.is_open())
  {
    logFile << currentDateTime()<<"||One Hop: "<<oneHopNeighMac<<"|Two Hop: "<<twoHopNeighMac;
    logFile << "\n";
    logFile.close();
  }
  else cout << "Unable to open file";

}

void initializeLogFile(string description, IPAddr localAddress){\
	ofstream log;
	//:: Declared Time Variables for Timestamping
	time_t currTime;
	struct tm * timeinfo;
	char buffer [80];

	time (&currTime);
	timeinfo = localtime (&currTime);

	//:: Set time format to be ( HH : MM : SS AM/PM)
	if( description != "Log")
	strftime (buffer,80,"At %I:%M:%S %p --> ",timeinfo);

	log.open("log.txt", ofstream::out | ofstream::app);
	if( !log.is_open() ){
				cout << "Failed to Open Log File for writing." << endl;
			}
	else{
		
	     if( description == "Log")
		{
			log << "Team : Pi3"<<endl;
			log <<"Team Member(s): Shauli, Jesmin, Raj!b"<<endl;
			log << endl;
			log << "Log Activity For Pi#:" << " " << localAddress.toString()<<endl;
	 		log <<"*********************************************************" << endl;	
		}		
	     else
		{
		log << buffer;
		log << description << " " << localAddress.toString() << endl;
		
		}	
	}

	log.close();		
}

void writeToLogFile(){
	ofstream log;		

	//:: Declared Time Variables for Timestamping
	time_t currTime;
	struct tm * timeinfo;
	char buffer [80];

	time (&currTime);
	timeinfo = localtime (&currTime);

	//:: Set time format to be ( HH : MM : SS AM/PM)
	strftime (buffer,80,"At %I:%M:%S %p --> ",timeinfo);
		
	log.open("log.txt", ofstream::out | ofstream::app);			
		if( !log.is_open() ){
			cout << "Failed to Open Log File for writing." << endl;
		}
		else{
			//cout << "Processing Buffer...." << endl;
			//:: Pass in Time stamp first
			log << buffer;			
			
			//:: Pass In Neighbor List from Vector
			log << "Current 1-hop Neighbor(s): ";
			for(int i = 0; i < numberOfOneHopNeighbor; i++){
				if( i == numberOfOneHopNeighbor-1)
					log << oneHopNeighborsListArray[i].neighborAddr.toString()<<endl;
				else
					log << oneHopNeighborsListArray[i].neighborAddr.toString()<<", ";
			}
			
			if(numberOfOneHopNeighbor == 0)
				//log << "EMPTY!!!!!!" << endl;	
					
			//:: Close the file
			log.close();
		}
}
//Receive part
  void receive(){
printf("##########Thread 2: Receiver thread is Started...\n");
  struct Ifconfig ifc;
  init(&ifc);

  while(1) {
  int i;

  // setting up the socket address structure for the source of the packet
  struct sockaddr_ll from;
  socklen_t fromlen = sizeof(from);
  // setting up the buffer or receiving
  unsigned char * buf ;//= (char*)malloc(ifc.mtu);
  buf = new unsigned char [1000];
  if (buf == NULL)
    die("Cannot allocate receiving buffer\n");

    int recvlen = recvfrom(ifc.sockd, buf, ifc.mtu,0 /*MSG_DONTWAIT*/, (struct sockaddr*) &from, &fromlen);
IPAddr rcvdNeighbours;
    if (recvlen < 0) {
     if(errno!=EAGAIN)
       std::cout<<"Cannot receice data :\n"<<strerror(errno)<<std::endl;
    } else if (recvlen < 80) //Here, we are working for less than 50 of the packet length. The packet which contain more than 50
// will not be processed.
{
IPAddr myPI(3,1);




IPAddr twoHopNeighbors;
      memcpy(&rcvdNeighbours, buf+36, sizeof(rcvdNeighbours));
if(myPI.toString() != rcvdNeighbours.toString())
{
      printf("Received %d bytes from ", recvlen);
      for (i=0; i<from.sll_halen-1; i++)
	  printf("%02X:", from.sll_addr[i]);
      printf("%02X >\n\n", from.sll_addr[from.sll_halen-1]);
	  printf("Some Crucial Received Values:\n vTime: %d\n", buf[33]);
	  printf("Total IPUDP Packet Length:  %d\n",buf[2]);
	  printf("Total OLSR Packet Length: %d\n",buf[28]);
	  cout<<"Originator Address: "<<rcvdNeighbours.toString()<<endl;
	initializeLogFile("Received Packet From:", rcvdNeighbours);



    time_t now = 0,validTimeUpto;
    time(&now);

    validTimeUpto = now + (6);
    int j = 0;
	std::lock_guard<std::mutex> lock(g_i_mutex); ++g_i;
    for(j=0; j<numberOfOneHopNeighbor; j++)
    {
        if((oneHopNeighborsListArray[j].neighborAddr) == (rcvdNeighbours))
        {
            oneHopNeighborsListArray[j].validTimeUpto = validTimeUpto;
            break;
        }
    }

    if(j == numberOfOneHopNeighbor)
    {
        oneHopNeighborsListArray[numberOfOneHopNeighbor].neighborAddr = rcvdNeighbours;
        oneHopNeighborsListArray[numberOfOneHopNeighbor++].validTimeUpto = validTimeUpto;
	writeToLogFile();
    }
}
 }

}
destroy(&ifc);
}


//Send  Message portion
void sendMessage()
{
    struct Ifconfig ifc;
    init(&ifc);
    printf("##########Thread 1: Sender thread is Started...\n");

    buffer = new unsigned char [1000];
    //shared library
    static std::shared_ptr<IPUDPPacketFactory> iPuDPFactory =
    std::make_shared<ConcreteIPUDPPacketFactory>();
    static std::shared_ptr<OLSRPacketFactory> factory =
    std::make_shared<ConcreteOLSRPacketFactory>();
    static std::shared_ptr<OLSRHelloFactory> helloFactory =
    std::make_shared<ConcreteOLSRHelloFactory>();

    //objects
    std::shared_ptr<IPUDPPacket> ipudp;
    std::shared_ptr<OLSRPacket> olsrP;
    std::shared_ptr<OLSRHello> helloPacket;

     if (iPuDPFactory){
        ipudp = iPuDPFactory->createIPUDPPacket();
     }

     if (factory){
        olsrP = factory->createOLSRPacket();
     }

     if (helloFactory) {
        helloPacket = helloFactory->createOLSRHello();
     }
    //setupFactory();

    while(1)
    {

      printf("\n\nSending from ");
      /* print the MAC addr */
      int i;
      for (i=0; i<MACADDRLEN-1; i++)
        printf("%02X:", ifc.mac[i]);
      printf("%02X\n", ifc.mac[MACADDRLEN-1]);

      /* set-up destination structure in a sockaddr_ll struct */
      struct sockaddr_ll to;
      memset(&to, 0, sizeof(to)); /* clearing the structure, just in case */
      to.sll_family = AF_PACKET; /* always AF_PACKET */
      to.sll_ifindex = ifc.ifindex;
      to.sll_halen = MACADDRLEN;

      /* setup broadcast address of FF:FF:FF:FF:FF:FF */
      for (i=0; i<MACADDRLEN; i++)
        to.sll_addr[i] = 0xff;

      IPAddr src(3,1), dst(255,255), neigh(1,1), neigh2(4,1);
      olsrHelloProcessor.oneHopNeighbour.push_back(neigh);
      olsrHelloProcessor.oneHopNeighbour.push_back(neigh2);

      ipudp->setHeader(buffer, 28, src, dst, ipUdpPacketProcessor.timeToLive, 11);
	std::lock_guard<std::mutex> lock(g_i_mutex); ++g_i;
for(int j=0;j<numberOfOneHopNeighbor; j++)
{
	olsrHelloProcessor.oneHopNeighbour.push_back(oneHopNeighborsListArray[j].neighborAddr);
}

      olsrP->setHeader(buffer, olsrPacketProcessor.packetLength,olsrPacketProcessor.messageType,src,olsrPacketProcessor.timeToLive,olsrPacketProcessor.hopCount,olsrPacketProcessor.packetSequenceNumber,olsrPacketProcessor.msgSequenceNumber,olsrPacketProcessor.msgSize);
      helloPacket->setHeader(buffer, 7,olsrHelloProcessor.mprNeighbor,olsrHelloProcessor.oneHopNeighbour);

      int sentlen = sendto(ifc.sockd, buffer, sizeof(ipUdpPacketProcessor)+sizeof(olsrPacketProcessor)+sizeof(olsrHelloProcessor), 0, (struct sockaddr*) &to, sizeof(to));
      printf("%d bytes is Broadcasted.\n", sentlen);

     this_thread::sleep_for (chrono::seconds(3));
    }

destroy(&ifc);

}

void neighborEraser()
{
printf(" Thread 3: Neighbor Processor thread is Started...\n");
 while(1) {
  time_t now = 0;
  time(&now);

  for(int i =0; i<numberOfOneHopNeighbor; i++)
  {
      if(oneHopNeighborsListArray[i].validTimeUpto <= now)
      {
          for(int j= i; j<numberOfOneHopNeighbor-1; j++)
          {
              oneHopNeighborsListArray[j].neighborAddr = oneHopNeighborsListArray[j+1].neighborAddr;
              oneHopNeighborsListArray[j].validTimeUpto = oneHopNeighborsListArray[j+1].validTimeUpto;
          }
          numberOfOneHopNeighbor--;
writeToLogFile();
printf("Removed One neighbor\n");
      }

  }

this_thread::sleep_for (chrono::seconds(1));
}
}





