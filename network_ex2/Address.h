#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER

#define MAX_IP_SIZE 45 //Support IPv6

#include <windows.h>

typedef struct address
{
	char address[MAX_IP_SIZE];
	unsigned int port;
} address;

BOOL areAddressesEquals(address a1, address a2);

#endif