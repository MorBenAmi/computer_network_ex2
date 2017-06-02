#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputHandler.h"
#include "OutputFileHandler.h"
#include "PacketQueue.h"

void handleInput(char *input_file, char *scheduler_type, int default_weight, int quantum)
{
	FILE *file = NULL;
	long int current_time = 0;
	char line[256];
	packet *current_packet = NULL;

	packetQueue *queue = createQueue();
	file = fopen(input_file, "r");
	if (file == NULL)
	{
		printf("Unable to open input file\n");
		exit(1);
	}
	//TODO Limor -> set RR or DRR, quantum 

	while (1) {
		if (current_packet == NULL)
		{
			fgets(line, sizeof(line), file);
			if (line == NULL || *line == '\0')
			{
				//TODO Limor -> update DRR/RR that no more pkts
				break;
			}
			current_packet = factoryPacket(line, default_weight);
			memset(line, '\0', sizeof(line));
		}

		if (current_packet->Time <= current_time)
		{
			//TODO Limor -> update DRR or RR for current_packet + time 
			//TODO Limor -> free!
			enqueue(queue, current_packet);
			current_packet = NULL;
		}
		else
		{
			//TODO Limor -> update time 
			current_time++;
		}
	}

	freeQueue(queue);

	fclose(input_file);
}