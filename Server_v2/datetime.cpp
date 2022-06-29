#include "datetime.h"
#include <iostream>
#include <string>
#include "datetime.h"

using namespace std;

DateTime::DateTime()
{

}

istream& operator >> (istream& in, DateTime& t)
{
    cout << "year: ";
    in >> t.year;

    cout << endl << "month: ";
    in >> t.month;
    if (t.month > 12)
        t.month = 12;
    else if (t.month <= 0)
        t.month = 1;

    cout << endl << "day: ";
    in >> t.day;
    cout << endl << "hour: ";
    in >> t.hour;
    if (t.hour >= 24)
        t.hour = 0;
    else if (t.hour < 0)
        t.hour = 0;

    cout << endl << "minute: ";
    in >> t.minute;
    if (t.minute >= 60)
        t.minute = 59;
    else if (t.minute < 0)
        t.minute = 0;
    return in;
}

ostream& operator << (ostream& out, DateTime& t)
{
    out << "year: " << t.year << " / month: " << t.month << " / day: " << t.day << endl;
    out << "hour: " << t.hour << " / minute: " << t.minute << endl;
    return out;
}

bool operator<(const DateTime& t1, const DateTime& t2)
{
    if (t1.year < t2.year)
    {
        return true;
    }
    else if (t1.year == t2.year)
    {
        if (t1.month < t2.month)
            return true;
        else if (t1.month == t2.month)
        {
            if (t1.day < t2.day)
                return true;
            else if (t1.day == t2.day)
            {
                if (t1.hour < t2.hour)
                    return true;
                else if (t1.hour == t2.hour)
                {
                    if (t1.minute < t2.minute)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator<=(const DateTime& t1, const DateTime& t2)
{
    if (t1.year < t2.year)
    {
        return true;
    }
    else if (t1.year == t2.year)
    {
        if (t1.month < t2.month)
            return true;
        else if (t1.month == t2.month)
        {
            if (t1.day < t2.day)
                return true;
            else if (t1.day == t2.day)
            {
                if (t1.hour < t2.hour)
                    return true;
                else if (t1.hour == t2.hour)
                {
                    if (t1.minute < t2.minute)
                        return true;
                    else if (t1.minute == t2.minute)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator>(const DateTime& t1, const DateTime& t2)
{
    if (t1.year > t2.year)
    {
        return true;
    }
    else if (t1.year == t2.year)
    {
        if (t1.month > t2.month)
            return true;
        else if (t1.month == t2.month)
        {
            if (t1.day > t2.day)
                return true;
            else if (t1.day == t2.day)
            {
                if (t1.hour > t2.hour)
                    return true;
                else if (t1.hour == t2.hour)
                {
                    if (t1.minute > t2.minute)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator>=(const DateTime& t1, const DateTime& t2)
{
    if (t1.year > t2.year)
    {
        return true;
    }
    else if (t1.year == t2.year)
    {
        if (t1.month > t2.month)
            return true;
        else if (t1.month == t2.month)
        {
            if (t1.day > t2.day)
                return true;
            else if (t1.day == t2.day)
            {
                if (t1.hour > t2.hour)
                    return true;
                else if (t1.hour == t2.hour)
                {
                    if (t1.minute > t2.minute)
                        return true;
                    else if (t1.minute == t2.minute)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

DateTime operator+(const DateTime& t1, const DateTime& t2)
{
    DateTime newdatetime;
    newdatetime.year = t1.year + t2.year;
    newdatetime.month = t1.month + t2.month;
    newdatetime.day = t1.day + t2.day;
    newdatetime.hour = t1.hour + t2.hour;
    newdatetime.month = t1.month + t2.month;
    return newdatetime;

}

DateTime::operator std::string() const
{
    string result;
    result = to_string(year) + "/" + to_string(month) + "/" + to_string(day) + " , " + to_string(hour) + ":" + to_string(minute);
    return result;
}
