//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIC"素质之书"NOR, ({ "sbook"}));
	set("long","这是一本"HIC"素质之书"NOR"，你可以阅读(read)有关增长臂力(str)悟性(int)根骨(con)身法(dex)方面的知识。\n");

	set("unit","本");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",1);
	set("flag","spec/sbook");
	set("desc","暂时性提高一些天赋。");
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
	int i;
	    
	if (!arg)
      		return notify_fail("你要阅读什么知识?\n");
      		
	if (arg!="str" && arg!="dex" && arg!="int" && arg!="con")
      		return notify_fail("你要阅读什么知识?\n");
      	
      	if (me->query_temp("sbook")>9)
      		return notify_fail("你看了看这本书，发现已经没什么好学的了!\n");
      		
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

	i=random(3)+3;
	if (i+query_temp("sbook")>9) i=10-query_temp("sbook");
	
	switch(arg)
	{
		case "int":
			me->add_temp("apply/intelligence",i);
			break;
		case "str":
			me->add_temp("apply/strength",i);
			break;
		case "dex":
			me->add_temp("apply/dexerity",i);
			break;
		case "con":
			me->add_temp("apply/constitution",i);
			break;
	}
	me->add_temp("sbook",i);
	write(HIY"你读完"HIC"素质之书"HIY"发现自己好象变得厉害了一点。\n"NOR);
	degree();
	return 1;
}	 