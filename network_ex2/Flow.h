#ifndef FLOW_HEADER
#define FLOW_HEADER

#include "PacketQueue.h"
#include "Address.h"

typedef struct flow
{
	address* src_addr;
	address* dst_addr;

	packetQueue* queue;
} flow;

bool areFlowEquals(flow* src_flow, flow* other_flow);
void addToFlow(flow* src_flow, packet* packet);

#endif