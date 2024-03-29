//
// Created by aurailus on 08/01/19.
//

#include "MenuScene.h"

MenuScene::MenuScene(ClientState& state) : Scene(state) {
    fontTexture = new Texture((char*)"../res/tex/gui/font.png");

    auto alphaText = new TextEntity(fontTexture);
    alphaText->set("Zeus Alpha 0.01");
    alphaText->setScale(3);
    alphaText->setPos(glm::vec3(8, 4, 0));
    entities.push_back(alphaText);

    auto titleText = new TextEntity(fontTexture);
    titleText->set("Zeus");
    titleText->setScale(12);
    titleText->setPos(glm::vec3(490, 120, 0));
    entities.push_back(titleText);

    auto mainMenuText = new TextEntity(fontTexture);
    mainMenuText->set("MAIN MENU");
    mainMenuText->setScale(4);
    mainMenuText->setPos(glm::vec3(530, 230, 0));
    entities.push_back(mainMenuText);
}

void MenuScene::update() {
    //Nothing
}

void MenuScene::draw() {
    state.renderer.beginChunkDeferredCalls();
    state.renderer.endDeferredCalls();
    state.renderer.beginGUIDrawCalls();

    for (auto &element : entities) {
        element->draw(state.renderer);
    }

    state.renderer.swapBuffers();
}

void MenuScene::cleanup() {
    fontTexture->clear();
    delete fontTexture;
}