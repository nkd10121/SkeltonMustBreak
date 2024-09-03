#pragma once
#include "SceneBase.h"

#include <vector>
#include <map>

class TitlePlayer;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect(SceneManager& mgr);
	virtual ~SceneStageSelect();

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
		Stage1,
		Stage2,
		Stage3,
		Upgrade,
	};

	e_Destination m_destinationScene;

	std::vector<std::pair<int, int>> m_uiPos;

	std::vector<int> m_handles;

	float m_angle;
	int m_cursorOffsetX;

	int m_fontHandle;
	int m_textHandle;

	int m_lightHandle;
	std::shared_ptr<TitlePlayer> m_player;
};

