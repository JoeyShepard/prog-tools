#include <stdio.h>
#include <unistd.h>

int write_full(int fd,void *data,int size)
{
    int bytes_sent=0;
    while(size-bytes_sent>0)
    {
        int bytes_written=write(fd,data+bytes_sent,size-bytes_sent);
        if (bytes_written<0) return -1;
        bytes_sent+=bytes_written;
    }
    return size;
}

int read_full(int fd,void *data,int size)
{
    //printf("read_full: expectding %d bytes\n",size);
    int bytes_received=0;
    while(size-bytes_received>0)
    {
        //printf("read_full: reading\n");
        int bytes_read=read(fd,data+bytes_received,size-bytes_received);
        //printf("read_full: read %d bytes\n",bytes_read);
        if (bytes_read<=0) return bytes_read;
        bytes_received+=bytes_read;
    }
    return size;
}

