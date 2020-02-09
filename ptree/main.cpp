#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using namespace std;
using namespace boost::property_tree;
using namespace xml_parser;

int main(int argc, char *argv[]) {
    try {
        ptree pt;
        read_xml(string(argv[1]), pt);

        // Traverse property tree example
        for (ptree::value_type const &node : pt.get_child("breakfast_menu")) {
            string rootLabel = node.first;
            cout << rootLabel << ":\n";
            ptree subtree_w, subtree_r = node.second;

            for (ptree::value_type const &v : subtree_r.get_child("")) {
                string label = v.first;
                ptree subsubtree_r = v.second;

                if (label != "<xmlattr>") {
                    string value = subtree_r.get<string>(label);
                    cout << label << ":  " << value << endl;
                    subtree_w.put(label, value + "only for ckt");
                }
                for (ptree::value_type const &vv : subsubtree_r.get_child("")) {
                    string label_sub = vv.first;
                    if (label_sub == "<xmlattr>") {
                        ptree::value_type xmlattr_v = subsubtree_r.get_child("<xmlattr>").front();
                        cout << xmlattr_v.first << ":" << xmlattr_v.second.data() << endl;
                    }
                }

            }
            cout << endl;
            //write top level
            pt.get_child("breakfast_menu").put_child(rootLabel, subtree_w);
        }
        xml_writer_settings<string> settings('\t', 1);
        xml_parser::write_xml(string(argv[1])+"_out", pt, locale(), settings);

    } catch (const exception &e) {
        cerr << "Parse XML error " << e.what() << '\n';
    }
    return 0;
}