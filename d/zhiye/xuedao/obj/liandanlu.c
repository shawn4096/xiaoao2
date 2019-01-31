// qinxiu-jiasha.c
 
#include <ansi.h> 
//#include <armor.h> 
 
inherit ITEM; 
 
void create() 
{ 
        set_name( RED "炼丹炉" NOR, ({ "liandan lu", "lu" }) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "个"); 
                set("long", "这是一个神秘的炼丹炉，是血刀门私有产品，阵阵幽香真是从这炉中发出。\n"); 
                set("value", 100000); 
				set("no_get", 1); 
				set("no_give", 1); 
				set("no_sell", 1); 
                set("material", "steel"); 
                set("armor_prop/armor", 50); 
        } 
        setup(); 
} /*
void init()
{
	add_action("do_open","open");
	add_action("do_cloese","close");
	//add_action("do_jilian","jilian");
	add_action("do_liandan","liandan");

}
int do_open(string arg)
{
	object me;
	me=this_palyer();
	if (!arg||arg!="lu")
	{
		return notify_fail("你要打开什么？");
	}
	if (query_temp("open"))
	{
		return nofiy_fail("此炉已经打开了\n");
	}
	this_object()->set_temp("poen",1);
	tell_object(me,"你打开炼丹炉。\n");
	return 1;
}
int do_close(string arg)
{
	object me;
	me=this_palyer();
	if (!arg||arg!="lu")
	{
		return notify_fail("你要盖上什么？");
	}
	if (query_temp("close"))
	{
		return nofiy_fail("此炉已经盖好了\n");
	}
	this_object()->set_temp("close",1);
	tell_object(me,"你将炼丹炉盖好。\n");
	return 1;
}

int do_liandan(string arg)
{
	object me;
	me=this_palyer();
	if (!arg)
	{
		return notify_fail("你要炼什么？");
	}
	if (arg=="五露丸")
	{
	}
	if (arg=="五肉丸")
	{
	}


	if (query_temp("close"))
	{
		return nofiy_fail("此炉已经盖好了\n");
	}
	this_object()->set_temp("close",1);
	tell_object(me,"你将炼丹炉盖好。\n");
	return 1;
}
*/