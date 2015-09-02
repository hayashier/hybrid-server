#ifndef _CONFHET_H_
#define _CONFHET_H_

const int BUF_SIZE = 1024;
const int HTTP1SSL_PORT = 5000;
const int HTTP1_PORT = 5001;
const std::string HTTP1SSL_FILE = "hybrid_server";
const std::string HTTP1_FILE = "server";



// I will add HTTP/2 function in the future.
// HTTP/1.1  version = 1, http = 1, init = -1
// HTTP/2    version = 2, http = 0, init = 0
// HTTP/1.1 →  HTTP/2 version = 2, http = 0, stage = -1

const int version = 1;
const int http = 1;
const int init = -1;

#endif
