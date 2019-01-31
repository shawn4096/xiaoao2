#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_tiao(string arg);

void create()
{
	  set("short", "广场东");
	  set("long",@long
这里是一个平平开阔的大广场，广场上有昆仑派的弟子在习武，西面仍然
是广场，东面过去就是悬崖了，北面是下山的路。广场一侧埋了数个高低错落
有秩的梅花桩(zhuang)，显然是给门中弟子练习基本腿法之所。
long);
	  set("exits",([
               "northwest" : __DIR__"shanlu04",
               "west" : __DIR__"guangchang",
          ]));
          set("objects",([
                CLASS_D("kunlun") + "/yulingzi" : 1,
				__DIR__"npc/kl-dizi3" :  2,
          ]));
		  set("item_desc", ([
                "zhuang" : "按梅花状错落有致排列一排木桩。\n有弟子正在这些桩上跳跃(tiao)。\n"]));

          set("outdoors", "昆仑");
          setup();
}

void init()
{
	add_action("do_tiao","tiao");
	add_action("do_tiao","jump");
}

int do_tiao(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("leg", 1);
	if (!arg||arg!="zhuang")
		return notify_fail("你上蹿下跳要做什么？\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("你太累了，先歇歇吧！\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
		if (level < 100) 
		{
			message_vision("$N吸了口气，纵向梅花桩，由低到高走了一圈，感觉基本腿法有些收获。\n", me);
			me->improve_skill("leg", me->query_int() / 4);
		}
		else
			message_vision("$N微一运劲，轻轻跃到梅花桩上，可惜对$P而言已经无法提高了。\n", me);
		return 1;
}