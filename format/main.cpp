#include<boost/format.hpp>
#include<iostream>

using namespace std;

int main() {
    using boost::format;

    format fmt("hello: %2% world: %1%\n");
    fmt% "first";
    fmt% "second";
    cout << fmt;
}