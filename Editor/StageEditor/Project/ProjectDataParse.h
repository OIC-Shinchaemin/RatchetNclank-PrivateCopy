#pragma once
#include "ActionBase.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class ProjectDataParse : public ActionBase {
public:
    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <param name="any"></param>
    /// <returns></returns>
    /// <created>いのうえ,2021/03/26</created>
    /// <changed>いのうえ,2021/03/26</changed>
    // ********************************************************************************
    virtual bool Action(std::any any) override;
};

