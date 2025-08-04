#include <netinet/in.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#include "common.h"


#define WINDOW_TITLE "SDL2 wrapper for fx-CG50"

enum
{
    ENDIAN_NONE,
    ENDIAN_LITTLE,
    ENDIAN_BIG
};

uint16_t screen[DWIDTH*DHEIGHT];
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
int scale_factor=3;
int server_endian=ENDIAN_NONE;
int client_endian=ENDIAN_NONE;

void error_exit(const char *msg)
{
    printf("%s",msg);
    exit(EXIT_FAILURE);
}

void create_window()
{
    //Create SDL2 window
    window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DWIDTH*scale_factor,DHEIGHT*scale_factor,SDL_WINDOW_SHOWN);
    if (window==NULL)
    {
        printf("SDL2 could not create window. SDL error: %s\n", SDL_GetError());
        exit(1);
    }

    //Draw to texture
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB565,SDL_TEXTUREACCESS_STREAMING,DWIDTH,DHEIGHT);
}

void destroy_window()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int main(int argc, char *argv[])
{
    //Determine local endianness to know whether grapics data from client needs to be swapped
    //Generally better to use htonl etc but do processing here rather than on sh4 inside qemu
    int endian_test=1;
    if (*((char *)&endian_test)==1) server_endian=ENDIAN_LITTLE;
    else server_endian=ENDIAN_BIG;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("SDL2 did not initialize. SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    
    //Open socket
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1) error_exit("Unable to open socket\n");
    else printf("Socket opened\n");

    //Stop "Address already in use" error when restarting server too quickly
    int option=1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));

    //Bind address
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(PORT);
    int bind_result=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if (bind_result==-1)
    {
        perror("Unable to bind address");
        exit(1);
    }
    else printf("Address bound\n");

    while(1)
    {
        //Listen for connection
        int listen_result=listen(sockfd,1);
        if (bind_result==-1) error_exit("Unable to begin listening\n");
        else printf("Listening for connection...\n");
        
        //Accept connection
        struct sockaddr_in client;
        int client_len=sizeof(client);
        int connfd=accept(sockfd,(struct sockaddr *)&client,&client_len);
        if (connfd==-1) error_exit("Unable to accept connection\n");
        else printf("Connection accepted\n");

        //Create SDL2 window for each connection
        printf("Creating SDL2 window\n");
        create_window();
        printf("SDL2 window created\n");

        //Wait for messages
        struct pollfd poll_server;
        poll_server.fd=connfd;
        poll_server.events=POLLIN; 
        bool disconnect=false;
        while(disconnect==false)
        {
            //Check if screen data received
            int event_count=poll(&poll_server,1,0);
            if (event_count==0)
            {
                //No events to process
            }
            else
            {
                if (poll_server.revents&POLLHUP)
                {
                    printf("Client disconnected by hang up\n");
                    disconnect=true;
                    break;
                }
                else if (poll_server.revents&POLLIN)
                {
                    //Process messages from client
                    bool first_message=true;
                    int messages_left=1;
                    int tcp_type;
                    uint32_t message;
                    void *message_ptr=&message;
                    int message_size=sizeof(message);
                    while (messages_left>0)
                    {
                        int bytes_read=read_full(connfd,message_ptr,message_size);
                        if (bytes_read==0)
                        {
                            //No error available - just disconnection
                            printf("Client disconnected\n");
                            disconnect=true;
                            break;
                        }
                        else if (bytes_read<0)
                        {
                            //Error - print error message for errno
                            perror("Client disconnected");
                            disconnect=true;
                            break;
                        }
                        else
                        {
                            if (first_message==true)
                            {
                                tcp_type=ntohl(message);
                                switch (tcp_type)
                                {
                                    case TCP_FRAME_DATA:
                                        message_ptr=screen;
                                        message_size=sizeof(screen);
                                        messages_left++;
                                        break;
                                    case TCP_CLIENT_LITTLE_ENDIAN:
                                        client_endian=ENDIAN_LITTLE;
                                        break;
                                    case TCP_CLIENT_BIG_ENDIAN:
                                        client_endian=ENDIAN_BIG;
                                        break;
                                    default:
                                        printf("Unknown TCP message type: 0x%X\n",message);    
                                        exit(EXIT_FAILURE);
                                }
                                first_message=false;
                            }
                            else
                            {
                                switch (tcp_type)
                                {
                                    case TCP_FRAME_DATA:
                                        //Screen data received
                                        if (server_endian==ENDIAN_NONE)
                                        {
                                            error_exit("Server endianness not set\n");
                                        }
                                        else if (client_endian==ENDIAN_NONE)
                                        {
                                            error_exit("Client endianness not set\n");
                                        }

                                        //Swap endianness of screen data if endianness of client and server differ
                                        if (client_endian!=server_endian)
                                        {
                                            for (int i=0;i<DWIDTH*DHEIGHT;i++)
                                            {
                                                uint16_t pixel=screen[i];
                                                pixel=pixel<<8|pixel>>8;
                                                screen[i]=pixel;
                                            }
                                        }

                                        //Update screen
                                        SDL_UpdateTexture(texture,NULL,screen,DWIDTH*sizeof(uint16_t));
                                        SDL_RenderCopy(renderer,texture,NULL,NULL);
                                        SDL_RenderPresent(renderer);

                                        //Ready to receive next frame
                                        int32_t message=htonl(TCP_FRAME_READY);
                                        int result=write_full(connfd,&message,sizeof(message));
                                        if (result<0)
                                        {
                                            perror("Unable to send frame ready message");
                                            exit(EXIT_FAILURE);
                                        }

                                        break;
                                    default:
                                        //Should never reach here unless error in messages_left calculation above
                                        printf("Unexpected data from server 0x%X for message type 0x%X\n",message,tcp_type);
                                        exit(EXIT_FAILURE);
                                }
                            }
                        }
                        messages_left--;
                    }
                }
            }
            
            //Exit loop if no longer connected
            if (disconnect==true) break;

            //Handle SDL events
            SDL_Event event;
            bool disconnect_client=false;
            while ((SDL_PollEvent(&event))&&(disconnect_client==false))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        disconnect_client=true;
                        break;
                    case SDL_KEYDOWN:
                        int32_t messages[]={htonl(TCP_KEYPRESS),htonl(event.key.keysym.scancode)};
                        int result=write_full(connfd,messages,sizeof(messages));
                        if (result<0)
                        {
                            perror("Unable to send keypress data");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        //None of the examples with SDL_RenderReadPixels worked even when adjusted for 16bit format so output raw data
                        FILE *fptr=fopen("screenshot/screenshot.raw","w");
                        fwrite(screen,2,DWIDTH*DHEIGHT,fptr);
                        fclose(fptr);
                        printf("Screenshot saved to screenshot/screenshot.raw\n");
                        break;
                }
            }

            //Window closed - disconnect client
            if (disconnect_client==true)
            {
                shutdown(connfd,SHUT_RDWR);
                close(connfd);
                printf("Closing SDL2 window\n");
                break;
            }

            //Wait 1ms
            usleep(DELAY_MS);
        }

        //Client disconnected - close SDL2 window
        destroy_window();
    }

    //Close socket
    close(sockfd);

    return 0;    
}

