#include "CanvasLocator.h"

#include "My/UI/UICanvas.h"
#include "My/UI/UIPanel.h"


std::weak_ptr<my::UICanvas> my::ServiceLocator<my::UICanvas>::_service;


my::CanvasLocator::CanvasLocator() {
}

my::CanvasLocator::~CanvasLocator() {
}

void my::CanvasLocator::AddElement(const ElemPtr& elem) {
    _ASSERT_EXPR(super::GetService(), L"�����ȃ|�C���^���Q�Ƃ��Ă��܂�");
    super::GetService()->AddElement(elem);
}

void my::CanvasLocator::RemoveElement(const ElemPtr& elem) {
    _ASSERT_EXPR(super::GetService(), L"�����ȃ|�C���^���Q�Ƃ��Ă��܂�");
    super::GetService()->RemoveElement(elem);
}