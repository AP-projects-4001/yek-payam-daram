#include "date.h"
#include <iostream>
#include <string>
#include "date.h"
#include <exception>
#include <stdexcept>

using namespace std;

Date::Date()
{

}

void Date::set_day(int day_inp)
{
    day = day_inp;
}

int Date::get_day()
{
    return day;
}


void Date::set_month(int month_inp)
{
    month = month_inp;
}


int Date::get_month()
{
    return month;
}


void Date::set_year(int year_inp)
{
    year = year_inp;
}


int Date::get_year()
{
    return year;
}


istream & operator >> (std::istream &in,  Date &t)
{
    int day , month , year;
    cout << "enter year:" << endl;
    in >> year;
    // if (year < 0)
    cout << "enter month:" << endl;
    in >> month;
    cout << "enter day:" << endl;
    in >> day;
    t.set_day(day);
    t.set_month(month);
    t.set_year(year);
    return in;
}

ostream & operator << (std::ostream &out,  Date &t)
{
    out << "year:" << t.get_year() << "month:" << t.get_month() << "day:" << t.get_day() << endl;
    return out;
}

bool operator<(const Date& t1, const Date& t2)
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
            else
                false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator<=(const Date& t1, const Date& t2)
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
                true;
            else
                false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator>(const Date& t1, const Date& t2)
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
            else
                false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator>=(const Date& t1, const Date& t2)
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
                true;
            else
                false;
        }
        else
            return false;
    }
    else
        return false;
}

Date operator+(const Date& t1, const Date& t2)
{
    Date newdate;
    newdate.year = t1.year + t2.year;
    newdate.month = t1.month + t2.month;
    newdate.day = t1.day + t2.day;
    return newdate;
}

Date::operator string() const
{
    string result;
    result = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    return result;
}
