// *** CPSC 4210/5210 Assignment 3 code
// ***** IPAddr: a representation of IPv4 addresses

#ifndef __IPADDR_H
#define __IPADDR_H

#include <string>
#include <sstream>
//#include <cstdint>

// Encapsulates an IP address.
// NOTE: we do not implement the net mask; for the assignment, the net
// mask assumed is 255.255.0.0
class IPAddr {
private:
	unsigned char addr[4]; // IP address in network byte order (MSB at index 0)

public:
	// constructs an address given at most 4 bytes of the address; in
	// dotted notation, the address constructed is a.b.pi.node; 
	IPAddr(unsigned char a, unsigned char b,
				 unsigned char pi, unsigned char node) {
		addr[0]=a;  addr[1]=b; addr[2]=pi; addr[3]=node;
	}

	// constructs an IP address on the "link local network".
	// The address constructed is 169.254.pi.node 
	IPAddr(unsigned char pi, unsigned char node) {
		addr[0]=169; addr[1]=254; addr[2]=pi; addr[3]=node;
	}

	// Default constructed address, the broadcast address: 169.254.255.255
	IPAddr() {
		addr[0]=169; addr[1]=254; addr[2]=255; addr[3]=255;
	}

	// constructs an IP address from a 32 bit word in network order; can
	// be used to extract the IP address directly from IP and OLSR
	// packet headers
	IPAddr(uint32_t word) {
		*((uint32_t*)addr) = word;
	}

	// returns a string containing the decimal dot notation
	// corresponding to the address
	std::string toString() {
		std::ostringstream sstr;  // stringstream used for conversion
		sstr << (int) addr[0] << "."
				 << (int) addr[1] << "."
				 << (int) addr[2] << "."
				 << (int) addr[3];
		return sstr.str();
	}

	// returns a 32 bit word corresponding to the address in network
	// byte order. This value can be used directly in IP and OLSR
	// packets. 
	uint32_t to32bWord() {
		return *((uint32_t*)addr);  // 4 byte array array structure makes
																// the conversion trivial
	}
	// equality comparison
	bool operator==(IPAddr a) {
		return (to32bWord() == a.to32bWord());
	}

};

#endif

