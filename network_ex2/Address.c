#include "Address.h"

BOOL areAddressesEquals(address a1, address a2)
{
	if (strcmp(a1.address, a2.address) == 0 && a1.port == a2.port)
		return TRUE;
	return FALSE;
}