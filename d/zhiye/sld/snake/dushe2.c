inherit NPC;
//void kuser();
void create()
{
	set_name("毒蛇", ({ "du she", "dushe", "snake", "she" }) );
	set("race", "野兽");
	set("age", 20);
	set("long", "一条黄中间黑的毒蛇，全身血红、长舌吞吐、嗤嗤作声、头作三角\n");
	set("attitude", "peaceful");

	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 100000);

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
		if(ob[i]->query("id")=="xiong huang")
		break;
		if(i>=sizeof(ob)) {
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, me);
		}

	}
	
}
void die()
{
        message_vision("$N啪的一声断成两截！$N死了。\n", this_object());
//        ob = new(__DIR__"obj/shedan");
        if (!random(5))
        	new(__DIR__"obj/shedan")->move(environment(this_object()));
        destruct(this_object());
}
int hit_ob(object me, object victim, int damage)
{
        victim->apply_condition("snake_poison",
                victim->query_condition("snake_poison") + 8);
        return 0;
}
