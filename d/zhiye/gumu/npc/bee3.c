// bee3.c  By River 98/09
//edit by sohu@xojh 增加驱使玉蜂攻击的指令
inherit NPC;
#include <ansi.h>
#include "bee3.h"
void create()
{
        set_name(HIC"玉蜂"NOR, ({ "yu feng", "bee","feng" }) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只可爱的玉蜂，可能是小龙女以前饲养的。\n");
        set("attitude", "peaceful");         

        set("str", 10);
        set("con", 20);

        set("limbs", ({  "身体",  "翅膀" , "头部" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 3000);

        set_temp("apply/attack", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        setup();
}

void die()
{        
	object me = query_temp("last_damage_from");
	if (objectp(me))
		message_vision("\n$N被$n一下挥落，魂消烟散，尸骨全无。\n", this_object(),me); 
	else
		message_vision("\n$N被一下挥落，魂消烟散，尸骨全无。\n", this_object()); 
        destruct(this_object());
}

int hit_ob(object me, object victim, int damage)
{
        if (victim->query_temp("ynxj/fengmi"))
        {
			message_vision(HIR"\n在蜂蜜若隐若现的幽香指引下，玉蜂拼命向$N发起了攻击!\n",victim); 
			victim->add_condition("bee_poison", 2);
			victim->receive_damage("qi",random(100),me);
        }
        return 0;
}     
