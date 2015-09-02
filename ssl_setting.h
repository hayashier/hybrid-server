#ifndef _SSLSET_H_
#define _SSLSET_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <event.h>
#include <event2/listener.h>
#include <event2/bufferevent_ssl.h>
#include <fstream>

#include "http1response.h"
#include "http1header.h"
#include "http1parser.h"


class SSL_Controller {
public:
    SSL_Controller();
    ~SSL_Controller();
    static void ssl_readcb(struct bufferevent *bev, void *arg);
    static void ssl_acceptcb(struct evconnlistener *serv, int sock, struct sockaddr *sa, int sa_len, void *argv);
    static SSL_CTX *evssl_init();
    static void send_response(struct bufferevent* bev);
};

#endif
