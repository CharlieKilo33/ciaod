#include <iostream>
#include <windows.h>
 
using namespace std;
 
//How to make an autoclicker in c++ // 2019!
 
int x=0, y=0, cps;
bool click=false;
 
void Menu()
{
  cout << "Add CPS (click per second):" << endl;
  cin >> cps;
}
[[noreturn]] void Clicker()
{
  while (true)
  {
    if(GetAsyncKeyState(VK_LBUTTON)) // Left button of the mouse
    {
      click = true;
    }
        
    if(GetAsyncKeyState(VK_RBUTTON)) //Right button of the mouse
    {
      click = false;
    }
        
    if(click)
    {
      mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0 , 0);
      mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0 , 0);
      Sleep(1000/cps);
    }
  }
}
int main()
{
  Menu();
  Clicker();
}