#include "timekhodam.h"
#include <iostream>
#include <string>


using namespace std;

TimeKhodam::TimeKhodam() {
    hour = 0;
    minute = 0;
}

TimeKhodam::TimeKhodam(int hour_inp) {

    hour = hour_inp;
    minute = 0;
}

int TimeKhodam::getter_hour() {
    return hour;
}
int TimeKhodam::getter_min() {
    return minute;
}
void TimeKhodam::setter_hour(int hour_inp) {
    if (hour_inp > 24 || hour_inp < 0)
    {
        TimeException error("wrong hour!");
        throw error;
    }
    else
        hour = hour_inp;
}
void TimeKhodam::setter_min(int min_inp) {
    if (min_inp > 59 || min_inp < 0)
    {
        TimeException error("wrong minute!");
        throw error;
    }
    else
        minute = min_inp;
}
string TimeKhodam::time_of_day() const
{
    if (hour >= 0 && hour <= 11)
        return "Morning";
    else if (hour == 12 && minute == 0)
        return "Afternoon";
    else if (hour >= 12 && hour <= 16)
        return "Evening";
    else
        return "Night";
}
void TimeKhodam::compare(TimeKhodam t2)
{
    if (hour > t2.hour)
    {
        cout << "secend time is grater" << endl;
    }
    else if (hour == t2.hour)
    {
        if (minute < t2.minute)
            cout << "secend time is grater" << endl;
        else if (minute == t2.minute)
            cout << "equal" << endl;
        else
            cout << "secend time is smaller" << endl;
    }
    else
    {
        cout << "secend time is smaller" << endl;
    }
}

istream& operator >> (istream& in, TimeKhodam& t)
{
    cout << "enter hour:" << endl;
    int hour;
    in >> hour;
    t.setter_hour(hour);
    int minute;
    cout << "enter minute:" << endl;
    in >> minute;
    t.setter_min(minute);
    return in;
}

ostream& operator << (ostream& out, TimeKhodam& t)
{
    out << t.getter_hour() << " : " << t.getter_min() << endl;
    out << t.time_of_day() << endl;
    return out;
}


bool operator<(const TimeKhodam& t1, const TimeKhodam& t2)
{
    bool b;

    if (t1.hour < t2.hour)
        b = true;

    else if (t1.hour == t2.hour)
    {
        if (t1.minute < t2.minute)
            b = true;
    }
    else
        b = false;

    return b;
}

bool operator>(const TimeKhodam& t1, const TimeKhodam& t2)
{
    bool b;

    if (t1.hour > t2.hour)
        b = true;

    else if (t1.hour == t2.hour)
    {
        if (t1.minute > t2.minute)
            b = true;
    }
    else
        b = false;

    return b;
}

bool operator>=(const TimeKhodam& t1, const TimeKhodam& t2)
{
    bool b;

    if (t1.hour > t2.hour)
        b = true;

    else if (t1.hour == t2.hour)
    {
        if (t1.minute > t2.minute)
            b = true;
        else if (t1.minute == t2.minute)
            b = true;
    }
    else
        b = false;

    return b;
}

bool operator<=(const TimeKhodam& t1, const TimeKhodam& t2)
{
    bool b;

    if (t1.hour < t2.hour)
        b = true;

    else if (t1.hour == t2.hour)
    {
        if (t1.minute < t2.minute)
            b = true;
        else if (t1.minute == t2.minute)
            b = true;
    }
    else
        b = false;

    return b;
}

TimeKhodam operator+(const TimeKhodam& t1, const TimeKhodam& t2)
{
    TimeKhodam result{ 0 };
    result.hour = t1.hour + t2.hour;
    result.minute = t1.minute + t2.minute;
    return result;

}

TimeKhodam::operator string() const
{
    string result;
    result = to_string(hour) + ":" + to_string(minute);
    return result;
}

