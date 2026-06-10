#pragma once
#include "Bird.h"
#include "Pipes.h"
#include <vector>

class GameManager
{
public:
	void GameLoop();
	void InitGame();
	void CloseGame();
private:
	void RenderFrame();
	void RenderObjects();
	void RenderText();
	void RenderDebugText();

	void UpdatePlayer(Bird* bird, float deltaTime);
	void UpdateEnv(std::vector<Pipe>* pipes, float deltaTime);
	void GeneratePipes();
	void HandleScore();

	void RestartGame();
	bool IsColliding(Rectangle* dx, Rectangle* dy);
};