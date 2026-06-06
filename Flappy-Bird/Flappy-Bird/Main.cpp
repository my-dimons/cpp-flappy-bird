#include <iostream>
#include <windows.h>
#include <vector>
#include <thread>           
#include <chrono>          
#include <mutex>             
#include <condition_variable> 

#include "Key.h"
#include "KeyboardInput.h"
#include "Grid.h"
#include "Bird.h"

using namespace std;

KeyboardInput keyboardInput;
KEY_EVENT_RECORD krec;
Grid grid;
Object bird;

bool gameRunning = true;

int FPS = 3;
std::chrono::duration<double> FPS_TIME = (1.0s / FPS);

void generateGrid() {
  using namespace std::literals::chrono_literals;

  bird.Update();

  while (gameRunning) {
    grid.printGrid();
    std::this_thread::sleep_for(FPS_TIME);
  }
}

void handleInput() {
  while (gameRunning) {
    keyboardInput.getconchar(krec);
    //keyboardInput.outputPressedKey(krec);
    if (keyboardInput.keyPressed(keyboardInput.getJumpKeys(), krec)) {
      cout << "JUMPING" << endl;
    }
    else if (keyboardInput.keyPressed(keyboardInput.getQuitKeys(), krec)) {
      cout << "Quitting Game";
      gameRunning = false;
    }
  }
}

int main()
{
  std::thread grid(generateGrid);
  std::thread input(handleInput);
  
  grid.join();
  input.join();
  
  return 0;
}