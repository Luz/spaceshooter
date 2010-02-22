#ifndef SAVELOADSCHUSS_HPP
#define SAVELOADSCHUSS_HPP

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
