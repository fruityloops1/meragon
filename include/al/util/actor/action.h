#pragma once

#include "al/actor/liveactor.h"

namespace al {

/**
 * @brief Starts an action found in the actor's archive
 *
 * @param actor The actor to start the Action on
 * @param actionName Name of the action
 * @param unk1 Unknown. Can be nullptr
 * @param unk2 Unknown. Can be nullptr
 * An action can be a Skeletal Animation, Visibility Animation, Texture Animation, etc.
 */
void startAction(LiveActor* actor, const char* actionName, void* unk1, void* unk2);

} // namespace al