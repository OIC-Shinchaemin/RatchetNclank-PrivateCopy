#ifndef RACHET_SAVE_DATA_H
#define RACHET_SAVE_DATA_H


#include <cstdint>
#include <string>
#include <vector>


namespace rachet {
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
    rachet::SaveDataParam _param;
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
#endif // !RACHET_SAVE_DATA_H