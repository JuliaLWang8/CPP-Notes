/*
    Interfaces example
*/

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

#include "inheritance.h"

// Forward References ////////////////////////////////////////////////////////
class FACTORY_INTF;
class BLAH;

// Interfaces ////////////////////////////////////////////////////////////////
class TOP_LEVEL_CLASS_INTF
// Top level class has client facing functions
{
public:
    
    TOP_LEVEL_CLASS_INTF() = default;
    TOP_LEVEL_CLASS_INTF(const TOP_LEVEL_CLASS_INTF&) = delete;
    TOP_LEVEL_CLASS_INTF& operator=(const TOP_LEVEL_CLASS_INTF&) = delete;
    virtual ~TOP_LEVEL_CLASS_INTF() = default;

    virtual int some_function(const SOME_DB &db, FACTORY_INTF &factory) = 0;
    virtual bool another_fn() = 0;

protected:
    //
private:
    //
};

class FACTORY_INTF
// Factory class stores data, accesses data, modifies data
{
public:
    
    FACTORY_INTF() = default;
    FACTORY_INTF(const FACTORY_INTF&) = delete;
    FACTORY_INTF& operator=(const FACTORY_INTF&) = delete;
    virtual ~FACTORY_INTF() = default;

    virtual DATA_INTF* get_data_info(std::string &key) = 0;
protected:
    //
private:
    //
    std::unordered_map<std::string, DATA_INTF*> m_data_map;
};

class DATA_INTF
// The actual data itself - data members = data we want to store
{
public:
    
    DATA_INTF() = default;
    DATA_INTF(const DATA_INTF&) = delete;
    DATA_INTF& operator=(const DATA_INTF&) = delete;
    virtual ~DATA_INTF() = default;

    virtual void set_blah(const BLAH &eh) = 0;
    virtual const BLAH& get_blah() = 0;
    virtual void set_some_bool() = 0;
    virtual bool get_the_bool() = 0;

protected:
    //
private:
    // Data members
};

// Example using interfaces //////////////////////////////////////////////////
class TOP_LEVEL_CLASS_EXAMPLE : public TOP_LEVEL_CLASS_INTF
{
public:
    // Can have additional inputs to derived class
    TOP_LEVEL_CLASS_EXAMPLE(FACTORY_INTF& factory_in):
        m_factory(factory_in) {}

    TOP_LEVEL_CLASS_EXAMPLE(const TOP_LEVEL_CLASS_EXAMPLE&) = delete;
    TOP_LEVEL_CLASS_EXAMPLE& operator=(const TOP_LEVEL_CLASS_EXAMPLE&) = delete;
    virtual ~TOP_LEVEL_CLASS_EXAMPLE() = default;

    // functions called by users, some_function can modify factory
    int some_function(const SOME_DB &db, FACTORY_INTF &factory);
    bool another_fn();

protected:
    //
private:
    // Top level class hosts the factory storing data
    FACTORY_INTF &m_factory;
};

class FACTORY_EXAMPLE : public FACTORY_INTF
{
public:
    
    FACTORY_EXAMPLE() = default;
    FACTORY_EXAMPLE(const FACTORY_EXAMPLE&) = delete;
    FACTORY_EXAMPLE& operator=(const FACTORY_EXAMPLE&) = delete;
    virtual ~FACTORY_EXAMPLE() = default;

    // Functions for map (insert data, getting data, etc.)
    DATA_INTF* get_data_info(std::string &key);
    void insert_data_to_map(std::string key, DATA_INTF* val);
    std::vector<std::string> check_mapping();

protected:
    //
private:
    // The factory stores the data mapping (from name to data)
    std::unordered_map<std::string, DATA_INTF*> m_data_map;
};

class DATA_EXAMPLE : public DATA_INTF
// The actual data itself - data members = data we want to store
{
public:
    
    DATA_EXAMPLE() = default;
    DATA_EXAMPLE(const DATA_EXAMPLE&) = delete;
    DATA_EXAMPLE& operator=(const DATA_EXAMPLE&) = delete;
    virtual ~DATA_EXAMPLE() = default;

    void set_blah(const BLAH &eh);
    const BLAH& get_blah();
    void set_some_bool();
    bool get_the_bool();

protected:
    //
private:
    // Data members
    BLAH m_eh;
    bool eh_exists = false;
};

// Example usage /////////////////////////////////////////////////////////////
void main(){
    FACTORY_EXAMPLE factory;
    SOME_DB* m_db;

    TOP_LEVEL_CLASS_EXAMPLE top_level = TOP_LEVEL_CLASS_EXAMPLE(factory);
    int out = top_level.some_function(m_db, factory);

}