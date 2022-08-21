#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

namespace al {

void initLayoutActor(al::LayoutActor* layoutActor, const LayoutInitInfo& info, const char* archiveName, const char*);

} // namespace al