#pragma once
#include "SceneBase.h"
class SceneRanking :  public SceneBase
{
public:
	SceneRanking(SceneManager& mgr);
	virtual ~SceneRanking();

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
};

