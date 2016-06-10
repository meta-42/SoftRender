#include "mre.h"

Memory* mopen(char* filename)
{
	FILE* file;
	char fname[MAX_PATH];

	strcpy(fname, filename);

	file = fopen(fname, "rb");

	if (!file)
	{
		return NULL;
	}
	
	Memory* memory = (Memory*)calloc(1, sizeof(Memory));
	strcpy(memory->filename, fname);

	fseek(file, 0, SEEK_END);
	memory->size = ftell(file);
	fseek(file, 0, SEEK_SET);

	//Buffer多存储一字节为0,当作结束标记
	memory->buffer = (unsigned char*)calloc(1, memory->size + 1);
	fread(memory->buffer, memory->size, 1, file);
	memory->buffer[memory->size] = 0;

	fclose(file);

	//printf("%s", memory->buffer);
	return memory;
}

Memory* mclose(Memory* memory)
{
	if (memory->buffer)
	{
		free(memory->buffer);
	}
	free(memory);
	return NULL;
}
