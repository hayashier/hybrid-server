CC = g++
HTTP1SSL = hybrid_server
HTTP1 = server
HTTP1SSL_SOURCE = main.cpp hybrid_server.cpp ssl_setting.cpp http1header.cpp http1parser.cpp http1response.cpp
HTTP1_SOURCE = server.cpp socket.cpp http1header.cpp http1parser.cpp http1response.cpp

.PHONY: all clean

all: $(HTTP1SSL) $(HTTP1)

$(HTTP1SSL): $(HTTP1SSL_SOURCE)
	g++ $(HTTP1SSL_SOURCE) -o $(HTTP1SSL) -levent -levent_openssl -lssl -lcrypto -O0 -Wall  -g -std=c++11

$(HTTP1): $(HTTP1_SOURCE)
	g++ $(HTTP1_SOURCE) -o $(HTTP1) -g -std=c++11 -O0 -Wall


clean:
	rm -rf *.o $(HTTP1SSL) $(HTTP1)
