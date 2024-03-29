//
// Created by aurailus on 17/04/19.
//

#ifndef ZEUS_ATLASREF_H
#define ZEUS_ATLASREF_H


#include <vec4.hpp>
#include <string>

struct AtlasRef {
    int tileX = 0;
    int tileY = 0;
    int tileWidth = 0;
    int tileHeight = 0;

    bool base = false;

    glm::vec4 pos {};
    glm::vec4 uv {};
    std::string name = "";

    int width = 0;
    int height = 0;
};


#endif //ZEUS_ATLASREF_H
