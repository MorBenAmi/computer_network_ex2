#include "Flow.h"

bool areFlowEquals(flow* src_flow, flow* other_flow)
{


	return true;
}

void addToFlow(flow* src_flow, packet* packet)
{
	enqueue(src_flow->queue, packet);
}