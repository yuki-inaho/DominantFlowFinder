#pragma once
#include <chrono>

class Timer
{
public:
    void tic()
    {
        start = std::chrono::system_clock::now();
    }

    double toc()
    {
        end = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        return elapsed;
    }

    std::chrono::system_clock::time_point start, end;
};