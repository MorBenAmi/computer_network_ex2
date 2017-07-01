#ifndef SCHEDULER_HANDLER
#define SCHEDULER_HANDLER

#include "FlowList.h"


flowNode* handleRR(flowList* flow_list, flowNode* current_flow_node, long* current_time);
flowNode* handleDRR(flowList* flow_list, flowNode* current_flow_node, long* current_time, int quantom, BOOL* is_continues_sending);

#endif
