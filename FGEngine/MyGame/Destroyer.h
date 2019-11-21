#pragma once
#include "Entity.h"
#include "StateMachine.h"

class Renderer;

class Destroyer : public FG::Entity {

public:
	~Destroyer() {}

	void Start() override;
	void Disable()override;

	void Update(float deltaTime)override;
	void Render(Renderer* const renderer)override;
	void OnCollision(FG::Entity* other)override;


private:
	

};