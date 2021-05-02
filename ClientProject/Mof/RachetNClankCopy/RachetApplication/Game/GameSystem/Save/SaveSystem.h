#ifndef MY_SAVE_SYSTEM_H
#define MY_SAVE_SYSTEM_H


#include <string>

#include "SaveData.h"


namespace my {
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
    bool Fetch(my::SaveData& out);
    /// <summary>
    /// ��������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    bool Save(const my::SaveDataParam& param);
};
}
#endif // !MY_SAVE_SYSTEM_H