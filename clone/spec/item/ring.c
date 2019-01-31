
#include <ansi.h>
#include <armor.h>

inherit FINGER;

#include "token.h"

string t_power(int i)
{
	if( i >= 90 )	return HIM"紫色级首饰(超级)"NOR;
	if( i >= 70 )	return HIR"红色级首饰(高级)"NOR;	
	if( i >= 50 )	return HIY"黄色级首饰(很好)"NOR;
	if( i >= 40 )	return HIC"蓝色级首饰(不错)"NOR;		
	if( i >= 30 )	return HIW"白色级首饰(一般)"NOR;		

	return "不值一提";
}

void create()
{	
	int i;
	set_name(HIW"白金钻戒"NOR, ({ "ring" }) );
	set_weight(100);
	set("unit", "个");
	set("value", 3000000);
	set("no_get",1);
	set("no_drop",1);
	set("armor_type", "token_finger");
	set("armor_prop/armor",15+random(20));
	set("armor_prop/parry",15+random(20));
	set("armor_prop/dodge",15+random(20));
	i=this_object()->query("armor_prop/armor")+this_object()->query("armor_prop/parry")+this_object()->query("armor_prop/dodge");
	set("long","一个"HIW"白金"NOR"制成的戒指,还镶着一颗硕大的"HIW"钻石"NOR"闪耀着引人夺目的光彩。\n这个首饰看起来综合评价为"+t_power(i)+"\n在它的内圈刻着一行铭文:\n");

	//write("i="+i);
	setup();

}

void init()
{
	add_action("do_discard","discard");
	token_reload();
}