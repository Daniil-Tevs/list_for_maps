
#include "classes.h"

int main() {
    std::fstream in("../input.txt");
    std::string url;
    in>>url;
    RouterWriterTxt road_text(url);
    road_text.Write("../output.txt");

    RouterWriterJson road_json(url);
    road_json.Write("../output.json");
    return 0;
}
