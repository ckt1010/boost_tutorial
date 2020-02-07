#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class A_parent {
  public:
    A_parent() { cout << "in A_parent construct;\n"; };
    ~A_parent() { cout << "in A_parent deconstruct;\n"; };

  private:
    A_parent(A_parent &a) { cout << "in A_parent copy construct;\n"; };
    A_parent operator=(A_parent &a) {
        cout << "in A_parent equal construct;\n";
        return *this;
    };
};

class A: public A_parent {
  private:
  public:
    A();
    ~A();
    A operator=(A &a) {
        cout << "in A_parent equal construct;\n";
        return *this;
    };
};

A::A() : A_parent() { cout << "in A constructed\n"; }

A::~A() { cout << "in A deconstructed\n"; }

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

    cout << "\nCopy test:\n";
    A copy1, copy2;
    copy1 = copy2;

    
}