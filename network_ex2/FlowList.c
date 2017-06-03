#include "FlowList.h"
#include <stdlib.h>

void addFlow(flowList* list, flow* flow)
{
	flowNode* new_node = (flowNode*)malloc(sizeof(flowNode));
	new_node->value = flow;
	new_node->next = NULL;
	if (list->first == NULL)
	{
		list->first = new_node;
	}
	else 
	{
		list->last->next = new_node;
	}
	list->last = new_node;

}

flowList* createFlowList()
{
	flowList *list = (flowList *)malloc(sizeof(flowList));
	list->first = NULL;
	list->last = NULL;
	return list;
}
