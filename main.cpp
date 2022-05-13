
#include "classes.h"

int main() {
    std::fstream in("../input.txt");
    std::string url;
    in>>url;
    RouterWriterTxt road_text(url);
    road_text.Write("../output.txt");

    RouterWriterJson road_json(url);
    road_json.Write("../output.json");

    RouterWriterXml road_xml(url);
    road_xml.Write("../output.xml");
    return 0;
}
