#include "ActionManager.h"
#include "ActionKeyName.h"

#include "MeshLoad.h"
#include "MeshLoadDialog.h"
#include "SaveProject.h"
#include "SaveProjectDialog.h"
#include "LoadProject.h"
#include "LoadProjectDialog.h"
#include "ProjectDataParse.h"
#include "AddObject.h"
#include "FileClose.h"

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^�A�����Ŋe�A�N�V������o�^���Ă���
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
ActionManager::ActionManager(void) {
    _action_map[ActionKeyName::MeshLoad]          = std::make_shared<MeshLoad>();
    _action_map[ActionKeyName::MeshLoadDialog]    = std::make_shared<MeshLoadDialog>();
    _action_map[ActionKeyName::SaveProject]       = std::make_shared<SaveProject>();
    _action_map[ActionKeyName::SaveProjectDialog] = std::make_shared<SaveProjectDialog>();
    _action_map[ActionKeyName::LoadProject]       = std::make_shared<LoadProject>();
    _action_map[ActionKeyName::LoadProjectDialog] = std::make_shared<LoadProjectDialog>();
    _action_map[ActionKeyName::ProjectDataParse]  = std::make_shared<ProjectDataParse>();
    _action_map[ActionKeyName::AddObject]         = std::make_shared<AddObject>();
    _action_map[ActionKeyName::FileClose]         = std::make_shared<FileClose>();
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
ActionManager::~ActionManager(void) {
}

// ********************************************************************************
/// <summary>
/// �A�N�V�����̌Ăяo��
/// </summary>
/// <param name="key">�Ăяo���A�N�V����</param>
/// <returns>true : ����, false : ���s</returns>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
bool ActionManager::Action(const std::string& key, std::any any) {
    // �L�[����A�N�V�������������āA������Ȃ����false��Ԃ��B
    auto& action = _action_map.find(key);
    if (action == _action_map.end()) {
        return false;
    }
    // ������΃A�N�V�������ʂ�Ԃ��B
    return action->second->Action(any);
}
