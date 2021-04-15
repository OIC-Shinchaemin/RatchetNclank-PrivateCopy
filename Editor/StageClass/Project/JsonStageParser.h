#pragma once
#include "StageParser.h"

/// <summary>
/// json�t�@�C������X�e�[�W�f�[�^�ɕ�������N���X
/// </summary>
class JsonStageParser : public IStageParser {
public:

    /// <summary>
    /// �t�@�C������X�e�[�W�f�[�^�ɕ�������
    /// </summary>
    /// <param name="path">�t�@�C���p�X</param>
    /// <param name="out">�o�̓f�[�^</param>
    /// <returns>StageFileResult_Success : ����, ����ȊO : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) override;
};

