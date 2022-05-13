#include "classes.h"
#include <list>
#include <string>
#include <fstream>
RouterWriter::RouterWriter(std::string name_url)
    {
        m_urlName =name_url;
        int begin_number,end_number;
        double tmp_lat,tmp_lon;
        std::string tmp;
        begin_number=m_urlName.find("gz")+5;
        name_url = m_urlName.substr(begin_number,name_url.size()-(begin_number+2));
        m_coordinates.emplace_back(std::make_pair(0,0));
        auto it = m_coordinates.begin();
        while(!name_url.empty())
        {
            if(name_url.find(';')==-1)
                break;
            end_number = name_url.find(';');
            tmp_lat = std::stod(name_url.substr(0,end_number))/(std::pow(10,7));
            name_url = name_url.substr(end_number+1,name_url.size()-(end_number+1));
            end_number = name_url.find(';');
            tmp_lon = std::stod(name_url.substr(0,end_number))/(std::pow(10,7));
            name_url = name_url.substr(end_number+1,name_url.size()-(end_number+1));
            if(begin_number!=0) {
                it->first = tmp_lat;
                it->second = tmp_lon;
                m_start_lat = tmp_lat;
                m_start_lon = tmp_lon;
                begin_number = 0;}
            else
                m_coordinates.emplace_back(std::make_pair(m_start_lat+tmp_lat,m_start_lon+tmp_lon));
        }
        it = m_coordinates.begin();
        auto tmp_it = m_coordinates.begin();
        std::advance(tmp_it,1);
        for(; it != m_coordinates.end() && tmp_it!=m_coordinates.end(); ) {
            if(abs(it->first - tmp_it->first)<0.0000001 || (abs(it->second - tmp_it->second)<0.0000001))
            {
                m_coordinates.erase(tmp_it);
                tmp_it = it;
                tmp_it++;

            }
            else {
                std::advance(it, 1);
                std::advance(tmp_it, 1);
            }
        }
    }

    std::pair<float,float> RouterWriter::getBegin() {return {m_start_lat,m_start_lon};}
    std::string RouterWriter::getUrl() {return m_urlName;}

RouterWriterTxt::RouterWriterTxt(std::string nameUrl): RouterWriter(nameUrl) {}
    void RouterWriterTxt::Write(const std::string &where) {
        std::ofstream out(where);
        out<<std::fixed; out.precision(7);
        for(auto i : m_coordinates)
            out<<i.first<<" "<<i.second<<std::endl;
    }

RouterWriterJson::RouterWriterJson(std::string nameUrl) : RouterWriter(nameUrl) { }
    void RouterWriterJson::Write(const std::string &where) {
        std::ofstream out(where);
        out<<std::fixed; out.precision(7);
        out<<"{ \"route\": [\n";
        auto it = m_coordinates.end();
        std::advance(it,-1);
        for(auto i : m_coordinates)
            if(i!=*it)
                out<<"{ \"lat\" : "<<i.first<<", \"lon\" : "<<i.second<<"},"<<std::endl;
            else
                out<<"{ \"lat\" : "<<i.first<<", \"lon\" : "<<i.second<<"}"<<std::endl;
        out<<"] }";
    }