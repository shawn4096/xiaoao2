//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (MAG"精英之书"NOR, ({ "ebook","book"}));
	set("long","这是一本天神馊狐赠送给你的一本"MAG"精英之书"NOR"，阅读("HIY"read"NOR")它能让你快速成长。\n");

	set("unit","本");
	set_weight(100);
	set("value",3000);
    set("treasure",1);

	set("degree",1);
	if (this_player()->query("buyvip"))	
		set("rest",2);
	else 
		set("rest",1);
	set("no_give",1);
    set("no_drop",1);
	set("no_get",1);
	set("no_steel",1);
	set("flag","spec/ebook");
    set("desc","一定时间内经验加成。");
    set("credit",1000);
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
      		return notify_fail("你要读什么啊?\n");
      		
	if (arg !="ebook")
			return notify_fail("eee你要读什么?\n"+arg);
      	
    
    if (!restrict()) 
	{
		return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");
	}   

	
	if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);

		else
                me->add_condition("db_exp", 10000);
	
	write(HIY"你细细阅读"HIC"精英之书"HIY"心有所得,做什么都是事半功倍。\n"NOR);

	degree();
	
	return 1;
}	 
