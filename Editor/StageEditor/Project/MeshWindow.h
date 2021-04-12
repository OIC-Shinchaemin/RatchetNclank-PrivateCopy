#pragma once
#include "MofImGui/MofImGui.h"
#include "Define.h"
#include "Singleton.h"

// ********************************************************************************
/// <summary>
/// メッシュデータ保持ウィンドウクラス
/// </summary>
// ********************************************************************************
class MeshWindow : public Singleton<MeshWindow> {
private:

    //! メッシュリスト
    std::vector<MeshData> _mesh_list;
    //! 選択中の番号      
    int                   _mesh_list_current { 0 };
    //! 選択中のアイテム      
    MeshData*             _mesh_select_item  { nullptr };

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    void ShowMeshList(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    void ShowMeshInfo(void);

public:

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/21</created>
    /// <changed>いのうえ,2021/03/21</changed>
    // ********************************************************************************
    MeshWindow(void);
    
    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/21</created>
    /// <changed>いのうえ,2021/03/21</changed>
    // ********************************************************************************
    ~MeshWindow(void);

    // ********************************************************************************
    /// <summary>
    /// ウィンドウの表示
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Show(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/19</created>
    /// <changed>いのうえ,2021/03/19</changed>
    // ********************************************************************************
    MeshData* GetSelectMeshData(void);
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetSelectNo(void) const;
    void SetSelectNo(int no);

    /// <summary>
    /// 
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const MeshList& GetMeshList(void) const;
    MeshList& GetMeshList(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    void AddMeshList(const MeshData* data);
    void MeshLoadDialog(void);

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    void MeshRelease(void);
};

