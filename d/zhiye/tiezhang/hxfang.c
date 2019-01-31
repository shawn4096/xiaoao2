//hxfang.c 后厢房
#include <ansi.h>

inherit ROOM;
string look_hongzao();
int do_naqu(string arg);

void create()
{
	set("short", "后厢房");
	set("long", @LONG
这是大厅后面的一个小房间，虽然也是岩石砌成，但布置的非常舒适。四
壁用挂毯遮住，不露一点石壁的痕迹。屋内转圈摆放了一些椅子，上面铺着厚
厚的软垫，坐上去一定很舒适。这里是帮主处理帮中日常事务的地方。后面通
向后花院。桌子上放了几个碟子，碟子中有很多大红枣(hongzao)。
LONG
	);
	set("exits", ([
		"north" : __DIR__"hhyuan-1",
		"south" : __DIR__"wztang",
	]));
	set("objects", ([
		"/kungfu/class/tiezhang/qqren" : 1,

		__DIR__"npc/yahuan" : 1,
		
// __DIR__"npc/qqren" : 1,
	
		]));
	set("item_desc", ([ 
		"hongzao" : (: look_hongzao :),
	]));
	set("hongzao_count",5+random(10));
	setup();
}
int init()
{
	//
	add_action("do_naqu","na");
}
string look_hongzao()
{
    return
    "\n这碟子中放了很多大红枣，看起来香脆可口，也许你可以尝试拿取些(na)尝尝。"
    "\n";
}

int do_naqu(string arg)
{
	int i;
	object ob;
	object me=this_player();
	if (!arg || (arg != "hongzao" && arg != "红枣"))
        {
			if (query("hongzao_count") < 1)
			{
				message_vision ("$N伸手抓向那些红枣，发现红枣已经被别人拿没了！\n",me);
				return 1;
			}
        return notify_fail("你想拿什么？\n");
       // return 1;
		}
		else{
			write(HIC"你悄然伸手，从碟子上将那些红枣抓在手，然后悄悄吃了起来。\n"NOR);
			//this_player()->set_temp("marks/摘2", 1);
			for (i=0;i<1+random(5);i++ )
			{			
				ob=new("/d/tiezhang/obj/zaohe");
				ob->move(me);
				add("hongzao_count", -1);
			}

        return 1;
       }


}
