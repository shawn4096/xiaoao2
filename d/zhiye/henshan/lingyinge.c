#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "群玉院");
        set("long", @LONG
此处是衡阳城大大有名的群玉院子，在其门首挑着一盏小红灯笼。
院子中一片丝竹和欢笑之声，中间又夹杂着猜枚行令，唱曲闹酒，
当真是笙歌处处，一片升平景象。老板娘便是绯胭。
LONG );
	set("objects", ([
		//__DIR__"npc/feiyan" : 1,
		"/d/hmy/npc/qufeiyan" : 1,

	]));

	set("exits", ([
		"south" : __DIR__"hengyang11",
		"north" : __DIR__"qunyuyuan",

	]));	

	set("no_fight", 1);
	//set("sleep_room", 1);

	setup();
		
}	

void init()
{
	tell_object(this_player(), HIW "\n你一走进群玉院，一串玉环被你走路所带动"
                                   "的风吹得「叮叮」作响。\n\n" NOR);	
}

