#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_strike(string arg);
void create()
{
	  set("short", "广场西");
	  set("long",@long
这里是一个平平开阔的大广场，广场上有昆仑派的弟子在习武，东面仍然
是广场，西面过去就是悬崖了，北面是下山的路。在这个大广场边上摆放了一
排的人字桩(zhuang),上面绑了厚厚的棉垫，斑驳陆离，似乎渗透了不少的鲜血
显然是有人经常在此练习拳法所致。
long);
	  set("exits",([
             "northeast" : __DIR__"shanlu04",
             "east" : __DIR__"guangchang",
          ]));
          set("objects",([
	       __DIR__"npc/kl-dizi3" :  1,
          ]));
        set("item_desc", ([
                "zhuang" : "一排九个人字桩，排成一排，上面绑了绳子和棉花。\n有弟子正在挥拳打（da）向这些人字桩。\n"]));

          set("outdoors", "昆仑");
          setup();
}

void init()
{
	add_action("do_strike","cuff");
	add_action("do_strike","da");
}

int do_strike(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("cuff", 1);
	if (!arg||arg!="zhuang")
		return notify_fail("你要击打什么？\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("你太累了，先歇歇吧！\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
		if (level < 100) 
		{
			message_vision("$N吸了口气，耸身作势，握拳向人字桩上击去。\n", me);
			me->improve_skill("cuff", me->query_int() / 3);
		}
		else
			message_vision("$N微一运劲，将人字桩击飞，这根木桩对$P而言已经无法提高了。\n", me);
		return 1;
}