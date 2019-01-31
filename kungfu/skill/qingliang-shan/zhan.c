// zhan.c 展字诀
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

int perform(object me, object target)
{                                  
      int skill,lvl;
      object weapon;
      
	  if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("「展字诀」只能在战斗中对对手使用。\n");
//笔法或刀法
      if (!objectp(weapon = me->query_temp("weapon")) 
		|| (weapon->query("skill_type") != "brush"&&weapon->query("skill_type") != "blade"))
		  return notify_fail("你的武器不对，现在无法使用「展字诀」。\n");
      
	  if (me->query_skill_mapped("blade") != "qingliang-shan"
			||me->query_skill_mapped("parry") != "qingliang-shan"
			|| me->query_skill_mapped("brush") != "qingliang-shan")
                return notify_fail("你激发不对，现在无法使用「戳字诀」。\n");

      if( (int)me->query_skill("qingliang-shan",1) < 350 )
                return notify_fail("你的清凉扇不够娴熟，不会使用「展字诀」！\n");
      
      if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("你的基本内功等级不够，不能使用「展字诀」！\n");  
      if( (int)me->query_skill("blade",1) < 350 )
                return notify_fail("你的基本刀法等级不够，不能使用「展字诀」！\n");  
      if( (int)me->query_skill("brush",1) < 350 )
                return notify_fail("你的基本笔法等级不够，不能使用「展字诀」！\n");  
      
      
      if( (int)me->query_dex() < 60 )
                return notify_fail("你的身法不够强，不能使用「展字诀」！\n");
      if( (int)me->query("neili") < 1500 )
		      return notify_fail("你的内力太少了，无法使用出「展字诀」！\n");
      if( (int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力太弱，不能使用「展字诀」！\n");
      if( me->query_temp("qls/zhan"))
                return notify_fail("你正在施展「展字诀」！\n");
           
      skill = (int)me->query_skill("qingliang-shan", 1);
      
	  lvl = (int)me->query_skill("qingliang-shan", 1)+(int)me->query_skill("blade", 1)/2+(int)me->query_skill("brush", 1)/2;
        
	  lvl=lvl/4;   
      	
      message_vision(HIW"$N右手"NOR+weapon->query("name")+HIW"“刷”的一声展开，施展出"+HIW"「展字诀」"+HIW"，形成一片扇影，将自己周身护住，水泄不通。\n" NOR, me, target);

	  me->add_temp("apply/parry", lvl/3);
	  me->add_temp("apply/armor", lvl/5);
      me->add_temp("apply/dodge", lvl/5);
        
	 
     me->set_temp("qls/zhan", lvl);
     //call_out("remove_effect",1,me,);
	 remove_effect(me,(int)skill/50);
     return 1;
}

void remove_effect(object me,int count)
{
	int lvl;
	object weapon;
	if (!me||!me->query_temp("qls/zhan")) return 0;
	lvl=me->query_temp("qls/zhan");
	weapon=me->query_temp("weapon");

	if (!me->is_fighting()
		||me->query_skill_mapped("brush")!="qingliang-shan"
		||me->query_skill_mapped("blade")!="qingliang-shan"
		||me->query_skill_mapped("parry")!="qingliang-shan"
		||!objectp(weapon)
		||count<0)
	{
		me->add_temp("apply/parry", -lvl/3);
		me->add_temp("apply/armor", -lvl/5);
		me->add_temp("apply/dodge", -lvl/5);
		me->delete_temp("qls/zhan");
		if (weapon)
			tell_object(me, HIW"\n你心神一乱，将手中"+weapon->query("name")+HIW"一收，撤去了“展字诀”。\n"NOR); 
		else tell_object(me, HIW"\n你心神一乱，撤去了“展字诀”。\n"NOR); 
		return;
	}
	call_out("remove_effect",1,me,count-1);

}

string perform_name(){ return YEL"展字诀"NOR; }

int help(object me)
{
	write(HIC"\n清凉扇之「展字诀」："NOR"\n");
	write(@HELP
	清凉扇是昆仑派灵清居士外门绝技，以扇为兵器既可以
	化作短棍，又可以化作刀法攻击，俗话说一寸短，一寸
	险，靠近攻击威力极为犀利，对于不善用力的女性玩家
	这清凉扇也是门派的重要外家功夫。
	展字诀是将手中扇子类武器展开，形成一片扇影，或以
	笔法展开，形成一片棍影，护住周身要害。对于暗器类
	功夫有防御奇效。
	
	注意：set 清凉扇 合 有点穴，破气功效

	指令：perform brush.zhan

要求：
	最大内力需求 5000 以上；
	当前内力需求 1500 以上；
	清凉扇的等级 350 以上；
	基本内功等级 350 以上；
	基本笔法等级 350 以上；
	基本刀法等级 350 以上；
	后天身法大于 60  以上；
	激发刀法为清凉扇
	激发笔法为清凉扇
	激发招架为清凉扇；、
	内功不限；
	手持刀或笔类武器
HELP
	);
	return 1;
}
