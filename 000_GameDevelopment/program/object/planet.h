#pragma once
#include "..//Common.h"

class Planet {
public:
    Shared<dxe::Mesh> mesh;
    tnl::Vector3 pos;
    float radius;
    float gravity_range;

    // コンストラクタ（生成時に呼ばれる）
    Planet(tnl::Vector3 p, float r);

    // 描画
    void render(Shared<dxe::Camera> cam);
};