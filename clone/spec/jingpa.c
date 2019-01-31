//flowray 2005.6.16
#include <ansi.h>


inherit SPEC;


void create()
{
	set_name (HIR"鸳鸯锦帕"NOR, ({ "jin pa","jinpa","pa"}));
	set("long",HIM" 一方精心绘绣的锦帕，上面刺着两只白头鸳鸯戏水，旁边绣着几行小令:\n"HIW
   " 【四张机
  鸳鸯织就欲双飞
  可怜未老头先白
  碧波春草
  晓寒深处
  相对浴红衣】\n\n"NOR
 "快点把它归还（"HIY"guihuan"NOR"）给失主吧。\n");

	set("unit","方");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",1);
	set("flag","spec/jingpa");
	set("rest",10);
	set("desc","换取三个时辰的鬼谷算术时间。(VIP专用)");
	set("credit",300);
	setup();
}

void init()
{
	add_action("do_back","guihuan");   
}

int do_back(string str)
{
	object my_object,me = this_player();
	int this_week = time()/86400/7;
	
	if (!me->is_vip())
		return notify_fail("只有贵宾玩家才能使用锦帕。\n");
		
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
	
	if (!str)
		return notify_fail("你要把东西还谁啊？\n");
    
	if (!(my_object = present(str, environment(me))))
		return notify_fail("你要找的人不在这里。去别处找找看吧。\n");
	
	if ( str != "ying gu")
		return notify_fail("这个人好象不是失主吧！\n");
    
	if (!living(my_object))
		return notify_fail("哦，你得先把她弄醒在说。\n");
	
	if (me->query("ggs/left_time")>25200 || me->query("ggs/last_week")!=this_week)
		return notify_fail("你看了看锦帕又把它放回了怀里。\n");
	
		
	me->add("ggs/left_time",10800);
	write("你给瑛姑一方"HIR"鸳鸯锦帕\n"NOR);
	write("瑛姑呢喃到：“可怜未老头先白……头先白……，既然你帮我找回了我孩子的遗物，我自然要传授你更深的鬼谷算术”。\n");
	write("瑛姑给你增加了三个时辰的鬼谷算术时间\n");
	
	degree();
	
	return 1;
}	 