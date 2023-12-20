/**
 * This class represents duration of time in terms of hours,minutes and seconds.
 * It normilize the time where minutes and seconds will be within the range of -60 and 60.
 * This class has several interfaces where the user can access each time part (hours, minutes
 * and seconds) separately and change. Mathematical operators like addition, subtaction and unary
 * negations are overloaded along with comparison and stream I/O operators.
*/
#ifndef TIME_SPAN_H_
#define TIME_SPAN_H_

#include <iostream>
using namespace std;

class TimeSpan
{
public:
    // Constructors
    TimeSpan();
    TimeSpan(double seconds);
    TimeSpan(double minutes, double seconds);
    TimeSpan(double hours, double minutes, double seconds);

    // getters and setters
    int hours() const;
    int minutes() const;
    int seconds() const;
    void set_time(int hours, int minutes, int seconds);

    // Operator overloads: Arithmethic
    TimeSpan operator-() const;
    TimeSpan &operator+=(const TimeSpan &time);
    TimeSpan operator+(const TimeSpan &time) const;
    TimeSpan &operator-=(const TimeSpan &time);
    TimeSpan operator-(const TimeSpan &time) const;

    // Operator overloads: Comparison
    bool operator==(const TimeSpan &time) const;
    bool operator!=(const TimeSpan &time) const;
    bool operator<(const TimeSpan &time) const;
    bool operator>(const TimeSpan &time) const;
    bool operator>=(const TimeSpan &time) const;
    bool operator<=(const TimeSpan &time) const;

     // Operator overloads: Streams
    friend ostream &operator<<(ostream &os, const TimeSpan &time);
    friend istream &operator>>(istream &is, TimeSpan &time);

private:
    int hours_;
    int minutes_;
    int seconds_;
    int Round(double total_seconds);
    void SetTimeSpan(double total_seconds);
    double ComputeTotalSeconds(const TimeSpan& time) const;
};

#endif /* time_span_hpp */
