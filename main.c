//Includes
#define _PSP_FW_VERSION 150
#include <psppower.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspdisplay_kernel.h>
#include <pspkerneltypes.h>
#include <pspmoduleinfo.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspthreadman.h>
#include <math.h>
#include <time.h> 
#include <pspctrl.h>
#include <pspgu.h>
#include <pspgum.h>
#include <string.h>
#include <pspctrl_kernel.h>
#include "address.h"
#define print pspDebugScreenPuts
#define tcolor pspDebugScreenSetTextColor

// Created 9/28/2008
// Sonnie + xWhite_Shadowx
PSP_MODULE_INFO("SWFU", 0x3010, 1, 2); 
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(1012);

//Threads
SceUID thid;
SceCtrlData pad;
void *vram;
unsigned char buffer[10];
int fd;
char menudrawn=0;
int offcolor=0xFF000000;
unsigned char gameId[10];
int running=0;
int module_start(SceSize args, void *argp) __attribute__((alias("_start")));
int module_stop(SceSize args, void *argp) __attribute__((alias("_stop")));



//Colors
unsigned int lgreen = 0x0066ff00;
//unsigned int green = 0x
unsigned int white = 0xFFFFFFFF;
unsigned int black = 0x00000000;
unsigned int red =  0x000000FF;
unsigned int dred = 0x00000080;
unsigned int grey = 0x00808080;
unsigned int lblue = 0x00FFFF00;
unsigned int blue = 0x00FF0000;
unsigned int yellow = 0xFF00FFFF;
//Vars
int pctab=1;
int pccheat=1;
int pcset = 1;
int paused = 0;
unsigned int ritbepaused;
unsigned int dispcheatcode = 0;
//Code Values
unsigned int jrra = 0x03e00008;
unsigned int respawntime0 = 0x00000000;
unsigned int respawntime5 = 0x40a00000;
unsigned int nop = 0x00000000;
#define MAX_THREAD 64

static int thread_count_start, thread_count_now, pauseuid = -1;
static SceUID thread_buf_start[MAX_THREAD], thread_buf_now[MAX_THREAD], thid1 = -1, thid2 = -1;

static void pause_game(SceUID thid)
{
	if(pauseuid >= 0)
		return;
	pauseuid = thid;
	sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, thread_buf_now, MAX_THREAD, &thread_count_now);
	int x, y, match;
	for(x = 0; x < thread_count_now; x++)
	{
		match = 0;
		SceUID tmp_thid = thread_buf_now[x];
		for(y = 0; y < thread_count_start; y++)
		{
			if((tmp_thid == thread_buf_start[y]) || (tmp_thid == thid1) || (tmp_thid == thid2))
			{
				match = 1;
				break;
			}
		}
		if(match == 0)
			sceKernelSuspendThread(tmp_thid);
	}
}

static void resume_game(SceUID thid)
{
	if(pauseuid != thid)
		return;
	pauseuid = -1;
	int x, y, match;
	for(x = 0; x < thread_count_now; x++)
	{
		match = 0;
		SceUID tmp_thid = thread_buf_now[x];
		for(y = 0; y < thread_count_start; y++)
		{
			if((tmp_thid == thread_buf_start[y]) || (tmp_thid == thid1) || (tmp_thid == thid2))
			{
				match = 1;
				break;
			}
		}
		if(match == 0)
			sceKernelResumeThread(tmp_thid);
	}
}




