#pragma once
#include "Singleton.h"
#include "MofImGui/MofImGui.h"
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// Gui表示しているWindowの矩形情報
/// </summary>
// ********************************************************************************
class GuiWindowRect : public Singleton<GuiWindowRect> {
public:

    struct Data {
        std::string name{ "" };
        CRectangle  rect{ Mof::Rectangle() };
        bool*       active_pointer{ nullptr };
    };

private:

    //! データ配列
    std::vector<Data> _data_array;

public:

    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    GuiWindowRect(void) = default;

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    ~GuiWindowRect(void) = default;

    // ********************************************************************************
    /// <summary>
    /// 矩形の登録
    /// </summary>
    /// <param name="name">登録名</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Add(const std::string& name = "");

    // ********************************************************************************
    /// <summary>
    /// 矩形の検索
    /// </summary>
    /// <param name="name">検索する名前</param>
    /// <returns>成功：矩形データポインタ、失敗：nullptr</returns>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    CRectangle* Find(const std::string& name);

    // ********************************************************************************
    /// <summary>
    /// データ配列の取得
    /// </summary>
    /// <returns>データ配列</returns>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    const std::vector<Data>& GetDataArray(void) const;

    // ********************************************************************************
    /// <summary>
    /// Guiを操作しているかのフラグ取得
    /// </summary>
    /// <returns>Guiを操作しているかのフラグ</returns>
    /// <created>いのうえ,2021/03/20</created>
    /// <changed>いのうえ,2021/03/20</changed>
    // ********************************************************************************
    bool IsGuiItemUse(void) const;
};