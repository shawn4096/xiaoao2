//

#include <ansi.h>


inherit SPEC;

void create()
{
	set_name (HIW"正神丸"NOR, ({ "zhengshen wan","wan"}));
	set("long","这是一颗"HIW"正神丸"NOR"，你可以服(fu)下它提高你的正神值。\n");

	set("unit","颗");
	set_weight(100);
	set("value",3000000);
  set("no_give",1);
  set("no_drop",1);	
  set("no_get",1);
	set("degree",1);
	set("flag","spec/addshen");
	set("rest",1);
	set("desc","提高200k正神。");
  set("credit",100);                  
	setup();
}

void init()
{
	add_action("do_eat","eat");
	add_action("do_eat","fu");    
}

int do_eat(string arg)
{
	object me=this_player();
	
	if (!arg)
		return notify_fail("你要服用什么?\n");
	    
	if (arg!="zhengshen wan" && arg!="wan")
		return notify_fail("你要服用什么?\n");
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
    
	me->add("shen", 200000);

 
        write(HIY"你服下一颗"HIW"正神丸"HIY"顿觉全身洋溢这浩然正气\n"NOR);
        degree(); 
	return 1;
}	 