//Code Vars
int pcflash = 1;
int pcwalk = 1;
unsigned int off = "[OFF]";
unsigned int on = "[ON]";
unsigned int isInfiniteHealthON ="[OFF]";
unsigned int isInfiniteForceON = "[OFF]";
unsigned int isFastPowerRegenON = "[OFF]";
unsigned int isFlashON = "[OFF]";
unsigned int isWalkON = "[OFF]";
unsigned int isibodieON = "[OFF]";
unsigned int isptsON = "[OFF]";
unsigned int isSjON= "[OFF]";
unsigned int isPauseON="[FALSE]";
unsigned int clockSpeed = "[DEFAULT]";
unsigned int cpspeed = "[333]";
//Codes
unsigned int *InfiniteHealth1=(unsigned int*) (0x00C612F0+0x08800000);
unsigned int *InfiniteHealth2=(unsigned int*) (0x00C613B0+0x08800000);
unsigned int *InfiniteHealth3=(unsigned int*) (0x00c60AB0 +0x08800000);
unsigned int *InfiniteForce1=(unsigned int*) (0x00C61F34 +0x08800000);
unsigned int *InfiniteForce2=(unsigned int*) (0x00C62774+0x08800000);
unsigned int *InfiniteForce3=(unsigned int*) (0x00C62834+0x08800000);
unsigned int *FastPowerRegen1 = (unsigned int*) (0x00C62808 +0x08800000);
unsigned int *FastPowerRegen2 = (unsigned int*) (0x00C62834 +0x08800000);
unsigned int *flash = (unsigned int*) (0x00481aa8 +0x08800000);
unsigned int *walk =(unsigned int*) (0x0027f2b0 +0x08800000);
unsigned int *ibodie = (unsigned int*) (0x0027bd98 + 0x08800000);
unsigned int *pts = (unsigned int*) (0x00904164 + 0x08800000);
unsigned int *saberj1 = (unsigned int*) (0x000080D8   +0x08800000); 
unsigned int *saberj2 = (unsigned int*) (0x00000600  +0x08800000); 
unsigned int *saberj3 = (unsigned int*) (0x00000604  +0x08800000); 
unsigned int *saberj4 = (unsigned int*) (0x00000608  +0x08800000); 
unsigned int *saberj5 = (unsigned int*) (0x0000060c  +0x08800000); 
unsigned int *saberj6 = (unsigned int*) (0x00000610  +0x08800000); 
unsigned int *saberj7 = (unsigned int*) (0x00000614  +0x08800000); 
unsigned int *saberj8 = (unsigned int*) (0x00000618  +0x08800000); 
unsigned int *saberj9 = (unsigned int*) (0x0000061c  +0x08800000); 
unsigned int *saberj10 = (unsigned int*) (0x00000620  +0x08800000); 
unsigned int *saberj11 = (unsigned int*) (0x00000624  +0x08800000); 
unsigned int *saberj12 = (unsigned int*) (0x00000628 +0x08800000); 
unsigned int *saberj13 = (unsigned int*) (0x0000062c +0x08800000); 
unsigned int *saberj14 = (unsigned int*) (0x00000630 +0x08800000); 
unsigned int *saberj15 = (unsigned int*) (0x00000634 +0x08800000); 
unsigned int *saberj16 = (unsigned int*) (0x00000638 +0x08800000); 
unsigned int *saberj17 = (unsigned int*) (0x0000063c +0x08800000); 
unsigned int *saberj18 = (unsigned int*) (0x00000640 +0x08800000); 
unsigned int *saberj19 = (unsigned int*) (0x00000644 +0x08800000); 
unsigned int *saberj20 = (unsigned int*) (0x00000648 +0x08800000);  
unsigned int *saberj21 = (unsigned int*) (0x0000064c +0x08800000);  
unsigned int *saberj22 = (unsigned int*) (0x00000650 +0x08800000); 

//Refresh the buttons
void refresh()
{
	pad.Buttons=0;
	sceCtrlPeekBufferPositive(&pad, 1);
	sceCtrlSetSamplingCycle(0); 
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}
int ths = 1;
void setdisp()
{
sprintf(buffer, "[%d]", scePowerGetCpuClockFrequency());

    if(dispcheatcode==1)
    {
    print("\n\n\n\n\nBuilt in Cheats Menu\n\n");
    tcolor(blue);
    print("[<------->Game Cheats<------->]\n");
    tcolor(red);
    print("Invincibility: Enter: ");
    tcolor(lblue);
    print("CORTOSIS\n");
    tcolor(red);
    print("Infinite Force: Enter: ");
    tcolor(lblue);
    print("VERGENCE\n");
    tcolor(red);
    print("1,000,000 Force Pts: Enter: ");
    tcolor(lblue);
    print("SPEEDER\n");
    tcolor(red);
    print("All Force Powers: Enter: ");
    tcolor(lblue);
    print("TYRANUS\n");
    tcolor(red);
    print("Maximum Force power level: Enter: ");
    tcolor(lblue);
    print("KATARN\n");
    tcolor(red);
    print("Maximum combo level: Enter: ");
    tcolor(lblue);
    print("COUNTDOOKU\n");
    tcolor(red);
    print("Amplified damage: Enter: ");
    tcolor(lblue);
    print("LIGHTSABER\n");
    tcolor(red);
    print("New Combo: Enter: ");
    tcolor(lblue);
    print("MARAJADE\n");
    tcolor(red);
    print("All Costumes: Enter: ");
    tcolor(lblue);
    print("GRANDMOFF\n");
    tcolor(yellow);
    print("\n\n\n\n\n\n\n\n\nPress /_\\ To go back to options");
    if((pad.Buttons & PSP_CTRL_TRIANGLE))
		{
			dispcheatcode=0;
			pspDebugScreenClear();
		}
    } 
    else if(dispcheatcode==0)
    {
	if(pcset==1){tcolor(red);}
	else{tcolor(blue);}
	print("\nPause Game:  ");
	print(isPauseON);

	if(pcset==2){tcolor(red);}
	else{tcolor(blue);}
	print("\nClock Speed:  ");
	print(cpspeed);
	
	if(pcset==3){tcolor(red);}
	else{tcolor(blue);}
	print("\nPress X here for Built-in Cheats");


	switch(pcset)
	{
	case 1:
	if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pcset=2;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isPauseON="[TRUE]";
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isPauseON="[FALSE]";
		}
	break;
	case 2:
	if((pad.Buttons & PSP_CTRL_UP))
		{
			pcset=1;
		}
	if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pcset=3;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			clockSpeed=222;
			cpspeed="[222]";
		}
	 if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			clockSpeed=333;
			cpspeed="[333]";
		}
	break;
	case 3:
	if((pad.Buttons & PSP_CTRL_UP))
		{
			pcset=2;
		}
	if((pad.Buttons & PSP_CTRL_CROSS))
		{
			dispcheatcode=1;
		}
	break;
	}
}
}
	void setenable()
	{
		if(isPauseON=="[TRUE]")
		{
			pause_game(thid);
		}
		else if(isPauseON=="[FALSE]")
		{
			resume_game(thid);
		}
	switch(clockSpeed)
	{
	case 222:
		cocksped(2);
			break;
	case 333:
		cocksped(1);
			break;
	}

	}
