/*************************************************************************//*!

                    @file    GameApp.cpp
                    @brief    ��{�Q�[���A�v���B

                                                            @author    �_�c�@��
                                                            @date    2014.05.14
*//**************************************************************************/

#include    "MofImGui/MofImGui.h"
#include    <filesystem>

//INCLUDE
#include    "GameApp.h"

#include    "MouseMoveCameraController.h"
#include    "MeshViewCameraController.h"

#include    "Define.h"

#include    "DebugGui.h"

#include    "MainMenu.h"
#include    "ToolMenu.h"

#include    "EditorParameter.h"
#include    "GuiWindowRect.h"
#include    "MeshWindow.h"
#include    "ObjectWindow.h"
#include    "ActionManager.h"
#include    "ParameterMap.h"
#include    "WindowKeyName.h"
#include    "MouseUtilities.h"
#include    "FileDialog.h"
#include    "ToolIcon.h"
#include    "Cursor.h"

//COMMAND
#include    "CommandManager.h"
#include    "ObjectPlantCommand.h"
#include    "CommandLogWindow.h"

//Singleton
GuiWindowRect             gui_window_rect;
ActionManager             action_manager;
ParameterMap<bool>        parameter_map_bool;
ParameterMap<int>         parameter_map_int;
ParameterMap<float>       parameter_map_float;
ParameterMap<Vector4>     parameter_map_vec4;
ParameterMap<std::string> parameter_map_string;
ParameterMap<ObjectList>  parameter_map_objectlist;
ParameterMap<MeshList>    parameter_map_meshlist;
ToolIcon                  tool_icon;
CommandManager            command_manager;
MeshWindow                mesh_window;
ObjectWindow              object_window;
CommandLogWindow          command_log_window;

EditorParameter           editor_parameter;

CXGamePad                 gamepad;

CCamera                   main_camera;
MouseMoveCameraController camera_controller;


