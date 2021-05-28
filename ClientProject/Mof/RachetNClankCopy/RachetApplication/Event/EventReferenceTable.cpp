#include "EventReferenceTable.h"


my::EventReferenceTable::EventReferenceTable() :
    _data_table() {
}

my::EventReferenceTable::~EventReferenceTable() {
}

my::EventReferenceTable& my::EventReferenceTable::Singleton(void) {
    static my::EventReferenceTable object;
    return object;
}

std::any my::EventReferenceTable::At(const std::string& key) {
    return this->_data_table.at(key);
}

void my::EventReferenceTable::Register(const std::string& key, std::any value) {
    this->_data_table.emplace(key, value);
}

void my::EventReferenceTable::Dispose(const std::string& key) {
    this->_data_table.erase(key);
}

void my::EventReferenceTable::Reset(void) {
    this->_data_table.clear();
}