void codedisp()
{
	if(pccheat==1){tcolor(red);}
	else{tcolor(blue);}
	print("\nInfinite Health  ");
	print(isInfiniteHealthON);
	
	if(pccheat==2){tcolor(red);}
	else{tcolor(blue);}
	print("\nInfinite Force  ");
	print(isInfiniteForceON);

	if(pccheat==3){tcolor(red);}
	else{tcolor(blue);}
	print("\nFast Force Regenerate ");
	print(isFastPowerRegenON);
	
	if(pccheat==4){tcolor(red);}
	else{tcolor(blue);}
	print("\nGameplay Speed ");
	print(isFlashON);

	if(pccheat==5){tcolor(red);}
	else{tcolor(blue);}
	print("\nWalk Speed ");
	print(isWalkON);
	
	if(pccheat==6){tcolor(red);}
	else{tcolor(blue);}
	print("\nInvert Player ");
	print(isibodieON);

	if(pccheat==7){tcolor(red);}
	else{tcolor(blue);}
	print("\nForce Points ");
	print(isptsON);

	if(pccheat==8){tcolor(red);}
	else{tcolor(blue);}
	print("\nSaber Joker ");
	print(isSjON);


	switch(pccheat)
	{
	case 1:
	if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=2;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isInfiniteHealthON=off;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isInfiniteHealthON=on;
		}
	break;
	case 2:
if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=1;
		}
