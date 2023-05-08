#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

buffer_t* CreateBuffer(size_t size)
{
    buffer_t* buffer;
    
    buffer = (buffer_t*)malloc(sizeof(buffer_t));
    buffer->data = (char*)malloc(size);
    buffer->totalSize = size;
    buffer->ptr = buffer->data;
    return buffer;
}

void WriteBuffer(buffer_t* buffer, void* data, size_t len)
{
    char* bytes = (char*) data;
    if(len + GetBufferSize(buffer) > buffer->totalSize) {
        printf("ERROR: Buffer Overflow! Please resize! (If you can find out how)\n");
        return;
    }
    
    for(int i = 0; i < len; i++) {
        buffer->ptr[0] = bytes[i];
        buffer->ptr++;
    }
    return;
}

void ResetBuffer(buffer_t* buffer)
{
    buffer->ptr = buffer->data;
    return;
}

size_t GetBufferSize(buffer_t* buffer)
{
    return buffer->ptr - buffer->data;
}

void DeleteBuffer(buffer_t* buffer)
{
    free(buffer->data);
    free(buffer);
    return;
}