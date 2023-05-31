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
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	AnimationClip animationClips[enAnimationClip_Num];
	Animation animation;

};