if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=3;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isInfiniteForceON=off;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isInfiniteForceON=on;
		}
	break;
	case 3:
		if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=2;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=4;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isFastPowerRegenON=off;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isFastPowerRegenON=on;
		}
	break;
	case 4:
		if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=3;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=5;
		}
			switch(pcflash)
			{
			case 1:
			   isFlashON=off;
			   if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcflash=2;
			    }
			   break;
			case 2:
				isFlashON="[Fast]";
				if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcflash=3;
				}
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcflash=1;
				}
				break;
				case 3:
				isFlashON="[Faster]";
				if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcflash=4;
				}
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcflash=2;
				}
				break;
			case 4:
				isFlashON="[Slow]";
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcflash=3;
				}
				if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcflash=5;
				}
				break;
				case 5:
				isFlashON="[Slower]";
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcflash=4;
				}
				break;
			}	
	break;
	case 5:
		if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=4;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=6;
		}
		switch(pcwalk)
			{
			case 1:
			   isWalkON=off;
			   if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcwalk=2;
			    }
			   break;
			case 2:
					isWalkON="[Fast]";
				if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcwalk=3;
				}
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcwalk=1;
				}
				break;
				case 3:
					isWalkON="[Faster]";
				if((pad.Buttons & PSP_CTRL_RIGHT))
				{
					pcwalk=4;
				}
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcwalk=2;
				}
				break;
			case 4:
				isWalkON="[Slow]";
				if((pad.Buttons & PSP_CTRL_LEFT))
				{
					pcwalk=3;
				}
				break;
		}
		break;
		case 6:
		if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=5;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=7;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isibodieON=off;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isibodieON=on;
		}
	break;
			case 7:
		if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=6;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=8;
		}
	if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isptsON=off;
		}
	if((pad.Buttons & PSP_CTRL_RIGHT))
		{
			isptsON="12345678";
		}
	break;
			case 8:
	    if((pad.Buttons & PSP_CTRL_UP))
		{
			pccheat=7;
		}
		if((pad.Buttons & PSP_CTRL_DOWN))
		{
			pccheat=8;
		}
	    if((pad.Buttons & PSP_CTRL_LEFT))
		{
			isSjON=off;
		}
     	if((pad.Buttons & PSP_CTRL_RIGHT))
 		{
			isSjON="[ON] (UP=Bigger, Down=Smaller, Right=Normal)";
		}
	}
	
	
}
 void cheatenable()
{
	if(isInfiniteHealthON==on)
	{
		*InfiniteHealth1=0x43020000;
		*InfiniteHealth2=0x43020000;
		*InfiniteHealth3=0x43480000;
	}
	if(isInfiniteForceON==on)
	{
		*InfiniteForce1=nop;
		*InfiniteForce2=nop;
		*InfiniteForce3=nop;
	}
	if(isFastPowerRegenON==on)
	{
		*FastPowerRegen1=nop;
		*FastPowerRegen2=nop;
	}
	if(isFlashON=="[Faster]")
	{
		*flash=0x40300000;
	}
    if(isFlashON=="[Fast]")
	{
		*flash=0x3Fc00000;
	}
	if(isFlashON=="[Slow]")
	{
		*flash=0x3f000000;
	}
	if(isFlashON=="[Slower]")
	{
		*flash=0x3eb00000;
	}
	if(isFlashON=="[OFF]"&&*flash!=0x3f800000)
	{
		*flash=0x3f800000;
	}
	if(isWalkON=="[Faster]")
	{
		*walk=0x3c044004;
	}
	if(isWalkON=="[Fast]")
	{
		*walk=0x3c043Fc7;
	}
	if(isWalkON=="[Slow]")
	{
		*walk=0x3c043f00;
	}
	if(isWalkON=="[OFF]"&&*walk!=0x3c043f80)
	{
		*walk=0x3c043f80;
	}
	if(isptsON=="12345678")
	{
		*pts=0x00BC614E;
	}
	if(isibodieON==on)
	{
		*ibodie=0x3c043f80;
	}
	if(isibodieON==off&&*ibodie!=0x3c04bf80)
	{
		*ibodie=0x3c04bf80;
	}
	if(isSjON!=off)
	{
		*saberj1=0x0e200180;
		*saberj2=0x3c0808c8;
		*saberj3=0x8508cb64;
		*saberj4=0x3c193c04;
		*saberj5=0x37383f80;
		*saberj6=0x34090010;
		*saberj7=0x340a0040;
		*saberj8=0x340b0020;
		*saberj9=0x3c0c08a5;
		*saberj10 = 0x15090003;
		*saberj11 = 0x8d8d9e24;
		*saberj12 = 0x25ae0001;
		*saberj13 = 0xad8e9e24;
		*saberj14 = 0x150a0003;
		*saberj15 = 0x00094902;
		*saberj16 = 0x01a97022;
		*saberj17 = 0xad8e9e24;
		*saberj18 = 0x150b0002;
		*saberj19 = 0x00000000;
		*saberj20 = 0xad989e24;
		*saberj21 = 0x03e00008;
		*saberj22 = 0x0E2E1BB8;
	}


}

//Draw the menu
int drawmeup()
{
while(menudrawn)
{
	cocksped();
	startMenu();
	pad.Buttons=0;
	refresh();
	if(pad.Buttons & PSP_CTRL_CIRCLE)
	{
	//Return the standard VRAM
    sceDisplaySetFrameBufferInternal(0, 0, 512, 0, 1);
      
    //Allow the game to receive input
    sceCtrlSetButtonMasks(0x10000, 0); // Unset HOME key
    sceCtrlSetButtonMasks(0xFFFF, 0);  // Unset mask
	resume_game(thid);//Resumey
	if(menudrawn) menudrawn=0;
	continue;
	}
	else if((pad.Buttons & PSP_CTRL_START) && (pad.Buttons & PSP_CTRL_SELECT))
	{
	running=0;
	menudrawn=0;
	}
drawmenu();
				setenable();
//Tab Display
	switch(pctab)
	{
	case 1:
		if(pad.Buttons & PSP_CTRL_RTRIGGER)
		{
			pctab=2;
pspDebugScreenClear();
		}
	break;
	case 2:
		 if(pad.Buttons & PSP_CTRL_LTRIGGER)
		{
			pctab=1;
			pspDebugScreenClear();
		}
	break;
	}

	pad.Buttons=0;
	refresh();
	sceKernelDelayThread(10000);
}
}


