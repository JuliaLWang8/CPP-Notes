// Dependencies //////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <vector>
#include <iterator>
#include <ostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <utility>

// Macro Definitions /////////////////////////////////////////////////////////
#define INPUT_PREFIX "input"

// Enumerations //////////////////////////////////////////////////////////////
// Typedefs //////////////////////////////////////////////////////////////////
// Forward References ////////////////////////////////////////////////////////
class SOME_DB;
class SOME_SETTINGS;
class BLAH;
class Base;
class Derived;

/*
    Abstract Classes: have at least 1 pure virtual function, we can't create
        an object of that class
    Pure Virtual Function:      virtual <type> fn_name(<type> arg1, ...) = 0;
        Only implement function in derived class (overriding) 
        - if we don't, the derived class will also be abstract
        - can only change <type> to a COVARIANT type
        - can't change <type> of args
    Covariant return types: 
        - ptr/ref to class, must be same class or derived
    Interface: all methods are pure virtual
*/

// Interfaces ///////////////////////////////////////////////////////////////
class SOME_CLASS_INTF
{
public:
    
    SOME_CLASS_INTF() = default;
    SOME_CLASS_INTF(const SOME_CLASS_INTF&) = delete;
    SOME_CLASS_INTF& operator=(const SOME_CLASS_INTF&) = delete;
    virtual ~SOME_CLASS_INTF() = default;

    virtual int some_function(const SOME_DB &db, SOME_SETTINGS &settings) = 0;
    virtual bool another_fn() = 0;
    virtual Base* return_type_example() = 0;

protected:
    //
private:
    // an example function
    virtual Base* get_blah(SOME_SETTINGS &settings){
        static Base dummy_info;
        return &dummy_info;
    }
};

/*Design decisions
    Separate interfaces for: top level, storing data (factory), data itself
*/

/*
    Fake: implementation with same functionality but not for production
    Mock: set expectations which form a specification of calls expected
    Stub: predefined answers to method calls 
*/

// Inheritance /////////////////////////////////////////////////////////////////

class SOME_CLASS_STUB: public SOME_CLASS_INTF
/*
    Derived class from SOME_CLASS_INTF, public derivation 
    If public derivation:
        public members of Base -> public members of Derived
        protected members of Base -> protected members of Derived
    If protected derivation:
        public & protected of Base -> protected of Derived
    If private derivation: 
        public & protected of Base -> private of Derived
*/
{
public:
    // We can add additional inputs to constructor of derived class
    SOME_CLASS_STUB(const SOME_DB& db_input, SOME_SETTINGS& settings_input):
        m_db(db_input), m_settings(settings_input) {}

    SOME_CLASS_STUB(const SOME_CLASS_STUB&) = delete;
    SOME_CLASS_STUB& operator=(const SOME_CLASS_STUB&) = delete;
    virtual ~SOME_CLASS_STUB() = default;

    // All pure virtual classes get implemented in derived class
    int some_function(const SOME_DB &db, SOME_SETTINGS &settings);
    bool another_fn();
    Derived* return_type_example();

    // Derived classes can have additional functions
    std::vector<int> a_new_function_for_this_class();

protected:
    //
private:
    // And additonal data members 
    const SOME_DB& m_db;
    SOME_SETTINGS& m_settings;
    BLAH *m_blah;
};

// in .cpp file: ///////////////////////////////////
int SOME_CLASS_STUB::some_function(const SOME_DB &db, SOME_SETTINGS &settings){return 0;}
bool SOME_CLASS_STUB::another_fn(){ return true;}
std::vector<int> SOME_CLASS_STUB::a_new_function_for_this_class(){}
Derived* SOME_CLASS_STUB::return_type_example(){}

// More about derived classes //////////////////////////////////////////////
class Base {
public:
    int a;
};

class Derived : public Base {
public:
    int b;
    // object of derived class has both a and b
};

int main()
{
    // Can pass in derived as base
    Base *ptr = new Derived();
    delete ptr;

    // Example
    Derived example;
    example.a = 3;
}