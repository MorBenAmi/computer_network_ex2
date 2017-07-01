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



void handleInput(char *input_file, char *scheduler_type, int default_weight, int quantum)
{
	FILE *file = NULL;
	long int current_time = 0;
	packet *current_packet = NULL;
	flowList *flow_list = NULL;
	flowNode* current_flow = NULL;
	BOOL is_continues_sending = FALSE;

	file = fopen(input_file, "r");
	if (file == NULL)
	{
		printf("Unable to open input file\n");
		exit(1);
	}

	flow_list = createFlowList();
	current_packet = readPacket(file, default_weight);
	while (current_packet != NULL || allFlowsEmpty(flow_list) == FALSE)
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

	freeList(flow_list);
	fclose(file);
}

void addPacketToRelevantFlow(flowList *list, packet *packet)
{
	flowNode *pos = list->first;
	flow *exist_flow = NULL;
	while (pos != NULL)
	{
		if (areAddressesEquals(pos->value->src_addr, packet->src_address) == TRUE &&
			areAddressesEquals(pos->value->dst_addr, packet->dest_address) == TRUE)
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