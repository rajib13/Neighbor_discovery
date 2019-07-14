// *** CPSC 4210/5210 Assignment 3 code
// ***** IPUDPPacketFactory interface: provides a function that
// ***creates an appropriate concrete IPUDPPacket object referenced
// ***via the IPUDPPacket interface; it is used in the test fixtures
// ***for IPUDPPacket.

#ifndef __IPUDPPACKETFACTORY_H
#define __IPUDPPACKETFACTORY_H

#include <memory>
#include "IPUDPPacket.h"

class IPUDPPacketFactory {
public:
	// returns a shared_ptr to interface class IPUDPPacket.
	// The concrete object must create an object to a concrete IPUDPPacket.
	virtual std::shared_ptr<IPUDPPacket> createIPUDPPacket()=0;

	virtual ~IPUDPPacketFactory() {};
};

#endif
