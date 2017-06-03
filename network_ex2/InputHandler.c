#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputHandler.h"
#include "OutputFileHandler.h"

packet* readPacket(FILE* file, int default_weight)
{
	char line[256];

	memset(line, '\0', sizeof(line));
	fgets(line, sizeof(line), file);
	if (line == NULL || *line == '\0')
	{
		return NULL;
	}
	return factoryPacket(line, default_weight);
}

bool allFlowsEmpty(flowList* list)
{
	flowNode* pos = list->first;
	while (pos != NULL)
	{
		if (!isEmpty(pos->value->queue))
			return false;
		pos = pos->next;
	}
	return true;
}

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
		printf("%d:%d\n", *current_time, current_packet->pktID);//todo: change to output file
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
			*is_continues_sending = false;
			current_flow_node->value->credit = 0;
			current_flow_node = current_flow_node->next;
		}
		else if (current_flow_node->value->credit >= front(current_flow_node->value->queue)->length)
		{
			current_packet = dequeue(current_flow_node->value->queue);
			printf("%d:%d\n", *current_time, current_packet->pktID);//todo: change to output file
			current_flow_node->value->credit -= current_packet->length;
			(*current_time) += current_packet->length;
			*is_continues_sending = true;
			return current_flow_node;
		}
		else
		{
			if (!(*is_continues_sending))
				current_flow_node->value->credit += (current_flow_node->value->weight*quantom);
			else
				current_flow_node = current_flow_node->next;

			*is_continues_sending = false;
			return current_flow_node;
		}
	}

	if (allFlowsEmpty(flow_list))
		(*current_time)++;

	*is_continues_sending = false;
	return current_flow_node;
}

void handleInput(char *input_file, char *scheduler_type, int default_weight, int quantum)
{
	FILE *file = NULL;
	long int current_time = 0;
	packet *current_packet = NULL;
	flowList *flow_list = NULL;
	flow* current_flow = NULL;
	bool is_continues_sending = false;

	file = fopen(input_file, "r");
	if (file == NULL)
	{
		printf("Unable to open input file\n");
		exit(1);
	}

	flow_list = createFlowList();
	current_packet = readPacket(file, default_weight);
	while (current_packet != NULL || !allFlowsEmpty(flow_list))
	{
		while (current_packet != NULL && current_packet->time <= current_time)
		{
			addPacketToRelevantFlow(flow_list, current_packet);
			current_packet = readPacket(file, default_weight);
		}
		if (strcmp(scheduler_type, "RR") == 0)
			current_flow = handleRR(flow_list, current_flow, &current_time);
		else
			current_flow = handleDRR(flow_list, current_flow, &current_time,quantum, &is_continues_sending);
	}

	//todo: free all flows...

	fclose(file);
}

void addPacketToRelevantFlow(flowList *list, packet *packet)
{
	flowNode *pos = list->first;
	flow *exist_flow = NULL;
	while (pos != NULL)
	{
		if (areAddressesEquals(pos->value->src_addr, packet->src_address) &&
			areAddressesEquals(pos->value->dst_addr, packet->dest_address))
		{
			exist_flow = pos->value;
			break;
		}
		pos = pos->next;
	}
	if (exist_flow != NULL)
	{
		addToFlow(exist_flow, packet);
	}
	else
	{
		addFlow(list, createFlowByPacket(packet));
	}
}