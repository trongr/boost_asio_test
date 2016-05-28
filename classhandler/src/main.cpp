#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class printer {
public:
    printer(boost::asio::io_service& io)
        : timer_(io, boost::posix_time::seconds(1)),
          count_(0){

    }
}

int main(){
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

    int count = 0;
    t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

    io.run();

    std::cout << "Final count is " << count << std::endl;

    return 0;
}
