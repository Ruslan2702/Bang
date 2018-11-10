#include <string>
#include <unistd.h>     // close()
#include <memory>
#include <functional>


std::string int2ipv4(uint32_t ip);


class Socket {
public:
    Socket() : m_Sd(-1) {}

    Socket(int sd) : m_Sd(sd) {}

    ~Socket() { if (m_Sd > 0) ::close(m_Sd); }

public:
    int sd() const noexcept { return m_Sd; }
    void connect(const std::string &host, int port) noexcept(false);
    void connect(const std::string &host, int port, int timeout) noexcept(false);
    void send(const std::string &s) noexcept(false);
    bool hasData() noexcept(false);
    std::string recv() noexcept(false);
    std::string recv(size_t bytes) noexcept(false);
    std::string recvTimed(int timeout) noexcept(false);
    void setRcvTimeout(int sec, int microsec) noexcept(false);
    void setNonBlocked(bool opt) noexcept(false);
    void setReuseAddr(int sd) noexcept(false);
    void createServerSocket(uint32_t port, uint32_t queue_size) noexcept(false);
    std::shared_ptr<Socket> accept() noexcept(false);
    void close() { ::close(m_Sd); }

    void httpQuery(const std::string &query, std::function<void(const std::string &s)> cb) noexcept(false) {
        send(query);
        std::string res = recv();
        cb(res);
    }

private:
    //Socket(const Socket &s);
    //const Socket& operator=(const Socket &s);
private:
    int m_Sd;
};

