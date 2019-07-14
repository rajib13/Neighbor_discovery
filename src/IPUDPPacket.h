// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacket interface: creates the combined header of IP/UDP packed

#ifndef __IPUDPPACKET_H
#define __IPUDPPACKET_H

#include "IPAddr.h"

// interface class; provide a concrete class implementing the member function.
// Note this is an instance of the Adapter design pattern: you will
// adapt your existing code that creates packet headers to the
// provided interface.
class IPUDPPacket {
public:
	// assigns values according to the IP/UDP packet header to the
	// buffer buf.
	// buflen is the size of the buffer in bytes
	// src is the IP address of the source
	// dest is the IP address of the destination
	// TTL is the value of the time to live field
	// datalen is the size of the data portion following the IP+UDP
	// header
	// RETURNS
	// the length of the header in bytes, or -1 if the buffer is not big
	// enough to store the data and the headers
	virtual int setHeader(unsigned char * buf, int buflen, IPAddr src,
								 IPAddr dest, int TTL, int datalen)=0;




	// data structure containing the header fields extracted from the
	// received IPUDP header
	struct HeaderInfo {
		int headerLen; // length of ID+UDP header in bytes, or the offset where data portion begins
		int dataLen; // length of data, in bytes
		int TTL; // TTL value
		IPAddr src;  // source IP address
		IPAddr dest; // destination IP address
	};

	// decodes the IP and UDP headers and returns relevant info in the
	//   HeaderInfo structure
	// PARAMETERS
	// buf (in) is the buffer, pointing to the start of the IP packet
	// buflen (in) is the allocated length of the buffer
	// hi (out) is an output parameter containing IP, UDP relevant
	//   `fields extracted from the header
	// RETURNS
	// true if buf contains a valid IP/UDP header. The header is valid
  //   if all of the following conditions hold:
	// a) UDP port number is 698;
	// b) the IP header protocol value is 138
	// c) the IP version is 4,
	// d) the IP header checksum checks
	// If one or more of the conditions (a)-(d) fail, the function returns
  //   false, in which case hi's value is unspecified.
	virtual bool isValid(unsigned char * buf, int buflen, HeaderInfo & hi)=0;

	virtual ~IPUDPPacket() {}
};

#endif
