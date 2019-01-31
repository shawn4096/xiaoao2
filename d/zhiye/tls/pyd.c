//普云洞
//cool@SJ,990605

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",HIY"普云洞"NOR);
	set("long",@LONG
原来这普云阁乃是一个小山洞，一进洞，门就无声无息的关闭了，眼前是
一个天然形成的石甬道，洞的顶上有一条狭长的石缝，光线来自那里，这条道
周围分布着几个山洞，隐隐有些光从洞中透出。
LONG
	);
         
	set("exits", ([
		"out" : __DIR__"lsy",
		"north" : __DIR__"shangyang",
		"northup" : __DIR__"shaoshang",
		"northwest" : __DIR__"guanchong",
		"northeast" : __DIR__"zhongchong",
		"southwest" : __DIR__"shaoze",
		"southeast" : __DIR__"shaochong",
	]));
	set("no_fight",1);
	setup();
}
void init()
{
	object me;
	me=this_player();
	
	message_vision(HIC"屋外的枯荣长老突然喝道；你只能修习一脉，你可要想好了！。\n"NOR, me);

	if (!me->query("liumai_pass") 
		|| me->query("family/family_name") != "天龙寺"
		|| (me->query_skill("liumai-shenjian") && !me->query("quest/tls/yyz/liumai/pass")))
		//|| (me->query("liumai-shenjian")&&!me->query("quest/tls/lmsj/ciqu/pass")))
	{
		message_vision(HIY"枯荣长老突然发现你居然没有通过测试就进来了，顿时大怒，喝道；给我出来！。\n"NOR, me);

		me->move("/d/tls/lsy");	
		return ;
	}

}

int valid_leave(object me, string dir)
{
		
	me=this_player();

	//if (!me->query("quest/tls/liumai/pass"))
	if (!me->query("liumai_pass") )
	{
		me->move("d/tls/road");
		me->unconscious();
		return notify_fail("枯荣长老大喝一声道，“你是怎么进来的？随后一股大力将你送了出去。”\n");
	}
	if ( dir != "out" 
		 && !me->query("quest/tls/yyz/liumai/pass")
		 && me->query_skill("liumai-shenjian",1)>29)
	{
		message_vision(HIC"\n\n枯荣大师在屋外喊道，“别太多不烂，你只能选择一脉，否则会走火入魔。”\n"NOR,me);
		return notify_fail("\n枯荣大师意味深长地说道：目前天龙寺内只有段誉修得全部的六脉神剑。\n");
	}
	
	return ::valid_leave(me, dir);
	
	
}
