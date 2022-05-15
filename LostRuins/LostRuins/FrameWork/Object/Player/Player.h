#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <list>
#include <cstdlib>
#include "../../Mgr/TextureHolder.h"
#include "../../Mgr/SoundHolder.h"
#include "../../Animation/AnimationController.h"
#include "../../Animation/rapidcsv.h"
#include "../../Mgr/Utils.h"
#include "../../Mgr/InputManager.h"
#include "../../Mgr/AttackManager.h"
#include "../CollisionBlock/CollisionBlock.h"
#include "../../Mgr/EffectManager.h"
#include "../DamageAndRecovery/DamageAndRecovery.h"


using namespace sf;

class ZombieWalker;
class Monster;

enum class Status
{
	STATUS_IDLE,
	STATUS_RUN,
	STATUS_JUMP,
	STATUS_FALLING,
	STATUS_CROUCH,
	STATUS_ROLL,
	STATUS_ATK_TWO_STAND,
	STATUS_ATK_DAGGER,
	STATUS_SPELL,
	STATUS_HIT,
	STATUS_DEAD,
};

class Player
{
private:
	const Vector2f scale = Vector2f(1.f, 1.f);
	const Vector2f scaleFlipX = Vector2f(-1.f, 1.f);
	const Vector2f hitBoxStand = Vector2f(10.f, 48.f);
	const Vector2f hitBoxCrouch = Vector2f(10.f, 23.f);

	const int START_HEALTH = 20;
	const int START_MANA = 20;
	const float START_SPEED = 150.f;
	const float START_JUMP_SPEED = 300.f;
	const float START_ROLL_SPEED = 150.f;
	const float START_ROLL_TIME = 0.5f;
	const float GRAVITY_POWER = 600.f;
	const float START_IMMUNE_MS = 500.f;
	const float START_KNOCK_BACK_SPEED = 180.f;
	const float DEAD_FALLING_SPEED = 200.f;
	const float DEAD_TIME_COUNT = 1.f;
	const int MAX_TEXT_CACHE_SIZE = 50;

	AnimationController animation;
	AttackManager attackMgr;
	EffectManager effectMgr;

	Sprite sprite;

	Vector2f position;
	Vector2i resolustion;
	IntRect gameMap;

	Sound soundBackGround;
	Sound soundWalk;
	Sound soundJump;
	Sound soundRoll;
	Sound soundDagger;
	Sound soundTwoHanded;
	Sound soundFireArrow;
	Sound soundDamage;
	Sound soundDeath;

	int tileSize;
	int health;
	int maxHealth;
	int mana;
	int maxMana;

	float speed;
	float JumpingSpeed;
	float fallingSpeed;
	float rollSpeed;
	float knockBackSpeed;

	float attackFps;
	float soundDelay;
	float rollTime;
	float immuneMs;
	float deadTime;

	Status currentStatus;
	bool isFloor;
	bool isJump;
	bool isAttack;
	bool isSpell;
	bool isDelay;
	bool isCrouch;
	bool isRoll;
	bool isHit;
	bool isAlive;
	bool isPause;

	bool isXequip;
	bool isZequip;
	bool isAequip;

	Time lastHit;

	std::map<std::string, Texture> texmap;
	std::list<DamageAndRecovery*> unuseDorR;
	std::list<DamageAndRecovery*> useDorR;

	RectangleShape hitBox;

	ZombieWalker* zombie;

public:
	void Init(ZombieWalker* zombie);
	void Update(float dt, std::vector <CollisionBlock*> blocks, Time playTime, std::vector<Monster*>& monsters);
	void Draw(RenderWindow* window, View* mainView);
	
	void PlayerAction(float dt, Time playTime, std::vector<Monster*> monsters);
	void Spawn(IntRect gameMap, Vector2i res, int tileSize);
	void Spawn(float x, float y);

	bool OnHitted(int damage, Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	Sprite GetSprite() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	int GetMana() const;
	int GetMaxMana() const;
	RectangleShape GetHitBox();
	bool GetAlive();
	void SetPause(bool isPause);
	bool GetPause();

	void SetXWeapon(bool isXequip);
	void SetZWeapon(bool isZequip);
	void SetASpell(bool isAequip);

	void AnimationInit(Sprite* sprite);
	void SoundInit();
	void UpdateCollision(std::vector <CollisionBlock*> blocks);

	void AnimationUpdate(float dt);
	void SetStatus(Status newStatus);

};

