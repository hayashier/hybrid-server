#include <iostream>
#include <unistd.h>
#include "ssl_setting.h"
#include "hybrid_server.h"
using namespace std;

int http1ssl() {
    SSL_CTX *ctx;
    struct evconnlistener *listener;
    struct event_base *evbase;
    struct sockaddr_in sin;
    
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(HTTP1SSL_PORT);
    sin.sin_addr.s_addr = htonl(0x7f000001);
    ctx = SSL_Controller::evssl_init();
    if (ctx == NULL) return 1;
    evbase = event_base_new();
    listener = evconnlistener_new_bind(
                                    evbase, SSL_Controller::ssl_acceptcb, (void *) ctx,
                                    LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 1024,
                                    (struct sockaddr *)&sin, sizeof(sin));

    event_base_loop(evbase, 0);

    evconnlistener_free(listener);
    SSL_CTX_free(ctx);
    return 0;
}
