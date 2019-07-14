#include <sys/socket.h>
#include <sys/types.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

#include "sock.h"
#include "senceiver.h"
//#include "IPAddr.h"

using namespace std;

/* broadcast a hello world packet */
int main()
{
IPAddr myPi(3,1);
initializeLogFile("Log",myPi);

// This all threads are implemented into senceiver.h file.
    	std::thread senderThread (sendMessage);
	std::thread receiverThread (receive);
	std::thread neighborEraserThread (neighborEraser);

    	receiverThread.join();
	senderThread.join();
	neighborEraserThread.join();

return 0;
}





