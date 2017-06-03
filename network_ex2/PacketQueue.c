#include "PacketQueue.h"
#include <stdlib.h>


packetQueue *createQueue()
{
	packetQueue *queue = (packetQueue *)malloc(sizeof(packetQueue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void freeQueue(packetQueue *queue)
{
	packetNode *node = queue->head;
	while (node != NULL)
	{
		queue->head = queue->head->next;
		freePacket(node->value);
		free(node);
		node = queue->head;
	}
}

packet *dequeue(packetQueue *queue)
{
	packetNode *node = queue->head;
	packet* value = NULL;
	if (node == NULL)
		return NULL;

	value = node->value;
	queue->head = queue->head->next;
	if (queue->head == NULL)
		queue->tail = NULL;

	free(node);
	return value;
}

void enqueue(packetQueue *queue, packet *pkt)
{
	packetNode *node = (packetNode*)malloc(sizeof(packetNode));
	node->value = pkt;
	node->next = NULL;
	if (queue->head == NULL)
		queue->head = node;
	else
		queue->tail->next = node;

	queue->tail = node;
}

packet *front(packetQueue *queue)
{
	if (queue->head == NULL)
		return NULL;
	return queue->head->value;
}

bool isEmpty(packetQueue *queue)
{
	return queue->head == NULL;
}