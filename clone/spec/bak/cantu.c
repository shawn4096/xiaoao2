// cantu.c 苗家剑法残图 For 雪山飞狐之苗家剑法 quest by lsxk@hsbbs /2007/7/20
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIY"苗家剑法残图"NOR, ({"cantu","mjjf cantu"}));
    set("long",YEL"这是一卷记录了苗家剑法的残图,图上的剑招已经相当模糊,你基本无法从中学到任何有用东西。\n"NOR);

    set("unit","卷");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/cantu");
    set("rest",3);
    set("desc","记录苗家剑法精髓的一卷图解!");
    set("credit",300);
	setup();
}

void init()
{
    add_action("do_fanyue","fanyue");
  
}

int do_fanyue(string arg)
{
	object me=this_player();
	
	    
    if (arg!="mjjf cantu")
                    return notify_fail("你要翻阅什么?\n");
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

    me->set_temp("sj_credit/quest/public/mjjf",1);
    write(HIM"你反复翻阅这卷残图,觉得如果有人能略微指导一下,你应该能比较轻松地学会大多数精妙的剑招!\n"NOR);
	degree();
	return 1;
}	 
