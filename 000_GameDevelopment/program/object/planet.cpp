#include "planet.h"

Planet::Planet(tnl::Vector3 p, float r) : pos(p), radius(r) {
  
    //スイングバイ領域を作る
    gravity_range = r * GRAVITY_RANGE_FACTOR;

   
   // 1. メッシュを読み込む
    mesh = dxe::Mesh::CreateFromFileMV("resource/graphics/example/planet.mv1", 10.0f);

   
    mesh->setPosition(pos);

    mesh->setMtrlAmibent(tnl::Vector3(1.0f, 1.0f, 1.0f));
    
}

void Planet::render(Shared<dxe::Camera> cam) {
    if (mesh) {
        mesh->render(cam);
    }
}