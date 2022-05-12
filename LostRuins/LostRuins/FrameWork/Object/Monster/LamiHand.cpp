#include "LamiHand.h"
#include <functional>

LamiHand::LamiHand()
{
	
}

void LamiHand::Init(Vector2f pos, int handSide)
{
	isAttacking = false;

	AnimationInit(&sprite);
	
	strIdle = "Lami2HandIdle";
	strNearAttack = "Lami2HandAttackNear";
	strNearAttackToIdle = "Lami2HandAttackNearToIdle";
	strMiddleAttack = "Lami2HandAttackMiddle";
	strMiddleAttackToIdle = "Lami2HandAttackMiddleToIdle";
	strFarAttack = "Lami2HandAttackFar";
	strFarAttackToIdle = "Lami2HandAttackFarToIdle";
	strDiving = "Lami2HandDiving";
	strReappearing = "Lami2HandReappearing";
	strReappearingToIdle = "Lami2HandReappearingToIdle";

	sprite.setOrigin(80.f,31.f);
	sprite.setPosition(pos);
	
	if (handSide == 0)		//left hand
	{
		sprite.setScale(3.f, 3.f);
	}
	else if(handSide == 1)	//Right hand
	{
		sprite.setScale(-3.f, 3.f);
	}
	currentStatus = Lami2Status::STATUS_IDLE;
	/*animation.Play(strIdle, std::bind(&LamiHand::IdlePlay, this));*/
}
//animation.Play(strIdle, std::bind(&LamiHand::AnimationUpdate, this));
void LamiHand::Update(float dt, Vector2f pos)
{
	sprite.setPosition(pos);
	animation.Update(dt);
	AnimationUpdate();
}

void LamiHand::Draw(RenderWindow* window)
{
	window->draw(sprite);
}

Sprite LamiHand::GetSprite()
{
	return sprite;
}

void LamiHand::AnimationPlay(Lami2Status newStatus)
{
	switch (newStatus)
	{
	case Lami2Status::STATUS_IDLE:
		animation.Play(strIdle);
		/*animation.Play(strIdle, std::bind(&LamiHand::AnimationUpdate, this));*/
		break;
	case Lami2Status::STATUS_ATTACK_NEAR:
		animation.Play(strNearAttack);
		break;
	case Lami2Status::STATUS_ATTACK_MIDDLE:
		animation.Play(strMiddleAttack);
		break;
	case Lami2Status::STATUS_ATTACK_FAR:
		animation.Play(strFarAttack);
		break;
	case Lami2Status::STATUS_DIVING:
		animation.Play(strDiving);
		break;
	case Lami2Status::STATUS_REAPPEARING:
		animation.Play(strReappearing);
		break;
	case Lami2Status::STATUS_DEAD:
		break;
	default:
		break;
	}
}

void LamiHand::AnimationUpdate()
{
	switch (currentStatus)
	{
	case Lami2Status::STATUS_IDLE:
		SetStatus(Lami2Status::STATUS_IDLE);
		break;
	case Lami2Status::STATUS_ATTACK_NEAR:
		if (isAttacking == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_ATTACK_MIDDLE:
		if (isAttacking == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_ATTACK_FAR:
		if (isAttacking == false)
		{
			SetStatus(Lami2Status::STATUS_IDLE);
		}
		break;
	case Lami2Status::STATUS_DIVING:
		SetStatus(Lami2Status::STATUS_DIVING);
		break;
	case Lami2Status::STATUS_REAPPEARING:
		SetStatus(Lami2Status::STATUS_REAPPEARING);
		break;
	case Lami2Status::STATUS_DEAD:
		SetStatus(Lami2Status::STATUS_IDLE);
		break;
	default:
		break;
	}
}

void LamiHand::SetStatus(Lami2Status newStatus)
{
	Lami2Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case Lami2Status::STATUS_IDLE:
		if (prevStatus == Lami2Status::STATUS_ATTACK_NEAR)
		{
			sprite.setOrigin(48,31);
			/*animation.Play(strNearAttackToIdle);*/
			animation.Play(strNearAttackToIdle, std::bind(&LamiHand::IsAttackingFalse, this));
			/*animation.PlayQueue(strIdle);*/
		}
		else if (prevStatus == Lami2Status::STATUS_ATTACK_MIDDLE)
		{
			sprite.setOrigin(90, 31);
			/*animation.Play(strMiddleAttackToIdle);*/
			animation.Play(strMiddleAttackToIdle, std::bind(&LamiHand::IsAttackingFalse, this));
			/*animation.PlayQueue(strIdle);*/
		}
		else if (prevStatus == Lami2Status::STATUS_ATTACK_FAR)
		{
			sprite.setOrigin(54, 33);
			/*animation.Play(strFarAttackToIdle);*/
			animation.Play(strFarAttackToIdle, std::bind(&LamiHand::IsAttackingFalse, this));
			/*animation.PlayQueue(strIdle);*/
		}
		else if (prevStatus == Lami2Status::STATUS_REAPPEARING)
		{
			sprite.setOrigin(59, 31);
			/*animation.Play(strReappearingToIdle);*/
			animation.Play(strReappearingToIdle, std::bind(&LamiHand::IsAttackingFalse, this));
			/*animation.PlayQueue(strIdle);*/
		}
		else
		{
			/*sprite.setOrigin(80, 31);*/
			animation.PlayQueue(strIdle);
		}
		break;
	case Lami2Status::STATUS_ATTACK_NEAR:
		isAttacking = true;
		sprite.setOrigin(105, 47);
	/*	animation.Play(strNearAttack);*/
		animation.Play(strNearAttack, std::bind(&LamiHand::IsAttackingFalse, this));
		break;
	case Lami2Status::STATUS_ATTACK_MIDDLE:
		isAttacking = true;
		sprite.setOrigin(110, 32);
		animation.Play(strMiddleAttack);
		break;
	case Lami2Status::STATUS_ATTACK_FAR:
		isAttacking = true;
		sprite.setOrigin(111, 38);
		animation.Play(strFarAttack);
		break;
	case Lami2Status::STATUS_DIVING:
		sprite.setOrigin(69, 32);
		animation.Play(strDiving);
		break;
	case Lami2Status::STATUS_REAPPEARING:
		sprite.setOrigin(113, 95);
		animation.Play(strReappearing);
		break;
	default:
		break;
	}
}

void LamiHand::IdlePlay()
{
	animation.Play(strNearAttack);
}

void LamiHand::AnimationInit(Sprite* sprite)
{
	animation.SetTarget(sprite);

	rapidcsv::Document clips("data_tables/animations/monster/monster_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopType)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texmap.find(colTexture[j]) == texmap.end())
			{
				auto& ref = texmap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}

			clip.frames.push_back(AnimationFrame(texmap[colTexture[j]],
				IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}
}

void LamiHand::IsAttackingFalse()
{
	sprite.setOrigin(80, 31);

	isAttacking = false;
	animation.PlayQueue(strIdle);
}
