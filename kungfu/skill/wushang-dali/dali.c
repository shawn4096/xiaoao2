// by SOHU@XOJHU 2014.1
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon,weapon2;
		int ski;
		weapon=me->query_temp("weapon");
		weapon2=target->query_temp("weapon");
		ski=me->query_skill("wushang-dali",1)+me->query_skill("tianwang-zhua",1)/2;
        //write("weight="+weapon->query("weight"));
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「无上大力」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("wushang-dali", 1) < 250 )
                return notify_fail("你的无上大力杵功力太浅，无法使用「无上大力」攻击。\n");
		 if( (int)me->query_skill("staff", 1) < 250 )
                return notify_fail("你的基本杖法功力太浅，无法使用「无上大力」攻击。\n");
        if( !weapon||weapon->query("skill_type")!="staff")
                return notify_fail("你的无上大力杵必须用杖法类武器才能使用。\n");
        if( (int)me->query_skill("tianwang-zhua", 1) < 250 )
                return notify_fail("你的天王爪功力太浅，无法使用「无上大力」攻击。\n");
        if( me->query_temp("wushang_dali") )
                return notify_fail("你正在使用「无上大力」绝技攻击。\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力太浅，无法使用「无上大力」攻击。\n");
        if( (int)me->query_str() < 50 )
                return notify_fail("你的有效臂力不够，无法使用「无上大力」攻击。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，无法使用「无上大力」攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
            || me->query_skill_mapped("staff") != "wushang-dali" 
			|| me->query_skill_prepared("claw") != "tianwang-zhua"
			|| me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("你的准备功夫不对。\n");

        me->add("neili", -200);
        me->add("jingli", -40);
		me->set_temp("wushang_dali",1);
        message_vision(RED"$N"+RED"大喝一声，双手抡起手中的"+weapon->query("name")+RED+"带起一股劲风，猛然向$n砸了下去！\n" NOR,me,target);
        message_vision(HIY"$N"+HIY"此时双手用劲，连腰力也同时使上了，"+weapon->query("name")+HIY"上所发呼呼风声更加响了一倍。\n" NOR,me,target);
		
		if (!userp(target))
        {
			me->add_temp("apply/attack", ski/2);
	        me->add_temp("apply/damage", ski/4);
			me->add_temp("apply/staff", ski/4);
			me->set_temp("wsdl/dalitemp",1);
        }
		if (random(me->query_str(1))>target->query_dex(1)/2)
		{
		    if (weapon2)
			{ 
				message_vision(HIR"$N的这招力大沉猛，$n心中对$N甚是轻视，举起手中的"+weapon2->query("name")+HIR"迎了上去。\n"NOR,me,target);
			    if (random(me->query_str(1))>target->query_str(1)/2 && weapon2->query("imbue")<3)
			    {
				 message_vision(HIY"$n只觉一股大力传来，户口巨震，手中的"+weapon2->query("name")+HIY"顿时断为两截。\n"NOR,me,target);
				 weapon2->broken("砸断的");			     
				 target->receive_damage("qi",1000+ski*5,me);
                 target->receive_wound("qi",ski/2,me);
			     }			  
			}else {
                 message_vision(RED"$n只觉一股大力传来，户口巨震，气血翻涌，哇地吐出一口鲜血。\n"NOR,me,target);
				 target->receive_damage("qi",2000+ski*5,me);
                 target->receive_wound("qi",ski,me);
			}
		 
		 }else message_vision(HIC"$n微微一笑，向旁边闪开去，$N这招结果砸在地上，形成一个巨大的深坑。\n"NOR,me,target);		
		
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
       if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?3:1);
        if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
        if(me->is_fighting(target)
			&&me->query_skill_mapped("staff")=="wushang-dali"
			&&me->query_skill_mapped("claw")=="tianwang-zhua")
    	{	
		  weapon->unequip();
		  message_vision(WHT"$N放下手中的"+weapon->query("name")+WHT"突然五指变抓，施展出大轮寺天王爪绝技。\n"NOR,me,target);

		  me->add_temp("apply/attack",me->query_skill("tianwang-zhua",1)/2);
		  me->add_temp("apply/damage",me->query_skill("tianwang-zhua",1)/4);
		  if (!userp(target))
			target->add_busy(2);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		  me->add_temp("apply/attack",-me->query_skill("tianwang-zhua",1)/2);
		  me->add_temp("apply/damage",-me->query_skill("tianwang-zhua",1)/4);
          weapon->wield();        
		}
		if (me->query_temp("wsdl/dalitemp"))
        {
			me->add_temp("apply/attack", -ski/2);
	        me->add_temp("apply/damage", -ski/4);
			me->add_temp("apply/staff", -ski/4);
			me->delete_temp("wsdl/dalitemp");
        }
		me->start_perform(3,"无上大力");
		me->delete_temp("wushang_dali");
        me->start_busy(1);
        return 1;
}

string perform_name(){ return HIR"无上大力"NOR; }

int help(object me)
{
        write(HIR"\n无上大力杵之「无上大力」："NOR"\n\n");
        write(@HELP 
	无上大力杵是大轮寺弟子初期的武技，传
	自金轮法王弟子达尔巴，达尔巴神力天生，
	乃是金轮法王的首席二弟子。当初在英雄
	关一战，力克一灯大师大弟子，至刚至猛
	威力绝伦。需要和天王爪组合，方能形成
	有效攻击，且影响威力。
	注意：有效臂力至少需要50。
	
	指令：perform staff.dali
	
要求：
	当前内力要求 500 以上；
	最大内力要求 2500 以上；
	当前精力要求 500 以上；
	天王爪法等级 250 以上；
	基本内功等级 250 以上；
	基本杖法等级 250 以上；
	激发爪法为天王爪，且备天王爪；
	激发招架为无上大力杵；
	激发杖法为无上大力杵；
HELP
        );
        return 1;
}