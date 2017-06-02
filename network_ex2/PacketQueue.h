#ifndef PACKET_QUEUE_HEADER
#define PACKET_QUEUE_HEADER

#include "Packet.h"
#include <stdbool.h>

typedef struct packetNode {
	packet* value;
	struct packetNode* next;
} packetNode;

typedef struct packetQueue
{
	packetNode *head;
	packetNode *tail;
} packetQueue;


packetQueue *createQueue();
void enqueue(packetQueue* queue, packet* packet);
packet *dequeue(packetQueue *queue);
packet *front(packetQueue *queue);
bool isEmpty(packetQueue *queue);

void freeQueue(packetQueue *queue);

#endif
