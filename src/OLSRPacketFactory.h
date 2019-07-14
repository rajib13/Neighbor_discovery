// *** CPSC 4210/5210 Assignment 3 code
// ***** OLSRPacketFactory interface: provides a function that
// ***creates an appropriate concrete OLSRPacket object referenced
// ***via the OLSRPacket interface; it is used in the test fixtures
// ***for IPUDPPacket.

#ifndef __OLSRPACKETFACTORY_H
#define __OLSRPACKETFACTORY_H

#include <memory>
#include "OLSRPacket.h"

class OLSRPacketFactory {
public:
	// returns a shared_ptr to interface class IPUDPPacket.
	// The concrete object must create an object to a concrete IPUDPPacket.
	virtual std::shared_ptr<OLSRPacket> createOLSRPacket()=0;

	virtual ~OLSRPacketFactory() {};
};

#endif
