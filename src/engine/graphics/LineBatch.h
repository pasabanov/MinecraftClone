#ifndef MINECRAFT_LINEBATCH_H
#define MINECRAFT_LINEBATCH_H

#include <headers/includes.h>

#include <engine/graphics/Mesh.h>


class LineBatch {

    inline static const std::vector<int> VERTEX_ATTRS = { 3, 4, 0 };
    inline static const uint VERTEX_SIZE = std::accumulate(VERTEX_ATTRS.begin(), VERTEX_ATTRS.end(), 0);

    Mesh mMesh;
    std::vector<float> mBuffer;

public:

    void line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color = { 1, 1, 1, 1 });

    void box(glm::vec3 pos, const glm::vec3& size, const glm::vec4& color = { 1, 1, 1, 1 });

    void clearBuffer();

    void render();

    void draw() const;
};

#endif //MINECRAFT_LINEBATCH_H