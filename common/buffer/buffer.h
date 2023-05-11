#ifndef BUFFER_H
#define BUFFER_H

typedef struct buffer_s
{
    char*  dataStart;
    char*  dataEnd;
    size_t allocatedLength;
} buffer_t;

buffer_t* CreateBuffer(size_t size);
void      WriteBuffer(buffer_t* buffer, void* data, size_t len);
void      EraseBuffer(buffer_t* buffer);

size_t    GetBufferSize(buffer_t* buffer);
void      DeleteBuffer(buffer_t* buffer);

#endif // BUFFER_H
