#pragma once

#include "Singleton.h"
#include "ActionBase.h"
#include <unordered_map>
#include <memory>

// ********************************************************************************
/// <summary>
/// �e�A�N�V�����̊Ǘ��N���X
/// </summary>
// ********************************************************************************
class ActionManager : public Singleton<ActionManager> {
private:
    
    //! �A�N�V�����}�b�v
    std::unordered_map<std::string, std::shared_ptr<ActionBase>> _action_map;

public:

    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^�A�����Ŋe�A�N�V������o�^���Ă���
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    ActionManager(void);

    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    ~ActionManager(void);

    // ********************************************************************************
    /// <summary>
    /// �A�N�V�����̌Ăяo��
    /// </summary>
    /// <param name="key">�Ăяo���A�N�V����</param>
    /// <returns>true : ����, false : ���s</returns>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    bool Action(const std::string& key, std::any any);
};