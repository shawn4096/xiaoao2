inherit NPC;

void create()
{
	set_name("����", ({ "du she", "dushe", "snake", "she" }));
	set("race", "Ұ��");
	set("age", 20);
	set("long", "һ�����м�ڵĶ��ߣ�ȫ��Ѫ�졢�������¡�����������ͷ������\n");
	set("attitude", "peaceful");

	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 50000);
        set("no_get",1); // By Spiderii@yt ��ֹ���ҷ��Ӷ���pk

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
	
	if(interactive(me) && (!myfam || myfam["family_name"] != "������" || me->query("xionghuangjiu")!=1 ))
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
        message_vision("$Nž��һ���ϳ����أ�$N���ˡ�\n", this_object());
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

