//sjsz_ling.c  试剑山庄令牌  by lsxk@hsbbs 2008/06/27

#include <ansi.h>
#include <combat.h>
inherit ITEM;

void create()
{
       set_name(HIY"试剑令"NOR, ({ "shijian ling","ling"}));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
               set("long",HIY"这是一块试剑山庄的试剑令，据说可以使用此物进入山庄探宝！\n"NOR);
		set("value", 0);
        set("treasure",1);
		set("material", "wood");
		set("no_drop",1);
		set("no_give",1);
		set("no_get",1);
	    set("no_steel",1);
		set("sjsz",1);//试剑山庄标记，以防假冒
	 }
}
