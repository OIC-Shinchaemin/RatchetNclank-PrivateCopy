#pragma once
#include "ActionBase.h"
#include "Define.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class SaveProject : public ActionBase {
public:
    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <param name="any"></param>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/21</created>
    /// <changed>いのうえ,2021/03/21</changed>
    // ********************************************************************************
    virtual bool Action(std::any any) override;

};

