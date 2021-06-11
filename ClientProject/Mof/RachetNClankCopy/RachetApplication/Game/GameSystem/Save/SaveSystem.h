#ifndef RACHET_SAVE_SYSTEM_H
#define RACHET_SAVE_SYSTEM_H


#include <string>

#include "SaveData.h"


namespace rachet {
class SaveSystem {
private:
    std::string _path;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SaveSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SaveSystem();
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="out"></param>
    /// <returns></returns>
    bool Fetch(rachet::SaveData& out);
    /// <summary>
    /// ��������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    bool Save(const rachet::SaveDataParam& param);
};
}
#endif // !RACHET_SAVE_SYSTEM_H