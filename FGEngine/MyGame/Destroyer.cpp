#include "Destroyer.h"

void Destroyer::Start()
{
	isActive = true;
}

void Destroyer::Disable()
{  
	isActive = false; 
}

void Destroyer::Update(float deltaTime)
{

}

void Destroyer::Render(Renderer* const renderer)
{

}

void Destroyer::OnCollision(FG::Entity* other)
{

}


