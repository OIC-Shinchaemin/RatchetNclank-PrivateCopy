#include "EventReferenceTable.h"


ratchet::event::EventReferenceTable::EventReferenceTable() :
    _data_table() {
}

ratchet::event::EventReferenceTable::~EventReferenceTable() {
}

ratchet::event::EventReferenceTable& ratchet::event::EventReferenceTable::Singleton(void) {
    static ratchet::event::EventReferenceTable object;
    return object;
}

std::any ratchet::event::EventReferenceTable::At(const std::string& key) {
    return this->_data_table.at(key);
}

void ratchet::event::EventReferenceTable::Register(const std::string& key, std::any value) {
    this->_data_table.emplace(key, value);
}

void ratchet::event::EventReferenceTable::Dispose(const std::string& key) {
    this->_data_table.erase(key);
}

void ratchet::event::EventReferenceTable::Reset(void) {
    this->_data_table.clear();
}