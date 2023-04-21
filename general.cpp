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

// Macro Definitions /////////////////////////////////////////////////////////
// Enumerations //////////////////////////////////////////////////////////////
// Typedefs //////////////////////////////////////////////////////////////////
// Forward References ////////////////////////////////////////////////////////
class SOME_DB;
class SOME_SETTINGS;
class Base;
class Derived;
void some_function(CLASS_NAME& m_obj);

// 1 Macros //////////////////////////////////////////////////////////////////
#define DEBUG 0
// later on in code:
#ifdef DEBUG
    std::cout << "do something" << std::endl;
#endif

// 2 Const and Static ////////////////////////////////////////////////////////
/* const
    - prevents obj, methods, variables, from modifying the items value 
    - const item must have an explicit value upon declaration
    - const_cast: when we need to pass in a non-const and we have a const
*/
const SOME_DB& m_db;
SOME_SETTINGS settings(const_cast<SOME_DB*>(&m_db));

/*static
    - Vars in a fn: space for it is allocated for the lifetime of program
    - Vars in a class: vars shared by class objects (init outside of class)
    - Static class obj: scope is lifetime of program
        non-static? constructor->destructor->main
        "static CLASSNAME objname" in main? constructor->main->destructor
    - Static fns in a class: can only access static data members or other
      static member functions 
        Do:         ClASSNAME::static_fn()
        Don't:      objname.static_fn()
*/

// 3 Chars and Strings ////////////////////////////////////////////////////////
void chars_strings(){
    char m_fixed_len[20] = "Hello!";        //any length over 7 works
    char m_not_fixed[] = "I like coding";
    strcat_s(m_fixed_len, 20, m_not_fixed); // char concatenation

    std::string m_str1 = "What day is it? ";
    std::string m_str2 = "Friday!"; 
    std::cout << m_str1+m_str2;             //can add strings

    // Find char in string 
    if (m_str1.find("?") != std::string::npos){
        // ? is in m_str1
    }
}

// 4 Class Template //////////////////////////////////////////////////////////
class CLASS_NAME
{
public:
    // order: types, static methods, creational (ctor, dtor, assign), virtual, non-virtual
    
    // CLASS_NAME() = default;
    // or 
    // example - passing reference in a constructor
    CLASS_NAME(const SOME_DB& db_input, SOME_SETTINGS& settings_input):
        m_db(db_input), m_settings(settings_input) {}

    CLASS_NAME(const CLASS_NAME&) = delete;
    CLASS_NAME& operator=(const CLASS_NAME&) = delete;
    virtual ~CLASS_NAME() = default;

protected:
    // order: types, static methods, creational, virtual, non-virtual
private:
    // order: types, static methods, creational, virtual, non-virtual

    // Data members 
    const SOME_DB& m_db;
    SOME_SETTINGS& m_settings;
};

// 5 Pointers and References /////////////////////////////////////////////////
void ptr_example(const SOME_DB& m_db, SOME_SETTINGS& m_settings){
    CLASS_NAME *m_classname;
    m_classname = new CLASS_NAME(m_db, m_settings);
    delete m_classname;
}

/*references: 
    - must be initialized at declaration, fixed type, no address, 1 level 
    of indirection
    - class members can't be references unless initialized before
*/

CLASS_NAME &reference_obj;            //reference
CLASS_NAME *ptr = &reference_obj;     //pointer from ref

const SOME_DB m_db;
SOME_SETTINGS *m_settings;
CLASS_NAME new_class_object(m_db, *m_settings);
some_function(new_class_object); //pass new_class_object as reference

// List of references
std::list<std::reference_wrapper<CLASS_NAME>> list_name;

// 6 Vector Fun /////////////////////////////////////////////////////////////
void vector_example(){
    std::vector<std::string> m_str_vec = {"a", "b", "c"};
        // Methods: m_str_vec.begin() .end() .size() .push_back() .clear()

    // Iterating 
    std::vector<std::string>::iterator iter;
    for (iter = m_str_vec.begin(); iter < m_str_vec.end(); iter++){
        std::cout << *iter;
    }
    // or
    for (auto elem : m_str_vec){
        std::cout << elem;
    }
    // or
    while (iter != m_str_vec.end()){
        //
        iter = next(iter, 1);
    }

    // Lambda functions in 1 line
    if(
        std::find_if(                // function - sort, find, find_if, etc.
            m_str_vec.begin(), m_str_vec.end(),  
            // []: references to any variables used in {}
            // (): create variables here
            // {}: return <function to isolate elements of the vector>
            [](const std::string& str)  
            { return str.find("substring") != std::string::npos; }
        ) != m_str_vec.end()
    ){
        std::cout << "Do something";
    }

    // Avoiding the last comma
    // Print vector to cout (can change cout to ostream)
    std::copy(m_str_vec.begin(), m_str_vec.end()-1, std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << m_str_vec.back();
    // or
    char const *pre = "";
    for (auto elem : m_str_vec){
        std::cout << pre << elem;
        pre=", ";
    }

}

// 7 Control Flow Template /////////////////////////////////////////////////
void switch_example(){
    int blah = 2;
    switch (blah){
        case 1: 
            // result = something;
            break; 
        case 2: 
            // ...
        default:
            // result = default case;
            break;
    }
}

// 8 Map fun ///////////////////////////////////////////////////////////////
void maps_examples(CLASS_NAME key, Base &val){
    // std::map< key type, value type>
        //value type CAN'T be a reference
        //           CAN be a pointer
        //           CAN be derived class
    std::map<CLASS_NAME, Base*> map_name;
    map_name.insert({key, &val});
    map_name.insert(std::make_pair(key, new Derived())); 

    // unordered map
    std::unordered_map<CLASS_NAME, Base*> unordered_map_name;
    unordered_map_name[key] = &val;
    if (unordered_map_name.count(key)){
        // found key in the map
    }
    for (auto const& x : unordered_map_name){
        // x.first is key
        // x.second is val
    }
}

// 9 File systems //////////////////////////////////////////////////////////
void file_fun(std::ostream &f){
    f << "Outputting this to file f\n";

    // Reading from file
    std::ifstream in_file;
    std::ofstream out_file;
    std::string str;

    in_file.open("in.txt");
    if (in_file.fail()){
        f << "Can't open blah.txt\n";
    } else {
        while (!in_file.eof()){
            // getting each line of blah.txt
            getline(in_file, str);
            f << str << ", ";
        }
        in_file.close();
    }

    // Writing from file
    out_file.open("out.txt");
    if (out_file.fail()){
        f << "can't open out.txt\n";
    } else {
        out_file << "writing this to out.txt\n";
        out_file.close();
    }
}

int main(){
    //Calling file_fun - ostream
    std::ofstream f("blah.txt", std::ios::out);
    if (!f.rdbuf()->is_open()){
        //can't open file
        return 0;
    }
    file_fun(f);
}