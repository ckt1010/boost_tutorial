#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class A {
  private:
  public:
    A();
    ~A();
};

A::A() {
    cout << "A constructed\n";
}

A::~A() {cout << "A deconstructed\n";}

int main() {
    cout << "scoped_ptr:\n";
    scoped_ptr<A> sptr(new A);
    cout << "\nscoped_array:\n";
    scoped_array<A> sptr_arr(new A[5]);

    cout << "\nunique_ptr:\n";
    unique_ptr<A[]> my_array(new A[5]);

    cout << "\nshared_ptr:\n";
    boost::shared_ptr<A> shptr(new A);
    boost::weak_ptr<A> wptr(shptr);
}