#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class Printer {
public:
    Printer(boost::asio::io_service& io):
        _timer(io, boost::posix_time::seconds(1)),
        _count(0) {
        _timer.async_wait(boost::bind(&Printer::print, this));
    }

    ~Printer(){
        std::cout << "Final count is " << _count << std::endl;
    }

    void print(){
        if (_count < 5){
            std::cout << _count << std::endl;
            ++_count;

            _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
            _timer.async_wait(boost::bind(&Printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer _timer;
    int _count;
};

int main(){
    boost::asio::io_service io;
    Printer p(io);
    io.run();

    return 0;
}
