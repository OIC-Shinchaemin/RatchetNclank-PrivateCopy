#include "EventReferenceTable.h"


ratchet::EventReferenceTable::EventReferenceTable() :
    _data_table() {
}

ratchet::EventReferenceTable::~EventReferenceTable() {
}

ratchet::EventReferenceTable& ratchet::EventReferenceTable::Singleton(void) {
    static ratchet::EventReferenceTable object;
    return object;
}

std::any ratchet::EventReferenceTable::At(const std::string& key) {
    return this->_data_table.at(key);
}

void ratchet::EventReferenceTable::Register(const std::string& key, std::any value) {
    this->_data_table.emplace(key, value);
}

void ratchet::EventReferenceTable::Dispose(const std::string& key) {
    this->_data_table.erase(key);
}

void ratchet::EventReferenceTable::Reset(void) {
    this->_data_table.clear();
}