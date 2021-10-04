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
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static ObservationManager& Singleton(void) {
        static ObservationManager instance;
        return instance;
    }

    //auto* GetTextSystemClosedMessageObservation(void) {
        //return _text_system_closed;
    //}


    void Clear(void) {
    }
};
}
#endif // !RATCHET_MESSAGE_OBSERVATION_MANAGER_H