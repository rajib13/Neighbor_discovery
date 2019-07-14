// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacket interface: creates the combined header of IP/UDP packed

#ifndef __IPUDPPACKETSAMPLE_H
#define __IPUDPPACKETSAMPLE_H

#include <cstring>
#include "IPUDPPacket.h"
#include "definition.h"

class IPUDPPacketSample : public IPUDPPacket {
public:

    uint8_t verSionIHL = ipUdpPacketProcessor.versionIHL;
    uint8_t typeOfService = ipUdpPacketProcessor.typeOfService;
    uint16_t totalLength = ipUdpPacketProcessor.totalLength;
    uint16_t identification = ipUdpPacketProcessor.identification;
    uint16_t flagOffset = ipUdpPacketProcessor.flagsOffset;
    uint8_t protocol = ipUdpPacketProcessor.protocol;
    uint16_t checksumIP = ipUdpPacketProcessor.headerChecksum;
    uint16_t sourcePort = ipUdpPacketProcessor.sourcePort;
    uint16_t destinationPort = ipUdpPacketProcessor.destinationPort;
    uint16_t length = ipUdpPacketProcessor.length;
    uint16_t checksumUDP = ipUdpPacketProcessor.checksumUdp;

	// Can provide any constructors needed; the sample relies on the
	// default constructor supplied by the compiler
uint16_t testconvertion(int tstchk)
 {
    uint16_t ckvalue = 0;
    if (tstchk <= 1)
    {
        return !tstchk;
    }
    ckvalue = tstchk % 2;
    testconvertion(tstchk / 2);
    return ((ckvalue*10) + !ckvalue);

  }
	// concrete implementation for the header routine
	int setHeader(unsigned char * buf, int buflen, IPAddr src,
								IPAddr dest, int TTL, int datalen) {
		// we don't do much, just fill the data length part of the header,
		// as demo.

		//std::memset(buf, 0, buflen);  // we clear the buffer first!
		//*(reinterpret_cast<uint8_t*>(buf)) = (&ver_ihl);
		memcpy(buf,&verSionIHL,sizeof(verSionIHL));
		*(reinterpret_cast<uint8_t*>(buf+1)) = typeOfService;  // set the packet
		*(reinterpret_cast<uint16_t*>(buf+2)) = buflen;
		*(reinterpret_cast<uint16_t*>(buf+4)) = totalLength;
		*(reinterpret_cast<uint16_t*>(buf+6)) = identification;
		*(reinterpret_cast<uint8_t*>(buf+8)) = flagOffset;
		*(reinterpret_cast<uint8_t*>(buf+9)) = protocol;
		*(reinterpret_cast<uint16_t*>(buf+10)) = checksumIP;
		*(reinterpret_cast<uint32_t*>(buf+12)) = src.to32bWord();
		*(reinterpret_cast<uint32_t*>(buf+16)) = dest.to32bWord();
		*(reinterpret_cast<uint16_t*>(buf+20)) = sourcePort;
		*(reinterpret_cast<uint16_t*>(buf+22)) = destinationPort;
		*(reinterpret_cast<uint16_t*>(buf+24)) = length;
		*(reinterpret_cast<uint16_t*>(buf+26)) = checksumUDP;
return 1;
																										// length field
	}

		// concrete implementation for the isValid routine
	// Notice, this fakes the decoding of the header.
	bool isValid(unsigned char * buf, int buflen, HeaderInfo & hi) {

        if (20 > buflen)
        {
            return false;
        }
        if (100 < buflen)
        {
            return false;
        }

        IPAddr origin(169,254,3,1), destination(169,254,255,255);
		hi.headerLen = buflen;
		hi.dataLen = 48;
		hi.TTL = 1;
        hi.src = origin;
		hi.dest = destination;

		return true;

	}
};

#endif
