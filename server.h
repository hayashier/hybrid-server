#ifndef _SERVERHET_H_
#define _SERVERHET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <errno.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <future>
#include <thread>

#include "configure.h"

#include "http1response.h"
#include "http1header.h"
#include "http1parser.h"
#include "socket.h"

int http1();

#endif
