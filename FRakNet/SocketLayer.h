/// \file
/// \brief \b [Internal] Encapsulates Berkely sockets
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.


#ifndef __SOCKET_LAYER_H
#define __SOCKET_LAYER_H

#ifdef _COMPATIBILITY_1
#include "Compatibility1Includes.h"
#elif defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> 
/// Unix/Linux uses ints for sockets
typedef int SOCKET;
#define INVALID_SOCKET -1 
#define SOCKET_ERROR -1
#endif

class RakPeer;

// A platform independent implementation of Berkeley sockets, with settings used by RakNet
class SocketLayer
{

public:

	/// Default Constructor
	SocketLayer();

	/// Destructor	
	~SocketLayer();

	static inline SocketLayer* Instance()
	{
		return &I;
	}

	SOCKET Connect(SOCKET writeSocket, unsigned int binaryAddress, unsigned short port);
	SOCKET CreateBoundSocket(unsigned short port, bool blockingSocket, const char *forceHostAddress);

#if !defined(_COMPATIBILITY_1)
	const char* DomainNameToIP(const char *domainName);
#endif

#ifdef __USE_IO_COMPLETION_PORTS
	void AssociateSocketWithCompletionPort(SOCKET socket, ClientContextStruct* completionKey);
#endif

	bool AssociateSocketWithCompletionPortAndRead(SOCKET readSocket, unsigned int binaryAddress, unsigned short port, RakPeer* rakPeer);
	void Write(const SOCKET writeSocket, const char* data, const int length);
	int RecvFrom(const SOCKET s, RakPeer *rakPeer, int *errorCode);

#if !defined(_COMPATIBILITY_1)

	void GetMyIP(char ipList[10][16]);
#endif

	int SendTo(SOCKET s, const char *data, int length, char ip[16], unsigned short port);
	int SendTo(SOCKET s, const char *data, int length, unsigned int binaryAddress, unsigned short port);

	unsigned short GetLocalPort(SOCKET s);
private:

	static bool socketLayerStarted;
#ifdef _WIN32
	static WSADATA winsockInfo;
#endif
	static SocketLayer I;
};

#endif

