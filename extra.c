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
void imposter_quickedit()
{
	pspDebugScreenSetXY(1, 6);
	pspDebugScreenSetTextColor(lblue);
	unsigned int *p1 = (unsigned int*) (0x00bc0038+0x08800000);
	int namelength;
	int letcounter = 0;
	int valcounter = 0;
			pspDebugScreenSetXY(1, 7);
			tcolor(red);
			print("Name: ");
		while(letcounter<13)
		{
			unsigned char *letbuffer = (unsigned char*) (offset+letcounter);
			sprintf(namebuffer, " %c ", *letbuffer);
			sprintf(namebuffer2, "%d", strlen(namebuffer));
			if(strlen(namebuffer)==1)
			{
				sprintf(namebuffer, "   ");
			}
			print(namebuffer);
			letcounter++;
		}
		
		pspDebugScreenSetXY(1, 8);
		print("Hex:  ");
		while(valcounter<13)
		{
			unsigned char *letbuffer = (unsigned char*) (offset+valcounter);
			sprintf(namebuffer1, "%02hX ", *letbuffer);
			print(namebuffer1);
			valcounter++;
		}
	unsigned char *let1 = (unsigned char*) (offset);
	unsigned char *let2 = (unsigned char*) (offset+1);
	unsigned char *let3 = (unsigned char*) (offset+2);
	unsigned char *let4 = (unsigned char*) (offset+3);
	unsigned char *let5 = (unsigned char*) (offset+4);
	unsigned char *let6 = (unsigned char*) (offset+5);
	unsigned char *let7 = (unsigned char*) (offset+6);
	unsigned char *let8 = (unsigned char*) (offset+7);
	unsigned char *let9 = (unsigned char*) (offset+8);
	unsigned char *let10 = (unsigned char*) (offset+9);
	unsigned char *let11 = (unsigned char*) (offset+10);
	unsigned char *let12 = (unsigned char*) (offset+11);
	unsigned char *let13 = (unsigned char*) (offset+12);
	unsigned char *let14 = (unsigned char*) (offset+13);
	unsigned char *let15 = (unsigned char*) (offset+14);
	unsigned char *let16 = (unsigned char*) (offset+15);
	//Hex
	pspDebugScreenSetXY(7, 9);
	tcolor(pcletselect);
	switch(pclet)
	{
		case 1:
			print("^                              ");
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				pclet=2;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let1=*let1+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let1=*let1-0x10;
			}
			}
			break;
		case 2:
			
			print(" ^                             ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=1;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=3;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let1=*let1+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let1=*let1-0x01;
			}
			}
			break;
		case 3:
			print("   ^                           ");
				if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=2;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=4;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let2=*let2+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let2=*let2-0x10;
			}
			}
			break;
		case 4:
		print("    ^                          ");

			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=3;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=5;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let2=*let2+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let2=*let2-0x01;
			}
			}
			break;
		case 5:
		print("      ^                        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=4;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=6;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let3=*let3+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let3=*let3-0x10;
			}
			}
			break;
		case 6:
			print("       ^                       ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=5;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=7;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let3=*let3+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let3=*let3-0x01;
			}
			}
			break;
		case 7:
						print("         ^                     ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=6;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=8;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let4=*let4+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let4=*let4-0x10;
			}
			}
			break;
			case 8:
			print("          ^                    ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=7;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=9;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let4=*let4+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let4=*let4-0x01;
			}
			}
			break;
			case 9:
			print("            ^                   ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=8;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=10;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let5=*let5+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let5=*let5-0x10;
			}
			}
			break;
			case 10:
			print("             ^                  ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=9;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=11;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let5=*let5+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let5=*let5-0x01;
			}
			}
			break;
			case 11:
			print("               ^                ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=10;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=12;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let6=*let6+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let6=*let6-0x10;
			}
			}
			break;
			case 12:
			print("                ^               ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=11;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=13;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let6=*let6+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let6=*let6-0x01;
			}
			}
			break;
			case 13:
			print("                  ^             ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=12;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=14;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let7=*let7+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let7=*let7-0x10;
			}
			}
			break;
			case 14:
			print("                   ^            ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=13;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=15;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let7=*let7+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let7=*let7-0x01;
			}
			}
			break;
			case 15:
			print("                     ^          ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=14;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=16;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let8=*let8+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let8=*let8-0x10;
			}
			}
			break;
			case 16:
			print("                      ^         ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=15;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=17;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let8=*let8+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let8=*let8-0x01;
			}
			}
			break;
			case 17:
			print("                        ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=16;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=18;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let9=*let9+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let9=*let9-0x10;
			}
			}
			break;
			case 18:
			print("                         ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=17;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=19;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let9=*let9+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let9=*let9-0x01;
			}
			}
			break;
case 19:
			print("                           ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=18;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=20;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let10=*let10+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let10=*let10-0x10;
			}
			}
			break;
			case 20:
			print("                            ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=19;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=21;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let10=*let10+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let10=*let10-0x01;
			}
			}
			break;
			case 21:
			print("                              ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=20;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=22;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let11=*let11+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let11=*let11-0x10;
			}
			}
			break;
			case 22:
			print("                               ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=21;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=23;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let11=*let11+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let11=*let11-0x01;
			}
			}
			break;
			case 23:
			print("                                 ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=22;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=24;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let12=*let12+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let12=*let12-0x10;
			}
			}
			break;
			case 24:
			print("                                  ^        ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=23;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=25;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let12=*let12+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let12=*let12-0x01;
				
			}
			}
			break;
			case 25:
			print("                                    ^      ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=24;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=26;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let13=*let13+0x10;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let13=*let13-0x10;
				
			}
			}
			break;
			case 26:
			print("                                     ^     ");
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				
				pclet=25;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				
				pclet=26;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(pcletselect==red)
				{
					pcletselect=yellow;
				}
				else
				{				
					pcletselect=red;
				}
			}
			if(pcletselect==red)
			{
			if(pad.Buttons & PSP_CTRL_UP)
			{
				*let13=*let13+0x01;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				*let13=*let13-0x01;
				
			}
			}
			break;




	}
	}