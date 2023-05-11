#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

buffer_t* CreateBuffer(size_t size)
{
    buffer_t* buffer;
    
    buffer = (buffer_t*) malloc(sizeof(buffer_t));
    buffer->dataStart = (char*)malloc(size);
    buffer->allocatedLength = size;
    buffer->dataEnd = buffer->dataStart;
    return buffer;
}

void WriteBuffer(buffer_t* buffer, void* data, size_t len)
{
    char* bytes = (char*) data;
    if(len + GetBufferSize(buffer) > buffer->allocatedLength) {
        printf("ERROR: Buffer Overflow! Please resize! (If you can find out how)\n");
        return;
    }
    
    for(int i = 0; i < len; i++) {
        buffer->dataEnd[0] = bytes[i];
        buffer->dataEnd++;
    }
    return;
}

void EraseBuffer(buffer_t* buffer)
{
    buffer->dataEnd = buffer->dataStart;
    return;
}

size_t GetBufferSize(buffer_t* buffer)
{
    return buffer->dataEnd - buffer->dataStart;
}

void DeleteBuffer(buffer_t* buffer)
{
    free(buffer->dataStart);
    free(buffer);
    return;
}
