#include <stdio.h>
#include <stdlib.h>
#include "InputHandler.h"
#include "OutputFileHandler.h"

#define NUM_OF_ARGS 6

int main(int argc, char* argv[])
{
  char *output_file, *input_file, *scheduler_type;
  int default_weight, quantum;

  if (argc != NUM_OF_ARGS) {
    printf("error");
    exit(1);
  }

  scheduler_type = argv[1];
  input_file = argv[2];
  output_file = argv[3];
  default_weight = atoi(argv[4]);
  quantum = atoi(argv[5]);

  openFile(output_file);

  handleInput(input_file, scheduler_type, default_weight, quantum);

  closeFile();

  exit(0);
}
