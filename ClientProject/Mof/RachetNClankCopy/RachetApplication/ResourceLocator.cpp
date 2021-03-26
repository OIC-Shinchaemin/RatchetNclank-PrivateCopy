#include "ResourceLocator.h"


std::weak_ptr<my::ResourceMgr> my::ServiceLocator<my::ResourceMgr>::_service;


my::ResourceLocator::ResourceLocator() :
    super() {
}

my::ResourceLocator::~ResourceLocator() {
}