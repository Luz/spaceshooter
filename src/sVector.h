#ifndef SVECTOR_H_
#define SVECTOR_H_
#include <cassert>
/*#include <bits/stl_iterator_base_funcs.h>
#include <bits/functexcept.h>
#include <bits/concept_check.h>*/
#include <memory>
#include <iostream>
using namespace std;

template<typename _Tp>
class sVector
{
private: 
  class sVectorElement;

public:
  class iterator;
	sVector();
	
	~sVector();
	
	unsigned int size()
	{
		return Length;
	}
	
	_Tp*     push_back(_Tp in);
	void     erase(iterator& in);
	void     sort();
	iterator begin()
	{
		iterator Temp(Start);
		return  Temp;
	}
	iterator end()
	{
		iterator Temp(End);
		return  Temp;
		
	}
	
	iterator middle()
	{
		iterator Temp(Middle);
		return Temp;
	}

  class iterator
  {
    public:
      iterator()
      :Element(0) {}

      iterator(const sVector<_Tp>::iterator& other)
      :Element(other.Element) {}
      
      iterator(sVectorElement* in)
      :Element(in) {}
      unsigned int ID()
      {
      	assert(Element);
      	return Element->ID;
      }
      bool end()
      {
      	cout <<"sVector: end: " << Element << ", ";
      	if(Element)
      	{
      		cout << "0" << endl;
      		return 0;
      	}
     		cout << "1" << endl;
      	return 1;
      }
      
      _Tp& getNext()
      {
      	assert(Element->Next);
     		return Element->Next->Store;
      }
      
      _Tp& getPrev()
      {
      	assert(Element->Prev);
    		return Element->Prev->Store;
      }
      
    	_Tp* operator++()
    	{
     		Element=Element->Next;
    		if(Element)
    		{
      		return &(Element->Store);
    		}
    	  return 0;
    	}
    	
    	bool operator==(iterator& other)
    	{
    		return Element==other.Element;
    	}
    	
    	iterator& operator=(const sVector<_Tp>::iterator&  other)
    	{
    		Element = other.Element;
    		return *this;
    	}
    	_Tp* operator++(int t)
    	{
     		Element=Element->Next;
    		if(Element)
    		{
      		return &(Element->Store);
    		}
    	  return 0;
    	}

      _Tp* operator--(int t)
    	{
     		Element=Element->Prev;
    		if(Element)
    		{
      		return &(Element->Store);
    		}
    		return 0;
    	}
          	
    	_Tp* operator--()
    	{
     		Element=Element->Prev;
    		if(Element)
    		{
      		return &(Element->Store);
    		}
    		return 0;
    	}
    	
      _Tp* operator->()  const
      {
      	if(Element)
        	return &(Element->Store);
      	else
        	return 0;
      }
      
      _Tp& operator*()  const
      {
      	assert(Element);
      	return Element->Store;
      }
      
      friend  void sVector<_Tp>::erase(iterator& in);
  	private:
  	  sVectorElement* Element;
  };

	
private:
	class sVectorElement
	{
	public:
	  sVectorElement(_Tp in)
	  :Store(in)
	  {
	  } 
	  sVectorElement* Next;
	  sVectorElement* Prev;
	  unsigned int ID;
	  _Tp Store;
	};

  sVectorElement* Start;
  sVectorElement* End;
  sVectorElement* Middle;
  unsigned int Length;
};




template<typename _Tp>
sVector<_Tp>::sVector()
:Start(0),End(0),Middle(0),Length(0)
{
}

template<typename _Tp>
sVector<_Tp>::~sVector()
{
	cout<< "Remove sVector" << endl;
	if(Start)
	{
		while(Start->Next)
		{
			Start=Start->Next;
		  delete Start->Prev;		
		}
		delete Start;
	}
	cout<< "Remove complites" <<endl;
}

template<typename _Tp>
_Tp* sVector<_Tp>::push_back(_Tp in)
{

	Length++;
	if(!End)
	{
		End = new sVectorElement(in);
		Start = End;
		End->Prev=0;
		End->Next=Start;
		Middle=End;

	}
	else
	{
		End->Next=new sVectorElement(in);
		End->Next->Prev = End;
		End = End->Next;
		End->Next = 0;
  	if(Length&0x01)
  	{
  		assert(Middle);
 		  Middle = Middle->Next;
	  }
	}
	End->ID=Length;
	return &End->Store;
}

template<typename _Tp>
void   sVector<_Tp>::erase(iterator& in)
{
	cout << "\t\tsVector::erase: "<<in.ID() <<", Size: " << Length << endl;
	sVectorElement* Prev = in.Element->Prev;
	sVectorElement* Next = in.Element->Next;
	sVectorElement* Element = in.Element;
	
	
	if(Length>1)
	{
  	//handle end
  	if(Element==End) End=End->Next;
  	
  	//handle start
  	if(Element==Start) Start=Start->Prev;
  	
  	//handle middle  	
  	if(Length&0x01)
  	{
  		if(Middle!=Prev)
   		{
        Middle=Middle->Prev;		
		  }
  	}else	if(Element==Middle) Element=Element->Next;


  	if(Next)
  	{
  	  Next->Prev=Prev;
  	}

  	if(Prev)
  	{
  		Prev->Next=Next;
  	}
	}
	else
	{
		Start=0;
		End=0;
		Middle=0;
	}

  iterator Temp=	in;
  if(Temp++)
  {
  	for(;Temp.end();Temp++)
  	{
  		Temp.Element->ID--;
  	}
  }
  
	delete in.Element;
  in.Element=0;
	Length--;
}

template<typename _Tp>
void sVector<_Tp>::sort()
{
	if(!Start) 
	{
//		cout << "Sort: Kein Start" << endl;
		return;
	}
	sVectorElement* Work = Start->Next;
	while(Work)
	{
//		cout << "Sort: Work: " << Work->ID << endl;
   	sVectorElement* TempPrev=Work->Prev;
		if((TempPrev->Store) < (Work->Store))
		{
			Work=Work->Next;
			continue;
		}
		else
    {
    	sVectorElement* TempNext=Work->Next;
//      cout << "Sort: Change: " << Work->ID << "/" << TempPrev->ID << endl;  
      Work->Next = TempPrev;
      Work->Prev = TempPrev->Prev;
      Work->ID--;
      
      TempPrev->Prev=Work;
      TempPrev->Next=TempNext;
      TempPrev->ID++;    	
      
    	if(TempPrev==Middle)
    	{
    		 Middle = Work;
//    		cout << "Sort: NewMiddle(W): " << Middle->ID << endl;
    	}else	if(Work==Middle)
    	{
    		Middle = TempPrev;
//    		cout << "Sort: NewMiddle(T): " << Middle->ID << endl;
    	}
    	
      if(Work->Prev)
      {
      	Work->Prev->Next=Work;
      }
      else
      {
//      	cout << "Sort: NewStart: " << Work->ID << endl;
      	Start=Work;
      	Work=Work->Next;
      }
      
      if(TempNext)
      {
      	TempNext->Prev=TempPrev;
      }
      else
      {
         End=TempPrev;
//      	cout << "Sort: New End: "  << End->ID << endl;
      }
      
    }    		
	}
//	cout <<"End Sort: (S): " << Start <<" (M): " <<Middle << " (E): " << End << endl;
}


#endif /*SVECTOR_H_*/
