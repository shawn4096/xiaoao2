
//�岽��
//wubushe.c 
//���Լ�ǿ
inherit NPC;
#include <ansi.h>

void create()
{
	set_name(HIR"�岽��"NOR, ({ "wubu she", "she", "snake" }) );
	set("race", "Ұ��");
	set("age", 20);
	set("long", "һ�����м�ڵľ綾֮�ߣ��������¡�����������ͷ�����ǣ��ų����ж������岽������\n");
	set("attitude", "peaceful");

	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
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
        message_vision("$Nž��һ���ϳ����أ�$N���ˡ�\n", this_object());
//        ob = new(__DIR__"obj/shedan");
        if (!random(3))
        	new(__DIR__"obj/wbsdan")->move(environment(this_object()));
        destruct(this_object());
}
int hit_ob(object me, object victim, int damage)
{
	 if (random(3)) return 0;
	 message_vision(BLU"$N������˲��һ��Ҫ��$n��С�ȣ�\n"NOR,me,victim);
     victim->receive_damage("qi",100,me);
	 victim->add_condition("wubushe_poison", 1);
	 return 0;
}
