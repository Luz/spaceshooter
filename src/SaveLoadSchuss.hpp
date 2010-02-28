#ifndef SAVELOADSCHUSS_HPP
#define SAVELOADSCHUSS_HPP

#include <fstream>

class Archive;

class DataSchuss
{
public:
    DataSchuss();
/*private:
    friend class boost::serialization::access;
    DataSchuss* stops[10];
    template<class Archive>
    void serialize(Archive & ar);*/
};

#endif
