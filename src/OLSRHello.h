// *** CPSC 4210/5210 Assignment 3 code
// ***** OLSRHello interface: creates the header of a Hello Message

#ifndef __OLSRHELLO_H
#define __OLSRHELLO_H

#include <vector>
#include "IPAddr.h"

// interface class; provide a concrete class implementing the member function.
// Note this is an instance of the Adapter design pattern: you will
// adapt your existing code that creates packet headers to the
// provided interface.
class OLSRHello {
public:
	// assigns values according to the OLSR packet header to the
	// buffer buf.
	// buflen is the size of the buffer in bytes
	// mpr is a vector of IP addresses selected to be MPR's
	// nbours is a vector of IP addresses that are the neighbour nodes
	// RETURNS
	// the length of the entire message in bytes, or -1 if the buffer is not big
	// enough to store the message and the headers
	virtual int setHeader(unsigned char * buf, int buflen, std::vector<IPAddr> mpr,
												std::vector<IPAddr> nbours)=0;

	virtual ~OLSRHello() {}

	  // two types of neighbours are considered (even though MPR selection
  // may not be implemented)
	enum class NeighborType { MPR, SYM /* regular neighbours*/, NOTN/*not neighbours*/ };

	// data structure containing the header fields extracted from the
	// received OLSR Hello message header
	struct HeaderInfo {
		std::vector<IPAddr> neighbors;
		// This entry marks the type of the nodes returned in the vector:L
		// The nodes can be MPR nodes, or regular SYM nodes, or NOTN is the list is empty.
		// Note that we do not extract the link code, but we use it to check if the message is valid.
		NeighborType type;
		// this field returns the offset relative to the start of the buffer passed to the
		// isValid function below of the end of the neighbor list in the message. For example,
		// if there is a single list in the message, then this value should equal the size of
		// the message; Use this value to extract all of the neighbour lists present in the
		// Hello message
		int LMOffsetEnd;
	};

	// decodes the OLSR Hello message header and returns relevant info in the
	// HeaderInfo structure
	// PARAMETERS
	// buf (in) is the buffer, pointing to the start of the Hello message, where
	//   the reserved, Htime and Willingness fields are placed; the buf pointer
	//   is not changed in order to extract the various lists of neighbours. Use
	//   offset for this purpose (see below)
	// msglen (in) is the length of the message stored in the buffer, in bytes
	// offset is the offset in bytes, relative to buf, of the list of neighbours we
	//   wish to extract; for the first list of neighbours the offset can equal 0 or 4.
	//   For lists that are not first in the Hello message, the offset should point to
	//   the start of the "Link code" field pertaining to the list.
	// hi (out) is an output parameter containing the relevant
	//   information extracted from the message
	// RETURNS
	// true if buf contains a valid Hello message list. A hello message list is
	// valid if all of the following conditions hold:
	// a) Link Code value is as specified in class
	// b) offset is 0, 4 or some value larger than 4 but less than or equal to
	//   msglen-4 and it is positive
	// Otherwise the function returns false, in which case hi's value is unspecified.
	virtual bool isValid(unsigned char * buf, int msglen, int offset, HeaderInfo & hi)=0;
};

#endif
