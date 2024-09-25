#include "MyLib.h"
#include <cassert> 
#include "DxLib.h"
#include "MyLib.h"

MyLib::Collidable::Collidable(Priority priority, GameObjectTag tag):
	priority(priority),
	tag(tag)
{
}

MyLib::Collidable::~Collidable()
{

}

void MyLib::Collidable::Init(std::shared_ptr<MyLib::Physics> physics)
{
	physics->Entry(shared_from_this());	// 物理情報に自身を登録
}

void MyLib::Collidable::Finalize(std::shared_ptr<MyLib::Physics> physics)
{
	physics->Exit(shared_from_this());	// 物理情報登録解除
}

void MyLib::Collidable::AddThroughTag(GameObjectTag tag)
{
	bool found = (std::find(throughTags.begin(), throughTags.end(), tag) != throughTags.end());
	if (found)
	{
		assert(0 && "指定タグは既に追加されています");
	}
	else
	{
		throughTags.emplace_back(tag);
	}
}

void MyLib::Collidable::RemoveThroughTag(GameObjectTag tag)
{
	bool found = (std::find(throughTags.begin(), throughTags.end(), tag) != throughTags.end());
	if (!found)
	{
		assert(0 && "指定タグは存在しません");
	}
	else
	{
		throughTags.remove(tag);
	}
}

bool MyLib::Collidable::IsThroughTarget(const std::shared_ptr<Collidable> target) const
{
	bool found = (std::find(throughTags.begin(), throughTags.end(), target->GetTag()) != throughTags.end());
	return found;
}

//MyLib::ColliderData* MyLib::Collidable::CreateColliderData(ColliderData::Kind kind, bool isTrigger)
//{
//	if (m_colliderData != nullptr)
//	{
//		assert(0 && "colliderDataは既に作られています。");
//		return m_colliderData;
//	}
//	switch (kind)
//	{
//	case ColliderData::Kind::Line:
//		m_colliderData = new ColliderDataLine(isTrigger);
//		break;
//	case ColliderData::Kind::Sphere:
//		m_colliderData = new ColliderDataSphere(isTrigger);
//		break;
//	default:
//		assert(0 && "colliderData作成に失敗。");
//		break;
//	}
//	return m_colliderData;
//}

std::shared_ptr<MyLib::ColliderData> MyLib::Collidable::AddCollider(const ColliderData::Kind& kind,bool isTrigger)
{
	std::shared_ptr<ColliderData> collider;

	if (kind == ColliderData::Kind::Sphere)
	{
		collider = std::make_shared<ColliderDataSphere>(isTrigger);
	}
	else if (kind == ColliderData::Kind::Line)
	{
		collider = std::make_shared<ColliderDataLine>(isTrigger);
	}
	else
	{
		assert(false);
		collider = std::make_shared<ColliderDataSphere>(isTrigger);
	}

	m_colliders.emplace_back(collider);

	return collider;
}
