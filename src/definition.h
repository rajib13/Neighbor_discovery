//#ifndef DEFINTION_H
//#define DEFINITION_H

#define MAXM_MESSAGE_COUNT 10
#define WILL_DEFAULT 3
#define MAC_LENGTH 4
#define NEIGHBORTYPE 6
#define LINKTYPE 7
#include <string>
#include <netinet/in.h>
#include <bitset>
//#include "IPAddr.h"

using namespace std;
/*
typedef struct linkTable
{
char ownIntrFaceAddr[MAC_LENGTH];
char neighborIntrFaceAddr[MAC_LENGTH];
short int symmetricTime;
short int assymetricTime;
short int lostTime;
} linkTable;
linkTable linkTableStruct[20];

typedef struct dataProcessor
{
char      reserved13Bit[2];
char      hTime[1];
char      willingness[1];
bitset<8>      linkCode;
char      reserved8Bit[1];
uint16_t  linkMessageSize;
char      *neighborIntFaceAddr;
} dataProcessor;
dataProcessor dataProcessorStruct;


typedef struct msgProcessor
{
char      msgType[1];
char      vTime[1];
uint16_t  msgSize;
char      originatorAddr[4];
char      timeToLive[1];
char      hopCount[1];
uint16_t  msgSqNo;
struct    dataProcessor assynchronousData;
struct    dataProcessor synchronousData;
} msgProcessor;
msgProcessor msgProcessorStruct;

typedef struct olsrPacketProcessor
{
uint16_t  packetLength;
uint16_t  packetSqNo;
struct    msgProcessor helloMessage;
} olsrPacketProcessor;
olsrPacketProcessor olsrPacketProcessorStruct;
*/

typedef struct ipUdpPacket {
    uint8_t versionIHL = 0x45;
    uint8_t typeOfService = 0;
    uint16_t totalLength = 28;
    uint16_t identification = 0;
    uint16_t flagsOffset = 0;
    uint8_t timeToLive = 1;
    uint8_t protocol = 138;
    uint16_t headerChecksum = 0;
    uint32_t srcAddress;
    uint32_t dstAddress;
    uint16_t sourcePort = 698;
    uint16_t destinationPort = 698;
    uint16_t length = 28;
    uint16_t checksumUdp = 0;
}ipUdpPacket;
ipUdpPacket ipUdpPacketProcessor;

 typedef struct olsrPacket{
    uint16_t packetLength = 24;
    uint16_t packetSequenceNumber = 1;
    uint8_t  messageType = 1;
    uint8_t  vTime = 6;
    uint16_t msgSize = 12;
    uint32_t srcAddr;
    uint8_t  timeToLive = 1;
    uint8_t  hopCount = 0;
    uint16_t msgSequenceNumber = 1;
 }olsrPacket;
 olsrPacket olsrPacketProcessor;

 typedef struct olsrHello{

    uint16_t frontReserved = 0;
    uint8_t hTime = 0;
    uint8_t willingness = 3;
    uint8_t midReserved = 0;
    uint8_t linkCode = 0x6;
    uint16_t linkMessageSize;
    std::vector<IPAddr> mprNeighbor, oneHopNeighbour;

 }olsrHello;
 olsrHello olsrHelloProcessor;

  typedef struct oneHopNeighbors{
	  IPAddr neighborAddr;
	  time_t validTimeUpto;
 }oneHopNeighbors;
 oneHopNeighbors oneHopNeighborsListArray[10];


//#endif
