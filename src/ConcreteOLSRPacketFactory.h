// *** CPSC 4210/5210 Assignment 3 code
// *** Provides a concrete IPUDPPacketFactory sample class that creates IPUDPacket objects

#ifndef __CONCRETEOLSRPACKETFACTORY_H
#define __CONCRETEOLSRPACKETFACTORY_H

#include <memory>
#include "OLSRPacketFactory.h"
#include "OLSRPacketTestCases.h"

class ConcreteOLSRPacketFactory : public OLSRPacketFactory {
public:
	std::shared_ptr<OLSRPacket> createOLSRPacket() {
		return std::make_shared<OLSRPacketTestCases>();
	}


};

#endif
