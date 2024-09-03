#pragma once
#include "SceneBase.h"
class SceneDebug : public SceneBase
{
public:
	SceneDebug(SceneManager& mgr);
	virtual ~SceneDebug();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="input"></param>
	void Update(std::shared_ptr<Input>& input);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:
	//遷移先
	enum class e_Destination : int
	{
		Title,
		StageSelect,
		Upgrade,
		InGame,
		Result,
		Pause,
		Option,
		Ranking
	};

	e_Destination m_destinationScene;
};

