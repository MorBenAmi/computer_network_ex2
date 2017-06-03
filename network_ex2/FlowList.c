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
void freeList(flowList *list)
{
	flowNode *node = list->first;
	flowNode *next_node = NULL;
	while (node != NULL)
	{
		next_node = node->next;
		freeFlow(node->value);
		free(node);
		node = next_node;
	}
	free(list);
}