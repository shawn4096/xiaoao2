// hongsha.c
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED+HIW"红砂血劲气"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("「红砂血劲气」只能在战斗中用。\n");

  if( me->query_temp("weapon")) 
         return notify_fail("你手握武器，如何使得出「红砂血劲气」？\n");
         
  if( (skill = (int)me->query_skill("hongsha-zhang", 1)) < 350 )
         return notify_fail("你的红砂掌不够娴熟，不会使「红砂血劲气」！\n");
  if (!me->query("quest/xd/hongsha/pass"))
         return notify_fail("你的红砂掌尚未领会贯通，不会使「红砂血劲气」！\n");

  if( (int)me->query_skill("xuedao-jing", 1) < 350 )
         return notify_fail("你的内功火候不够，不会使用「红砂血劲气」！\n");

  if( me->query_skill_mapped("force") != "xuedao-jing")
         return notify_fail("你所用的内功和「红砂血劲气」相互冲突！\n");

  if (me->query_skill_prepared("strike") != "hongsha-zhang" ||
      me->query_skill_mapped("strike") != "hongsha-zhang")
         return notify_fail("你必须先将红砂掌运用于掌法之中才行。\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("你掌上不带内力，怎么使得出「红砂血劲气」来？\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("你的真气不足，不能施展「红砂血劲气」！\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("你的内力不足，不能施展「红砂血劲气」！\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("你的精力不足，不能施展「红砂血劲气」！\n");
  if (me->query_temp("hsz/hongsha"))
         return notify_fail("你正在施展「红砂血劲气」！\n");
  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  
  message_vision(HIR "\n$N猛然间运气与双掌，猛喝一声，腾起一股血气，弥漫周身，双掌顿时变得"HBRED+HIW"血红"NOR+HIR"一片，\n"NOR,me,target);
  
  me->add_temp("apply/attack",skill/5);
  me->add_temp("apply/damage",skill/8);
  me->add_temp("apply/strike",skill/5);
  
  me->set_temp("hsz/hongsha",skill);
  call_out("remove_effect",1,me,skill/30);
  me->add("jingli",-100);
  me->add("neili",-150-random(100));

  return 1;
}

int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_skill("hongsha-zhang",1);
	if (!me->is_fighting()
		||me->query_skill_mapped("strike")!="hongsha-zhang"
		||me->query_skill_prepared("strike")!="hongsha-zhang"
		||me->query_temp("weapon")
		||count<0)
	{
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/damage",-skill/8);
		me->add_temp("apply/strike",-skill/5);
		me->delete_temp("hsz/hongsha");
		message_vision(HIR"$N将运行双臂的红砂血劲气停止，脸色顿时煞白一片。\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
	

}
int help(object me)
{
	write(RED"\n红砂掌之「红砂血劲气」："NOR"\n\n");
        write(@HELP
	红砂掌乃是血刀门弟子入门武技，红砂乃是取大雪山
	剧毒之物，以自身鲜血滋养，久而久之，血液中带有
	毒性。同时因为血液中蕴含这些奇物之毒，这红砂掌
	对于血刀门的心法却有滋养之意。
	红砂血劲气就是凭借平时修炼的红砂掌血毒蕴藏在丹
	田，待得施展时运气于臂，掌法威力提升。需解密获
	得。
	
	指令：perform strike.hongsha

要求：
	最大内力  1500 以上；
	当前内力  500  以上；
	血刀经    350  级以上；
	红砂掌法  350  级以上；
	激发掌法为红砂掌；
	激发招架为红砂掌；
	空手且备红砂掌；
HELP
        );
        return 1;
}