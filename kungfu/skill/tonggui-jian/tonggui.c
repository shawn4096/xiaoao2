// jianjue.c 同归剑法 同归剑诀
// modified by xjqx@SJ 2009/01/01
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「同归剑诀」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，如何能够使出「同归剑诀」？！\n");

        if( (int)me->query_skill("tonggui-jian", 1) < 250 )
                return notify_fail("你的同归剑法不够娴熟，无法使出「同归剑诀」。\n");
                
        if( me->query_temp("tgj/tonggui"))
                return notify_fail("你正在使用「同归剑诀」！\n");
        
		if( !me->query("quest/qz/tgj/tonggui/pass"))
                return notify_fail("你只听说过这招，并不会使用「同归剑诀」！\n");
			

        if( (int)me->query_skill("xiantian-gong", 1) < 250 )
         return notify_fail("你的特殊内功火候不够，无法使出「同归剑诀」！\n");

        if( me->query_skill_mapped("force") != "xiantian-gong")
        return notify_fail("你的现在使用的内功不对，无法使出「同归剑诀」！\n");    

        if (me->query_skill_mapped("sword") != "tonggui-jian"
         || me->query_skill_mapped("parry") != "tonggui-jian")
                return notify_fail("你现在无法使用「同归剑诀」进行攻击。\n");

        if( me->query("max_neili") <= 2500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「同归剑诀」！\n");

        if( me->query("neili") <= 500 )
                return notify_fail("你的内力不够，劲力不足以施展「同归剑诀」！\n");

        if( me->query("jingli") <= 500 )
                return notify_fail("你的精力有限，不足以施展「同归剑诀」！\n");

        message_vision(HIW"$N剑势陡变，脚下以北斗七星的方位连续施展出七招剑法，这七招招式猛烈，只攻不守，招招猛攻$n要害!\n"
			+"$N心中发狠，招招猛攻，力求与$n同归于尽，正是「"HIR"同归剑诀"NOR"」的招式！\n"NOR, me,target);
		
		if (me->query("neili")<500)
			me->set("neili",0);
        me->add("neili", -500);
        me->add("jingli", -300);
        
        skill = me->query_skill("tonggui-jian",1);
      	
		improve = skill/5 ;//原来是5
      	

        me->set_temp("tgj/tonggui", improve);
        
        me->add_temp("apply/sword", improve);
		me->add_temp("apply/attack", improve);
        me->add_temp("apply/damage", improve/2);

		me->add_temp("apply/dodge", -improve);
		me->add_temp("apply/parry", -improve);
		me->add_temp("apply/dexerity", -improve);
		me->add_temp("apply/armor", -improve);
        call_out("remove_effect", 1,  me, weapon, 7);
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int improve;
        if(!me||!me->query_temp("tgj/tonggui")) return;
		improve = me->query_temp("tgj/tonggui");
        
		if(!me->is_fighting()
         || !weapon
         || me->query_skill_mapped("sword") != "tonggui-jian"
         || me->query_skill_mapped("parry") != "tonggui-jian"
         || count < 1 )
		{
          
			me->add_temp("apply/sword", -improve);
			me->add_temp("apply/attack", -improve);
			me->add_temp("apply/damage", -improve/2);

			me->add_temp("apply/dodge", improve);
			me->add_temp("apply/parry", improve);
			me->add_temp("apply/dexerity", improve);
			me->add_temp("apply/armor", improve);
			me->delete_temp("tgj/tonggui");
			if (weapon)
				message_vision(HIW"$N使完"NOR"「"HIR"同归剑诀"NOR+HIW"」，"NOR+weapon->name()+HIW"的同归剑法威力大减。\n"NOR, me);

			return;
        }
        call_out("remove_effect", 1, me, weapon, count -1);
        
}               
string perform_name(){ return HIC"同归剑诀"NOR; }


int help(object me)
{
        write(HIG"\n同归剑法之"+RED"「同归剑诀」："NOR"\n\n");
        write(@HELP
	同归剑法为全真七子所创。全套剑法只攻不守，招招猛攻敌人要害，
	力求与敌同归于尽，故得此名。全真七子忌惮欧阳锋武功高强，怕
	欧阳锋重回中原时全真教有覆灭之虞，为避免七人落单时不敌其武
	功而创出，意在牺牲一人而保全同门。丘处机与江南七怪及焦木大
	师交手时首次使出。
	注意，此招只攻不守，使用此招会大幅度牺牲防御来换取短时间的
	攻击力，慎用。
	
	指令：perform sword.tonggui

要求：
	当前内力需求 1000 以上；
	最大内力需求 2500 以上；
	当前精力需求 600 以上；
	同归剑法等级 300 以上；
	先天功的等级 300 以上；
	基本剑法等级 300 以上；
	天罡北斗阵法 200 以上；
	激发剑法为同归剑法；
	激发招架为同归剑法或空明拳；
	激发内功为先天功，
	手持剑类武器。
HELP
        );
        return 1;
}
