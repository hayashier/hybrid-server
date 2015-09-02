#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include "configure.h"
#include "hybrid_server.h"


int main() {
    int pid;
    pid = fork();
    if (pid == -1) {
        std::cout << "Fork error..." << std::endl;
        exit(1);
    }
    else if (pid == 0) {
        if (execl("server", "server", NULL) == -1) {
            std::cout << "Exec error..." << std::endl;
            exit(1);
        }
    }
    else {
        http1ssl();
    }
    return 0;
}
