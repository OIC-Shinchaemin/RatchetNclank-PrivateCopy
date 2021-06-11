#include "EventReferenceTable.h"


rachet::EventReferenceTable::EventReferenceTable() :
    _data_table() {
}

rachet::EventReferenceTable::~EventReferenceTable() {
}

rachet::EventReferenceTable& rachet::EventReferenceTable::Singleton(void) {
    static rachet::EventReferenceTable object;
    return object;
}

std::any rachet::EventReferenceTable::At(const std::string& key) {
    return this->_data_table.at(key);
}

void rachet::EventReferenceTable::Register(const std::string& key, std::any value) {
    this->_data_table.emplace(key, value);
}

void rachet::EventReferenceTable::Dispose(const std::string& key) {
    this->_data_table.erase(key);
}

void rachet::EventReferenceTable::Reset(void) {
    this->_data_table.clear();
}