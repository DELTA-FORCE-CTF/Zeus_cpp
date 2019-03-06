//
// Created by aurailus on 27/12/18.
//

#ifndef ZEUS_DEBUGGUI_H
#define ZEUS_DEBUGGUI_H

#include "../../engine/graphics/Histogram.h"
#include "../../engine/graphics/HudText.h"
#include "../../engine/Window.h"
#include "../../engine/Ray.h"
#include "../../engine/graphics/RectEntity.h"

#include <sstream>

class DebugGui {
public:
    DebugGui(glm::vec2 bufferSize);

    void bufferResized(glm::vec2 bufferSize);

    void pushGuiObjects(std::vector<Entity*> &list);
    void update(Player* player, LocalWorld* world, Window* window, BlockAtlas* atlas, double fps, int chunks, int drawCalls);
    void positionElements(glm::vec2 bufferSize);

    ~DebugGui();

private:
    int videoMemAvail, videoMemTotal;

    Texture *fontTexture;
    Texture *colorHistTexture, *whiteHistTexture, *transWhiteHistTexture;

    HudText    *dataText, *crosshairText;
    RectEntity *dataBG,   *crosshairBG;

    HudText    *chunkUpdateText,      *meshUpdateText,      *fpsText,      *drawCallsText,                       *videoMemoryText;
    Histogram  *chunkUpdateHistogram, *meshUpdateHistogram, *fpsHistogram, *drawCallsHistogram, *chunkHistogram, *videoMemoryHistogram;
    RectEntity *chunkUpdateBG,        *meshUpdateBG,        *fpsBG,        *drawCallsBG,                         *videoMemoryBG;
};


#endif //ZEUS_DEBUGGUI_H
