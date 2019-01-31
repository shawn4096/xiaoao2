// pomo.c  泼墨披麻剑法，源自丹青生
//叫作‘泼墨披麻剑法’，甚么‘白虹贯日’、‘腾蛟起凤’，又是甚么‘春风杨柳’
//cre by sohu@xojh 2014

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a,skill;

	if( !target ) target = offensive_target(me);
    skill=me->query_skill("qixian-wuxingjian",1);
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「泼墨披麻剑」只能对战斗中的对手使用。\n");

	//if( me->query_temp("qxwxj/shan") )
		//return notify_fail("你正在使用「七弦黄龙闪」。\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 350 )
		   return notify_fail("你的七弦无形剑等级不足，无法使出「泼墨披麻剑」。\n");
 
        if( (int)me->query_skill("sword", 1) < 350 )
		   return notify_fail("你的基本剑法等级不足，无法使出「泼墨披麻剑」。\n");


        if( (int)me->query_skill("force", 1) < 350 )
		    return notify_fail("你的基本内功等级不足，无法使出「泼墨披麻剑」。\n");

        if( (int)me->query("max_neili") < 2500 )
		   return notify_fail("你的内力修为太浅，无法使出「泼墨披麻剑」。\n");

	    if( (int)me->query("neili") < 1000 )
		   return notify_fail("你的真气不足，无法使出「泼墨披麻剑」。\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("你的精力不足，无法使出「泼墨披麻剑」。\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("你没有使用吸星大法，无法使出「泼墨披麻剑」?\n");

	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("你使得了「泼墨披麻剑」么?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /3;
        
        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("qxwxj/pomo",3);
		me->add_temp("apply/attack",skill/3);
        me->add_temp("apply/damage",skill/4);
		message_vision(HIB"$N忽然间势若疯狂，神情宛如墨意淋漓，手中"+weapon->query("name")+HIB"化作一支画笔，施展开来，大开大合。\n"+
			"$N笔力雄健如龙蛇狂舞，笔法森严，一笔笔便如长剑的刺划，正是丹青生绝技「泼墨披麻剑」！"NOR,me,target);
        
        for(a=0;a<3;a++)
        {		     
		     if (me->is_fighting(target))
		      {		      
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
				 
			   }
			
        }
		if (me->is_fighting(target)&&me->query("quest/hmy/qxwxj/pomo/pass")) //quest后
	    {
			message_vision(HIG"$N手中"+weapon->query("name")+HIG"向前直刺而去，手腕斗转间施展出极为厉害的招式「玉龙倒悬」，仗剑当头硬砍，宛如泼墨！\N"NOR,me,target);
            me->add_temp("apply/sword",skill/2);
			me->add_temp("apply/damage",skill/2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/damage",-skill/2);
			me->add_temp("apply/sword",-skill/2);
			message_vision(HIC "$N" HIC "一声长吟，手中" + weapon->query("name") + HIC
              "连划三个圆圈，幻作三个光圈，便如是有形之物，缓缓向$n" HIC
              "身前移去！\n"NOR,me,target);
			if (me->is_fighting(target)&&random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)
			{
			   message_vision(HIR"只觉剑气满室，寒风袭体，微微一楞，已连中三剑，鲜血飞溅！\n"NOR,me,target);
			   target->receive_damage("qi",3000+random(2000),me);
			   target->receive_wound("qi",1000+random(1000),me);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			}else
			{
				message_vision(CYN"可是$n" CYN "见来势迅猛，飞身一跃，闪开了$N" CYN "这凌厉的几剑。\n"NOR,me,target);
			}
			 
    	}
		me->add_temp("apply/attack",-skill/3);
        me->add_temp("apply/damage",-skill/4);
		me->delete_temp("qxwxj/pomo");
		//me->delete_temp("gl_sword");
        me->start_perform( 3 + random(2), "「泼墨披麻剑」");
        me->start_busy(1);
        return 1;
}

string perform_name(){ return HIB"泼墨披麻剑"NOR; }
int help(object me)
{
        write(HIY"\n七弦无形剑"+HIB"「泼墨披麻剑」"NOR"\n");
        write(@HELP
		
	「泼墨披麻剑」乃是传自梅庄四友的丹青生，他号称酒、画、剑三绝。
	一身武功深不可测，他曾经在一次大醉之中将趁酒意正浓厚之际，以
	笔作画，无意中将自己的剑法和剑意融入到这副画中。提示，若解开
	丹青生小quest，则该剑法威力飞跃。
	
	指令：perform sword.pomo

要求：
	基本内功等级 350 以上；
	基本剑法等级 350 以上；
	七弦无形剑法 350 以上；
	无需特定门派内功支持，
	吸星大法有额外加成。

HELP
        );
        return 1;
}

