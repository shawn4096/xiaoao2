//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIC"精英之书"NOR, ({ "ebook","book"}));
        set("long","这是一本"HIR"精英之书(珍藏版)"NOR"，阅读("HIY"read"NOR")它能让你象精英一样成长。\n");

	set("unit","本");
	set_weight(100);
	set("value",3000);

	set("degree",1);
	set("flag","spec/ebook");
    set("rest",7);
    set("desc","一定时间内经验加成。");
    set("credit",200);
	setup();
}

void init()
{
	add_action("do_read","read");
  
}

int do_read(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("你要读什么?\n");
      		
	if (arg!="book")
      		return notify_fail("你要读什么?\n");
      	
      		
      	if (!restrict()) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}   

	
	if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 50000);
	else
                me->add_condition("db_exp", 50000);
me->add_temp("apply/attack",100);
me->add_temp("apply/damage",100);
me->add_temp("apply/defense",100);
	
	write(HIY"你细细阅读"HIC"精英之书"HIY"心有所得,做什么都是事半功倍。\n"NOR);

	degree();
	return 1;
}	 
