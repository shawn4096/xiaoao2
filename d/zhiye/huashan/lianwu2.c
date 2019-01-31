// Room: /d/huashan/lianwu2.c
// Date: Look 99/03/25
#include <ansi.h>
#include <room.h>
inherit ROOM;
int ning_come(object me);
void create()
{
        set("short", "练武场");
        set("long", @LONG
这是华山派的练武场，厚厚的石墙上打有一排排手掌痕迹，地砖已被踩出
一个个脚印。
LONG
        );
        set("no_sleep_room","1");

	 set("objects",([
		__DIR__"npc/shidaizi" : 1,
	 ]));
        set("exits",([
		"south" : __DIR__"wuqiku",
		"west" : __DIR__"celang2",
	 ]));
	 set("outdoors", "华山" );
        set("coor/x",100);
  set("coor/y",-10);
   set("coor/z",80);
   setup();
}

void init()
{ 
	object ning;
	object me=this_player();

    if (me->query_temp("wushuang/askning1"))
    {
		call_out("ning_come",5,me);
    }
}

int ning_come(object me)
{
        message_vision(HIC"$N站在练武场当中，四周一片空寂，施戴子师兄正在哪儿刻苦练功,这时，一道人影飘然而至。\n"NOR,me);
		if (!present("ning zhongze",environment(me)))
		{
			new("/d/huashan/npc/ningzhongze.c")->move(environment(me));
		}
		return 1;

}