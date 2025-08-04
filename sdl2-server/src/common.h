//Code common to server and test-client

#ifndef __GUARD_TCP_TEST_COMMON
    #define __GUARD_TCP_TEST_COMMON

    #define PORT        50505
    #define BACKLOG     1   //Should only accept one connection at a time

    #define DWIDTH      396
    #define DHEIGHT     224
    #define C_RGB(r,g,b) (((r) << 11) | ((g) << 6) | (b))
    #define COL_MAX     31

    #define FRAME_MS    40  //ie 25 FPS
    #define FPS         (1000/FRAME_MS)
    #define DELAY_FPS   (1000000/FPS)
    #define DELAY_MS    1000

    enum TcpMsgType
    {
        TCP_FRAME_DATA=0x101,
        TCP_FRAME_READY,
        TCP_KEYPRESS,
        TCP_CLIENT_BIG_ENDIAN,
        TCP_CLIENT_LITTLE_ENDIAN,
    };

    int write_full(int fd,void *data,int size);
    int read_full(int fd,void *data,int size);

#endif
