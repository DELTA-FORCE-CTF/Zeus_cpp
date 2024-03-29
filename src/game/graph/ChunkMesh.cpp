//
// Created by aurailus on 25/11/18.
//

#include "ChunkMesh.h"

ChunkMesh::ChunkMesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indCount = 0;
}

void ChunkMesh::create(const std::vector<ChunkVertex>& vertices, const std::vector<unsigned int>& indices) {
    this->indCount = (int)indices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &IBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ChunkVertex), &vertices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_OFFSET_CHUNK(position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_OFFSET_CHUNK(texCoords));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, STRIDE_OFFSET_CHUNK(normal));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, STRIDE_OFFSET_CHUNK(shaderMod));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, STRIDE_OFFSET_CHUNK(modValues));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ChunkMesh::draw() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
}

void ChunkMesh::cleanup() {
    if (IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indCount = 0;
}

ChunkMesh::~ChunkMesh() {
    cleanup();
}