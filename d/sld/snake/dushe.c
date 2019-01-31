inherit NPC;

void create()
{
	set_name("毒蛇", ({ "du she", "dushe", "snake", "she" }));
	set("race", "野兽");
	set("age", 20);
	set("long", "一条黄中间黑的毒蛇，全身血红、长舌吞吐、嗤嗤作声、头作三角\n");
	set("attitude", "peaceful");

	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 50000);
        set("no_get",1); // By Spiderii@yt 防止捣乱分子恶意pk

	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);

	setup();
}

void init()
{
	object me;
	object* inv;
	int i;
	mapping myfam;

	::init();
	me=this_player();
	myfam = (mapping)me->query("family");
	if ((int)me->query("xionghuangjiu")) return;
	
	if(interactive(me) && (!myfam || myfam["family_name"] != "神龙教" || me->query("xionghuangjiu")!=1 ))
	{
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++)
			if(inv[i]->query("id")=="xiong huang")
			break;
			if(i>=sizeof(inv)) 
			{
				remove_call_out("kill_ob");
				call_out("kill_ob", 1, me);
			}
	}
}
/*
void die()
{
        message_vision("$N啪的一声断成两截！$N死了。\n", this_object());
//        ob = new(__DIR__"obj/shedan");
        if (!random(5))
        	new(__DIR__"obj/shedan")->move(environment(this_object()));
        destruct(this_object());
}*/
int hit_ob(object me, object victim, int damage)
{
	if (random(victim->query("combat_exp"))>me->query("combat_exp")/2)
	{
		victim->apply_condition("snake_poison",1);
	}
	return 0;
}


