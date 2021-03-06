#ifndef RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_DATA_H
#define RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_DATA_H


#include <cstdint>
#include <string>
#include <vector>


namespace ratchet {
namespace game {
namespace gamesystem {
namespace save{
struct SaveDataParam {
    //! 所持
    int money;
    //! 所持
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
    ratchet::game::gamesystem::save::SaveDataParam _param;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SaveData();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SaveData();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    void MoveParam(SaveDataParam& param);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetMoney(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    const std::vector<std::string>& GetAvailableMechanicalWeaponsAddress(void);
};
}
}
}
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SAVE_SAVE_DATA_H