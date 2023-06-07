#include "stdafx.h"
#include "Game.h"
#include "stdio.h"

Game::Game() {

	animationClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_walk].SetLoopFlag(true);

	modelRender.Init("Assets/modelData/unityChan.tkm",animationClips, enAnimationClip_Num);
	spriteRender.Init("Assets/target.dds",100,100);


	wchar_t tx[256];
	swprintf_s(tx, 256, L"a%d", int(100));
	fontRender.SetText(tx);

	spriteRender.SetPosition(Vector3{100.0f,200.0f,0.0f});
	modelRender.SetPosition(Vector3{ 50.0f,0.0f,0.0f });

	Quaternion rot;
	rot.SetRotationDegX(90.0f);
	
	modelRender.SetRotation(rot);

	modelRender.PlayAnimation(enAnimationClip_walk);


}

Game::~Game() {

	

}

void Game::Update() {	

	spriteRender.Update();
	modelRender.Update();
}

void Game::Render(RenderContext& rc) {

	modelRender.Draw(rc);
	spriteRender.Draw(rc);
	fontRender.Draw(rc);

}