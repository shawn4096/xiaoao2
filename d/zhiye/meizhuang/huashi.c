// Room: /d/meizhuang/huashi.c
// By Lklv
// add by sohu#xojh 泼墨
#include <ansi.h>
inherit ROOM;
int do_guanmo(string arg);
void create()
{
	set("short", "画室");
	set("long", @LONG
这是一间画室，画室正中随意摆放着几把椅子，四壁上挂着几幅年代久远
的卷轴。走进卷轴细看，只见一幅幅水墨丹青，笔法鬼斧神工、龙蛇飞舞，显
然出自大家之手，正中厅挂着一副水墨仙人背面图画(hua)，墨意淋漓，笔力
雄健,让人忍不住开始观摩(guanmo)起来。

LONG
	);
	set("exits", ([
		"east" : __DIR__"huilang6",
	]));

        set("objects", ([
                __DIR__"npc/danqingsheng" : 1,
        ]));
    set("item_desc", ([
          "画" :  HIC"画中所绘是一个仙人的背面，墨意淋漓，笔力雄健。你虽不懂画， \n"+
							"却也知确是力作，又见画上题款是：“丹青生大醉后泼墨”八字。\n"+
							"端的是笔法森严，一笔笔便如长剑的刺划。尤其是画上这个"HIG"‘醉’"HIC"字。\n"+
		 					"这字中画中，更似乎蕴藏着一套极高明的剑术。\n"NOR,
		  "hua" :  HIC"画中所绘是一个仙人的背面，墨意淋漓，笔力雄健。你虽不懂画， \n"+
							"却也知确是力作，又见画上题款是：“丹青生大醉后泼墨”八字。\n"+
							"端的是笔法森严，一笔笔便如长剑的刺划。尤其是画上这个"HIG"‘醉’"HIC"字。\n"+
							"这字中画中，更似乎蕴藏着一套极高明的剑术。\n"NOR,
       ]));
	setup();
}
void init()
{
	
        add_action("do_guanmo", "guanmo"); 
       
}

int do_guanmo(string arg)
{
    int j;
	
	object me=this_player();
    if (me->query("family/family_name")!="日月神教")
       return notify_fail("你不是我神教弟子，鬼鬼祟祟来此作甚？\n");
	if (!arg||arg!="醉")
	   return notify_fail("你傻站哪儿干什么？\n");
	if (!me->query_temp("qxwxj/pomoask"))
	   return notify_fail("这是丹青生的画室，陌生人不要乱观摩！\n");
	if (me->query("quest/hmy/qxwxj/pomo/pass"))
	   return notify_fail("你已经彻底了解泼墨披麻剑法，再看不出任何东西！\n");
    if (time()-me->query("quest/hmy/qxwxj/pomo/time")<86400)
       return notify_fail("你来的也太勤快点了！\n");
    j=random(me->query("kar"));
	
	if (arg=="醉"||arg=="剑意")
    {
       message_vision(HIW"$N观看这幅水墨画，见图中墨意淋漓，纵横捭阖，气势不凡，笔力雄健。\n"NOR,me);
	   message_vision(HIC"$N当目光聚焦在这个“醉”字后，忽觉一股剑意如长枪大戟，迎面而来！\n"NOR,me);
	   if (me->query("kar")<31
		&& j>=25
		&& me->query("int")>=25)
	    {
          
	      message_vision(HIY"而当你将目光“丹青生大醉后泼墨”这八个字后，觉得这几个字似乎有些不同。\n"+
						"端的是笔法森严，一笔笔便如长剑的刺划。尤其是画上这个‘醉’字，更是畅快淋漓至极！\n"NOR,me);
	      message_vision(HIC"$N恭喜你，你无意中领悟丹青生的泼墨披麻剑法绝技的真谛。\n"NOR,me);
	  
	   log_file("quest/pomopimajian",sprintf("%s(%s) 在梅庄画室，无意中领悟泼墨披麻剑的绝技。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/pomo/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/qxwxj/pomo/pass",1);
	   me->delete_temp("qxwxj/pomoask");
	   me->delete_temp("givehua");
	   me->start_busy(1);
	   return 1;
	  }
	   else {
		message_vision(HIY"\n$N虽然知道这幅画不同寻常，但看了半天却一时之间却是难以理解。看来你还是有待于重新来这领悟学习了。\n"NOR,me);
	    log_file("quest/pomopimajian",sprintf("%s(%s) 领悟泼墨披麻剑的绝技失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/pomo/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/qxwxj/pomo/fail",1);
		me->set("quest/hmy/qxwxj/pomo/time",time());
		me->delete_temp("qxwxj/pomoask");
	    me->delete_temp("givehua");
		me->start_busy(1);
        return 1;
	   }
	
    }

}


