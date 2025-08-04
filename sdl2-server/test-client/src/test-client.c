#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

//Reuse constants and struct from server
#include "common.h"


uint16_t screen[DHEIGHT*DWIDTH];

void error_exit(const char *msg)
{
    printf("%s",msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    //Open socket
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1) error_exit("Unable to open socket\n");
    else printf("Socket opened\n");

    //Connect to server
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(PORT);
    int connect_result=connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    if (connect_result==-1) error_exit("Unable to connect\n");
    else printf("Connected to server\n");

    //Notify server of endianness
    int endian_test=1;
    int32_t message;
    if (*((char *)&endian_test)==1) message=htonl(TCP_CLIENT_LITTLE_ENDIAN);
    else message=htonl(TCP_CLIENT_BIG_ENDIAN);
    int result=write_full(sockfd,&message,sizeof(message));
    if (result<0)
    {
        perror("Unable to send endianness");
        exit(EXIT_FAILURE);
    }

    //Polling structure
    struct pollfd poll_client;
    poll_client.fd=sockfd;
    poll_client.events=POLLIN;
    
    //Test pattern
    int colors[3]={COL_MAX,0,0};
    int phase=0;
    enum PhaseDirs {PHASE_DOWN,PHASE_UP};
    struct PhaseType
    {
        int dir;
        int index;
    } phases[6]={
        {PHASE_UP,      1},
        {PHASE_DOWN,    0},
        {PHASE_UP,      2},
        {PHASE_DOWN,    1},
        {PHASE_UP,      0},
        {PHASE_DOWN,    2},
    };

    //Timing for test pattern
    int ms_elapsed=0;

    //Usage message to user
    printf("Press ESC to exit...\n");

    //Send test screen patterns and receive key presses
    bool disconnect=false;
    bool frame_ready=true;
    while(1)
    { 
        //Time for new frame?
        ms_elapsed++;
        if ((ms_elapsed>=FRAME_MS)&&(frame_ready))
        {
            //Reset frame counter
            ms_elapsed=0;

            //Don't send another frame until server is ready
            frame_ready=false;

            //Generate test frame
            if (phases[phase].dir==PHASE_UP)
            {
                colors[phases[phase].index]++;
                if (colors[phases[phase].index]==COL_MAX)
                {
                    phase++;
                    if (phase==6) phase=0;
                }
            }
            else if (phases[phase].dir==PHASE_DOWN)
            {
                colors[phases[phase].index]--;
                if (colors[phases[phase].index]==0)
                {
                    phase++;
                    if (phase==6) phase=0;
                }
            }

            for (int i=0;i<DHEIGHT*DWIDTH;i++)
                screen[i]=C_RGB(colors[0],colors[1],colors[2]);

            //Send screen data
            uint32_t message=htonl(TCP_FRAME_DATA);
            int result=write_full(sockfd,&message,sizeof(message));
            if (result<0)
            {
                perror("Error while writing data");
                disconnect=true;
                break;
            }
            result=write_full(sockfd,(char *)screen,sizeof(screen));
            if (result<0)
            {
                perror("Error while writing data");
                disconnect=true;
                break;
            }
        }

        //Exit loop and disconnect
        if (disconnect) break;

        //Check for messages from server
        int event_count=poll(&poll_client,1,0);
        if (event_count==0)
        {
            //No events to process
        }
        else
        {
            if (poll_client.revents&POLLHUP)
            {
                error_exit("Server disconnected by hang up\n");
            }
            else if (poll_client.revents&POLLIN)
            {
                //Data received from server
                bool first_message=true;
                int messages_left=1,tcp_type;
                uint32_t message;
                while (messages_left>0)
                {
                    int bytes_read=read_full(sockfd,&message,sizeof(message));
                    if (bytes_read==0)
                    {
                        printf("Server disconnected\n");
                        disconnect=true;
                        break;
                    }
                    else if (bytes_read<0)
                    {
                        perror("Server disconnected with error");
                        disconnect=true;
                        break;
                    }
                    else
                    {
                        message=ntohl(message); 
                        if (first_message==true)
                        {
                            tcp_type=message;
                            switch (tcp_type)
                            {
                                case TCP_FRAME_READY:
                                    frame_ready=true;
                                    break;
                                case TCP_KEYPRESS:
                                    messages_left++;
                                    break;
                                default:
                                    printf("Unknown TCP message type: 0x%X\n",message);    
                                    disconnect=true;
                            }
                            first_message=false;
                        }
                        else
                        {
                            switch (tcp_type)
                            {
                                case TCP_KEYPRESS:
                                    printf("Keypress from server - %d\n",message);
                                    if (message==41)
                                    {
                                        printf("ESC pressed - exiting\n");
                                        disconnect=true;
                                    }
                                    break;
                                default:
                                    //Should never reach here unless error in message_count calculation above
                                    printf("Unexpected data from server - %d\n",message);
                                    disconnect=true;
                            }
                        }
                    }
                    messages_left--;
                }
            }
        }

        //Exit loop and disconnect
        if (disconnect) break;

        //Wait 1ms
        usleep(DELAY_MS);
    }

    //Close socket
    close(sockfd);

    return 0;    
}

