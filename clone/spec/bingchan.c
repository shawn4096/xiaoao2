//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIW"朱睛冰蟾"NOR, ({ "bingchan"}));
	set("long",""HIW"一只来自西域的蟾蜍，通体如雪晶莹亮白，眼珠却血
也般红，模样甚是可爱，却也不见有何珍异之处。"NOR"

你可以用它来吸毒("HIY"xidu"NOR")。\n");

	set("unit","只");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);	
	set("degree",1);
	set("flag","spec/bingchan");
	set("desc","可解百毒。");
        set("credit",100);       
	setup();
}

void init()
{
	add_action("do_xidu","xidu");
  
}

int do_xidu()
{
	object me=this_player();
      	
      		
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
	
	if (me->is_busy()) {return notify_fail("你正忙着呢。\n");}
			
	if(!mapp(me->query_conditions_by_type("poison")))
		{return notify_fail("你好象没有中毒吧。\n");}
	
	me->clear_conditions_by_type("poison");
		
	write(HIW"你除去衣物把朱睛冰蟾放在胸口，片刻之间冰蟾就转成黑色，你的脸气也红润了一些。\n"NOR);
	degree();
	return 1;
}	 
