// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacket interface: creates the OLSR header

#ifndef __OLSRPACKETTESTCASES_H
#define __OLSRPACKETTESTCASES_H

#include <cstring>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include <netinet/in.h>
#include <bitset>
#include "OLSRPacket.h"
#include "ConcreteOLSRPacketFactory.h"


using namespace std;

class OLSRPacketTestCases : public OLSRPacket {
public:
 uint8_t vTime =6;

	int setHeader(unsigned char * buf, int buflen, int msg_type, IPAddr origin,
                                            int TTL, int hop_count,
												uint16_t psn, uint16_t msn, int msglen) {
        int offset = 28;
       // we clear the buffer first!
		*(reinterpret_cast<uint16_t*>(buf+offset)) =  buflen;  // set the packet
		*(reinterpret_cast<uint16_t*>(buf+offset+2)) =  psn;
		*(reinterpret_cast<uint8_t*>(buf+4+offset)) =  msg_type;  // set the packet
		*(reinterpret_cast<uint8_t*>(buf+5+offset)) =  vTime;
		*(reinterpret_cast<uint16_t*>(buf+6+offset)) =  msglen;  // set the packet
		*(reinterpret_cast<uint32_t*>(buf+8 +offset)) =  origin.to32bWord();
		*(reinterpret_cast<uint8_t*>(buf+12+offset)) =  TTL;  // set the packet
		*(reinterpret_cast<uint8_t*>(buf+13+offset)) =  hop_count;
		*(reinterpret_cast<uint16_t*>(buf+14+offset)) =  msn;
																										// length field
		  // the size of the header in bytes
return 1;
	}

		bool isValid(unsigned char * buf, int buflen, HeaderInfo & hi) {
         if (buflen > 50)
         {
            return false;
         }

		hi.headerLen = buflen ;
		hi.dataLen = buflen;
        hi.org = IPAddr(169, 254, 3, 1);

		return true;

	}

};

#endif
