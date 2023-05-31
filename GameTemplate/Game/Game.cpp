#include "stdafx.h"
#include "Game.h"
#include "stdio.h"

Game::Game() {

	animationClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_walk].SetLoopFlag(true);

	modelRender.Init("Assets/modelData/unityChan.tkm",animationClips, enAnimationClip_Num);
	//modelRender2.Init("Assets/modelData/box.tkm",nullptr,0,enModelUpAxisZ);
	spriteRender.Init("Assets/target.dds",100,100);

	offScreen.files.emplace_back("Assets/modelData/unityChan.tkm");
	//offScreen.files.emplace_back("Assets/modelData/unityChan.tkm");
	offScreen.Init("Assets/modelData/box.tkm", nullptr, 0, enModelUpAxisZ);


	fontRender.SetText(L"Hello World!");

	spriteRender.SetPosition(Vector3{100.0f,200.0f,0.0f});
	modelRender.SetPosition(Vector3{ 50.0f,0.0f,0.0f });

	//modelRender2.SetPointLightRnage(10.0f);

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
	//modelRender2.Update();
}

void Game::Render(RenderContext& rc) {

	modelRender.Draw(rc);
	offScreen.Draw(rc);
	//modelRender2.Draw(rc);
	spriteRender.Draw(rc);
	fontRender.Draw(rc);

}