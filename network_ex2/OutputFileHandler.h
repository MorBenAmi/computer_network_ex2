#ifndef OUTPUT_FILE_HANDLER_HEADER
#define OUTPUT_FILE_HANDLER_HEADER

void openFile(char* output_path);

void closeFile();

void writePacketTime(int packet_id, int time);

#endif