#pragma once
#include <map>
#include <memory>
#include <vector>
#include <list>
#include "MyLib.h"
#include "Vec3.h"

class TrapBase;
class Input;

class TrapManager
{
public:
	TrapManager(int trapNum,std::list<MyLib::Vec3>& trapPoss);
	~TrapManager();

	void Init();
	void Update(std::shared_ptr<Input>& input,int slotNum,MyLib::Vec3 playerPos, MyLib::Vec3 playerVec,int* trapPoint,int nowPhase, std::shared_ptr<MyLib::Physics> physics);
	void Draw();

	void PreviewDraw();

private:
	//モデルハンドルを格納する
	std::vector<int> m_modelHandles;

	//座標と罠を格納する
	std::list<std::shared_ptr<TrapBase>> m_traps;

	//罠設置可能座標を格納する
	std::list<MyLib::Vec3> m_trapPoss;

	//設置予定座標を格納
	MyLib::Vec3 m_previewPos;

	int m_slotNum;
};

