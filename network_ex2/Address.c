#include "Address.h"

bool areAddressesEquals(address a1, address a2)
{
	return strcmp(a1.address, a2.address) == 0 && a1.port == a2.port;
}