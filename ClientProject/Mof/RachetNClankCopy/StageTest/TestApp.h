#pragma once


#include "Mof.h"
#include "Stage/Stage.h"


namespace test {
class CGameApp : public CSingleGameApplication {
private:
    //! �X�e�[�W
    Stage _stage;
    //! �J����
    Mof::CCamera _camera;
public:
    CGameApp() :
        _stage() {
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};
}