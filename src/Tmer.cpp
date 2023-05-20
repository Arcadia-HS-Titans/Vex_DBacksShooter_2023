#include "Timer.h"

Timer::Timer(std::string &&name) {
    start(name);
}

void Timer::start(std::string name) {
    startTime = std::chrono::high_resolution_clock::now();
    this->name = std::move(name);
}

void Timer::stop(bool record) {
    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
    time = end-start;
    //uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
}

long long Timer::getTime() {
    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
    time = end-start;
    return time;
}

Timer::~Timer() {
    stop(false);
}