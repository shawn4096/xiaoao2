// sanyinshou����.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "sys_anjin"; }

int min_qi_needed() { return 10; }

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;

        message("vision", HIG + me->name() + "һ������ӿ����ʹ�ޱ�"
		          "���������е������ְ��������ˣ�\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 1 ) {
                me->set_temp("last_damage_from", "�����ְ���������");
                me->die();
                return 0;
        }
        else
                tell_object(me, HIC "�����һ��鴤��Ȼ��"
		                "�����������˺�һ�󣬿����������ְ��������ˣ�\n" NOR );

        me->receive_wound("qi", 1000);
        me->receive_damage("jingli", 1000);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}
