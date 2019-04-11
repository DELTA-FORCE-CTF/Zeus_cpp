//
// Created by aurailus on 17/12/18.
//

#include "GameScene.h"

#include "../lua/l_register_block.h"
#include "../lua/l_register_blockmodel.h"
#include "entity/WireframeEntity.h"

GameScene::GameScene(ClientState* state) :
        Scene(state),
        gameGui(state->renderer->getCamera()->getBufferDimensions()),
        debugGui(state->renderer->getCamera()->getBufferDimensions()) {

    textureAtlas = new TextureAtlas("../res/tex");
    blockAtlas = new BlockAtlas(textureAtlas);

    LuaParser p;
    p.init();

    //Register APIs here
    l_register_block(this, &p);
    l_register_blockmodel(this, &p);

    p.doFile("../res/lua/file.lua");

    //The scene requires the blockAtlas for meshing and handling inputs.
    world = new LocalWorld(blockAtlas);

    //Wireframe
    auto wireframe = new WireframeEntity({0, 0, 0}, {1, 1, 1}, 0.01);
    entities.push_back(wireframe);

    player = new Player();
    player->create(world, state->renderer->getCamera(), wireframe);

    server = new ServerConnection("127.0.0.1", 12345, entities);
    server->init();

    gui.push_back(&gameGui);
    gui.push_back(&debugGui);
}


void GameScene::update() {
    server->update(*player);

    auto window = state->renderer->getWindow();

    player->update(window->input, state->deltaTime, window->getDeltaX(), window->getDeltaY());

    if (state->renderer->resized) {
        debugGui.bufferResized(state->renderer->getCamera()->getBufferDimensions());
        gameGui.bufferResized(state->renderer->getCamera()->getBufferDimensions());

        state->renderer->resized = false;
    }

    while (!server->chunkPackets.empty()) {
        auto it = server->chunkPackets.begin();
        Packet* p = *it;
        server->chunkPackets.erase(it);
        world->loadChunkPacket(p);
    }

    debugGui.update(player, world, blockAtlas, state->fps, (int)world->getMeshChunks()->size(), drawCalls, server->serverSideChunkGens, server->recvPackets);
    world->update();

    if (window->input.isKeyPressed(GLFW_KEY_F1)) {
        hudVisible = !hudVisible;
        debugGui.changeVisibilityState(hudVisible ? debugVisible ? 0 : 2 : 1);
        gameGui.setVisible(hudVisible);
    }

    if (window->input.isKeyPressed(GLFW_KEY_F3)) {
        debugVisible = !debugVisible;
        debugGui.changeVisibilityState(hudVisible ? debugVisible ? 0 : 2 : 1);
    }
}

void GameScene::draw() {
    auto &renderer = *state->renderer;
    auto &camera = *renderer.getCamera();

    drawCalls = 0;

    renderer.begin();
    renderer.enableTexture(textureAtlas->getTexture());

    drawCalls = world->render(renderer);

    for (auto entity : entities) {
        entity->draw(renderer);
    }

    state->renderer->beginGUI();

    for (auto entity : gui) {
        entity->draw(renderer);
    }

    state->renderer->end();
}

void GameScene::cleanup() {
    //TODO: Clean up
}