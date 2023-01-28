#pragma once

#include <stddef.h>

namespace al {

class LiveActor;
class ExecuteRequestKeeper {
public:
    ExecuteRequestKeeper(size_t);

    void request(LiveActor*, int);
};

} // namespace al
