#include "MeshLoadDialog.h"
#include "FileDialog.h"
#include "ActionManager.h"
#include "Define.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
bool MeshLoadDialog::Action(std::any any) {
    // �t�@�C���p�X
    char path[MAX_PATH];
    // �����ǂݍ���ł��邩�ǂ���(TODO:)
    bool array_flag;
    // �_�C�A���O�̊J�n
    bool open = FileDialog::Open(
        NULL, FileDialog::Mode::Open,
        "���b�V���t�@�C���ǂݍ���",
        "mesh file(*.mom)\0*.mom\0all file(*.*)\0*.*\0\0",
        "mom",
        path, array_flag
    );

    // �I�[�v���ɐ������Ă���΃��b�V���̓o�^���s��
    if (open) {
        // �t�@�C����
        std::string* out = std::any_cast<std::string*>(any);
        *out = FileDialog::GetFileName(path);
        // �o�^�f�[�^�̍쐬
        std::pair<std::string, std::string> data(*out, path);
        // ���b�V���̓ǂݍ��݁A�o�^������
        ActionManager::GetInstance().Action("MeshLoad", data);
        return true;
    }
    return false;
}
