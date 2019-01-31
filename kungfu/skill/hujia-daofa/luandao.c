// luandao.c   胡家刀法之「快乱刀诀」.
// Create by lsxk@hsbbs 2007/5/11
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me);
string perform_name() {return HIR"快乱刀诀"NOR;}
int perform(object me,object target)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
                
		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
				return notify_fail("「快乱刀诀」只能在战斗中使用。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 400 )
                return notify_fail("你的胡家刀法不够娴熟，还用不来「快乱刀诀」。\n");
    	if (me->query_skill("blade",1)<400)
                return notify_fail("你的基本刀法不足400，怎能使用「快乱刀诀」？！\n");
		if (me->query_skill("force",1)<400)
                return notify_fail("你的基本内功不足400，怎能使用「快乱刀诀」？！\n");

        if (!weapon 
         || weapon->query("skill_type") != "blade"
//         || me->query_skill_mapped("parry") != "hujia-daofa"
         || me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你的武功运用不对，无法使用「快乱刀诀」。\n");
    
        if ((int)me->query("neili") < 2000 )
                return notify_fail("你现在内力太弱，不能使用「快乱刀诀」。\n");

        if ((int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力太少，不能使用「快乱刀诀」。\n");

        if ((int)me->query("max_neili") < 9000 )
                return notify_fail("你现在的最大内力修为不够，不能使用「快乱刀诀」。\n");

        if ((int)me->query_temp("hjdf/ldj"))
                return notify_fail("你正在使用「快乱刀诀」绝技。\n"); 


        message_vision(YEL "$N顿时身形变快，手中"+weapon->name()+YEL"蓄势待发,刀式如风,此乃正是胡家刀法之「快乱刀诀」绝技！\n"NOR,me);
		message_vision(HIY "\n这胡家刀法，刚中有柔，柔中有刚，迅捷时似闪电奔雷，沉稳处如渊岳峙！\n"NOR,me);

        if (me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
			&& me->query_temp("lqsg/lq")
			&& me->query_skill_mapped("force") == "lengquan-shengong")
            message_vision(HIB"在$N的冷泉神功之「"HIW"冷泉"HIB"」绝技配合下，手中"+weapon->name()+HIB"隐隐地泛着蓝色。\n"NOR, me);
        
		me->start_perform(random(3)+1,"「快乱刀诀」");
        me->add("neili", -400);
        me->add("jingli", -200);
    
        skill = me->query_skill("hujia-daofa", 1)+me->query_skill("lengquan-shengong",1)/2;

        me->add_temp("apply/damage",  skill/4);
        me->add_temp("apply/attack",  skill/4);
        me->set_temp("hjdf/ldj", 1);
		
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		
		if (objectp(me)&& objectp(target))
		     call_out("check_fight",1, me, target,(int)skill/50);
        else remove_effect(me);
		return 1;
}

void check_fight(object me, object target,int amount)
{  
        object weapon;
		if (!me) return;
		weapon = me->query_temp("weapon");  

        if(!me->is_fighting()
		 ||!objectp(target)
         || !living(me)
         || me->is_ghost()
         || !weapon
		 || me->query_skill_mapped("blade")!="hujia-daofa"
		 || amount< 1) 
		{
            remove_effect(me);
			return;
		}
        else { 
				message_vision(HIW"在$N的轻身功夫配合下「"HIR"快乱刀"HIW"」绝技风驰电掣，手中"+weapon->name()+HIW"隐隐形成一层刀气。\n"NOR, me);
				
				me->add_temp("apply/damage",(int)me->query_skill("hujia-daofa",1)/10);
				
				me->set_temp("hjdf/ldja",1);
				switch (random(6))
				{
					case 0:
					case 1:
					case 2:
						COMBAT_D->do_attack(me,target, weapon, 3);
						break;
					case 4:
					case 3:
					
						COMBAT_D->do_attack(me,target, weapon, 3);
						COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
						break;
					case 5:
						COMBAT_D->do_attack(me,target, weapon, 3);
						COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
						COMBAT_D->do_attack(me,target, weapon, 3);
						break;
				}
				me->delete_temp("hjdf/ldja");
				me->add_temp("apply/damage",-(int)me->query_skill("hujia-daofa",1)/10);
			if (objectp(me)&&objectp(target))
				call_out("check_fight", 2, me, target,amount--);
			else {
				remove_effect(me);
				return;
			}
		}
}
int remove_effect(object me)
{         
        int skill;
		if (!me) return 0;
	
        skill = (int)me->query_skill("hujia-daofa", 1);
 
        me->add_temp("apply/damage",  -skill/4);
        me->add_temp("apply/attack",  -skill/4);
        me->delete_temp("hjdf/ldj");
        if(living(me) && !me->is_ghost())
           message_vision(HIY"$N一套「快乱刀诀」使完，刀势一换，动作又恢复了正常。\n"NOR, me);
        return 1;
}

int help(object me)
{
   write(WHT"\n胡家刀法「"HIR"快乱刀诀"WHT"」："NOR"\n");
   write(@HELP
	此「快乱刀诀」乃为胡家刀法之高级招试，刀法深藏不露，只待
	对手大意时，给于对手以沉重打击，从而克敌制胜！使用该招
	时，也会短时间内提高使用者的伤害力和命中率，厉害非常！
	若使用者会武林绝学冷泉神功之「冷泉」绝技，则相辅相成，
	威力惊人！

	指令：perform blade.luandao

要求：  
	当前内力 800 以上；
	当前精力 800 以上；
	最大内力 2500 以上；
	胡家刀法 200 以上；
	基本刀法 200 以上；

HELP
   );
   return 1;
}
