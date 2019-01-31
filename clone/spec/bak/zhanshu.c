// zhanshu.c 独孤战书 For hs 9jian quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIW"独孤战书"NOR, ({ "zhanshu"}));
    set("long",HIW"这是一封战书，收信人的名字已然看不清了，但落款却是清晰的四个大字——“独孤求败”！\n"NOR);

    set("unit","封");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/zhanshu");
    set("rest",3);
    set("desc","据说是剑魔独孤求败下的战书！");
    set("credit",800);
	setup();
}

void init()
{
    add_action("do_yuedu","yuedu");
  
}

int do_yuedu(string arg)
{
	object me=this_player();
	
	    
    if (arg!="zhanshu")
                    return notify_fail("你要阅读什么?\n");
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

    me->set_temp("sj_credit/quest/hs/jiujian",1);
    write(HIW"你阅读着独孤战书，部分已经看不清了，但是你却看到：\n"NOR);
    write(HIR"\n    吾纵横江湖一生，从无对手，欲求一败而不可，呜呼悲哉！\n难道这普天之下，莫非真没有我这"HIW"独孤九剑"HIR"的对手了么？\n\n"NOR);
    write(HIW"你当下大骇，喃喃念道“独孤九剑，独孤九剑。。”，难道这天下真有如此高明的剑法么？\n"NOR);
    write(HIW"随即，你淡然一笑，心想，定是哪个欺世之辈先声夺人之计，绝无可信而言，顺手便将战书扔在了一旁！\n"NOR);
	degree();
	return 1;
}	 
