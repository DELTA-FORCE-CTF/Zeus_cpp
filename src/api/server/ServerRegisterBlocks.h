//
// Created by aurailus on 29/06/19.
//

#ifndef ZEUS_SERVERREGISTERBLOCKS_H
#define ZEUS_SERVERREGISTERBLOCKS_H


#include <sol.hpp>
#include "../../def/ServerDefs.h"

class ServerRegisterBlocks {
public:
    ServerRegisterBlocks(sol::table& zeus, ServerDefs& defs);
};


#endif //ZEUS_SERVERREGISTERBLOCKS_H
