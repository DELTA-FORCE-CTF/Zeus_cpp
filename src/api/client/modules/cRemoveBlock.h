//
// Created by aurailus on 28/06/19.
//

#ifndef ZEUS_CREMOVEBLOCK_H
#define ZEUS_CREMOVEBLOCK_H

#include "../../../def/LocalDefs.h"
#include "../../../game/scene/world/LocalWorld.h"
#include <sol.hpp>

namespace ClientApi {
    void remove_block(sol::table &zeus, LocalDefs& defs, LocalWorld& world) {
        int air = defs.blocks().fromIdentifier("builtin:air").getIndex();

        zeus.set_function("remove_block", [&](sol::table pos) {
            if (!pos["x"] || !pos["y"] || !pos["z"]) {
                std::cout << Log::err << "remove_block vector is ill formed." << Log::endl;
                return;
            }
            world.setBlock({pos["x"], pos["y"], pos["z"]}, air);
        });
    }
}

#endif //ZEUS_CREMOVEBLOCK_H
