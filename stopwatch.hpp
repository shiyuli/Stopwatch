#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#ifndef _MSC_VER
#define STOPWATCH_GCC
#endif

#include <chrono>
#include <variant>
#include <ctime>
#include <ostream>

typedef std::chrono::time_point<std::chrono::system_clock> time_point_t;
typedef std::chrono::duration<double> duration_t;

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch() = default;

    void start();
    void stop();
    duration_t split() const;
    std::ostream& split(std::ostream& ostream) const;
    static std::ostream& current_time(std::ostream& ostream);

private:
    static std::ostream& time_stream(std::ostream& ostream, time_point_t time);
    static std::ostream& time_stream(std::ostream& ostream, duration_t time);

    static time_point_t get_time();

private:
    enum status
    {
        started,
        stopped
    }
#ifdef STOPWATCH_GCC
    status_;
#else
    status__;

    status get_status()
    {
        return status__;
    }

    void put_status(status status)
    {
        status__ = status;
    }

    __declspec(property(get = get_status, put = put_status)) status status_;
#endif

private:
    time_point_t started_time_;
    time_point_t stopped_time_;
};

Stopwatch::Stopwatch()
{
    status_ = status::stopped;
}

void Stopwatch::start()
{
    started_time_ = get_time();
    status_ = status::started;
}

void Stopwatch::stop()
{
    stopped_time_ = get_time();
    status_ = status::stopped;
}

duration_t Stopwatch::split() const
{
    return get_time() - started_time_;
}

std::ostream& Stopwatch::split(std::ostream& ostream) const
{
    return time_stream(ostream, get_time() - started_time_);
}

std::ostream& Stopwatch::current_time(std::ostream& ostream)
{
    return time_stream(ostream, get_time());
}

std::ostream& Stopwatch::time_stream(std::ostream& ostream, time_point_t time)
{
    std::time_t temp_time = std::chrono::system_clock::to_time_t(time);

#ifdef STOPWATCH_GCC
    ostream << ctime(&temp_time);
#else
    char* buffer = new char[26];
    ctime_s(buffer, 26, &temp_time);
    ostream << buffer;

    delete[] buffer;
    buffer = nullptr;
#endif

    return ostream;
}

std::ostream& Stopwatch::time_stream(std::ostream& ostream, duration_t time)
{
    ostream << time.count();;

    return ostream;
}

time_point_t Stopwatch::get_time()
{
    return std::chrono::system_clock::now();
}

#else
#endif //STOPWATCH_HPP_
