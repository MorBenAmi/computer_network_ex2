#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "OutputFileHandler.h"

static FILE* output_file;
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
//the file containe all the functions that responsable for writinng to the output file// 
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
void openFile(char* output_path)
{
	if (output_file != NULL)
		return;
	output_file = fopen(output_path, "w");
	if (output_file == NULL)
	{
		printf("Unable to open output file\n");
		exit(GetLastError());
	}
}

void closeFile()
{
	if (output_file == NULL)
		return;
	fclose(output_file);
	output_file = NULL;
}

void writePacketTime(int packet_id, int time)
{
	if (output_file == NULL)
		return;

  fprintf(output_file, "%d: %d\n", time, packet_id);
}



