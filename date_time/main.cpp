#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

int main() {
    date today = day_clock::local_day();
    ptime now = microsec_clock::local_time(); // use the clock

    try {
        // The following date is in ISO 8601 extended format (CCYY-MM-DD)
        std::string s("2001-10-9"); // 2001-October-09
        date d(from_simple_string(s));
        std::cout << to_simple_string(d) << std::endl;

        // Read ISO Standard(CCYYMMDD) and output ISO Extended
        std::string ud("20011009"); // 2001-Oct-09
        date d1(from_undelimited_string(ud));
        std::cout << to_iso_extended_string(d1) << std::endl;

        // Output the parts of the date - Tuesday October 9, 2001
        date::ymd_type ymd = d1.year_month_day();
        greg_weekday wd = d1.day_of_week();
        std::cout << wd.as_number() << wd.as_long_string() << " "
                  << ymd.month.as_long_string() << " " << ymd.day << ", " << ymd.year
                  << std::endl;

        // Let's send in month 25 by accident and create an exception
        std::string bad_date("20011109"); // 2001-??-09
        std::cout << "An expected exception is next: " << std::endl;
        date wont_construct(from_undelimited_string(bad_date));
        // use wont_construct so compiler doesn't complain, but you wont get here!
        std::cout << "oh oh, you shouldn't reach this line: "
                  << to_iso_string(wont_construct) << std::endl;
    } catch (std::exception &e) {
        std::cout << "  Exception: " << e.what() << std::endl;
    }

    try {
        date birthday(from_simple_string("2002-02-01"));
        weeks w(1);
        months y(10);
        days days_alive = today - birthday;
        days one_day(1);
        if (days_alive == one_day) {
            std::cout << "Born yesterday, very funny" << std::endl;
        } else if (days_alive < days(0)) {
            std::cout << "Not born yet, hmm: " << days_alive.days() << " days"
                      << std::endl;
        } else {
            std::cout << "Days alive: " << days_alive.days() << " and today is " << today
                      << std::endl;
        }
        std::cout << "day_of_year: " << today.day_of_year() << " days: " << w.days()
                  << " number_of_years: " << y.get_offset(today).days() << endl;
    } catch (...) {
        std::cout << "Bad date entered: "
                  << "2002-02-01" << std::endl;
    }

    try {
        date_period dp(today, today + days(10));
        cout << "date_period: " << dp << " length: " << dp.length() << endl;
        dp.shift(date_duration(100));
        cout << "date_period shift: " << dp << endl;
        dp.expand(date_duration(100));
        cout << "date_period expand: " << dp << " contains: " << dp.contains(today)
             << endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        day_iterator d_it(today);
        cout << "day_iterator: " << *d_it << " after ++: " << *(++d_it) << endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        using namespace boost::posix_time;
        date d(2002, Feb, 1);                 // an arbitrary date
        ptime t1(d, hours(5) + nanosec(100)); // date + time of day offset
        ptime t2 = t1 - minutes(4) + seconds(2);
        cout << "date: " << d << " ptime: " << t1 << " ptime offset: " << t2 << endl;

        std::stringstream ss("2004-Jan-1 05:21:33.20");
        ss >> t2;
        cout << " input streaming: " << t2 << endl;

        date today = now.date(); // Get the date part out of the time
        date tomorrow = today + date_duration(1);
        ptime tomorrow_start(tomorrow); // midnight

        // starting at current time iterator adds by one hour
        time_iterator titr(now, hours(1));
        for (; titr < tomorrow_start; ++titr) {
            std::cout << (*titr) << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        time_period tp(now, now - days(10));
        cout << "time_period: " << tp << " length: " << tp.length() << endl;
        tp.shift(hours(100));
        cout << "time_period shift: " << tp << endl;
        tp.expand(hours(100));
        cout << "time_period expand: " << tp << " contains: " << tp.contains(now) << endl;
    } catch (const std::exception &e) {
        std::cerr << "time_period: " << e.what() << '\n';
    }

    try {
        time_iterator t_it(now, seconds(1));
        cout << "time_iterator: " << *t_it << " after ++: " << *(++t_it) << endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // create some gregorian objects to output
        date d1(2002, Oct, 1);
        greg_month m = d1.month();
        greg_weekday wd = d1.day_of_week();

        // create a facet and a locale for chinese dates
        date_facet *chinese_dfacet = new date_facet("%Y年 %m月 %d日");
        time_facet *chinese_tfacet = new time_facet("%Y年 %m月 %d日 %H:%M:%S-%F");
        std::cout.imbue(locale(locale::classic(), chinese_tfacet));
        // std::cout.imbue(locale(locale::classic(), chinese_dfacet));
        cout << "chinese dates: " << now << endl;

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}