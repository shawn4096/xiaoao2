#include <ansi.h>

int exert(object me)
{
	if( me->is_fighting() )
		return notify_fail("战斗中运功疗伤？找死吗？\n");
	if ((int)me->query_skill("luohan-fumogong", 1) < 100)
		return notify_fail("你的罗汉伏魔功修为还不够。\n");
	if( (int)me->query("neili") < 200 )
		return notify_fail("你的真气不够。\n");
	if( (int)me->query("eff_jing") >= (int)me->query("max_jing"))
		return notify_fail("你的精神状态良好。\n");
      //修改为这里增加和尚喇嘛尼姑的特殊
      if ((int)me->query_skill("dacheng-fofa", 1) > 100
           ||(int)me->query_skill("buddhism", 1) > 100
           || (int)me->query_skill("huanxi-chan", 1) > 100)
      {
	message_vision(HIC"$N深深的吸了口气，一声法号：“"HIY"阿"HIB"弥"HIR"陀"HIY"佛"HIC"”运起罗汉诀，精神看来好多了。\n" NOR,me);

        me->receive_curing("jing", (int)me->query_skill("force")*2);
	me->add("neili", -100);
	me->start_exert(1);
	me->start_busy(2);
      }

      else
       {
        message_vision(HIM"$N深深的吸了口气，盘膝而坐，身体四周隐现"HIY"金光"HIM"气象庄严，运起罗汉诀。\n" NOR,me);
       me->receive_curing("jing", (int)me->query_skill("force")*2/3);
	me->add("neili", -100);
	me->start_exert(1);
	me->start_busy(2);
      }           
	return 1;
}

string exert_name(){ return HIC"罗汉诀"NOR; }

int help(object me)
{
        write(HIC"\n罗汉伏魔功功之「罗汉诀」："NOR"\n\n");
        write(@HELP
        要求：   能够疗精
                当前内力 500 以上；
                罗汉伏魔功等级 100 以上。

HELP
        );
        return 1;
}
