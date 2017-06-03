#ifndef FLOW_HEADER
#define FLOW_HEADER

#include "PacketQueue.h"
#include "Address.h"

typedef struct flow
{
	address src_addr;
	address dst_addr;
	int weight;
	int credit;

	packetQueue* queue;
} flow;

void addToFlow(flow* flow, packet* packet);
flow* createFlowByPacket(packet* packet);
void freeFlow(flow* flow);

#endif