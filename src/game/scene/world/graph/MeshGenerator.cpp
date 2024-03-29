//
// Created by aurailus on 01/12/18.
//

#include <thread>
#include "MeshGenerator.h"

MeshGenerator::MeshGenerator(std::vector<ChunkVertex> &vertices, std::vector<unsigned int> &indices,
                             LocalBlockAtlas& atlas, const BlockChunk& chunk, const std::vector<bool>& adj,
                             std::array<NoiseSample, 3>& blockOffsets) :
    vertices(vertices),
    indices(indices),
    atlas(atlas),
    chunk(chunk) {

    vertices.reserve(10000);
    indices.reserve(10000);

    Timer t("ChunkMesh Generation");

    glm::vec3 off;
    glm::vec3 vis;
    glm::vec3 check;

    auto end = (int)pow(TransPos::CHUNK_SIZE, 3);
    for (int i = 0; i < end; i++) {
        if (getDef(i).getModel().visible) {
            VecUtils::indAssignVec(i, off);

            LocalBlockModel& model = getDef(i).getModel();

            vis = off;

            for (auto& mod : model.meshMods) {
                switch (mod.first) {
                    default: break;

                    case MeshMod::OFFSET_X: {
                        vis.x += blockOffsets[0].get(off) * mod.second;
                        break;
                    }
                    case MeshMod::OFFSET_Y: {
                        vis.y += blockOffsets[1].get(off) * mod.second;
                        break;
                    }
                    case MeshMod::OFFSET_Z: {
                        vis.z += blockOffsets[2].get(off) * mod.second;
                        break;
                    }
                }
            }

            if (model.visible) {

                check = off; check.x -= 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[XNEG]);
                check = off; check.x += 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[XPOS]);
                check = off; check.y -= 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[YNEG]);
                check = off; check.y += 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[YPOS]);
                check = off; check.z -= 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[ZNEG]);
                check = off; check.z += 1;
                if (!faceOcculudedAt(check, adj)) addFaces(vis, model.parts[ZPOS]);

                addFaces(vis, model.parts[NO_CULL]);
            }
        }
    }

    vertices.shrink_to_fit();
    indices.shrink_to_fit();
}

LocalBlockDef& MeshGenerator::getDef(int ind) {
    return atlas.fromIndex(chunk.getBlock(ind));
}

LocalBlockDef& MeshGenerator::getDef(const glm::vec3 &pos) {
    return atlas.fromIndex(chunk.getBlock(pos));
}

bool MeshGenerator::faceOcculudedAt(const glm::vec3 &pos, const std::vector<bool> &adj) {
    auto off = TransPos::CHUNK_SIZE*TransPos::CHUNK_SIZE; //CHUNK_SIZE ^ 2
    if (pos.x < 0 || pos.x >= TransPos::CHUNK_SIZE || pos.y < 0 || pos.y >= TransPos::CHUNK_SIZE || pos.z < 0 || pos.z >= TransPos::CHUNK_SIZE) {

        if (pos.x == -1) return adj[off + (int)pos.y * TransPos::CHUNK_SIZE + (int)pos.z];
        if (pos.x == TransPos::CHUNK_SIZE) return adj[(int)pos.y * TransPos::CHUNK_SIZE + (int)pos.z];

        if (pos.y == -1) return adj[off*3 + (int)pos.x * TransPos::CHUNK_SIZE + (int)pos.z];
        if (pos.y == TransPos::CHUNK_SIZE) return adj[off*2 + (int)pos.x * TransPos::CHUNK_SIZE + (int)pos.z];

        if (pos.z == -1) return adj[off*5 + (int)pos.y * TransPos::CHUNK_SIZE + (int)pos.x];
        if (pos.z == TransPos::CHUNK_SIZE) return adj[off*4 + (int)pos.y * TransPos::CHUNK_SIZE + (int)pos.x];

        return false;
    }
    return getDef(pos).isCulling();
}

void MeshGenerator::addFaces(const glm::vec3 &offset, const vector<LocalMeshPart> &meshParts) {
    for (const LocalMeshPart& mp : meshParts) {

        glm::vec3 modData = {};

        switch (mp.shaderMod) {
            default: break;

            case ShaderMod::ROTATE_X:
            case ShaderMod::ROTATE_Y:
            case ShaderMod::ROTATE_Z:
            case ShaderMod::SWAY_ATTACHED:
            case ShaderMod::SWAY_FULL_BLOCK: {
                modData = {Util::packFloat((offset - 8.f) / 8), mp.modValue, 0};
                break;
            }
        }

        for (const MeshVertex &vertex : mp.vertices) {
            vertices.push_back({
                   vertex.pos + offset,
                   vertex.tex,
                   Util::packFloat(vertex.nml),
                   static_cast<float>(mp.shaderMod),
                   modData
            });
        }

        for (unsigned int index : mp.indices) {
            indices.push_back(indOffset + index);
        }

        indOffset += mp.vertices.size();
    }
}