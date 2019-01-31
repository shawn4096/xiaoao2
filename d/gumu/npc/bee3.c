// bee3.c  By River 98/09
//edit by sohu@xojh ������ʹ��乥����ָ��
inherit NPC;
#include <ansi.h>
#include "bee3.h"
void create()
{
        set_name(HIC"���"NOR, ({ "yu feng", "bee","feng" }) );
        set("race", "Ұ��");
        set("age", 4);
        set("long", "һֻ�ɰ�����䣬������С��Ů��ǰ�����ġ�\n");
        set("attitude", "peaceful");         

        set("str", 10);
        set("con", 20);

        set("limbs", ({  "����",  "���" , "ͷ��" }) );
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
		message_vision("\n$N��$nһ�»��䣬������ɢ��ʬ��ȫ�ޡ�\n", this_object(),me); 
	else
		message_vision("\n$N��һ�»��䣬������ɢ��ʬ��ȫ�ޡ�\n", this_object()); 
        destruct(this_object());
}

int hit_ob(object me, object victim, int damage)
{
        if (victim->query_temp("ynxj/fengmi"))
        {
			message_vision(HIR"\n�ڷ����������ֵ�����ָ���£����ƴ����$N�����˹���!\n",victim); 
			victim->add_condition("bee_poison", 2);
			victim->receive_damage("qi",random(100),me);
        }
        return 0;
}     
