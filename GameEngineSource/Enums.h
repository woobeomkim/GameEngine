#pragma once

enum class eComponentType
{
	Transform,
	Collider,
	Script,
	SpriteRenderer,
	Animator,
	Camera,
	End,
};

enum class eLayerType
{
	None,
	BackGround,
	//Tree
	Tile,
	//Character
	Player,
	Animal,
	Particle,
	Max = 16,
};

enum class eResourceType
{
	Texture,
	AudioClip,
	Animation,
	Prefab,
	End,
};

enum class eTextureType
{
	Bmp,
	Png,
	End,
};

enum class eColliderType
{
	Circle2D,
	Rect2D,
	End,
};