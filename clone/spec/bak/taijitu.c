// taijitu.c 太极图 For wd taiji quest by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (WHT"太极图"NOR, ({ "taiji tu"}));
    set("long",WHT"这是一副太极图，上面刻满了太极口诀要领，包括太极拳，太极剑。你觉得似乎可以从中领悟到什么。\n"NOR);

    set("unit","副");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/taijitu");
    set("rest",3);
    set("desc","似乎是武当派开山祖师张三丰之物!");
    set("credit",800);
	setup();
}

void init()
{
    add_action("do_yanjiu","yanjiu");
  
}

int do_yanjiu(string arg)
{
	object me=this_player();
	
	    
    if (arg!="taiji tu")
                    return notify_fail("你要研究什么?\n");
      	
   	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

    me->set_temp("sj_credit/quest/wd/taiji",1);
    write(HIG"你静心研究着"WHT"太极图"HIG"突然发觉自己明白了不少太极深意!\n"NOR);
	degree();
	return 1;
}	 
