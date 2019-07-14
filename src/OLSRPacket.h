// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacket interface: creates the combined header of IP/UDP packed

#ifndef __OLSRPACKET_H
#define __OLSRPACKET_H

#include "IPAddr.h"
#include <cstring>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include <netinet/in.h>
#include <bitset>

using namespace std;

// interface class; provide a concrete class implementing the member function.
// Note this is an instance of the Adapter design pattern: you will
// adapt your existing code that creates packet headers to the
// provided interface.
class OLSRPacket {
public:
	// assigns values according to the OLSR packet header to the
	// buffer buf.
	// buflen is the size of the buffer in bytes
	// msg_type is the type of the message (1 = Hello)
	// origin is the IP address of the originator node
	// TTL is the time to live value
	// hop_count is th ehop count value
	// psn is the packet sequence number
	// msglen is the size of the message portion following the OLSR packet
	// header, excluding the header
	// RETURNS
	// the length of the header in bytes, or -1 if the buffer is not big
	// enough to store the data and the headers
	virtual int setHeader(unsigned char * buf, int buflen, int msg_type, IPAddr origin,
												int TTL, int hop_count,
												uint16_t psn, uint16_t msn, int msglen)=0;



	//:: We post our Packet structure

	virtual ~OLSRPacket() {}

	// data structure containing the header fields extracted from the
	// received IPUDP header
	struct HeaderInfo {
		// length of OLSR packet header in bytes, or the offset where message portion begins
		int headerLen;
		// length of data (message), in bytes; we assume a single message per OLSR packet.
		// Note this is not equal to field MS from the OLSR packet header
		int dataLen;
		IPAddr org;  // originator IP address
	};

	// decodes the OLSR packet header and returns relevant info in the
	// HeaderInfo structure
	// PARAMETERS
	// buf (in) is the buffer, pointing to the start of the OLSR packet
	// buflen (in) is the allocated length of the buffer starting from the offset pointed by buf
	// hi (out) is an output parameter containing OLSR packet relevant
	// fields extracted from the header
	// RETURNS
	// true if buf contains a valid OLSR packet header. The header is valid if:
	// a) the message type is Hello AND
	// b) the packet contains a single message (PL == MS+4)
	// If any one of the conditions (a)-(b) fail, the function returns
  //   false, in which case hi's value is unspecified.
	virtual bool isValid(unsigned char * buf, int buflen, HeaderInfo & hi)=0;

};

#endif
