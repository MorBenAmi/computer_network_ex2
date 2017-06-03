#ifndef ADDRESS_HEADER
#define ADDRESS_HEADER

#include <stdbool.h>

#define MAX_IP_SIZE 45 //Support IPv6

typedef struct address
{
	char address[MAX_IP_SIZE];
	unsigned int port;
} address;

bool areAddressesEquals(address a1, address a2);

#endif