//
// Created by lab on 2021/3/29.
//

#include <iostream>
#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

public:
    Timer()
    {
        tic();
    }
    void tic()
    {
        start = std::chrono::system_clock::now();
    }
    double toc()
    {
        end = std::chrono::system_clock::now();
        // 除以1000返回的是ms
        // 除以1000000返回的是m
        return (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
    }
};

