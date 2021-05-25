#include "StageViewEvent.h"


my::StageViewEvent::StageViewEvent(){
}

my::StageViewEvent::~StageViewEvent() {
}

void my::StageViewEvent::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

bool my::StageViewEvent::Initialize(void) {
    return true;
}