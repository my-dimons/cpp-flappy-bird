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

std::condition_variable cv;
KeyboardInput keyboardInput;
KEY_EVENT_RECORD krec;

using namespace std;

double long const FPS = 1 / 6;

void read_quit_value() {
  if (keyboardInput.keyPressed(keyboardInput.getQuitKeys(), krec)) {
    cv.notify_one();
  }
}

void getconchar() {
  keyboardInput.getconchar(krec);
}

int main()
{
  Grid grid;
  std::thread th(read_quit_value);
  std::thread ch(getconchar);
  bool frameGenerated = true;

  std::mutex mtx;
  std::unique_lock<std::mutex> lck(mtx);
  //while (cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
  //  std::cout << '.' << std::endl;
  //}

  while (cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
    //cout << "*";
    //keyboardInput.outputPressedKey(krec);
    // 
    //if (keyboardInput.keyPressed(keyboardInput.getJumpKeys(), krec)) {
    //  cout << "JUMPING" << endl;
    //}

    grid.printGrid();
  }

  cout << "Quitting Game";
  return 0;
}

//// condition_variable::wait_for example
//#include <iostream>           // std::cout
//
//
//int value;
//
//void read_value() {
//  std::cin >> value;
//  cv.notify_one();
//}
//
//int main()
//{
//  std::cout << "Please, enter an integer (I'll be printing dots): \n";
//  std::thread th(read_value);
//
//  std::mutex mtx;
//  std::unique_lock<std::mutex> lck(mtx);
//  while (cv.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
//    std::cout << '.' << std::endl;
//  }
//  std::cout << "You entered: " << value << '\n';
//
//  th.join();
//
//  return 0;
//}