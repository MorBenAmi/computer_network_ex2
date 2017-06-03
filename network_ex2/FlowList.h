#ifndef FLOW_LIST_HEADER
#define FLOW_LIST_HEADER

#include "Flow.h"

typedef struct flowNode
{
	flow* value;
	struct flowNode* next;
} flowNode;

typedef struct flowList
{
	flowNode* first;
	flowNode* last;
} flowList;

void addFlow(flowList* list, flow* flow);
void freeList(flowList *list);

#endif
