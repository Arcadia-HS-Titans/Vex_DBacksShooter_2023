#ifndef OPENGLEXPERIMENTATION_TIMER_H
#define OPENGLEXPERIMENTATION_TIMER_H

#include <chrono>
#include <string>


struct Timer {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> startTime{};
    long long time{};
    std::string name{};

    /**
     * Once constructed, initialized startTime with the current time
     */
    explicit Timer(std::string &&name);
    ~Timer();

    /**
     * Made in case the same object wants to reset its startTime
     */
    void start(std::string name = "");

    /**
     * Stops by subtracting the end and start time
     */
    void stop(bool record = true);

    /**
     * @return The time it took in microseconds
     */
    [[nodiscard]] long long getTime();
};


#endif //OPENGLEXPERIMENTATION_TIMER_H
