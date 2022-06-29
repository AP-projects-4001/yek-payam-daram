#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include "timekhodam.h"
#include "date.h"

class DateTime : protected Date, protected TimeKhodam
{
public:
    DateTime();

public:
    friend std::istream& operator >> (std::istream& in, DateTime& t);
    friend std::ostream& operator << (std::ostream& out, DateTime& t);
    friend bool operator<(const DateTime& t1, const DateTime& t2);
    friend bool operator<=(const DateTime& t1, const DateTime& t2);
    friend bool operator>(const DateTime& t1, const DateTime& t2);
    friend bool operator>=(const DateTime& t1, const DateTime& t2);
    friend DateTime operator+(const DateTime& t1, const DateTime& t2);
    operator std::string() const;
};

class DateTimeException : public std::exception{
private:
    std::string message;

public:
    DateTimeException(std::string& msg) : message(msg){}
    DateTimeException(std::string maseg) : message(maseg){}
    std::string what()
    {
        return message;
    }
};


#endif // DATETIME_H
