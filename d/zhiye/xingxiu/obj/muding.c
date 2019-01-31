#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"神木王鼎"NOR,({ "shenmu wangding", "wangding", "shenmu" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一只雕琢而成的暗黄色小木鼎, 木理之间隐隐泛出红丝。鼎侧有五个铜钱大的圆孔，木鼎齐颈出有一道细缝，似乎上下分为两截。\n");
                set("value", 5);
                set("muding/remaining", 0);                
        }
}

void init()
{
    add_action("do_suck", "suck");
	add_action("do_fire", "dianxiang");
}

int do_suck(string arg)
{
        object me = this_player();

        if ( arg != "blood" || !living(this_player()))
        return notify_fail("你要吸什么？\n");

        if( this_player()->is_busy() )
                return notify_fail("你上一个动作还没有完成, 不能运功练毒。\n");
        if ( me->is_fighting())
        return notify_fail("你在战斗中不能运功练毒。\n");

        if(query("muding/remaining") < 1)
                return notify_fail("木鼎中没有血水了。\n");

        message_vision("$N伸掌将血液接住，盘膝运功，将血液吸入掌内。\n", me);
           me->receive_damage("jing", 10);
           me->receive_damage("jingli", 10);
           me->receive_damage("qi", 15);
           me->receive_damage("neili", 3);

        add("muding/remaining", -1);
        if ((int)me->query_skill("poison", 1) <= 30){
              me->apply_condition("xx_poison", 5);
              return 1;
              }
        if ((int)me->query_skill("poison", 1) > 150 ) return notify_fail("你的毒计已经达到瓶颈，以后只有靠自己修炼了。\n");

        if(random(10) > 6){
			if (me->query("family/family_name")=="星宿派")
			{
			
			  switch(random(3))
			  {
				case 0:
                  me->improve_skill("poison", (int)(me->query("int") / 2));
                  write (RED"你只觉掌中微微一凉，一股阴气顺着脉络侵入脑髓。\n"NOR"你对基本毒技的领会又加深了一些！\n");
                  break;
				case 1:
                  me->improve_skill("chousui-zhang", (int)(me->query("int") / 2));
                  write (RED"你只觉掌中微微一痒，一股毒气自掌沿手臂上升。\n"NOR "你对抽髓掌的领会又加深了一些！\n");
                  break;
				case 2:
                  me->improve_skill("huagong-dafa", (int)(me->query("int") / 2));
                  write (RED"你只觉掌中微微一痒，一股阴毒之气自掌沿手臂上升，直达丹田。\n"NOR "你对化功大法的领会又加深了一些！\n");
                  break;
              }

            }else {
				
				me->improve_skill("poison", (int)(me->query("int") / 2));
                write (RED"你只觉掌中微微一凉，一股阴气顺着脉络侵入脑髓。\n"NOR"你对基本毒技的领会又加深了一些！\n");

			}
			
		}
         return 1;
}
int do_fire()
{
	object fire;
	object me=this_player();
	
	if (me->query("family/family_name")!="星宿派")
	{
		return notify_fail("你不是星宿派，用不了这个神木王鼎\n");
	}
	if (me->query_skill("huagong-dafa",1)<150)
	{
		return notify_fail("你的化功大法不足150，用不了这个神木王鼎\n");
	}
	if (this_object()->query("dianxiang"))
	{
		return notify_fail("你已经在神木王鼎上点燃了三支药香。\n");
	}
	if (!objectp(present("fire",me)))
	{
		return notify_fail("你身上没带火折，无法点燃药香，用不了这个神木王鼎。\n");

	}
	message_vision(WHT"$N掏出一个火折，点燃了三支药香，插在神木王鼎上。\n微风浮动，药香袅袅，飘向四周~~~~~~~~~~~\n"NOR,me);
	this_object()->add_temp("dianxiang",3);
	return 1;
}