#pragma once
class Game :public IGameObject
{

public:

	Game();
	~Game(); 
	void Update();

	void Render(RenderContext& rc);

private:

	ModelRender modelRender;
	ModelRender modelRender2;
	SpriteRender spriteRender;
	FontRender fontRender;
	OffScreen offScreen;

	wchar_t text;

	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_walk,	//歩きアニメーション。
		enAnimationClip_Num,	//アニメーションクリップの数。
	};
	AnimationClip animationClips[enAnimationClip_Num];
	Animation animation;

};

