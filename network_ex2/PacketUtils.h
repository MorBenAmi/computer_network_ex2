#ifndef PACKET_UTIL_HEADER
#define PACKET_UTIL_HEADER
#include <stdbool.h>

#define MAX_IP_SIZE 45 //Support IPv6

typedef struct address
{
  char address[MAX_IP_SIZE];
  unsigned int port;
} address;

typedef struct packet
{
  long int pktID;
  long int Time;
  unsigned int length;
  address src_address;
  address dest_address;
  int weight;

  struct packet *next;
} packet;

typedef struct packetQueue
{
  packet *first;
  packet *last;
} packetQueue;

packetQueue *createQueue();

packet *factoryPacket(char *line, int default_weight);

void freeQueue(packetQueue *queue);

packet *dequeue(packetQueue *queue);

packet *front(packetQueue *queue);

bool isEmpty(packetQueue *queue);

void enqueue(packetQueue *queue, packet *pkt);

#endif
#pragma once
