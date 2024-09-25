#pragma once
#include "SceneBase.h"
class ScenePause : public SceneBase
{
public:
	ScenePause(SceneManager& mgr);
	virtual ~ScenePause();

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
		InGame,
		Option,
		Title,
	};

	e_Destination m_destinationScene;

	std::vector<int> m_handles;
	std::vector<std::pair<int, int>> m_uiPos;

	int m_textHandle;
	int m_fontHandle;

	float m_angle;
	int m_cursorOffsetX;
};

