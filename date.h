#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date
{
public:
    Date();

protected:
    int year;
    int month;
    int day;

public:
    void set_day(int day_inp);
    int get_day();
    void set_month(int month_inp);
    int get_month();
    void set_year(int year_inp);
    int get_year();

     friend std::istream & operator >> (std::istream &in,  Date &t);
     friend std::ostream & operator << (std::ostream &out,  Date &t);
     friend bool operator<(const Date& t1, const Date& t2);
     friend bool operator<=(const Date& t1, const Date& t2);
     friend bool operator>(const Date& t1, const Date& t2);
     friend bool operator>=(const Date& t1, const Date& t2);
     friend Date operator+(const Date& t1, const Date& t2);
      operator std::string() const ;

};

class DateException : public std::exception{
private:
    std::string message;

public:
    DateException(std::string& msg) : message(msg){}
    DateException(std::string maseg) : message(maseg){}
    std::string what()
    {
        return message;
    }
};

#endif // DATE_H
