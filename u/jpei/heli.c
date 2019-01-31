//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
        set_name (HIR"新婚贺礼"NOR, ({ "gift","he li"}));
        set("long","这是一份紫檀Master拜送的"HIR"新婚贺礼"NOR"，不知道装了些什么东西。你可以拆开(chai gift)看一下\n");

	set("unit","份");
	set_weight(100);
	set("value",3000);
        set("no_give",1);
        set("no_drop",1);
	set("flag","spec/ebook1");
        set("degree",1);
        set("desc","新婚贺礼。");
        set("credit",1);
	setup();
}

void init()
{
	add_action("do_read","chai");
  
}

int do_read(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("你要拆开什么?\n");
      		
	if (arg!="gift")
      		return notify_fail("你要拆开什么?\n");
      	
      		
     if(me->query("buyvip")){
                 me->add_condition("db_exp", 1000);
                 me->add_temp("apply/attack",100);
                 me->add_temp("apply/damage",100);
}
 


  	else
                me->add_condition("db_exp", 1000);
	
        write(HIY"你拆开"HIR"贺礼"HIY"一看，里面居然装了半截砖头，不由得心下大怒！\n"NOR);

	degree();
	return 1;
}	 
