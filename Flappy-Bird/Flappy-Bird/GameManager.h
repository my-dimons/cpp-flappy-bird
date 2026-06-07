#pragma once
class GameManager
{
public:
	void GameLoop();
	void InitGame();
	void CloseGame();
private:
	void RenderFrame();
	void RenderMode2D();
	void RenderText();
	void RenderDebugText();
};

