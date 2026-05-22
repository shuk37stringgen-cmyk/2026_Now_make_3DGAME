#pragma once
#include "..//Common.h"

/*
　星の種類は三種類
 スイング一周につき＋１

 大　バフ多め　

 中

 小




*/



class Planet {
public:
    Shared<dxe::Mesh> mesh;
    tnl::Vector3 pos;
    float radius;
    float gravity_range;
   

    // コンストラク
    Planet(tnl::Vector3 p, float r);

    // 描画
    void render(Shared<dxe::Camera> cam);
};