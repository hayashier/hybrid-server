#include "ssl_setting.h"

char buf[BUF_SIZE];

void SSL_Controller::ssl_readcb(struct bufferevent *bev, void *arg) {
    struct evbuffer *in = bufferevent_get_input(bev);

    //printf("Received %zu bytes\n", evbuffer_get_length(in));
    //printf("----- data ----\n");
    //printf("%.*s\n", (int)evbuffer_get_length(in), evbuffer_pullup(in, -1));

    //int nread;
    evbuffer_copyout(in, buf, (int)evbuffer_get_length(in));
    //printf("--- %d bytes copy\n", nread);
    //bufferevent_write_buffer(bev, in);
    SSL_Controller::send_response(bev);
    evbuffer_drain(in, -1);
}

void SSL_Controller::ssl_acceptcb(struct evconnlistener *serv, int sock, struct sockaddr *sa, int sa_len, void *arg) {
    struct event_base *evbase;
    struct bufferevent *bev;
    SSL_CTX *server_ctx;
    SSL *client_ctx;
    server_ctx = (SSL_CTX *) arg;
    client_ctx = SSL_new(server_ctx);
    evbase = evconnlistener_get_base(serv);
    bev = bufferevent_openssl_socket_new(evbase, sock, client_ctx,
                                        BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_enable(bev, EV_READ);
    bufferevent_setcb(bev, SSL_Controller::ssl_readcb, NULL, NULL, NULL);
    return;
}
void SSL_Controller::send_response(struct bufferevent* bev)
{
    //Need to impelement basename()
    std::string path = "";
    std::string path_string;
    std::string exe = HTTP1SSL_FILE;
    std::size_t pos = exe.rfind('/');
    if (pos != std::string::npos) {
        exe = exe.substr(pos + 1);
    }
    path_string = HTTP1_Parser::get_requestline_path(buf);
    path_string = HTTP1_Parser::argv_path_analyzer(path_string, path.c_str(), exe.c_str());
    std::ifstream output_file(path_string.c_str());
    int body_content_length = 0;
    std::vector<std::string> message_body;
    int is_file_exist = output_file.fail();
    HTTP1_Response::make_body(message_body, body_content_length, output_file);
    std::string recv_str = "";
    recv_str.append(buf);
    std::string server_response;
    std::vector<std::string> header = HTTP1_Response::make_header(version, body_content_length, is_file_exist, "");
    server_response = HTTP1_Response::make_response(header, message_body);
    bufferevent_write(bev, server_response.c_str(), server_response.length());
}

SSL_CTX *SSL_Controller::evssl_init() {
    SSL_CTX *server_ctx;

    SSL_load_error_strings();
    SSL_library_init();

    if (!RAND_poll()) return NULL;

    server_ctx = SSL_CTX_new(SSLv23_server_method());

    if(!SSL_CTX_use_certificate_chain_file(server_ctx, "./key/cert") ||
        !SSL_CTX_use_PrivateKey_file(server_ctx, "./key/pkey", SSL_FILETYPE_PEM)) {

        std::cout << "Could not recognize certification." << std::endl;
        std::cout << "Excute following three commands" << std::endl;
        std::cout << "openssl genrsa -out pkey 2048" << std::endl;
        std::cout << "openssl req -new -key pkey -out cert.req" << std::endl;
        std::cout << "openssl x509 -req -days 365 -in cert.req -signkey pkey -out cert" << std::endl;
        return NULL;
    }
    SSL_CTX_set_options(server_ctx, SSL_OP_NO_SSLv2);

    return server_ctx;
}
