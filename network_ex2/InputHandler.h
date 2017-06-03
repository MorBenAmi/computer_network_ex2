#ifndef INPUT_HANDLER_HEADER
#define INPUT_HANDLER_HEADER

#include "PacketQueue.h"
#include "FlowList.h"
#include <stdbool.h>

void handleInput(char *input_file, char *scheduler_type, int default_weight, int quantum);
void addPacketToRelevantFlow(flowList *list, packet *packet);
bool allFlowsEmpty(flowList* list);

#endif