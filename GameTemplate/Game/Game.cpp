#include "stdafx.h"
#include "Game.h"

Game::Game() {

	animationClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_walk].SetLoopFlag(true);

	modelRender.Init("Assets/modelData/unityChan.tkm",animationClips, enAnimationClip_Num);
	spriteRender.Init("Assets/target.dds",100,100);

	fontRender.SetText(L"Hello World!");

	spriteRender.SetPosition(Vector3{100.0f,200.0f,0.0f});
	modelRender.SetPosition(Vector3{ 50.0f,0.0f,0.0f });

	modelRender.PointLightRnage(100.0f);

	//modelRender.PlayAnimation(enAnimationClip_walk);

	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	
	modelRender.SetRotation(rot);

}

Game::~Game() {



}

void Game::Update() {


	modelRender.PlayAnimation(enAnimationClip_walk);
	

	//spriteRender.Update();
	modelRender.Update();
}

void Game::Render(RenderContext& rc) {

	modelRender.Draw(rc);
	//spriteRender.Draw(rc);
	fontRender.Draw(rc);

}