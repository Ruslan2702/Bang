#include <iostream>
#include <stdexcept>
#include <memory>
#include <errno.h>
#include <string.h>
#include "socket.hpp"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " host port" << std::endl;
        return 0;
    }

    try {
        std::string host(argv[1]);
        int port = std::stoi(argv[2]);

        Socket s;
        s.connect(host, port, /*timeout, sec*/5);

        s.send("It works");

    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}