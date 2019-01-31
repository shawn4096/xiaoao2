// /u/beyond/hangzhou/jingcisi.c 净慈寺
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIW"净慈寺"NOR);
        set("long", @LONG
净慈寺有前，中，後三殿，以中间的大雄宝殿最为壮观。大雄宝殿，外
观两层，黄色琉璃瓦屋顶，特别显的精美宏伟。寺廊的钟声在苍烟暮霭中回
荡，抑扬动听，这就是西湖十景之一“南屏晚钟”的来历。
LONG
);
	set("objects",([
			__DIR__"npc/you1" : 2,
			__DIR__"npc/kumu" : 1,
			
	]));
        set("exits", ([
			"southeast" : __DIR__"yuhuang",
			"northwest" : __DIR__"hubian1",
		]));
        set("coor/x",110);
	    set("coor/y",-360);
	    set("coor/z",0);
	    setup();
}

int init()
{
	object me;
	me=this_player();
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingcisi"))
	{
		
		message_vision(HIR"你刚进门就听到里面似乎有女声，且听的有人很是不情愿地说道，“你根本不是那道人的对手”\n"NOR,me);
		message_vision(HIC"\n但你毕竟是我的侄儿，我这儿有书信一封，你去嘉兴华法寺找我师弟焦木大师，让他暂时收留你，躲一躲也好！\n"NOR,me);
		me->set_temp("quest/射雕英雄传/江南七怪/findkumu",1);
		
		me->set("quest/射雕英雄传/江南七怪/findkumu",1);

		me->delete_temp("quest/射雕英雄传/江南七怪/jingcisi");
	}

}
