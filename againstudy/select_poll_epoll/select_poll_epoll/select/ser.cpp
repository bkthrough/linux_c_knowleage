#include"../unp.h"
#include<malloc.h>

typedef struct server_context_st
{
    int cli_cnt; //
    int clifds[SIZE];
    fd_set allfds;
    int maxfd;
}server_context_st;

static server_context_st *s_srv_ctx = NULL;

int server_init()
{
    s_srv_ctx = (server_context_st*)malloc(sizeof(server_context_st));
    if(s_srv_ctx == NULL)
        return -1;
    memset(s_srv_ctx, 0, sizeof(server_context_st));
    for(int i=0; i<SIZE; ++i)
    {
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}
void server_uninit()
{
    if(s_srv_ctx)
    {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

int create_server_proc(const char *ip, short port)
{
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(port);
    addrSer.sin_addr.s_addr = inet_addr(ip);

    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(fd, (struct sockaddr*)&addrSer, addrlen);
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    listen(fd, LISTENQ);
    return fd;
}

int accept_client_proc(int srvfd)
{
    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);

    int clifd;
ACCEPT:
    clifd = accept(srvfd, (struct sockaddr*)&addrCli, &addrlen);
    if(clifd == -1)
    {
        goto ACCEPT;
    }
    printf("accept a new client: %s:%d\n",inet_ntoa(addrCli.sin_addr),addrCli.sin_port);

    int i;
    for(i=0; i<SIZE; ++i)
    {
        if(s_srv_ctx->clifds[i] == -1)
        {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }
    if(i == SIZE)
    {
        printf("Server Over Load.\n");
        return -1;
    }
}

void handle_client_msg(int fd, char *buf)
{
    printf("recv buf is:> %s\n",buf);
    send(fd, buf, strlen(buf)+1, 0);
}

void recv_client_msg(fd_set *readfds)
{
    int clifd;
    char buffer[256];
    int n;
    for(int i=0; i<s_srv_ctx->cli_cnt; ++i)
    {
        clifd = s_srv_ctx->clifds[i];
        if(clifd < 0)
            continue;
        if(FD_ISSET(clifd, readfds))
        {
           n = recv(clifd, buffer, 256, 0);
           if(n <= 0)
           {
               FD_CLR(clifd, &s_srv_ctx->allfds);
               close(clifd);
               s_srv_ctx->clifds[i] = -1;
               s_srv_ctx->cli_cnt--;
               continue;
           }

           handle_client_msg(clifd, buffer);

        }
    }
}

int handle_client_proc(int srvfd)
{
    int clifd = -1;
    int retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;

    while(1)
    {
        FD_ZERO(readfds);
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;
        tv.tv_sec = 30;
        tv.tv_usec = 0;

        int i;
        for(i=0; i<s_srv_ctx->cli_cnt; ++i)
        {
            clifd = s_srv_ctx->clifds[i];
            FD_SET(clifd, readfds);
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }

        retval = select(s_srv_ctx->maxfd+1, readfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            perror("select");
            return -1;
        }
        if(retval == 0)
        {
            printf("server time out.\n");
            continue;
        }

        //accept
        if(FD_ISSET(srvfd, readfds))
        {
            accept_client_proc(srvfd);
        }
        else
        {
            recv_client_msg(readfds);
        }
    }
}

int main(int argc, char *argv[])
{
    int sockSer;
    if(server_init() < 0)
        perror("server_init");
    sockSer = create_server_proc(IPADDR, PORT);
    if(sockSer < 0)
    {
        perror("create_server_porc");
        goto err;
    }
    handle_client_proc(sockSer);
    return 0;
err:
    server_uninit();
    return -1;
}
