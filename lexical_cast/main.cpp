#include<boost/lexical_cast.hpp>
#include<iostream>

using namespace std;

int main() {
    using boost::lexical_cast;

    int test = 11;
    cout << typeid(test).name() << ":" << typeid(lexical_cast<float>(test)).name() << ":"
         << typeid(lexical_cast<string>(test)).name() << ":"
         << typeid(lexical_cast<long>(test)).name() << ":"
         << typeid(lexical_cast<double>(test)).name() << endl;
}