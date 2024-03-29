//
// Created by aurailus on 08/04/19.
//

#include "WireframeEntity.h"


WireframeEntity::WireframeEntity(glm::vec3 posA, glm::vec3 posB, float width, glm::vec3 color) {
    this->a = posA;
    this->b = posB - posA;
    this->width = width;
    this->color = color;

    buildMesh();
}

void WireframeEntity::updateMesh(glm::vec3 posA, glm::vec3 posB, float width) {
    this->a = posA;
    this->b = posB - posA;
    this->width = width;

    buildMesh();
}


void WireframeEntity::buildMesh() {
    indOffset = 0;

    vertices.clear();
    indices.clear();

    createBox(0,   0, 0,   0, b.y, 0);
    createBox(b.x, 0, 0,   0, b.y, 0);
    createBox(b.x, 0, b.z, 0, b.y, 0);
    createBox(0,   0, b.z, 0, b.y, 0);

    createBox(0, 0,   0,   b.x, 0, 0);
    createBox(0, b.y, 0,   b.x, 0, 0);
    createBox(0, b.y, b.z, b.x, 0, 0);
    createBox(0, 0,   b.z, b.x, 0, 0);

    createBox(0,   0,   0, 0, 0, b.z);
    createBox(0,   b.y, 0, 0, 0, b.z);
    createBox(b.x, b.y, 0, 0, 0, b.z);
    createBox(b.x, 0,   0, 0, 0, b.z);

    auto m = new EntityMesh();
    m->create(vertices, indices);
    setMesh(m);
}

void WireframeEntity::createBox(float x, float y, float z, float xSize, float ySize, float zSize) {
    float hw = (width/2.0f);
    float w = width;
    auto  c = color;

    std::vector<EntityVertex> myVerts {
    /*0*/ {{x - hw + a.x,             y - hw + a.y,             z - hw + a.z            }, {c, 1}, false, {0, 1, 0}},
    /*1*/ {{x - hw + a.x + xSize + w, y - hw + a.y,             z - hw + a.z            }, {c, 1}, false, {0, 1, 0}},
    /*2*/ {{x - hw + a.x + xSize + w, y - hw + a.y,             z - hw + a.z + zSize + w}, {c, 1}, false, {0, 1, 0}},
    /*3*/ {{x - hw + a.x,             y - hw + a.y,             z - hw + a.z + zSize + w}, {c, 1}, false, {0, 1, 0}},

    /*4*/ {{x - hw + a.x,             y - hw + a.y + ySize + w, z - hw + a.z            }, {c, 1}, false, {0, 1, 0}},
    /*5*/ {{x - hw + a.x + xSize + w, y - hw + a.y + ySize + w, z - hw + a.z            }, {c, 1}, false, {0, 1, 0}},
    /*6*/ {{x - hw + a.x + xSize + w, y - hw + a.y + ySize + w, z - hw + a.z + zSize + w}, {c, 1}, false, {0, 1, 0}},
    /*7*/ {{x - hw + a.x,             y - hw + a.y + ySize + w, z - hw + a.z + zSize + w}, {c, 1}, false, {0, 1, 0}},
    };

    std::vector<unsigned int> myInds {
        0, 1, 2, 2, 3, 0,
        4, 7, 6, 6, 5, 4,
        0, 4, 5, 5, 1, 0,
        3, 2, 6, 6, 7, 3,
        0, 3, 7, 7, 4, 0,
        1, 5, 6, 6, 2, 1,
    };

    vertices.insert(vertices.end(), myVerts.begin(), myVerts.end());
    for (auto i : myInds) indices.push_back(i + indOffset);

    indOffset += 8;
}