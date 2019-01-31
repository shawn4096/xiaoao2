
//五步蛇
//wubushe.c 
//毒性极强
inherit NPC;
#include <ansi.h>

void create()
{
	set_name(HIR"五步蛇"NOR, ({ "wubu she", "she", "snake" }) );
	set("race", "野兽");
	set("age", 20);
	set("long", "一条黄中间黑的剧毒之蛇，长舌吞吐、嗤嗤作声、头作三角，号称人中毒后，走五步即死。\n");
	set("attitude", "peaceful");

	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 800000);

	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);
	//call_out("kuser",5);
	setup();
}

void init()
{
	object *ob,me;
	int i;

	me=this_player();
	if(!environment(me))  return;
	if ((int)me->query("xionghuangjiu")) return;

	ob = all_inventory(me);
	for(i=0; i<sizeof(ob); i++)
	{
		if(ob[i]->query("id")=="xiong huang") break;
		if(!this_object()->is_fighting()) 
		{
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, me);
		}

	}
	
}
void die()
{
        message_vision("$N啪的一声断成两截！$N死了。\n", this_object());
//        ob = new(__DIR__"obj/shedan");
        if (!random(3))
        	new(__DIR__"obj/wbsdan")->move(environment(this_object()));
        destruct(this_object());
}
int hit_ob(object me, object victim, int damage)
{
	 if (random(3)) return 0;
	 message_vision(BLU"$N极其灵活，瞬间一口要中$n的小腿！\n"NOR,me,victim);
     victim->receive_damage("qi",100,me);
	 victim->add_condition("wubushe_poison", 1);
	 return 0;
}
