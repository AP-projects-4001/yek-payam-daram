#ifndef TIMEKHODAM_H
#define TIMEKHODAM_H
#include <iostream>
#include <exception>
#include <stdexcept>

class TimeKhodam
{
public:
    TimeKhodam();


protected:
    int hour;
    int minute;

public:
    TimeKhodam(int hour_inp);
    int getter_hour();
    int getter_min();
    void setter_hour(int hour_inp);
    void setter_min(int min_inp);
    std::string time_of_day() const;
    void compare(TimeKhodam t2);
    friend std::istream& operator >> (std::istream& in, TimeKhodam& t);
    friend std::ostream& operator << (std::ostream& out, TimeKhodam& t);
    friend bool operator<(const TimeKhodam& t1, const TimeKhodam& t2);
    friend bool operator<=(const TimeKhodam& t1, const TimeKhodam& t2);
    friend bool operator>(const TimeKhodam& t1, const TimeKhodam& t2);
    friend bool operator>=(const TimeKhodam& t1, const TimeKhodam& t2);
    friend TimeKhodam operator+(const TimeKhodam& t1, const TimeKhodam& t2);
    operator std::string() const;

};

class TimeException : public std::exception{
private:
    std::string message;

public:
    TimeException(std::string& msg) : message(msg){}
    TimeException(std::string maseg) : message(maseg){}
    std::string what()
    {
        return message;
    }

};

#endif // TIMEKHODAM_H
