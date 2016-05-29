//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <ctime>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class printer
{
public:
    printer(boost::asio::io_service& io)
        : strand_(io),
          timer1_(io, boost::posix_time::seconds(3)),
          timer2_(io, boost::posix_time::seconds(3)),
          timer3_(io, boost::posix_time::seconds(3)),
          timer4_(io, boost::posix_time::seconds(1)),
          count_(0)
    {
        timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
        timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
        timer3_.async_wait(strand_.wrap(boost::bind(&printer::print3, this)));
        timer4_.async_wait(boost::bind(&printer::print4, this));
    }

    ~printer()
    {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print1()
    {
        if (count_ < 10)
            {
                chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
                time_t now_t = chrono::system_clock::to_time_t(now);
                cout << ctime(&now_t) << " Timer 1: " << count_ << endl;
                ++count_;

                timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
                timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
            }
    }

    void print2()
    {
        if (count_ < 10)
            {
                chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
                time_t now_t = chrono::system_clock::to_time_t(now);
                cout << ctime(&now_t) << " Timer 2: " << count_ << endl;

                ++count_;

                timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
                timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
            }
    }

    void print3()
    {
        if (count_ < 10)
            {
                chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
                time_t now_t = chrono::system_clock::to_time_t(now);
                cout << ctime(&now_t) << " Timer 3: " << count_ << endl;

                ++count_;

                timer3_.expires_at(timer3_.expires_at() + boost::posix_time::seconds(1));
                timer3_.async_wait(strand_.wrap(boost::bind(&printer::print3, this)));
            }
    }

    void print4()
    {
        if (count_ < 10)
            {
                chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
                time_t now_t = chrono::system_clock::to_time_t(now);
                cout << ctime(&now_t) << " Timer 4: " << count_ << endl;

                ++count_;

                timer4_.expires_at(timer4_.expires_at() + boost::posix_time::seconds(1));
                timer4_.async_wait(strand_.wrap(boost::bind(&printer::print4, this)));
            }
    }

private:
    boost::asio::io_service::strand strand_;
    boost::asio::deadline_timer timer1_;
    boost::asio::deadline_timer timer2_;
    boost::asio::deadline_timer timer3_;
    boost::asio::deadline_timer timer4_;
    int count_;
};

int main()
{
    boost::asio::io_service io;
    printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
    io.run();
    t.join();

    return 0;
}
