#include "time_span.h"

// Constructors
TimeSpan::TimeSpan():hours_(0), minutes_(0), seconds_(0){}
TimeSpan::TimeSpan(double seconds){
    SetTimeSpan(seconds);
}
TimeSpan::TimeSpan(double minutes, double seconds){
    double total_seconds = minutes * 60 + seconds;
    SetTimeSpan(total_seconds);
}
TimeSpan::TimeSpan (double hours, double minutes, double seconds){
    double total_seconds = hours* 3600 +  minutes * 60 + seconds;
    SetTimeSpan(total_seconds);
}

//Getters and Setters
int TimeSpan::hours() const{
    return hours_;
}
int TimeSpan::minutes() const{
    return minutes_;
}
int TimeSpan::seconds() const{
    return seconds_;
}
void TimeSpan::set_time(int hours, int minutes, int seconds){
    double total_seconds = hours * 3600 + minutes * 60 + seconds;
    SetTimeSpan(total_seconds);
}

// Operator Overload
TimeSpan& TimeSpan::operator += (const TimeSpan& rhs){
    TimeSpan temp = *this;
    double total_seconds = ComputeTotalSeconds(temp) + ComputeTotalSeconds(rhs);
    SetTimeSpan(total_seconds);
    return *this;
}
TimeSpan TimeSpan::operator +(const TimeSpan& time) const{
    TimeSpan ret  = *this;
    ret += time;
    return ret;
}

TimeSpan& TimeSpan::operator -= (const TimeSpan& rhs){
    TimeSpan temp = *this;
    double total_seconds = ComputeTotalSeconds(temp) - ComputeTotalSeconds(rhs);
    SetTimeSpan(total_seconds);
    return *this;
}
TimeSpan TimeSpan::operator -(const TimeSpan& time) const{
    TimeSpan ret  = *this;
    ret -= time;
    return ret;
}

TimeSpan TimeSpan::operator -() const{
    TimeSpan temp = *this;
    double total_seconds = -(ComputeTotalSeconds(temp));
    return TimeSpan(total_seconds);
}

bool TimeSpan::operator == (const TimeSpan& rhs) const{
    bool status_hour = (hours_ == rhs.hours_);
    bool status_min = (minutes_ == rhs.minutes_);
    bool status_sec = (seconds_ == rhs.seconds_);
    return (status_hour && status_min && status_sec);
}

bool TimeSpan::operator != (const TimeSpan& rhs) const{
    return !(*this == rhs);
}
bool TimeSpan::operator >(const TimeSpan& rhs) const{
    int total_sec_this = minutes_ * 60 + seconds_;
    int total_sec_rhs = rhs.minutes_ * 60 + rhs.seconds_;
    // Comparing hours first was done to avoid possible overflow.
    if (hours_ > rhs.hours_){
        return true;
    }else if((hours_ == rhs.hours_) && (total_sec_this > total_sec_rhs)){
        return true;
    }else{
        return false;
    }
}
bool TimeSpan::operator<(const TimeSpan& rhs) const{
    bool status = (*this > rhs) || (*this == rhs);
    return !status;
}
bool TimeSpan::operator >=(const TimeSpan& rhs) const{
    return !(*this < rhs);
}
bool TimeSpan::operator <=(const TimeSpan& rhs) const{
    return !(*this > rhs);
}


// Friends: Operator overload
ostream& operator << (ostream& os, const TimeSpan& time){
    os << "Hours: "<<time.hours()<<", Minutes: "<<time.minutes()<< ", Seconds: "<< time.seconds();
    return os;
}
istream& operator >> (istream& is, TimeSpan& time){
    int hours, minutes, seconds;
    is >> hours >> minutes >> seconds;
    time.set_time(hours, minutes, seconds);
    return is;
}

/**
 * Helper function: Basically add 0.5 if greater than 0 and subract -0.5 if less then 0.
 * Since there is truncation, adding or subtracting will parameter to get to nearest interger.
 * Note: there is a possibility that we might loose precision. However, on this circumstances
 *  It only rounds the second which should be between -60 and 60. 
 */
int TimeSpan::Round(double total_seconds){
    if (total_seconds < 0){
        total_seconds -= 0.5;
    }else{
        total_seconds += 0.5;
    }
    return static_cast<int>(total_seconds);
}
/**
 * Helper function: sets member variables
 */
void TimeSpan::SetTimeSpan(double total_seconds){
    hours_ = total_seconds/3600;
    minutes_ = (total_seconds - hours()*3600)/60;
    seconds_ = Round(total_seconds - hours()*3600 - minutes()*60);
}

/**
 *  Helper function takes TimeSpan object and computes total seconds.
 */
double TimeSpan::ComputeTotalSeconds(const TimeSpan& time) const{
    double ret = time.hours_ * 3600 + time.minutes_*60 + time.seconds_;
    return ret;
}
