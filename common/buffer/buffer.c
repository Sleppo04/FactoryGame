#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

buffer_t* CreateBuffer(size_t size)
{
    buffer_t* buffer;
    
    buffer = (buffer_t*) malloc(sizeof(buffer_t));
    buffer->data_start = (char*)malloc(size);
    buffer->allocated_length = size;
    buffer->data_end = buffer->data_start;
    return buffer;
}

void WriteBuffer(buffer_t* buffer, void* data, size_t len)
{
    char* bytes = (char*) data;
    if(len + GetBufferSize(buffer) > buffer->allocated_length) {
        printf("ERROR: Buffer Overflow! Please resize! (If you can find out how)\n");
        return;
    }
    
    for(int i = 0; i < len; i++) {
        buffer->data_end[0] = bytes[i];
        buffer->data_end++;
    }
    return;
}

void EraseBuffer(buffer_t* buffer)
{
    buffer->data_end = buffer->data_start;
    return;
}

size_t GetBufferSize(buffer_t* buffer)
{
    return buffer->data_end - buffer->data_start;
}

void DeleteBuffer(buffer_t* buffer)
{
    free(buffer->data_start);
    free(buffer);
    return;
}