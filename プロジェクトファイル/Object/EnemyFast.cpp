﻿#include "EnemyFast.h"
#include "CsvLoad.h"
#include "DxLib.h"

#include "HitBox.h"
#include "SearchObject.h"

#include "SoundManager.h"
#include "ModelManager.h"

namespace
{
	//キャラクター名
	constexpr const char* kCharacterName = "FastSkelton";
	//モデルパス
	constexpr const char* kModelPath = "data/model/Skeleton_Minion.mv1";
	//押し出し当たり判定の半径
	constexpr float kCollisionRadius = 1.4f;
	//モデルの元のサイズ
	constexpr float kModelDefaultSize = 2.166f;
	//モデルサイズの拡大率
	constexpr float kModelSizeScale = 3.2f;
	constexpr float kModelOffsetY = 0.3f;
	//武器のモデルサイズ
	constexpr float kWeaponModelSize = 0.01f;
	//当たり判定の半径
	constexpr float kHitBoxRadius = 3.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
EnemyFast::EnemyFast():
	EnemyBase(Collidable::Priority::Middle)
{
	//当たり判定の設定
	InitCollision(kCollisionRadius);
	//モデルの読み込み
	LoadModel(kModelPath);
	//アニメーションやステータスを取得
	LoadData(kCharacterName);
	//この敵はプレイヤーを追跡しない
	m_isChase = false;
	//索敵範囲の設定
	m_searchRange = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyFast::~EnemyFast()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="physics">物理クラスのポインタ</param>
/// <param name="route">移動ルート</param>
void EnemyFast::Init(std::shared_ptr<MyLib::Physics> physics, std::vector<MyLib::Vec3> route)
{
	//代入
	m_pPhysics = physics;
	m_route = route;

	//ルートのy座標を調整
	AdjustmentRoute(kModelOffsetY, kModelSizeScale);


	//最初の目的地を設定する
	m_routeIdx = 1;
	m_destinationPos = m_route[m_routeIdx];

	//存在している状態にする
	m_isExist = true;

	Collidable::Init(m_pPhysics);

	//物理クラスの初期化
	InitRigidbody();

	//中心座標の設定
	CalculationCenterPos(kModelDefaultSize, kModelSizeScale);

	//当たり判定の座標を設定
	m_collisionPos = rigidbody.GetPos();

	//モデルの座標を設定
	SetModelPos(kModelOffsetY * kModelSizeScale);
	MV1SetPosition(m_modelHandle, m_modelPos.ConvertToVECTOR());

	//ダメージ判定をする当たり判定を作成
	InitHitBox(kHitBoxRadius);

	//モデルのサイズ設定
	MV1SetScale(m_modelHandle, VGet(kModelSizeScale, kModelSizeScale, kModelSizeScale));

	//アニメーションを設定
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, m_animIdx["Move"]);
	m_nowAnimIdx = m_animIdx["Move"];

	//通常状態に設定しておく
	m_updateFunc = &EnemyFast::WalkUpdate;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPos">プレイヤー座標</param>
/// <param name="isChase">プレイヤーが追跡できる状態かどうか</param>
void EnemyFast::Update(MyLib::Vec3 playerPos, bool isChase)
{
	//存在していない状態なら何もさせない
	if (!m_isExist)return;

	//アニメーションの更新
	m_isAnimationFinish = UpdateAnim(m_currentAnimNo);

	//状態の更新
	(this->*m_updateFunc)(playerPos, isChase);

	//中心座標の設定(ミニマップに表示するために必要)
	CalculationCenterPos(kModelDefaultSize, kModelSizeScale);

	//判定の更新
	MyLib::Vec3 centerPos = rigidbody.GetPos();
	centerPos.y += kModelDefaultSize / 2 * kModelSizeScale * 0.8f;
	m_pHitbox->Update(centerPos);

	//敵(プレイヤー)の攻撃にあたった時
	if (m_pHitbox->GetIsHit())
	{
		//HPを減らす処理を行う
		OnDamage();
	}

	//HPが0以下になったら死亡する
	if (m_status.hp <= 0)
	{
		//死亡処理を行う
		Death();
	}

	//アニメーションブレンドの更新をする
	UpdateAnimationBlend();
}

/// <summary>
/// 描画
/// </summary>
void EnemyFast::Draw()
{
	//存在していない状態なら何もさせない
	if (!m_isExist)return;

	//当たり判定座標を取得してモデルの描画座標を設定する
	SetDrawModelPos(kModelOffsetY * kModelSizeScale);
	//モデルの描画
	MV1DrawModel(m_modelHandle);
	//MV1DrawModel(m_weponHandle);
}