#pragma once
#include "MofImGui/MofImGui.h"

// ********************************************************************************
/// <summary>
/// メインメニュークラス
/// </summary>
// ********************************************************************************
class MainMenu {
private:
    MainMenu(void) = delete;
    ~MainMenu(void) = delete;

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/20</created>
    /// <changed>いのうえ,2021/03/20</changed>
    // ********************************************************************************
    static void File(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/20</created>
    /// <changed>いのうえ,2021/03/20</changed>
    // ********************************************************************************
    static void Edit(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/20</created>
    /// <changed>いのうえ,2021/03/20</changed>
    // ********************************************************************************
    static void View(void);

public:

    // ********************************************************************************
    /// <summary>
    /// メインメニューの表示
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    static void Show(void);
};

