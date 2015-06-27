/*
or points (x1,y1) and (x2,y2) the formula is sqrt((x1-x2)^2 + (y1-y2)^2)
shortest distance is sqrt( dx^2 + dy^2  ) 
that will give you distance between two points in two dimentions 
dx is distance of x coordinate, dy is distance of y coordinates. 
*/
//note to self: for some reason the ^2 function does not work, you can get negative numbers
// Distance between two points

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  
#define STRICT
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"  // class name
#define WINDOW_WIDTH  320              // size of window
#define WINDOW_HEIGHT 200

// MACROS /////////////////////////////////////////////////

// these read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// PROTOTYPES /////////////////////////////////////////////
void DisplayXY(HDC);
int CalcDistance(int,int,int,int);
void DrawDot(HDC); 

// GLOBALS ////////////////////////////////////////////////

HWND main_window_handle = NULL; // save the window handle
HINSTANCE main_instance = NULL; // save the instance
char buffer[80];                // used to print text
char buffer2[80];
int mouse_x=0,
    mouse_y=0,
	fwKeys;
bool ctrl_key= false,
	 mouse_Left_Click= false,
	 on = true;

// FUNCTIONS //////////////////////////////////////////////

//\\\\\\\\\\\\\\\\\\\\\\\\\ WinProc ///////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   //creates a handle to the device context

	//find out what the message is
	switch(msg)
	{	
	
	case WM_CREATE: //called when window is created
		{// do initialization stuff here
			return(0);
		} break;

	case WM_PAINT: //called when window needs repainting
		{//simply validate the window
		    
			//ValidateRect(hwnd, NULL);
			hdc = BeginPaint(hwnd,&ps);
		    EndPaint(hwnd,&ps);
			
			return(0);
		} break;

	case WM_KEYDOWN:
		{
			int virtual_code= (int)wparam;
			int key_bits= (int)lparam;
			
			switch(virtual_code)
			{
			case VK_CONTROL :
				{
					ctrl_key= true;
					break;
				}
			} //switch virtual_key

		}//end switch WM_KEYDOWN

		case WM_KEYUP: //reads if ctrl key is released
		{
			int virtual_code= (int)wparam;

			switch(virtual_code)
			{
			case VK_CONTROL : 
				{
					ctrl_key= false;
					break;
				}
			}//end switch virtual_code
		}//end case WM_KEYUP

	case WM_MOUSEMOVE :
		{
			mouse_x = (int) LOWORD(lparam);  // horizontal position of cursor 
			mouse_y = (int) HIWORD(lparam);  // vertical position of cursor 

			return(0);
		}
	
	case WM_LBUTTONDOWN :
		{
			mouse_Left_Click= true;
			break;
		}

	case WM_LBUTTONUP :
		{
			mouse_Left_Click= false;
			on=true;
			break;
		}

	case WM_DESTROY: 
		{// kill the application			
			//close the program
			PostQuitMessage(0);
			return(0);
		} break;

	} // end main switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

//\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	WNDCLASS winclass;	// this will hold the class created
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message
	HDC      hdc;       // generic dc
	//PAINTSTRUCT ps;     // generic paintstruct
	char buffer3[80];

	//fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// register the window class
	if (!RegisterClass(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
							  "Shortest distance between two points",	 // title
							  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						 	  200,200,	   // x,y
							  WINDOW_WIDTH,  // width
						      WINDOW_HEIGHT, // height
							  NULL,	   // handle to parent 
							  NULL,	   // handle to menu
							  hinstance,// instance
							  NULL)))	// creation parms
	{
		MessageBox(hwnd, "Window Could not be Created", NULL, MB_OK); //NULL is default for Error
		return(0);
	}

	// save the window handle and instance in a global
	main_window_handle = hwnd;
	main_instance      = hinstance;


	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
		hdc= GetDC(hwnd);
		
		
		DisplayXY(hdc);
		DrawDot(hdc);

		SetBkMode(hdc, TRANSPARENT); //set background color
		SetTextColor(hdc,RGB(0,0,0)); //set text color
		strcpy(buffer3, "hi");
		TextOut(hdc,100,100,buffer3,strlen(buffer3)); //print text
		
						
		sprintf(buffer3,"closest point x= %d", 1);
		SetTextColor(hdc,RGB(0,0,255)); //set text color
		TextOut(hdc,100,100,buffer3,strlen(buffer3)); //print text
		
		
		/* Debug comment block 
		//store mouse current position
			
		SetBkMode(hdc, TRANSPARENT); //set background color
		SetTextColor(hdc,RGB(0,0,0)); //set text color
		TextOut(hdc,100,100,buffer3,strlen(buffer3)); //print text
		
		//sprintf(buffer3,"distance= %d",  CalcDistance(mouse_x, 50, mouse_y, 50) );
		//int test= (mouse_x - 50)*(mouse_x - 50);
		//sprintf(buffer3,"test x1-x2= %d", test);

		SetTextColor(hdc,RGB(0,0,255)); //set text color
		TextOut(hdc,100,100,buffer3,strlen(buffer3)); //print text

		SetPixel(hdc, 50,50, RGB(255,255,255));
		*/

		//slow things down a bit
		Sleep(10);
		ReleaseDC(hwnd, hdc);

	} // end while


	// return to Windows like this
	return(msg.wParam);

} // end WinMain

void DrawDot(HDC hdc)
{
	static int i=1;
	RECT rect;
	int ballRadius= 2;

	if(mouse_Left_Click && on)
	{
		on= false; //not allowed to draw another dot until release mouse

		rect.left  = mouse_x - ballRadius;
		rect.right = mouse_x + ballRadius;
		rect.top   = mouse_y - ballRadius;
		rect.bottom= mouse_y + ballRadius;
		
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
	}//end if on crtl_Key && mouse_Left_click
	
	return;
}

int CalcDistance(int x1, int y1, int x2, int y2)
{
	
	//sqrt((x1-x2)^2 + (y1-y2)^2
	return( (int) sqrt( ( (x1 - x2)*(x1 - x2) ) + ( (y1 - y2)*(y1 - y2) ) ) );
}

void DisplayXY(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT); //set background color
	SetTextColor(hdc,RGB(0,0,0)); //set text color
	TextOut(hdc,0,0,buffer,strlen(buffer)); //print text
	
	// build up the messages
    sprintf(buffer,"X= %d", mouse_x);
		
	SetTextColor(hdc,RGB(0,0,255)); //set text color
	TextOut(hdc,0,0,buffer,strlen(buffer)); //print text
		
	////////////////

	SetTextColor(hdc,RGB(0,0,0)); //set text color
	TextOut(hdc,0,20,buffer2,strlen(buffer2)); //print text
		
	// build up the messages
    sprintf(buffer2,"Y= %d", mouse_y);
		
	SetTextColor(hdc,RGB(0,0,255)); //set text color
	TextOut(hdc,0,20,buffer2,strlen(buffer2)); //print text
	
	return;
}