#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PacketUtils.h"

void factoryAddress(address *add)
{
  strcpy(add->address, strtok(NULL, " "));
  add->port = atoi(strtok(NULL, " "));
}

packet *factoryPacket(char *line, int default_weight)
{
  char *value = strtok(line, " ");
  packet *pkt = (packet *)malloc(sizeof(packet));
  pkt->pktID = atol(value);
  value = strtok(NULL, " ");
  pkt->Time = atol(value);
  factoryAddress(&(pkt->src_address));
  factoryAddress(&(pkt->dest_address));
  value = strtok(NULL, " ");
  pkt->length = atoi(value);
  value = strtok(NULL, " ");
  if (value != NULL)
  {
    pkt->weight = atoi(value);
  }
  else
  {
    pkt->weight = default_weight;
  }
  return pkt;
}

packetQueue *createQueue()
{
  packetQueue *queue = (packetQueue *)malloc(sizeof(packetQueue));
  queue->first = NULL;
  queue->last = NULL;
  return queue;
}

void freeQueue(packetQueue *queue)
{
  packet *node = queue->first;
  while (node != NULL)
  {
    queue->first = queue->first->next;
    free(node);
    node = queue->first;
  }
}

packet *dequeue(packetQueue *queue)
{
  packet *node = queue->first;
  queue->first = queue->first->next;
  return node;
}

void enqueue(packetQueue *queue, packet *pkt)
{
  pkt->next = NULL;
  if (queue->first == NULL)
  {
    queue->first = pkt;
  }
  else if (queue->first->next == NULL)
  {
    queue->first->next = pkt;
    queue->last = pkt;
  }
  else
  {
    queue->last->next = pkt;
    queue->last = pkt;
  }
}

packet *front(packetQueue *queue)
{
  return queue->first;
}

bool isEmpty(packetQueue *queue)
{
  return queue->first == NULL;
}

