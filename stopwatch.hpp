#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#if (_MSC_BUILD && __cplusplus)
#define STOPWATCH_WIN_BUILD
#elif (__GNUC__ && __cplusplus)
#define STOPWATCH_GCC_BUILD
#endif

#ifdef _WIN32
#define STOPWATCH_WIN_RUN
#else
#define STOPWATCH_NIX_RUN
#endif

#ifdef STOPWATCH_WIN_BUILD
#define sprintf sprintf_s
#endif

#ifdef STOPWATCH_WIN_RUN
#include <windows.h>
#define sleep Sleep
#else
#include <unistd.h>
#endif

#include <chrono>
#include <ctime>
#include <ostream>
#include <vector>
#include <string>

typedef std::chrono::time_point<std::chrono::system_clock> time_point_t;
typedef std::chrono::duration<double> duration_t;

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch();

    void start();
    void stop();
    double split() const;
    std::ostream& split(std::ostream& ostream) const;
    duration_t split_raw() const;
    std::string splits() const;
    std::vector<duration_t> splits_raw() const;
    static std::ostream& now(std::ostream& ostream);

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
#ifdef STOPWATCH_WIN_BUILD
    status__;

    status get_status() const
    {
        return status__;
    }

    void put_status(status status)
    {
        status__ = status;
    }

    __declspec(property(get = get_status, put = put_status)) status status_;
#else
    status_;
#endif

private:
    time_point_t started_time_;
    time_point_t stopped_time_;
    std::vector<duration_t>* splits_;
};

inline Stopwatch::Stopwatch()
{
    status_ = status::stopped;
    splits_ = new std::vector<duration_t>();
}

inline Stopwatch::~Stopwatch()
{
    delete splits_;
    splits_ = nullptr;
}

inline void Stopwatch::start()
{
    started_time_ = get_time();
    status_ = status::started;
}

inline void Stopwatch::stop()
{
    stopped_time_ = get_time();
    status_ = status::stopped;
}

inline double Stopwatch::split() const
{
    return split_raw().count();
}

inline std::ostream& Stopwatch::split(std::ostream& ostream) const
{
    return time_stream(ostream, split_raw());
}

inline duration_t Stopwatch::split_raw() const
{
    const duration_t duration = get_time() - started_time_;
    splits_->push_back(duration);

    return duration;
}

inline std::string Stopwatch::splits() const
{
    std::string splits;
    const int total(static_cast<int>(splits_->size()));

    int index(0);
    for (duration_t split : *splits_)
    {
        char buffer[255];
        sprintf(buffer, "split(%d) %f s", index++, split.count());

        splits.append(buffer);

        if (index < total)
        {
            splits.append(" | ");
        }
    }

    return splits;
}

inline std::vector<duration_t> Stopwatch::splits_raw() const
{
    return *splits_;
}

inline std::ostream& Stopwatch::now(std::ostream& ostream)
{
    return time_stream(ostream, get_time());
}

inline std::ostream& Stopwatch::time_stream(std::ostream& ostream, time_point_t time)
{
    std::time_t temp_time = std::chrono::system_clock::to_time_t(time);

#ifdef STOPWATCH_WIN_BUILD
    char* buffer = new char[26];
    ctime_s(buffer, 26, &temp_time);
    ostream << buffer;

    delete[] buffer;
    buffer = nullptr;
#else
    ostream << ctime(&temp_time);
#endif

    return ostream;
}

inline std::ostream& Stopwatch::time_stream(std::ostream& ostream, duration_t time)
{
    ostream << time.count();;

    return ostream;
}

inline time_point_t Stopwatch::get_time()
{
    return std::chrono::system_clock::now();
}

#else
#endif //STOPWATCH_HPP_
