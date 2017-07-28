#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <event.h>
#include <evhttp.h>

void reqHandler(struct evhttp_request *req,void *arg)
{
    struct evbuffer *buf = evbuffer_new();

    // 发送响应
    evbuffer_add_printf(buf, "Thanks for the request");
    evhttp_send_reply(req,HTTP_OK,"Client",buf);

    evbuffer_free(buf);
    return;
}

int main(int argc,char **argv)
{
    short port = 8000;
    const char *addr = "192.168.1.187";
    struct evhttp *httpserv = NULL;

    event_init();
        // 启动http服务
    httpserv = evhttp_start(addr,port);
    printf("Server started on port %d\n",port);
    // 设置回调
    evhttp_set_gencb(httpserv, reqHandler,NULL);
    printf("Server started on port %d\n",port);

    event_dispatch();

    return 0;
}
