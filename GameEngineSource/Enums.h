#pragma once

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Script,
	Camera,
	End,
};

enum class eLayerType
{
	None,
	BackGround,
	//Tree
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