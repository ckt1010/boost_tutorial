#include <boost/array.hpp>
#include <boost/bimap.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/container/list.hpp>
#include <boost/container/map.hpp>
#include <boost/container/set.hpp>
#include <boost/timer/timer.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>
#include <map>
#include <set>

using namespace std;
using namespace boost;
using namespace boost::timer;
using namespace boost::container;

const int LENGTH = 10000;

template <typename T> void work_insert(T cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont.insert(i);
    }
}

void work_insert(circular_buffer<int> &cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont.push_back(i);
    }
}

template <typename T> void work_insert_pair(T cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont.insert(std::make_pair(i, to_string(i)));
    }
}

void work_insert_pair(bimap<int, std::string> &cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont.insert(bimap<int, std::string>::value_type(i, to_string(i)));
    }
}

template <typename T> void work_add(T cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont[i] = i;
    }
}

template <typename T> void work_find(T cont) {
    cout << __FUNCTION__ << " entered\n";
    auto_cpu_timer t;
    for (size_t i = 0; i < LENGTH; i++) {
        cont.find(1);
    }
}

int main() {
    // set club
    std::set<int> std_set;
    container::set<int> boost_set;
    unordered_set<int> uorder_set;

    circular_buffer<int> cirl_buf(LENGTH);

    bimap<int, std::string> bi_map;

    // map club
    std::map<int, std::string> std_map;
    unordered_map<int, std::string> uorder_map;

    // list club
    std::list<int> std_list;
    auto std_list_it = std_list.begin();

    container::list<int> boost_list;
    auto boost_list_it = boost_list.begin();

    // array club
    std::array<int, LENGTH> std_arr;
    boost::array<int, LENGTH> boost_arr;

    // insert
    cout << "\nstd_set: \n";
    work_insert(std_set);
    cout << "\nboost_set: \n";
    work_insert(boost_set);
    cout << "\nuorder_set: \n";
    work_insert(uorder_set);

    cout << "\ncirl_buf: \n";
    work_insert(cirl_buf);

    cout << "\nstd_map: \n";
    work_insert_pair(std_map);
    cout << "\nuorder_map: \n";
    work_insert_pair(uorder_map);
    cout << "\nbi_map: \n";
    work_insert_pair(bi_map);

    cout << "\nstd_arr: \n";
    work_add(std_arr);
    cout << "\nboost_arr: \n";
    work_add(boost_arr);

    try {
        // find
        cout << "\nstd_set: \n";
        work_find(std_set);
        cout << "\nboost_set: \n";
        work_find(boost_set);
        cout << "\nuorder_set: \n";
        work_find(uorder_set);

        cout << "\nstd_map: \n";
        work_find(std_map);
        cout << "\nuorder_map: \n";
        work_find(uorder_map);

    } catch (const std::exception &e) {
        std::cerr << "Find test: " << e.what() << '\n';
    }
}