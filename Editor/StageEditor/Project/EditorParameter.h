#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// �G�f�B�^�p�p�����[�^�ێ��N���X
/// </summary>
// ********************************************************************************
class EditorParameter {
private:

    //! mouse���\���t���O
    bool        _show_mouseinfo    { false };
    //! IsItem���\���t���O
    bool        _show_isiteminfo   { false };
    //! Rect���\���t���O
    bool        _show_rectinfo     { false };
    //! DemoWindow�\���t���O
    bool        _show_demo_window  { false };

    //! MeshWindow�\���t���O
    bool        _show_mesh_window  { true };
    //! ObjectWindow�\���t���O
    bool        _show_object_window{ true };
    //! ToolMenu�\���t���O
	bool        _show_tool_menu    { true };
    //! �O���b�h�̕\���t���O
    bool        _show_grid         { true };
    //! ���C�����j���[�\���t���O
    bool        _show_main_menu    { true };

	//! MeshView�̃J������Zoom��
	float       _mesh_view_zoom    { 1.0f };

	//! �G�f�B�^�̔w�i�F
	Vector4     _background_color  { Vector4(0,0,1,0) };

    //! �G�f�B�^�̃��[�h
    int         _edit_mode         { 0 };
    //! �O���b�h�̊Ԋu
    int         _grid_between      { 4 };
    //! �O���b�h�̃T�C�Y
    int         _grid_size         { 100 };

    //! �J���Ă���t�@�C����
    std::string _open_file_name    { "" };
    //! �f�ރt�H���_�̃p�X
    std::string _resource_path     { "" };

public:

    //! �e�Q�b�^�[
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

    //! �e�Z�b�^�[
    void SetResourcePath(const std::string& path);
    
    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    EditorParameter(void);
    
    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    ~EditorParameter(void);
};

