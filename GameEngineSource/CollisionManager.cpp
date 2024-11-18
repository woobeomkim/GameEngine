#include "CollisionManager.h"
#include "Collider.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Layer.h"
#include "Transform.h"

std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	Scene* scene = SceneManager::GetActiveScene();
	for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
	{
		for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
		{
			if (mCollisionLayerMatrix[row][col] == true)
			{
				LayerCollision(scene, (eLayerType)row, (eLayerType)col);
			}
		}
	}
}

void CollisionManager::LateUpdate()
{
}

void CollisionManager::Render(HDC hdc)
{
}

void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
{
	int row = 0;
	int col = 0;

	if (left <= right)
	{
		row = (UINT)left;
		col = (UINT)right;
	}
	else
	{
		row = (UINT)right;
		col = (UINT)left;
	}

	mCollisionLayerMatrix[row][col] = enable;
}

void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
{
	const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
	const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

	for (GameObject* left : lefts)
	{
		if (!left->IsActive())
			continue;
		Collider* leftCollider = left->GetComponent<Collider>();
		if (!leftCollider)
			continue;

		for (GameObject* right : rights)
		{
			if (!right->IsActive())
				continue;
			Collider* rightCollider = right->GetComponent<Collider>();
			if (!rightCollider)
				continue;
			if (left == right)
				continue;

			ColliderCollision(leftCollider, rightCollider);
		}
	}

}

void CollisionManager::ColliderCollision(Collider* left, Collider* right)
{
	CollisionID id = {};
	id.left = left->GetID();
	id.right = right->GetID();

	auto iter = mCollisionMap.find(id.id);
	if (iter == mCollisionMap.end())
	{
		mCollisionMap.insert(std::make_pair(id.id, false));
		iter = mCollisionMap.find(id.id);
	}

	if (Intersect(left, right))
	{
		if (iter->second == false)
		{
			left->OnCollisionEnter(right);
			right->OnCollisionEnter(left);
			iter->second = true;
		}
		else
		{
			left->OnCollisionStay(right);
			right->OnCollisionStay(left);
		}
	}
	else
	{
		if (iter->second == true)
		{
			left->OnCollisionExit(right);
			right->OnCollisionExit(left);
			iter->second = false;
		}
	}
}

bool CollisionManager::Intersect(Collider* left, Collider* right)
{
	Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
	Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

	Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
	Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

	Vector2 leftSize = left->GetSize() * 100.0f;
	Vector2 rightSize = right->GetSize() * 100.0f;


	eColliderType leftType = left->GetColliderType();
	eColliderType rightType = right->GetColliderType();

	if (leftType == eColliderType::Rect2D && rightType == eColliderType::Rect2D)
	{// AABB Ãæµ¹
		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.x / 2.0f))
		{
			return true;
		}
	}
	if (leftType == eColliderType::Circle2D && rightType == eColliderType::Circle2D)
	{
		Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
		Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
		float distance = (rightCirclePos - leftCirclePos).length();

		if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
		{
			return true;
		}
	}

	if (leftType == eColliderType::Rect2D && rightType == eColliderType::Circle2D
		|| leftType == eColliderType::Circle2D && rightType == eColliderType::Rect2D)
	{
		
	}
	return false;
}
