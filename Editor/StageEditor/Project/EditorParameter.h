#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// エディタ用パラメータ保持クラス
/// </summary>
// ********************************************************************************
class EditorParameter {
private:

    //! mouse情報表示フラグ
    bool        _show_mouseinfo    { false };
    //! IsItem情報表示フラグ
    bool        _show_isiteminfo   { false };
    //! Rect情報表示フラグ
    bool        _show_rectinfo     { false };
    //! DemoWindow表示フラグ
    bool        _show_demo_window  { false };

    //! MeshWindow表示フラグ
    bool        _show_mesh_window  { true };
    //! ObjectWindow表示フラグ
    bool        _show_object_window{ true };
    //! ToolMenu表示フラグ
	bool        _show_tool_menu    { true };
    //! グリッドの表示フラグ
    bool        _show_grid         { true };
    //! メインメニュー表示フラグ
    bool        _show_main_menu    { true };

	//! MeshViewのカメラのZoom率
	float       _mesh_view_zoom    { 1.0f };

	//! エディタの背景色
	Vector4     _background_color  { Vector4(0,0,1,0) };

    //! エディタのモード
    int         _edit_mode         { 0 };
    //! グリッドの間隔
    int         _grid_between      { 4 };
    //! グリッドのサイズ
    int         _grid_size         { 100 };

    //! 開いているファイル名
    std::string _open_file_name    { "" };
    //! 素材フォルダのパス
    std::string _resource_path     { "" };

public:

    //! 各ゲッター
    bool IsShowMouseInfo(void) const;
    bool IsShowIsItemInfo(void) const;
    bool IsShowRectInfo(void) const;
    bool IsShowDemoWindow(void) const;
    bool IsShowMeshWindow(void) const;
    bool IsShowObjectWindow(void) const;
    bool IsShowToolMenu(void) const;
    bool IsShowMainMenu(void) const;
    bool IsShowGrid(void) const;

    int GetEditMode(void) const;

    std::string GetResourcePath(void) const;

    //! 各セッター
    void SetResourcePath(const std::string& path);
    
    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    EditorParameter(void);
    
    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    ~EditorParameter(void);
};

