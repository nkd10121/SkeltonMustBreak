﻿#include "SpikeTrap.h"
#include "SoundManager.h"

//外部ファイルで
//1.攻撃力
//2.索敵範囲
//3.攻撃範囲
//4.クールタイム
//5.設置コスト
//		を変更できるようにしたい

SpikeTrap::SpikeTrap(std::shared_ptr<MyLib::Physics> physics):
	TrapBase(GameObjectTag::SpikeTrap),
	m_frameModelPos(),
	m_spikeModelPos(),
	m_isAttack(false),
	m_isInitCollision(false),
	m_attackCount(0)
{
	m_pPhysics = physics;

	//当たり判定の設定
	auto collider = Collidable::AddCollider(MyLib::ColliderData::Kind::Sphere, true);
	auto sphereCol = dynamic_cast<MyLib::ColliderDataSphere*>(collider.get());
	sphereCol->m_radius = 8.0f;

	m_pSearch = std::make_shared<SearchObject>(5.5f);

	//攻撃力の設定
	m_attack = 30;
}

SpikeTrap::~SpikeTrap()
{
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_spikeModelHandle);
}

void SpikeTrap::Init(int handle, int subHandle)
{
	m_frameModelPos = m_pos;
	m_spikeModelPos = m_pos;

	m_modelHandle = handle;
	m_spikeModelHandle = subHandle;

	m_frameModelPos.y -= 0.5f;

	MV1SetPosition(m_modelHandle, m_frameModelPos.ConvertToVECTOR());
	MV1SetScale(m_modelHandle, VECTOR(0.08f, 0.08f, 0.08f));

	m_spikeModelPos.y -= 4.5f;

	MV1SetPosition(m_spikeModelHandle, m_spikeModelPos.ConvertToVECTOR());
	MV1SetScale(m_spikeModelHandle, VECTOR(0.08f, 0.08f, 0.08f));

	m_pSearch->Init(m_pPhysics,m_pos);
}

void SpikeTrap::Update()
{
	if (!m_isAttack)
	{
		if (m_pSearch->GetIsTrigger())
		{

			m_isAttack = true;

			Collidable::Init(m_pPhysics);
			rigidbody.Init();
			rigidbody.SetPos(m_pos);
		}
	}


	if (m_isAttack)
	{
		if (m_attackCount == 1)
		{
			SoundManager::GetInstance().PlaySE("spike");
		}

		if (m_attackCount == 0 && m_spikeModelPos.y < 4.0f)
		{
			m_spikeModelPos.y += 0.8f;
		}
		else
		{
			m_attackCount++;
		}

		MV1SetPosition(m_spikeModelHandle, m_spikeModelPos.ConvertToVECTOR());

		if (m_attackCount == 30)
		{
			if (!m_isInitCollision)
			{
				Finalize(m_pPhysics);
				m_isInitCollision = true;
			}
		}

		if (m_attackCount > 30)
		{
			m_spikeModelPos.y -= 0.8f;

			if (m_spikeModelPos.y < -4.5f)
			{
				m_spikeModelPos.y = -4.5f;
			}
		}

		if (m_attackCount >= 7*60)
		{
			//すべてを初期化する
			m_spikeModelPos = m_pos;
			m_spikeModelPos.y -= 4.5f;
			MV1SetPosition(m_spikeModelHandle, m_spikeModelPos.ConvertToVECTOR());
			m_isAttack = false;
			m_isInitCollision = false;

			//当たり判定をリセット
			m_pSearch->IsTriggerReset();

			m_attackCount = 0;
		}
	}
}

void SpikeTrap::Draw()
{
	MV1DrawModel(m_modelHandle);
	MV1DrawModel(m_spikeModelHandle);
}
