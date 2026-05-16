#include "scene.h"
#include "object/010_object.h"
#include "object/030_obj_drawable.h"

namespace eng {

	//-----------------------------------------------------------------------------------------------------------------------
	// コンストラクタ
	Scene::Scene() {
		// カメラの生成
		camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F, dxe::Camera::eDimension::Type2D);
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// デストラクタ：すべてのオブジェクトを削除する
	Scene::~Scene() {
		deleteAllObject();
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// 生存していない（Aliveでない）オブジェクトをリストから削除する
	void Scene::deleteNotAliveObject() {
		update_objects_.remove_if([](Shared<Object>& obj) { return !obj->getAlive(); });

		draw_objects_.remove_if([](Shared<ObjDrawable>& obj) { return !obj->getAlive(); });
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// オブジェクトを更新・描画対象のリストに追加する
	void Scene::addObject(const Shared<Object>& obj) {
		update_objects_.emplace_back(obj);

		Shared<ObjDrawable> drawable = std::dynamic_pointer_cast<ObjDrawable>(obj);
		if (drawable) {
			draw_objects_.emplace_back(drawable);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// シーン内のすべてのオブジェクトを更新する
	// ・優先度順にソートしてから処理
	// ・更新が有効であれば update() を呼び出す
	// ・経過時間と経過フレームを更新
	void Scene::update() {

		// 更新優先度の高い順にソート（数値が大きいほど優先）
		update_objects_.sort([](Shared<Object>& l, Shared<Object>& r) {
			return l->getUpdatePriority() < r->getUpdatePriority();
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
		draw_objects_.sort([](Shared<eng::ObjDrawable>& l, Shared<eng::ObjDrawable>& r) {
			return l->getDrawPriority() > r->getDrawPriority();
		});

		for (auto obj : draw_objects_) {
			// 可視状態のオブジェクトのみ描画
			if (!obj->getVisible()) continue;
			obj->draw(camera_);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------
	// 登録されているすべてのオブジェクトを削除する
	// ・update_objects_ は delete を行う（メモリ解放）
	// ・draw_objects_ は clear のみ（delete はしない）
	void Scene::deleteAllObject() {
		update_objects_.clear();
		draw_objects_.clear();
	}

}