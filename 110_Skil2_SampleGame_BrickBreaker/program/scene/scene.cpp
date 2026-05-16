#include "scene.h"
#include "../common/object/object.h"

//-----------------------------------------------------------------------------------------------------------------------
// デストラクタ：すべてのオブジェクトを削除する
Scene::~Scene() {
	deleteAllObject();
}

//-----------------------------------------------------------------------------------------------------------------------
// 生存していない（Aliveでない）オブジェクトをリストから削除する
// update_objects_から削除する際は delete も行う
void Scene::deleteNotAliveObject() {

	// 描画対象リストから Aliveでないオブジェクトのポインタを削除（deleteはしない）
	std::list<Object*>::iterator it = draw_objects_.begin();
	while (it != draw_objects_.end()) {
		if (!(*it)->getAlive()) {
			it = draw_objects_.erase(it);  // eraseが新しいイテレータを返す
			continue;
		}
		it++;
	}

	// 更新対象リストから Aliveでないオブジェクトを delete してから削除
	it = update_objects_.begin();
	while (it != update_objects_.end()) {
		if (!(*it)->getAlive()) {
			delete (*it);                   // メモリ解放
			it = update_objects_.erase(it); // eraseが新しいイテレータを返す
			continue;
		}
		it++;
	}
}

//-----------------------------------------------------------------------------------------------------------------------
// オブジェクトを更新・描画対象の両方のリストに追加する
void Scene::addObject(Object* obj) {
	update_objects_.emplace_back(obj);
	draw_objects_.emplace_back(obj);
}

//-----------------------------------------------------------------------------------------------------------------------
// シーン内のすべてのオブジェクトを更新する
// ・優先度順にソートしてから処理
// ・更新が有効であれば update() を呼び出す
// ・経過時間と経過フレームを更新
void Scene::update() {

	// 更新優先度の高い順にソート（数値が大きいほど優先）
	update_objects_.sort([](Object* l, Object* r) {
		return l->getUpdatePriority() > r->getUpdatePriority();
		});

	for (auto obj : update_objects_) {
		// 1フレーム以上経過しているオブジェクトに対して経過時間を加算
		if (obj->getElapsedFrame() > 0) {
			obj->addElapsedTime(dxe::GetDeltaTime());
		}
		// 更新が有効な場合のみ update() を呼び出す
		if (obj->getEnableUpdate()) {
			obj->update();
		}
		// フレームカウントを進める
		obj->updateElapsedFrame();
	}
}

//-----------------------------------------------------------------------------------------------------------------------
// シーン内のすべてのオブジェクトを描画する
// ・描画優先度順にソートしてから描画
void Scene::draw() {

	// 描画優先度の高い順にソート（数値が大きいほど前に描画される）
	draw_objects_.sort([](Object* l, Object* r) {
		return l->getDrawPriority() > r->getDrawPriority();
		});

	for (auto obj : draw_objects_) {
		// 可視状態のオブジェクトのみ描画
		if (!obj->getVisible()) continue;
		obj->draw();
	}
}

//-----------------------------------------------------------------------------------------------------------------------
// 登録されているすべてのオブジェクトを削除する
// ・update_objects_ は delete を行う（メモリ解放）
// ・draw_objects_ は clear のみ（delete はしない）
void Scene::deleteAllObject() {
	for (auto obj : update_objects_) delete obj;
	update_objects_.clear();
	draw_objects_.clear();
}