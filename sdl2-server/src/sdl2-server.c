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


#define WINDOW_TITLE "none for now"


uint16_t screen[DWIDTH*DHEIGHT];
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
int scale_factor=3;

void info(const char *msg)
{
    printf("Server: %s\n",msg);
}

void error_exit(const char *msg)
{
    info(msg);
    exit(1);
}

void dupdate(void)
{
    SDL_UpdateTexture(texture,NULL,screen,DWIDTH*sizeof(uint16_t));
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void create_window()
{
    //Create SDL2 window
    window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DWIDTH*scale_factor,DHEIGHT*scale_factor,SDL_WINDOW_SHOWN);
    if (window==NULL)
    {
        printf("Server: SDL2 could not create window. SDL error: %s\n", SDL_GetError());
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
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Server: SDL2 did not initialize. SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    
    //Open socket
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1) error_exit("unable to open socket");
    else info("socket opened");

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
        perror("unable to bind address");
        exit(1);
    }
    else info("address bound");

    while(1)
    {
        //Listen for connection
        int listen_result=listen(sockfd,1);
        if (bind_result==-1) error_exit("unable to begin listening");
        else info("listening for connection...");
        
        //Accept connection
        struct sockaddr_in client;
        int client_len=sizeof(client);
        int connfd=accept(sockfd,(struct sockaddr *)&client,&client_len);
        if (connfd==-1) error_exit("unable to accept connection");
        else info("accepted connection");

        //Create SDL2 window for each connection
        info("creating SDL2 window");
        create_window();
        info("SDL2 window created");

        //Wait for messages
        struct pollfd poll_server;
        poll_server.fd=connfd;
        poll_server.events=POLLIN; 
        while(1)
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
                    info("client disconnected by hang up");
                    break;
                }
                else if (poll_server.revents&POLLIN)
                {
                    //Screen data received
                    int bytes_read=read_full(connfd,(char *)screen,sizeof(screen));
                    if (bytes_read==0)
                    {
                        info("client disconnected");
                        break;
                    }
                    else if (bytes_read<0)
                    {
                        info("client disconnected with error");
                        break;
                    }
                    else
                    {
                        //Screen data received - swap endianness
                        for (int i=0;i<DWIDTH*DHEIGHT;i++)
                        {
                            uint16_t pixel=screen[i];
                            pixel=pixel<<8|pixel>>8;
                            screen[i]=pixel;
                        }

                        //Update screen
                        dupdate();

                        //Request next frame
                        int32_t message=htonl(TCP_FRAME);
                        write_full(connfd,&message,sizeof(message));
                    }
                }
            }

            //Handle SDL events
            SDL_Event event;
            bool disconnect_client=false;
            while ((SDL_PollEvent(&event))&&(disconnect_client==false))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        /*
                        //Exit program
                        destroy_window();
                        SDL_Quit();
                        exit(0);
                        */
                        disconnect_client=true;
                        break;
                    case SDL_KEYDOWN:
                        int32_t messages[]={htonl(TCP_KEYPRESS),htonl(event.key.keysym.scancode)};
                        write_full(connfd,messages,sizeof(messages));
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        break;
                }
            }

            //Window closed - disconnect client
            if (disconnect_client==true)
            {
                shutdown(connfd,SHUT_RDWR);
                close(connfd);
                info("closing window");
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

