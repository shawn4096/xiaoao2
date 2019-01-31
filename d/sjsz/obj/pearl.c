//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIM"幸运珍珠"NOR, ({ "pearl"}));
	set("long","这是一颗采自东海之滨的"HIM"幸运珍珠"NOR"，据说对着它祈祷("HIY"pray pearl"NOR")会给人带来好运。\n");

	set("unit","颗");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",1);
	set("flag","spec/pearl");
        set("rest",100);
	set("desc","可以带来好运。");
        set("credit",100);
	
	setup();
}

void init()
{
	add_action("do_pray","pray");
  
}

int do_pray(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("你要祈祷什么?\n");
      		
	if (arg!="pearl")
      		return notify_fail("你要祈祷什么?\n");
      	
      	if (me->query("kar")>29)
      		return notify_fail("你运气已经很好了!\n");
      		
      	if (!restrict()) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}   


	me->set("kar",30);
	
	write(HIY"你把"HIM"幸运珍珠"HIY"轻轻的贴在胸前，默默的向上苍祈福......\n"NOR);
	write(HIW"你觉得自己的运气好象变好了。\n"NOR);
	degree();
	return 1;
}	 
