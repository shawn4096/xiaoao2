// scorpion_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
    me->receive_wound("jing", 50+random(10));
    me->receive_damage("qi", 100+random(100));
	me->receive_wound("qi", 50+random(50));
	if (!me->is_busy()) me->start_busy(1+random(1));
	else me->add_busy(1+random(1));
    me->apply_condition("scorpion_poison", duration - 1);
	me->set_temp("last_damage_from", "�綾����");	  
    tell_object(me, HIG "��е��������ѣ���֫��������������\n" NOR );
        if( duration < 1 ) return 0;
        return 1;
}
