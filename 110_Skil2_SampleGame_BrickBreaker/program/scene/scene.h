#pragma once
#include <dxe.h>

class Object;

/// シーンの基底クラス。ゲーム中の各シーン（例：タイトル、プレイ、リザルトなど）はこのクラスを継承して作成する。
class Scene {
public:
	Scene() = default;
	virtual ~Scene();

	/// 遅延初期化処理。シーン遷移直後のタイミングで初期化を行いたい場合に使う。
	virtual void lazyInitialize() = 0;

	/// 更新処理。登録されたすべてのオブジェクトに対して update を呼び出す。
	virtual void update();

	/// 描画処理。登録されたすべてのオブジェクトに対して draw を呼び出す。
	virtual void draw();

	/// オブジェクトをこのシーンに登録する（更新・描画対象に追加）。
	void addObject(Object* obj);

	/// 生存していない（alive でない）オブジェクトを update / draw リストから削除。
	/// updateリスト内のオブジェクトは delete される。
	void deleteNotAliveObject();

private:
	/// 登録されているすべてのオブジェクトを削除。
	void deleteAllObject();

	/// 更新対象のオブジェクト群（優先度付きでソート・削除される）
	std::list<Object*> update_objects_;

	/// 描画対象のオブジェクト群（優先度付きでソート・削除される）
	std::list<Object*> draw_objects_;
};