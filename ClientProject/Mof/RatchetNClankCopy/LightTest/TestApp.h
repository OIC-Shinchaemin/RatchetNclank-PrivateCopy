#pragma once


#include "Mof.h"
#include "Light/LightManager.h"


namespace test::light {
class CGameApp : public CSingleGameApplication {
private:
    //! ƒ‰ƒCƒg
    std::shared_ptr<ratchet::light::LightManager> _light_manager;
public:
    CGameApp() {
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};
}