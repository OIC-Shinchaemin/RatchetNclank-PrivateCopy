#ifndef MY_SAVE_DATA_H
#define MY_SAVE_DATA_H


#include <cstdint>


namespace my {
struct SaveDataParam {
    int money;
    SaveDataParam() : money(0) {
    }
    SaveDataParam(int m) :money(m) {
    }
};
class SaveData {
private:
    my::SaveDataParam _param;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SaveData();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SaveData();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    void MoveParam(SaveDataParam& param);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetMoney(void) const;
};
}
#endif // !MY_SAVE_DATA_H