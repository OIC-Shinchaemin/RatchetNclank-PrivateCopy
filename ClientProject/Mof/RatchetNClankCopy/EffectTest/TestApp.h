#pragma once


#include "Mof.h"
#include "Effect/EffectContainer.h"
#include "../RatchetApplication/ResourceManager.h"


namespace test::effect {
class CGameApp : public CSingleGameApplication {
private:
    //! �J����
    Mof::CCamera _camera;
    //! ���\�[�X
    std::shared_ptr<ratchet::ResourceMgr> _resource_manager;
    //! �J����
    ratchet::effect::EffectContainer _effect_container;
public:
    CGameApp() :
        _camera(),
        _resource_manager(),
        _effect_container(){
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};
}