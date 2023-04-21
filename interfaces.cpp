#include "interfaces.h"


int TOP_LEVEL_CLASS_EXAMPLE::some_function(const SOME_DB &db, FACTORY_INTF &factory){
    int ret = 0;
    // do some stuff, write to factory, etc.
    
    return ret;
}
    
bool TOP_LEVEL_CLASS_EXAMPLE::another_fn(){return false;}

DATA_INTF* FACTORY_EXAMPLE::get_data_info(std::string &key){
    if (m_data_map.count(key)){
        return m_data_map[key];
    } else {
        return nullptr;
    }
}

void FACTORY_EXAMPLE::insert_data_to_map(std::string key, DATA_INTF* val){
    m_data_map[key] = val;
}

std::vector<std::string> FACTORY_EXAMPLE::check_mapping(){
    std::vector<std::string> result;
    for (auto const& x : m_data_map)
    {
        if (x.first == "abc"){
            result.push_back(x.first);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

void DATA_EXAMPLE::set_blah(const BLAH &eh){
    m_eh = eh;
}

const BLAH& DATA_EXAMPLE::get_blah(){
    return m_eh;
}

void DATA_EXAMPLE::set_some_bool(){
    eh_exists = true;
    return;
}

bool DATA_EXAMPLE::get_the_bool(){
    return eh_exists;
}