#include "Scheduler.h"
#include <stdlib.h>
#include "OutputFileHandler.h"




flowNode* handleRR(flowList* flow_list, flowNode* current_flow_node, long* current_time)
{
	packet* current_packet = NULL;

	if (current_flow_node == NULL)
		current_flow_node = flow_list->first;

	while (current_flow_node != NULL &&
		(isEmpty(current_flow_node->value->queue) || current_flow_node->value->credit == 0))
	{
		current_flow_node->value->credit = current_flow_node->value->weight;
		current_flow_node = current_flow_node->next;
	}

	if (current_flow_node != NULL)
	{
		if (current_flow_node->value->credit == -1) //first time handling this flow
			current_flow_node->value->credit = current_flow_node->value->weight;

		current_packet = dequeue(current_flow_node->value->queue);
		writePacketTime(current_packet->packet_id, *current_time);
		current_flow_node->value->credit--;
		(*current_time) += current_packet->length;
	}
	else if (allFlowsEmpty(flow_list))
	{
		(*current_time)++;
	}

	return current_flow_node;
}

flowNode* handleDRR(flowList* flow_list, flowNode* current_flow_node, long* current_time, int quantom, bool* is_continues_sending)
{
	packet* current_packet = NULL;

	if (current_flow_node == NULL)
		current_flow_node = flow_list->first;

	while (current_flow_node != NULL)
	{
		if (current_flow_node->value->credit == -1) //first time handling this flow
			current_flow_node->value->credit = 0;

		if (isEmpty(current_flow_node->value->queue))
		{
			if (!(*is_continues_sending)) 
				current_flow_node->value->credit = 0;
			*is_continues_sending = false;
			current_flow_node = current_flow_node->next;
		}
		else if (current_flow_node->value->credit >= front(current_flow_node->value->queue)->length)
		{
			current_packet = dequeue(current_flow_node->value->queue);
			writePacketTime(current_packet->packet_id, *current_time);
			current_flow_node->value->credit -= current_packet->length;
			(*current_time) += current_packet->length;
			*is_continues_sending = true;
			return current_flow_node;
		}
		else
		{
			if (!(*is_continues_sending))
			{
				current_flow_node->value->credit += (current_flow_node->value->weight*quantom);
				*is_continues_sending = true;
			}
			else
			{
				current_flow_node = current_flow_node->next;
				*is_continues_sending = false;
			}

			return current_flow_node;
		}
	}

	if (allFlowsEmpty(flow_list))
		(*current_time)++;

	*is_continues_sending = false;
	return current_flow_node;
}