/*************************************************************************//*!
        @brief            �A�v���P�[�V�����̏�����
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

    CMofImGui::Setup(false, false);

    CUtilities::SetCurrentDirectory("Resource");
    std::string resource_dir = std::filesystem::current_path().string();
    editor_parameter.SetResourcePath(resource_dir);

    tool_icon.Load();

    float scene_w = window_width;
    float scene_h = window_height;

    main_camera.SetViewPort();
    main_camera.PerspectiveFov(MOF_ToRadian(60), scene_w / scene_h, 0.1f, 500.0f);
    main_camera.LookAt(Vector3(0.0f, 2.0f, -6.0f), Vector3(0, 0.5f, 0), Vector3(0, 1, 0));
    main_camera.Update();

    camera_controller.Initialize(&main_camera);

    CGraphicsUtilities::SetCamera(&main_camera);

    XGAMEPADCREATEINFO pad_info;
    pad_info.No = 0;
    gamepad.Create(&pad_info);

    return TRUE;
}
/*************************************************************************//*!
        @brief            �A�v���P�[�V�����̍X�V
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
    CMofImGui::Refresh();
    //�L�[�̍X�V
    g_pInput->RefreshKey();
    gamepad.RefreshKey();
	//mesh_view_controller.Update();

    // ToolMenu
    int* edit_mode = ParameterMap<int>::GetInstance().Get("edit_mode");
    {
        *edit_mode = EditMode::InstObject;
        bool is_alt = (g_pInput->IsKeyHold(MOFKEY_LALT) || g_pInput->IsKeyHold(MOFKEY_RALT));
        bool is_ctrl = (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsKeyHold(MOFKEY_RCONTROL));
        if (is_alt) {
            *edit_mode = EditMode::EditEye | EditMode::MoveCamera;
            Cursor::ChangeCursor(CursorType::PIN);
        }
        else if (is_ctrl) {
            *edit_mode = EditMode::EditHand | EditMode::MoveCamera;
            Cursor::ChangeCursor(CursorType::HAND);
        }
    }

    // �R�}���h�}�l�[�W���[
    {
        if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_Z)) {
            command_manager.Undo();
        }
        if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_Y)) {
            command_manager.Redo();
        }
    }
    // Short cut
    {
        bool is_ctrl  = (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsKeyHold(MOFKEY_RCONTROL));
        bool is_shift = (g_pInput->IsKeyHold(MOFKEY_LSHIFT)   || g_pInput->IsKeyHold(MOFKEY_RSHIFT));
        bool is_alt   = (g_pInput->IsKeyHold(MOFKEY_LALT)     || g_pInput->IsKeyHold(MOFKEY_RALT));
        if (is_ctrl && g_pInput->IsKeyPush(MOFKEY_N)) {
            MainMenu::New();
            Cursor::ChangeCursor(CursorType::WAIT);
        }
        if (is_ctrl && g_pInput->IsKeyPush(MOFKEY_O)) {
            MainMenu::Open();
            Cursor::ChangeCursor(CursorType::WAIT);
        }
        if (is_ctrl && is_alt && g_pInput->IsKeyPush(MOFKEY_C)) {
            MainMenu::Close();
            Cursor::ChangeCursor(CursorType::WAIT);
        }
        if (is_ctrl && g_pInput->IsKeyPush(MOFKEY_S)) {
            MainMenu::Save();
            Cursor::ChangeCursor(CursorType::WAIT);
        }
        if (is_ctrl && is_shift && g_pInput->IsKeyPush(MOFKEY_S)) {
            MainMenu::SaveAs();
            Cursor::ChangeCursor(CursorType::WAIT);
        }
        if ((is_shift && g_pInput->IsKeyPush(MOFKEY_F4)) || g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
            MainMenu::Quit();
        }
    }

    bool isUseGui = GuiWindowRect::GetInstance().IsGuiItemUse();
    if(!isUseGui) {
        // �J��������
        camera_controller.Update();
    }
    if (g_pInput->IsKeyPush(MOFKEY_F1)) {
        main_camera.SetTargetPosition(Vector3());
        main_camera.SetViewPosition(Vector3(0.0f, 2.0f, -6.0f));
        main_camera.Update();
        CGraphicsUtilities::SetCamera(&main_camera);
    }

    if (editor_parameter.IsShowMainMenu()) {
        MainMenu::Show();
    }
    
    if (editor_parameter.IsShowToolMenu()) {
        ToolMenu::Show();
    }

    if (editor_parameter.IsShowObjectWindow()) {
        object_window.Show();
    }

    if (editor_parameter.IsShowCommandLogWindow()) {
        command_log_window.Show();
    }

    if ((*edit_mode) & InstObject) {
        MeshData* mesh_pointer = mesh_window.GetSelectMeshData();
        if (mesh_pointer && !isUseGui && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
            ObjectData data;
            data.position       = MouseUtilities::GetWorldPos();
            data.mesh_path      = MeshAsset::GetKey(mesh_pointer->second.lock());
            data.name           = mesh_pointer->first;
            data.mesh_index     = mesh_window.GetSelectNo();
            ICommandPtr command = std::make_shared<ObjectPlantCommand>(&data);
            command_manager.Register(command);
        }
    }

    if (editor_parameter.IsShowMouseInfo())  { DebugGui::ShowMouseInfoWindow(); }
    if (editor_parameter.IsShowIsItemInfo()) { DebugGui::ShowIsItemInfoWindow(); }
    if (editor_parameter.IsShowRectInfo())   { DebugGui::ShowRectInfoWindow(); }
    if (editor_parameter.IsShowDemoWindow()) { ImGui::ShowDemoWindow(parameter_map_bool.Get(WindowKeyName::DebugDemoWindow)); }

    return TRUE;
}
/*************************************************************************//*!
        @brief            �A�v���P�[�V�����̕`��
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
    //�`��J�n
    g_pGraphics->RenderStart();
	Vector4* back_color = parameter_map_vec4.Get("background_color");

    //��ʂ̃N���A
    g_pGraphics->ClearTarget(back_color->r, back_color->g, back_color->b, back_color->a, 1.0f, 0);
    
	CGraphicsUtilities::SetCamera(&main_camera);
    g_pGraphics->SetDepthEnable(TRUE);

    // �O���b�h�̕\��
    if (editor_parameter.IsShowGrid()) {
        int grid_between = *parameter_map_int.Get("grid_between");
        int grid_size    = *parameter_map_int.Get("grid_size");
        CGraphicsUtilities::RenderGrid(grid_between, grid_size, MOF_COLOR_WHITE, PLANEAXIS_ALL);
    }

    for (const auto& it : object_window.GetObjectList()) {
        std::shared_ptr<CMeshContainer> mesh_pointer = nullptr;
        const int                       mesh_no      = it.mesh_index;
        if (mesh_no >= 0) {
            mesh_pointer = mesh_window.GetMeshList()[mesh_no].second.lock();
        }
        else {
            continue;
        }
        CMatrix44 object_rotation, object_scale;
        CMatrix44 object_matrix;
        object_rotation.RotationZXY(it.rotation);
        object_scale.Scaling(it.scale);
        object_matrix = object_scale * object_rotation;
        object_matrix.SetTranslation(it.position);
        // �I�𒆂̃I�u�W�F�N�g�������\������
        if (ObjectData::Compare(it, *object_window.GetSelectObjectData())) {
            CMatrix44 object_edge_scale, object_matrix_edge;
            object_edge_scale.Scaling(it.scale * 1.03f);
            object_matrix_edge = object_edge_scale * object_rotation;
            object_matrix_edge.SetTranslation(it.position);
            // ���C�g�̉e�����������߂ɑS�����ɐݒ�
            CMaterial edge_material;
            edge_material.SetAmbient (Vector4(1, 1, 1, 1));
            edge_material.SetDiffuse (Vector4(1, 1, 1, 1));
            edge_material.SetEmissive(Vector4(1, 1, 1, 1));
            edge_material.SetSpeculer(Vector4(1, 1, 1, 1));
            const int geo_size = mesh_pointer->GetGeometryCount();
            std::vector<LPMaterial> def_material(geo_size);
            for (int i = 0; i < geo_size; i++) {
                def_material[i] = mesh_pointer->GetGeometry(i)->GetMaterial();
            }
            for (int i = 0; i < geo_size; i++) {
                mesh_pointer->GetGeometry(i)->SetMaterial(&edge_material);
            }
            // �����\��
            g_pGraphics->SetDepthEnable(FALSE);
            mesh_pointer->Render(object_matrix_edge, Vector4(0, 1, 0, 1));
            g_pGraphics->SetDepthEnable(TRUE);
            // �}�e���A���̐ݒ��߂�
            for (int i = 0; i < geo_size; i++) {
                mesh_pointer->GetGeometry(i)->SetMaterial(def_material[i]);
            }
        }
        mesh_pointer->Render(object_matrix);
    }

    int* edit_mode = ParameterMap<int>::GetInstance().Get("edit_mode");
    if ((*edit_mode) & EditMode::InstObject) {
        CMatrix44 matrix_world_object;
        Vector3 mouse_pos = MouseUtilities::GetWorldPos();
        mouse_pos.y = 0.0f;
        matrix_world_object.SetTranslation(mouse_pos);
        MeshData* meshdata_pointer = mesh_window.GetSelectMeshData();
        if (meshdata_pointer && meshdata_pointer->second.lock()) {
            meshdata_pointer->second.lock()->Render(matrix_world_object, Vector4(1, 1, 1, 0.5f));
        }
    }

    g_pGraphics->SetDepthEnable(FALSE);

	if (editor_parameter.IsShowMeshWindow()) {
		mesh_window.Show();
	}

    CMofImGui::RenderSetup();
    CMofImGui::RenderGui();

    //�`��̏I��
    g_pGraphics->RenderEnd();
    return TRUE;
}
/*************************************************************************//*!
        @brief            �A�v���P�[�V�����̉��
        @param            None

        @return            TRUE        ����<br>
                        ����ȊO    ���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
    std::string* resource_path = parameter_map_string.Get("resource_path");
    CUtilities::SetCurrentDirectory(resource_path->c_str());
    CMofImGui::Cleanup();

    gamepad.Release();
    
	MeshAsset::Release();
	TextureAsset::Release();

    return TRUE;
}