#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

template <typename T> void show(T in) {
    for (auto t : in) {
        cout << t << ":";
    }
    cout << endl;
}

int main() {
    string str1 = "   Hello world, Hello world", str2 = "123";
    cout << "is_alnum: " << is_alnum()('1') << endl;
    cout << "is_alpha: " << is_alpha()('2') << endl;
    cout << "is_equal: " << is_equal()(str1, str2) << endl;
    cout << "to_upper_copy: " << to_upper_copy(str1) << endl;

    cout << "trim_copy: " << trim_copy(str1) << endl;

    auto it_first = find_first(str1, "wor");
    cout << "find_first: " << it_first << " index: " << it_first.begin() - str1.begin()
         << "-" << it_first.end() - str1.begin() << endl;

    auto it_last = find_last(str1, "wor");
    cout << "find_last: " << it_last << " index: " << it_last.begin() - str1.begin()
         << "-" << it_last.end() - str1.begin() << endl;

    auto it_tail = find_tail(str1, 1);
    cout << "find_tail: " << it_tail << " index: " << it_tail.begin() - str1.begin()
         << "-" << it_tail.end() - str1.begin() << endl;

    auto it_nth = find_nth(str1, "wor", 1);
    cout << "find_nth: " << it_nth << " index: " << it_nth.begin() - str1.begin() << "-"
         << it_nth.end() - str1.begin() << endl;

    vector<string> vec_all;
    find_all(vec_all, str1, "ld");
    cout << "\nfind_all: \n";
    show(vec_all);

    cout << "\nreplace_all_copy: " << replace_all_copy(str1, ", ", " and ") << endl;

    string output;
    replace_copy(str1.begin(), str1.end(), back_inserter(output), 'H', 'h');
    cout << "\nreplace_copy: " << output << endl;

    cout << "\nerase_first_copy: " << erase_first_copy(str1, "Hello") << " vs "
         << str1.erase(str1.find_last_of("world")) << endl;

    vector<string> vec_split;
    split(vec_split, str1, is_any_of(" "));
    cout << "\nsplit: ";
    show(vec_split);

    vector<string> vec_join;
    vec_join.push_back(str1);
    vec_join.push_back(str1);
    cout << "\njoin: " << join(vec_join, "~~~~~~") << endl;
    {
        cout << "\ntokenizer: ";
        tokenizer<> tok1(str1);
        show(tok1);
        cout << endl;
    }
    {
        cout << "\ntokenizer char_separator: ";
        char_separator<char> sep(" ", ",", keep_empty_tokens);
        tokenizer<char_separator<char>> tok2(str1, sep);
        show(tok2);
        cout << endl;
    }
    {
        cout << "\ntokenizer escaped_list_separator: ";
        tokenizer<escaped_list_separator<char>> tok2(str1);
        show(tok2);
        cout << endl;
    }
    {
        cout << "\ntokenizer offset_separator: ";
        vector<int> offset = {1, 2};
        offset_separator sep(offset.begin(), offset.end(), false);
        tokenizer<offset_separator> tok2(str1, sep);
        show(tok2);
        cout << endl;
    }
}