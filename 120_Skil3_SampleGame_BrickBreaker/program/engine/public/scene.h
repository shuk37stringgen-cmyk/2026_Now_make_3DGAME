#pragma once
#include <dxe.h>

namespace eng {

	class Object;
	class ObjDrawable;

	/// シーンの基底クラス。ゲーム中の各シーン（例：タイトル、プレイ、リザルトなど）はこのクラスを継承して作成する。
	class Scene : public std::enable_shared_from_this<Scene> {
	public:
		Scene();
		virtual ~Scene();

		/// 遅延初期化処理。シーン遷移直後のタイミングで初期化を行いたい場合に使う。
		virtual void lazyInitialize() = 0;

		/// 更新処理。登録されたすべてのオブジェクトに対して update を呼び出す。
		virtual void update();

		/// 描画処理。登録されたすべてのオブジェクトに対して draw を呼び出す。
		virtual void draw();

		/// オブジェクトをこのシーンに登録する（更新・描画対象に追加）。
		void addObject(const Shared<Object>& obj);

		/// 生存していない（alive でない）オブジェクトを update / draw リストから削除。
		void deleteNotAliveObject();

	protected:
		Shared<dxe::Camera> camera_;

	private :
		/// 登録されているすべてのオブジェクトを削除。
		void deleteAllObject();

		/// 更新対象のオブジェクト群（優先度付きでソートされる）
		std::list<Shared<Object>> update_objects_;

		/// 描画対象のオブジェクト群（優先度付きでソートされる）
		std::list<Shared<ObjDrawable>> draw_objects_;
	};

}