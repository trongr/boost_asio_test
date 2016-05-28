#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int main(){
    boost::asio::io_service io;
    cout << "starting, please wait...." << endl;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.wait();
    std::cout << "Hello, world!" << std::endl;

    cout << "trying to wait again on expired timer" << endl;
    t.wait();
    cout << "returning from expired timer. should be immediately following previous print" << endl;

    return 0;
}
