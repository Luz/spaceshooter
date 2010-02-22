#ifndef RAKETE_HPP
#define RAKETE_HPP

#include "Object.hpp"
//#include "SchussHandler.hpp"

//class SchussHandler;

class Rakete: public Object
{
    public:
        Rakete(std::string filename, float x=0, float y=0); //, SchussHandler* mschusshandler, float x=0, float y=0);
        //void schiessen();
        virtual ~Rakete();
    private:
        //SchussHandler* mSchussHandler;
        // ^-- dieser pointer wird bei allen schiessfähigen objekten benötigt,
            //(notfalls überklasse "schussfähig" erstellen)
};

#endif
