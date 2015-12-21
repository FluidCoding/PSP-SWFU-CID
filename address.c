#include <pspkernel.h>
#include <pspkerneltypes.h>
#include <pspmoduleinfo.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspthreadman.h>
#include <pspwlan.h>
#include <stdlib.h>
#include <pspchnnlsv.h>
#include <pspctrl.h>
#include <string.h>
#include <pspdebug.h>
#include <pspctrl_kernel.h>
#include <pspdisplay.h>
#include <pspdisplay_kernel.h>
#include <pspthreadman_kernel.h>
#include <pspumd.h>
#include "float.h"
//#include "main.c"
#define print pspDebugScreenPuts



int backcolor=0xFFFFFFFF;
unsigned int starttext=0x00660000;
unsigned int startback=0x00000000;
int startMenuRunning=1;
SceCtrlData pad;


int startMenu()
{
while(startMenuRunning)
{
refresh();
if(pad.Buttons & PSP_CTRL_START)
{
startMenuRunning=0;
pspDebugScreenClear();
continue;
}
pspDebugScreenSetXY(0, 0);
pspDebugScreenSetTextColor(0x0066ff00);
pspDebugScreenSetBackColor(startback);
print(" Welcome to Star Wars The Force Unleashed Cheat Device Rev1... \n");
pspDebugScreenSetTextColor(0xFFFFFFFF);
print("\nCredits:\nCoder: Sonnie & xWhite_Shadowx of www.codinghs.com\nCheats Supplied By: WhoisYou\n\n");
pspDebugScreenSetTextColor(0xFF00FFFF);
print("               PRESS START TO Initilize Device!!!");
sceKernelDelayThread(100000);
}
}
int cocksped(int pcclock)
{
	switch(pcclock)
	{
	case 1:
		scePowerSetClockFrequency(333, 333, 166);
		break;
	case 2:
		scePowerSetClockFrequency(170, 170, 130);
		break;
	}



}



