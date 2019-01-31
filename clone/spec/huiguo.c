//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIM"悔过舍利"NOR, ({ "sarira"}));
	set("long","这是一颗来自释迦摩尼的"HIM"指骨舍利子"NOR"，据说对着它悔过("HIY"pray sarira"NOR")会让人悔过自新。\n");

	set("unit","颗");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",1);
	set("flag","spec/sarira");
        set("rest",1);
	set("desc","可以洗心革面。");
        set("credit",5000);
	
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
      		return notify_fail("你要悔过什么?\n");
      		
	if (arg!="sarira")
      		return notify_fail("你要悔过什么?\n");
      	
      	if (me->query("shen")>0)
      		return notify_fail("你不是已经洗心革面了?\n");
      		
      	if (!restrict()) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}   


	me->set("shen",100);
	me->apply_condition("job_busy",40);// 15分钟 避免频繁来回切换
	
	write(HIY"你把"HIM"悔过舍利"HIY"轻轻的贴在额前，默默的忏悔以往的错误过失......\n"NOR);
	write(HIW"你觉得自己的心情好象变好了。\n"NOR);
	degree();
	return 1;
}	 
