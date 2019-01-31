// shanlu-1.c 瓜架
#include <ansi.h>
//#include <room.h>

inherit ROOM;
string look_hongzao();

void create()
{
   set("short", GRN"瓜架"NOR);
	set("long", @LONG
转过一个小弯，忽然眼前一绿，面前是一片很大的瓜架。在高大的木架旁，
种植着一些蔬菜和瓜类，架子上已爬满了各种植物，从茂密的叶子中，垂下各
种已经成熟的果实，丝瓜，苦瓜，葫芦....还有一些叫不出名称的瓜果也缠杂
在其中。瓜架一侧有几颗枣树，上面结了不少的大红枣(hongzao)。

LONG
);


    set("outdoors", "tiezhang");

	set("exits", ([
		"southeast" : __DIR__"shuijing.c",
		"west" : __DIR__"guangchang.c",
		]));

    set("objects", ([
		__DIR__"npc/qqzhang" : 1,
	]));
	set("item_desc", ([ 
		"hongzao" : (: look_hongzao :),
	]));
	set("no_clean_up", 0);
    set("hulu_count", 10);
	set("hongzao_count", 100);
	setup();
}

void init()
{
        add_action("do_zhai","zhai");
		add_action("do_cai","caizhai");
}

int do_zhai(string arg)
{
        object me = this_player();
        object ob;

        if (me->query_temp("marks/摘1") )
            return notify_fail("你已经摘过了，不要这么贪心！\n");

        if (!arg || (arg != "hulu" && arg != "葫芦"))
        {
        if (query("hulu_count") < 1)
        {
			message_vision ("$N拨开枝叶找来找去，发现葫芦已经被别人摘没了！\n",this_player());
			return 1;
        }
			return notify_fail("你想摘什么？\n");
			return 1;
		}

{
        write("你踮起脚尖，从架子上摘下了一个葫芦。\n");
        this_player()->set_temp("marks/摘1", 1);

            ob=new("/d/tiezhang/obj/qingshui-hulu");
            ob->move(this_player());
            add("hulu_count", -1);

        return 1;
       }
}
string look_hongzao()
{
    return
    "\n这几棵树上长了很多大红枣，也许你可以采摘些(caizhai)下来。"
    "\n";
}

int do_cai(string arg)
{
        object me = this_player();
        object ob;
		int i=0;

       //if (me->query_temp("marks/摘2") )
           // return notify_fail("你已经摘过了，不要这么贪心！\n");

        if (!arg || (arg != "hongzao" && arg != "红枣"))
        {
			if (query("hongzao_count") < 1)
			{
				message_vision ("$N拨开枝叶找来找去，发现红枣已经被别人摘没了！\n",this_player());
				return 1;
			}
        return notify_fail("你想摘什么？\n");
        return 1;
		}
		else{
			write("你爬上枣树，从树子上摘下了很多大红枣。\n");
			//this_player()->set_temp("marks/摘2", 1);
			for (i=0;i<1+random(5);i++ )
			{			
				ob=new("/d/tiezhang/obj/hongzao");
				ob->move(this_player());
				add("hongzao_count", -1);
			}

        return 1;
       }
	
}