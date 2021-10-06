#ifndef RATCHET_MESSAGE_OBSERVATION_MANAGER_H
#define RATCHET_MESSAGE_OBSERVATION_MANAGER_H


#include <tuple>
#include <memory>

#include "Base/Core/Trait.h"

#include "MessageObservation.h"
#include "Game/GameSystem/Text/TextSystemDefine.h"


namespace ratchet {
class ObservationManager {
private:
public:
    /// <summary>
    /// ƒVƒ“ƒOƒ‹ƒgƒ“
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static ObservationManager& Singleton(void) {
        static ObservationManager instance;
        return instance;
    }
    void Clear(void) {
    }
};
}
#endif // !RATCHET_MESSAGE_OBSERVATION_MANAGER_H