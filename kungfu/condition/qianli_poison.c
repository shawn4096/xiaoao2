// ǧ������ɢ.qianli_poison.c
// created by olives@SJ 5/1/2001
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	  if( duration < 1 ) return 0;
      message_vision(HIY"$N�������Ų����ģ���������˾�һ����ҡҡ�λΡ�\n"NOR, me);
      if(random(me->query_skill("force")*4+me->query("neili"))>me->query("neili"))
	   me->unconcious();
      else
      	   	me->add_busy(1);
		duration --;
      me->apply_condition("qianli_poison",duration);
      //me->set_temp("last_damage_from", "ǧ������ɢ����");	       
      return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}
