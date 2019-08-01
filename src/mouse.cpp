#include <cstdlib>
#include "mouse.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>


#define SCALER 10

void setDefaultPosition(int *lastPos)
{

	Display *display = XOpenDisplay(0);

	Screen* screen = DefaultScreenOfDisplay(display);
	
    Window root = DefaultRootWindow(display);
   
	XWarpPointer(display, None, root, 0, 0, 0, 0, screen->width/2, screen->height/2);
  	
  	lastPos[0] = screen->width/2;
  	lastPos[1] = screen->height/2;
  	

    XFlush(display);
    XCloseDisplay(display);

}


/*
	Figure out how to compute delta between frames 
	dumbass



*/


void moveMouse(int *leftPupil , int *rightPupil, int * last)
{
	
	static int lastLeft[2] = {0,0} , lastRight[2] = {0,0};

	
	if(lastLeft[0] != 0 && lastLeft[1] != 0 && lastRight[0] != 0 && lastRight[1] != 0 )
	{
		
		int dR[2] , dL[2] , aD[2];
		
		dR[0] = lastRight[0] - rightPupil[0];
		dR[1] =  lastRight[1] - rightPupil[1];
		dL[0] = lastLeft[0] - leftPupil[0];	
		dL[1] = lastLeft[1] - leftPupil[1];
		
		aD[0] = (dR[0] + dL[0]) *SCALER  ;
		aD[1] = (dR[1] + dL[1]) * SCALER ;
		
		
		if(aD[0] && aD[1])
		{
			Display *display = XOpenDisplay(0);

			Screen* screen = DefaultScreenOfDisplay(display);
	
			Window root = DefaultRootWindow(display);
						   
			last[0] +=  aD[0] , last[1] +=  aD[1];						
					   	
			XWarpPointer(display, None, root, 0, 0, 0, 0, last[0], last[1]);
			
			XFlush(display);
			XCloseDisplay(display);
		}
	}
	
	lastLeft[0] = leftPupil[0];
	lastLeft[1] = leftPupil[1];
	lastRight[0] = rightPupil[0];
	lastRight[1] = rightPupil[1];
	
	
}



void MouseClick(int button)
{
	Display *display = XOpenDisplay(NULL);
	
	XEvent event;
	
	memset(&event , 0 , sizeof(event));
	
	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;
	
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	
	
	XSendEvent(display, PointerWindow, True, 0xfff, &event);
	
	
	XFlush(display);
	usleep(100000);
	
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;

	XSendEvent(display, PointerWindow, True, 0xfff, &event);
	
	
	XFlush(display);
	
	XCloseDisplay(display);


}






