#include "planet.h"

Planet::Planet(tnl::Vector3 p, float r) : pos(p), radius(r) {
    // 星の半径の2.5倍をスイングバイ圏内に設定[cite: 1]
    gravity_range = r * GRAVITY_RANGE_FACTOR;

    // 球体のメッシュを作成
    mesh = dxe::Mesh::CreateSphereMV(radius, 64, 64);

    // テクスチャ（見た目）の設定。ファイルパスは兄貴の環境に合わせてくれ
    mesh->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));
    mesh->setPosition(pos);
}

void Planet::render(Shared<dxe::Camera> cam) {
    if (mesh) {
        mesh->render(cam);
    }
}