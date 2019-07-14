// *** CPSC 4210/5210 Assignment 3 code
// ***** OLSRHelloFactory interface: provides a function that
// ***creates an appropriate concrete OLSRHello object referenced
// ***via the OLSRHello interface; it is used in the test fixtures
// ***for OLSRHello.

#ifndef __OLSRHELLOFACTORY_H
#define __OLSRHELLOFACTORY_H

#include <memory>
#include "OLSRHello.h"

class OLSRHelloFactory {
public:
	// returns a shared_ptr to interface class IPUDPPacket.
	// The concrete object must create an object to a concrete IPUDPPacket.
	virtual std::shared_ptr<OLSRHello> createOLSRHello()=0;

	virtual ~OLSRHelloFactory() {};
};

#endif