int drawmenu()
{
	pspDebugScreenSetXY(0, 0);
	tcolor(yellow);
	print("==============||http://www.psphs.com||======||SonniE||==============");
	tcolor(red);
	print("--------------------------------------------------------------------");
    //Draw Tabsprint
	print("======================");
	if(pctab==1){tcolor(yellow);}
	else{tcolor(dred);}
	print("[CODES]");
	tcolor(red);print("=======");
	if(pctab==2){tcolor(yellow);}
	else{tcolor(dred);}
	print("[OPTIONS]");
	pspDebugScreenSetTextColor(red);
	print("======================");
	pspDebugScreenSetTextColor(red);
	print("\n--------------------------------------------------------------------");//END DRAW TABS
	refresh();
	if(pctab==1){codedisp();}
	if(pctab==2){setdisp();}
	/*
	if(pctab==1){codedisp();}
	if(pctab==2){imposterdisp();}
	if(pctab==3){settingdisp();}
	*/ 
	sceKernelDelayThread(100000);
	refresh();



}

int menucheck()
{
if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_VOLUP))
{
if(!menudrawn) menudrawn=1;
}
if(menudrawn)
{
//Stop the game from receiving input (USER mode input block)
      sceCtrlSetButtonMasks(0xFFFF, 1);  // Mask lower 16bits
      sceCtrlSetButtonMasks(0x10000, 2); // Always return HOME key
      
      //Setup a custom VRAM
    	sceDisplaySetFrameBufferInternal(0, vram, 512, 0, 1);
    	pspDebugScreenInitEx(vram, 0, 0);
}
drawmeup();
}


int mainThread(){
    signed int fd;
	running=1;
	
	sceKernelDelayThread(15000000);
	while(!sceKernelFindModuleByName("sceKernelLibrary"))
	sceKernelDelayThread(100000);
	sceKernelDelayThread(100000);
	do{
		fd=sceIoOpen("disc0:/UMD_DATA.BIN", PSP_O_RDONLY, 0777); 
		sceKernelDelayThread(10000);
	} while(fd<=0);
	
	sceIoRead(fd, gameId, 10);
	sceIoClose(fd);
  //Game ID Check
	if(strncmp(gameId, "ULUS-10345", 10)){               
		running=0;
		if(running) {
		pspDebugScreenInit();
		pspDebugScreenInitEx(0x44000000, 0, 0);
		vram=NULL;
		}
	}
	while(running){
	
	if(vram == NULL)
    {
      //Has the HOME button been pressed?
	
      unsigned int a_address=0;
      unsigned int a_bufferWidth=0;
      unsigned int a_pixelFormat=0;
      unsigned int a_sync;
   	  sceDisplayGetFrameBufferInternal(0, &a_address, &a_bufferWidth, &a_pixelFormat, &a_sync);
     
      if(a_address)
      {
        vram=(void*)(0xA0000000 | a_address);
      }
      else
      {
        sceDisplayGetMode(&a_pixelFormat, &a_bufferWidth, &a_bufferWidth);
        pspDebugScreenSetColorMode(a_pixelFormat);
      }
	  sceKernelDelayThread(1500);
      continue;
    }
				pad.Buttons=0;
				refresh();
				menucheck();
				cheatenable();
				sceKernelDelayThread(10000);
		
	}	
	sceDisplaySetFrameBufferInternal(0, 0, 512, 0, 1);
	sceCtrlSetButtonMasks(0x10000, 0);
	sceCtrlSetButtonMasks(0xFFFF, 0);
	sceKernelTerminateThread(thid);
}

int _start(SceSize args, void *argp){


	thid=sceKernelCreateThread("Main", &mainThread, 0x18, 0x512, 0, NULL);
	if(thid >= 0) sceKernelStartThread(thid, 0, NULL);	
	return 0;
	
}

int _stop(SceSize args, void *argp){

	running=0;
 	sceKernelTerminateThread(thid);
	return 0;
	
}
