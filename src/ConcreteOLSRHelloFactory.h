// *** CPSC 4210/5210 Assignment 3 code
// *** Provides a concrete IPUDPPacketFactory sample class that creates IPUDPacket objects

#ifndef __CONCRETEOLSRHELLOFACTORY_H
#define __CONCRETEOLSRHELLOFACTORY_H

#include <memory>
#include "OLSRHelloFactory.h"
#include "OLSRHelloTestCases.h"

class ConcreteOLSRHelloFactory : public OLSRHelloFactory {
public:
	std::shared_ptr<OLSRHello> createOLSRHello() {
		return std::make_shared<OLSRHelloTestCases>();
	}


};

#endif
