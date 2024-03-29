#ifndef __ANYMOTEKEY_H__
#define __ANYMOTEKEY_H__

typedef enum
{
	ANYMOTE_SOFTLEFT=1,
	ANYMOTE_SOFTRIGHT=2,
	ANYMOTE_HOME=3,
	ANYMOTE_BACK=4,
	ANYMOTE_CALL=5,
	ANYMOTE_ENDCALL=6,
	ANYMOTE_0=7,
	/*...*/
	ANYMOTE_9=16,
	ANYMOTE_STAR=17,
	ANYMOTE_POUND=18,
	ANYMOTE_DPADUP=19,
	ANYMOTE_DPADDOWN=20,
	ANYMOTE_DPADLEFT=21,
	ANYMOTE_DPADRIGHT=22,
	ANYMOTE_DPADCENTER=23,
	ANYMOTE_VOLUMEUP=24,
	ANYMOTE_VOLUMEDOWN=25,
	ANYMOTE_POWER=26,
	ANYMOTE_CAMERA=27,
	ANYMOTE_CLEAR=28,
	ANYMOTE_A=29,
	/*...*/
	ANYMOTE_Z=54,
	ANYMOTE_TAB=61,
	ANYMOTE_SPACE=62,
	ANYMOTE_SYM=63,
	ANYMOTE_EXPLORER=64,
	ANYMOTE_ENVELOPE=65,
	ANYMOTE_FOCUS=80,
	ANYMOTE_PLUS=81,
	ANYMOTE_MENU=82,
	ANYMOTE_SEARCH=84,
	ANYMOTE_PLAYPAUSE=85,
	ANYMOTE_STOP=86,
	ANYMOTE_NEXTSONG=87,
	ANYMOTE_PREVIOUSSONG=88,
	ANYMOTE_REWIND=89,
	ANYMOTE_FORWARD=90,
	ANYMOTE_MUTE=91,
	ANYMOTE_PAUSE=95,
	ANYMOTE_PROGRAMMUP=96,
	ANYMOTE_PROGRAMMDOWN=97,
	ANYMOTE_INFO=103,
	ANYMOTE_FULLSCREEN=104,
	ANYMOTE_FAVORITES=110,
	ANYMOTE_ESC=112,
	ANYMOTE_CHANELUP=117,
	ANYMOTE_CHANELDOWN=118,
	ANYMOTE_TV=120,
	ANYMOTE_DVR=121,
	ANYMOTE_GUIDE=122,
	ANYMOTE_PLAY=126,

	ANYMOTE_RED=384,
	ANYMOTE_GREEN=385,
	ANYMOTE_YELLOW=386,
	ANYMOTE_BLUE=387,
	ANYMOTE_TVONOFF=393,
	ANYMOTE_TVSWITCHINPUT=394,
	ANYMOTE_AVONOFF=395,
	ANYMOTE_BDEJECT=398,
	ANYMOTE_BDPOPUP=399,
	ANYMOTE_BDTOPMENU=400,
	ANYMOTE_SETTINGS=401,
} anymotekeycode;

#endif