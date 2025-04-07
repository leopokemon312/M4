// File: Date.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Date {
private:
    int day, month, year;
    static const int daysInMonth[12];
    static const string monthNames[12];

    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int daysInThisMonth(int m, int y) const {
        if (m == 2 && isLeapYear(y)) return 29;
        return daysInMonth[m - 1];
    }

    bool isValidDate(int m, int d, int y) const {
        if (m < 1 || m > 12 || d < 1 || y < 1) return false;
        return d <= daysInThisMonth(m, y);
    }

    int toDays() const {
        int total = 0;
        for (int i = 1; i < year; ++i)
            total += isLeapYear(i) ? 366 : 365;
        for (int i = 1; i < month; ++i)
            total += daysInThisMonth(i, year);
        return total + day;
    }

    void fromDays(int totalDays) {
        year = 1;
        while (totalDays > (isLeapYear(year) ? 366 : 365)) {
            totalDays -= isLeapYear(year) ? 366 : 365;
            year++;
        }
        month = 1;
        while (totalDays > daysInThisMonth(month, year)) {
            totalDays -= daysInThisMonth(month, year);
            month++;
        }
        day = totalDays;
    }

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int m, int d, int y) {
        if (!setDate(m, d, y)) {
            day = 1; month = 1; year = 2000;
        }
    }

    bool setDate(int m, int d, int y) {
        if (!isValidDate(m, d, y)) return false;
        month = m; day = d; year = y;
        return true;
    }

    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << monthNames[dt.month - 1] << " " << dt.day << ", " << dt.year;
        return os;
    }

    friend istream& operator>>(istream& is, Date& dt) {
        int m, d, y;
        char sep1, sep2;
        cout << "Enter date (MM/DD/YYYY): ";
        is >> m >> sep1 >> d >> sep2 >> y;
        if (!dt.setDate(m, d, y)) {
            cout << "Invalid date! Setting default.\n";
            dt.setDate(1, 1, 2000);
        }
        return is;
    }

    Date& operator++() {
        int days = toDays() + 1;
        fromDays(days);
        return *this;
    }

    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    Date& operator--() {
        int days = toDays() - 1;
        fromDays(days);
        return *this;
    }

    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    int operator-(const Date& other) const {
        return abs(toDays() - other.toDays());
    }
};

const int Date::daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const string Date::monthNames[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int main() {
    Date d1, d2(4, 18, 2014);
    cout << d1 << endl;
    cout << d2 << endl;

    d1.setDate(2, 29, 2009); // invalid
    d1.setDate(2, 29, 2008); // valid leap year
    cout << d1 << endl;

    cout << "\nDecrement (pre): " << --d1 << endl;
    cout << "Increment (pre): " << ++d1 << endl;

    cout << "\nDecrement (post): " << d1-- << endl;
    cout << "Increment (post): " << d1++ << endl;

    d1.setDate(4, 10, 2014);
    d2.setDate(4, 18, 2014);
    cout << "\nDays between: " << (d2 - d1) << endl;

    d1.setDate(2, 2, 2006);
    d2.setDate(11, 10, 2003);
    cout << "Days between: " << (d1 - d2) << endl;

    Date input;
    cin >> input;
    cout << input << endl;

    return 0;
}
