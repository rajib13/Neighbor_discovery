// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacket interface: creates the OLSR header

#ifndef __OLSRHELLOTESTCASES_H
#define __OLSRHELLOTESTCASES_H

#include <cstring>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include <netinet/in.h>
#include <bitset>
#include "OLSRHello.h"
#include "ConcreteOLSRHelloFactory.h"
//#include "definition.h"

using namespace std;

class OLSRHelloTestCases : public OLSRHello {
public:


    /*uint16_t frontReserved = olsrHelloProcessor.frontReserved;
    uint8_t hTime = olsrHelloProcessor.hTime;
    uint8_t willingness = olsrHelloProcessor.willingness;
    uint8_t linkcode = olsrHelloProcessor.linkCode;
    uint8_t midReserve = olsrHelloProcessor.midReserved;*/

    uint16_t frontReserved =0;
    uint8_t hTime = 0;
    uint8_t willingness = 3;
    uint8_t linkcode = 0x06;
    uint8_t midReserve = 0;
    uint16_t linkMessageSize;
	// Can provide any constructors needed; the sample relies on the
	// default constructor supplied by the compiler

	// concrete implementation for the header routine
    int setHeader(unsigned char * buf, int buflen, std::vector<IPAddr> mpr,
												std::vector<IPAddr> nbours) {

        int headerLength = 8;
        int neighborSize = (4*(int)nbours.size());
		int mprSize = (4*(int)mpr.size());

        linkMessageSize = headerLength + neighborSize + mprSize;

        int offset = 44;

		*(reinterpret_cast<uint16_t*>(buf+offset)) =  frontReserved;  // set the packet
		*(reinterpret_cast<uint8_t*>(buf+2+offset)) =  hTime;
		*(reinterpret_cast<uint8_t*>(buf+3+offset)) =  willingness;  // set the packet
        *(reinterpret_cast<uint8_t*>( (buf+offset)+4)) = linkcode;
		*(reinterpret_cast<uint8_t*>(buf+5+offset)) =  midReserve;
		*(reinterpret_cast<uint16_t*>(buf+6+offset)) =  linkMessageSize;

            for( int x = 0; x < (int)mpr.size(); x++){
        *(reinterpret_cast<uint32_t*>( (buf+offset)+8+(x*4)) ) = nbours[x].to32bWord();
	}
			for( int x = 0; x < (int)nbours.size(); x++){
        *(reinterpret_cast<uint32_t*>( (buf+offset)+12+(x*4)) ) = nbours[x].to32bWord();
	}
return 1;
																										// length field
		  // the size of the header in bytes
	}

   bool isValid(unsigned char * buf, int msglen, int offset, HeaderInfo & hi)
   {
       if(99 < msglen)
            return false;

       if (2 == offset)
            return false;

      if (0x05 == buf[4])
            return false;


     if((hi.neighbors.size()) == 0)
      hi.type  = OLSRHello::NeighborType::NOTN;

    else
      {
          // TODO: here you should implement the code for Symmetric Neighbor,
          // now we just check whether there is any neighbor or not.
           hi.type = OLSRHello::NeighborType::SYM;

      }
      hi.LMOffsetEnd = (hi.neighbors.size()*4) + 4;


      return true;

   }

};

#endif
