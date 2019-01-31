// Room: /u/swl/songshan/qgfeng.c

inherit ROOM;

void create()
{
        set("short", "青岗峰");
        set("long", @LONG
瀑布声已渐渐消失，而却景色蓦地开郎了许多，道路两旁，都是松
林，松树高大而笔挺，路也平坦了很多。再往上走就进入五岳剑派嵩山
剑派的核心区域，路旁搭了帐篷，有嵩山弟子正在迎来送往。
LONG);
        set("exits", ([ 
            "southdown" : __DIR__"shanlu3",
            "northup" : __DIR__"qgping",
        ]));
        set("item_desc",([
                "松树" : "一棵棵高大笔挺的松树，枝繁叶茂，有些树枝低的几乎伸手可触。\n",
                "松林" : "一棵棵高大笔挺的松树，枝繁叶茂，有些树枝低的几乎伸手可触。\n",
                "tree" : "一棵棵高大笔挺的松树，枝繁叶茂，有些树枝低的几乎伸手可触。\n",
        ]));
        set("objects", ([ 
            CLASS_D("songshan") + "/di" : 1,
            __DIR__"npc/ssdizi" : 3,
			__DIR__"obj/zhangpeng" : 1,
        ]));
        set("outdoors", "嵩山");
        set("shuzhi",4);
        set("coor/x",50);
  set("coor/y",180);
   set("coor/z",70);
   setup();
}

void init()
{
        object me = this_player();       
   
	    if (me->query_temp("ss/zsb_5"))
			add_action("do_zhe","zhe");
		
}


void reset_shuzhi()
{
        set("shuzhi", 4);
        delete("shuzhi_call_out");
}


int do_zhe(string arg)
{
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (arg == "shuzhi")
        {
            if (query("shuzhi")) 
                {
                        message_vision("$N慌慌张张的爬上树，伸手折下了一根树枝。\n", me);
                        add("shuzhi", -1);
                        if (query("shuzhi") <0)
                                set("shuzhi",0);
                        new(__DIR__"obj/shuzhi")->move(me);
                        me->start_busy(1);
                        me->set_temp("shuzhi",1);
                        return 1;
                }
                else
                {
                        if (!query("shuzhi_call_out"))
                        {
                                remove_call_out("reset_shuzhi");
                                set("shuzhi_call_out", 1);
                                call_out("reset_shuzhi", 500);
                        }
                        return notify_fail("松树已经光秃秃的了，你还想折什么？\n");
                }
        }
        return 0;
}
