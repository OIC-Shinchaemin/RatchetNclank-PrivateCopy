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
    /// コンストラクタ
    /// </summary>
    SaveSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SaveSystem();
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="out"></param>
    /// <returns></returns>
    bool Fetch(rachet::SaveData& out);
    /// <summary>
    /// 書き込み
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    bool Save(const rachet::SaveDataParam& param);
};
}
#endif // !RACHET_SAVE_SYSTEM_H