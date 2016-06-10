#pragma once

typedef struct
{
	char filename[256];
	
	unsigned int size;

	unsigned int position;

	unsigned char *buffer;

}Memory;

Memory* mopen(char* filename);
Memory* mclose(Memory* memory);
