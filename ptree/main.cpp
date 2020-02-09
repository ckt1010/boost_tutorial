#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using namespace std;
using namespace boost::property_tree;
using namespace xml_parser;
using namespace json_parser;

void show(ptree subtree_r) {
    if (subtree_r.ordered_begin() == subtree_r.not_found()) {
        return;
    }
    for (ptree::value_type const &v : subtree_r.get_child("")) {
        string label = v.first;
        ptree subsubtree_r = v.second;
        string value;
        if ("" == label) {//maybe is array from json file
            cout << v.second.data() << endl;
        } else if (label != "<xmlattr>") {
            value = subtree_r.get<string>(label);
            cout << label << ":" << value << endl;
        }

        show(subsubtree_r);
    }
}

int main(int argc, char *argv[]) {
    boost::filesystem::path pathObj(argv[1]);
    string ext = "";
    if (pathObj.has_extension()) {
        ext = pathObj.extension().string();
    } else {
        cerr << "illegal input file\n";
        return -1;
    }
    if (ext == ".xml") {
        try {
            ptree pt;

            read_xml(string(argv[1]), pt, trim_whitespace);

            // Traverse property tree example
            show(pt);

            // write
            pt.get_child("breakfast_menu").put("ckt", "tstts");
            xml_writer_settings<string> settings('\t', 1);
            xml_parser::write_xml(pathObj.filename().string() + "_out.xml", pt, locale(),
                                  settings);

        } catch (const exception &e) {
            cerr << "Parse XML error " << e.what() << '\n';
        }
    } else if (ext == ".json") {
        try {
            ptree pt;
            read_json(string(argv[1]), pt);

            // Traverse property tree example
            show(pt);

            //write
            pt.put("ckt", "tstts");
            write_json(pathObj.filename().string() + "_out.json", pt);
        } catch (const exception &e) {
            cerr << "Parse JSON error " << e.what() << '\n';
        }
    }

    return 0;
}