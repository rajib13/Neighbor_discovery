// *** CPSC 4210/5210 Assignment 3 code
// *** Provides a concrete IPUDPPacketFactory sample class that creates IPUDPacket objects

#ifndef __CONCRETEIPUDPPACKETFACTORY_H
#define __CONCRETEIPUDPPACKETFACTORY_H

#include <memory>
#include "IPUDPPacketFactory.h"
#include "IPUDPPacketSample.h"

class ConcreteIPUDPPacketFactory : public IPUDPPacketFactory {
public:
	std::shared_ptr<IPUDPPacket> createIPUDPPacket() {
		return std::make_shared<IPUDPPacketSample>();
	}
};

#endif
