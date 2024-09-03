#pragma once
#include "SceneBase.h"
class SceneOption : public SceneBase
{
public:
	SceneOption(SceneManager& mgr);
	virtual ~SceneOption();

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

	int m_fontHandle;
	int m_bgHandle;
};

