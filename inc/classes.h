#include <list>
#include <string>
#include <fstream>
class RouterWriter{
public:
    RouterWriter(std::string name_url);
    virtual void Write(const std::string& where) = 0;
    std::pair<float,float> getBegin();
    std::string getUrl();
protected:
    std::string m_urlName;
    double m_start_lat,m_start_lon;
    std::list<std::pair<float,float>> m_coordinates;
};

class RouterWriterTxt : public RouterWriter
{
public:
    RouterWriterTxt(std::string nameUrl);
    void Write(const std::string& where) override;

    virtual ~RouterWriterTxt()= default;
};

class RouterWriterJson : public RouterWriter
{
public:
    RouterWriterJson(std::string nameUrl);
    void Write(const std::string& where) override;

    virtual ~RouterWriterJson()= default;
};

class RouterWriterXml : public RouterWriter
{
public:
    RouterWriterXml(std::string nameUrl);
    void Write(const std::string& where) override;

    virtual ~RouterWriterXml()= default;
};