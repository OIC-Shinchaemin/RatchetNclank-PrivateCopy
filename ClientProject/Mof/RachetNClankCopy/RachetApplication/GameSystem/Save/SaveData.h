#ifndef MY_SAVE_DATA_H
#define MY_SAVE_DATA_H


#include <cstdint>
#include <string>
#include <vector>


namespace my {
struct SaveDataParam {
    //! ����
    int money;
    //! ����
    std::vector<std::string> available_weapons;

    SaveDataParam() : money(0), available_weapons() {
    }
    SaveDataParam(int m, std::vector<std::string>& move) :
        money(m),
        available_weapons(std::move(move)) {
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
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    const std::vector<std::string>& GetAvailableMechanicalWeaponsAddress(void);
};
}
#endif // !MY_SAVE_DATA_H