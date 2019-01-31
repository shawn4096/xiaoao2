//sanjue.c 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
  	string msg;
        int i;
        object weapon;
	if( !target ) target = offensive_target(me);
	if( !target || !me->is_fighting(target) )
		return notify_fail("「达摩三绝剑」只能在战斗中对对手使用。\n");
    weapon = me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="sword")
        return notify_fail("你必须使用在剑时才能使出「达摩三绝剑」！\n");
    if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("你的基本内功不够娴熟，不会使用「达摩三绝」。\n");
	if( (int)me->query_skill("dodge", 1) < 100 )
		return notify_fail("你的基本轻功不够娴熟，不会使用「达摩三绝」。\n");
	if( (int)me->query_skill("damo-jian", 1) < 100 )
		return notify_fail("你的达摩剑法不够娴熟，不会使用「达摩三绝」。\n");
     if(me->query_skill_mapped("sword")!="damo-jian"||me->query_skill_mapped("parry")!="damo-jian")
        return notify_fail("你没有激发达摩剑，不能使用「达摩三绝」。\n");
	if( (int)me->query_skill("yijin-jing", 1) < 100 )
		return notify_fail("你的易筋经内功修为不够，不能使用「达摩三绝」。\n");
    if( me->query_temp("sl/sanjue"))
		return notify_fail("你正在使用「达摩三绝」剑。\n");
	if( (int)me->query("max_neili", 1) < 1400 )
		return notify_fail("你现在内力太弱，不能使用「达摩三绝」。\n");
	if( (int)me->query("neili", 1) < 400 )
		return notify_fail("你现在内力太弱，不能使用「达摩三绝」。\n");
    if((int)me->query("jingli",1)< 200)
        return notify_fail("你现在精力太少，不能使用「达摩三绝」。\n");
        i = me->query_skill("damo-jian", 1);
        msg = HIY "$N轻啸一声，当下身形如叶般飞舞，迅捷如飞般发出连环三剑。\n"NOR;
        me->set_temp("sl/sanjue",1);
        if (userp(me) && me->query_skill("damo-jian",1)<350)
        {
          me->add_temp("apply/damage", i/4);
        }
		if (userp(me)&&me->query("class")!="bonze")
		{
          me->add_temp("apply/damage", i/6);
          me->add_temp("apply/attack", i/3);
		}
		me->add_temp("apply/strength", i/6);
        me->add_temp("apply/attack", i); 
  	    message_vision(msg, me, target);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        if (userp(me)&&me->query("class")!="bonze"&&me->is_fighting())
        {
			message_vision(HIR"$N心无妨碍，并没有什么出家人清规戒律限制，见$n仍然顽抗，不由地杀心大起。\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        }
	    me->add("neili", -200);
        //me->add("jingli",-100);
        me->start_busy(1);
	    me->add_temp("apply/strength",-i/6);
        me->add_temp("apply/attack", -i); 
		if (userp(me)&&me->query_skill("damo-jian",1)<350)
        {
          me->add_temp("apply/damage", -i/4);
        }
		if (userp(me)&&me->query("class")!="bonze")
		{
          me->add_temp("apply/damage", -i/6);
          me->add_temp("apply/attack", -i/3);
		}
		me->delete_temp("sl/sanjue");
        me->start_perform(3,"三绝剑");
        message_vision(HIC"$N一声长啸，身法渐渐缓慢下来。\n"NOR, me,target);
      return 1;
}
string perform_name(){ return HIC"三绝剑"NOR; }
int help(object me)
{
         write(HIC"\n达摩剑法之「三绝剑」："NOR"\n");
        write(@HELP
	达摩三绝剑乃是达摩老祖为了除魔卫道所遗留下来的少林入门武技。
	达摩三绝剑总共三招，剑光凛冽，迅捷无比。少林俗家因不受清规
	戒律限制，杀心仍在，有略微优势。350后因功力原因威力逐渐减弱。
	要求：
		基本内功：100
		基本轻功：100
		达摩剑法：100
		易筋经功：100
		最大内力：1400
		当前内力：500
		当前精力：200
		需激发达摩剑。       
HELP
        );
        return 1;
}

