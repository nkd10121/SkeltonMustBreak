#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class TitlePlayer;

class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& mgr);
	virtual~SceneTitle();

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
		StageSelect,
		Option,
		Quit,
		Ranking,
	};

	std::vector<int> m_handles;

	int m_lightHandle;

	float m_angle;
	int m_cursorOffsetX;
	e_Destination m_destinationScene;

	std::shared_ptr<TitlePlayer> m_player;
};

