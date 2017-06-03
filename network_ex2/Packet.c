#define _CRT_SECURE_NO_WARNINGS
#include "Packet.h"
#include <stdlib.h>
#include <string.h>

void factoryAddress(address *add)
{
	strcpy(add->address, strtok(NULL, " "));
	add->port = atoi(strtok(NULL, " "));
}

packet *factoryPacket(char *line, int default_weight)
{
	char *value = NULL;
	packet *pkt = NULL;

	value = strtok(line, " ");
	pkt = (packet *)malloc(sizeof(packet));
	pkt->pktID = atol(value);
	value = strtok(NULL, " ");
	pkt->time = atol(value);
	factoryAddress(&(pkt->src_address));
	factoryAddress(&(pkt->dest_address));
	value = strtok(NULL, " ");
	pkt->length = atoi(value);
	value = strtok(NULL, " ");
	if (value != NULL)
		pkt->weight = atoi(value);
	else
		pkt->weight = default_weight;
	return pkt;
}

void freePacket(packet* packet) 
{
	free(packet);
}