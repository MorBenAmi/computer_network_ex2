#include "Flow.h"

bool areFlowEquals(flow* src_flow, flow* other_flow)
{


	return true;
}

void addToFlow(flow* flow, packet* packet)
{
	enqueue(flow->queue, packet);
}

flow* createFlowByPacket(packet* packet)
{
	flow* new_flow = (flow*)malloc(sizeof(flow));
	new_flow->src_addr = packet->src_address;
	new_flow->dst_addr = packet->dest_address;
	new_flow->queue = createQueue();
	new_flow->weight = packet->weight;
	new_flow->credit = -1;
	enqueue(new_flow->queue, packet);
	return new_flow;
}