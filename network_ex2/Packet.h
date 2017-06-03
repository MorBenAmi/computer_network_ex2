#ifndef PACKET_HEADER
#define PACKET_HEADER

#include "Address.h"

typedef struct packet
{
	long int pktID;
	long int time;
	unsigned int length;
	address src_address;
	address dest_address;
	int weight;
} packet;

packet *factoryPacket(char *line, int default_weight);

void freePacket(packet* packet);

#endif
