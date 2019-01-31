#include <ansi.h>
#include <combat.h>
//#include <combat_msg.h>

inherit F_SSERVER;
int calc_damage(int,int,object,object);

string perform_name() {return RED"背    刺"NOR;}
int perform(object me, object target)
{
	    object weapon;
        string msg,result;
        int i,total,skill,j; 
		if( !target ) target = offensive_target(me);
		skill=me->query_skill("tenglong-bifa",1);
        
		if( !objectp(target) 
			|| !target->is_character() 
			//|| !me->is_fighting(target) 
			|| !living(target))
                return notify_fail("【背刺】只能在战斗时使用！\n");
		
		if( objectp(weapon=me->query_temp("weapon")) 
			&&weapon->query("skill_type")!="dagger") 
		{                                
            return notify_fail("你必须拿着匕首才能用【背刺】！\n");
        }
		if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou" )
                return notify_fail("你现在无法使用【背刺】进行攻击。\n");  

        if( (int)me->query_skill("chansi-shou", 1) < 450 )
                return notify_fail("你的缠丝手还不够熟练，不能使用【背刺】！\n");  

		
        if( (int)me->query_skill("tenglong-bifa", 1) < 450 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用【背刺】！\n");
 		if( (int)me->query_skill("dulong-dafa", 1) < 450 )
                return notify_fail("你的毒龙大法功力不足，不能用【背刺】。\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa"
			||me->query_skill_mapped("parry") != "tenglong-bifa")
                return notify_fail("只有激发腾龙匕法时才能使用【背刺】！\n");
        if (me->query_skill_mapped("dodge") != "youlong-shenfa")
                return notify_fail("只有使用游龙身法时才能使用【背刺】！\n");
        
        if((int)me->query_dex(1) < 70)
                return notify_fail("你现在身法不足70，不能使用【背刺】！\n");       
        if(me->query("gender") !="女性")
                return notify_fail("此招只能女性使用【背刺】！\n");       

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用【背刺】！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用【背刺】！\n");  
		if (!me->query("quest/sld/tlbf/beici/pass"))
				return notify_fail("你现在不理解这背刺妙用，不能使用【背刺】！\n");  
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用【背刺】。\n");
		//要判断状态。
		if( me->query_temp("tlbf/bcbei"))
                return notify_fail("你正在潜伏伏击对方中！\n");

		if( objectp(weapon=me->query_temp("weapon")))
		{
		weapon = me->query_temp("weapon");
		j=(int)skill/100;
		if (j>6) j=6;
		
		message_vision(BLU"$N施展游龙身法中「游龙蛇行」绝技，悄无声息，潜到$n的身旁，拔出手中"+weapon->query("name")+"暗自准备！\n"NOR,me,target);
		call_out("beici_attack",7-j,me,target);
		me->set_temp("tlbf/bcbei",1);
		me->add("neili",-200);
		me->add("jingli",-300);
		}
	    return 1;
}

int beici_attack(object me,object target)
{
	string msg,result;
	object weapon;
	int i,total;

	if (!me||!me->query_temp("tlbf/bcbei")||!target) 
	{
		me->delete_temp("tlbf/bcbei");
		return 0;
	}
	weapon=me->query_temp("weapon");

	if (!weapon||weapon->query("skill_type")!="dagger") 
	{
		me->delete_temp("tlbf/bcbei");
		return 0;
	}
	if( !target ) target = offensive_target(me);
	//若有手法则
	if (me->query_skill_mapped("hand")=="chansi-shou"
		||me->query_skill_prepared("hand")=="chansi-shou")
	{
	
		msg=HBMAG"$N咬破舌尖，逼出自身全部潜能，奋不顾身猛然贴地疾奔，冲向$n，双手施展出金蛇缠丝手招式，点、戳、绕、缠！\n"NOR;
		msg+=HIR"同时左手$N倒转手中"+weapon->name()+HIR"，撞向$n小腹["HIW"气海穴"HIR"]。\n"NOR;
		target->apply_condition("no_exert",1);
		target->set("jiali",0);
		if (random(me->query_skill("dulong-dafa",1))>target->query_skill("force",1)/2
			&&me->query("quest/sld/tlbf/beici/pass"))
		{
			msg+=HIM"$n小腹["HIW"气海穴"HIR"]一痛，真气外泄，顿时手足无力，瞬间无法出招。\n"NOR;
			if (target->query("neili")>6000)
			{
				target->receive_damage("neili",-6000);
			}
			else target->receive_damage("neili",0);
			target->apply_condition("no_perform",1);

		}	
		message_vision(msg,me,target);

	}
	
		msg=HBRED"$N瞻之在前忽然在后，突然出现在$n背后，"+weapon->name()+HBRED"已经插入$n背心，直至末柄。\n"NOR;

        i = calc_damage((int)me->query_skill("dodge",1),(int)me->query_skill("tenglong-bifa",1),me,target);
        total += i;
        if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
        target->receive_damage("qi", i, me );
        target->receive_wound("qi", i/2 , me);
        result = COMBAT_D->damage_msg(i,"刺伤");
		result = replace_string( result, "$w", weapon->name() );
        result = replace_string( result, "$l", "背部" );
        msg += result;
        message_vision(msg,me,target);
        COMBAT_D->report_status(target, 0);
        if(userp(me) && me->query("env/damage"))
		  tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
        if(userp(target)&& target->query("env/damage"))
		  tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
	    
		me->delete_temp("tlbf/bcbei");
	    me->start_perform(2,"背刺");
	    return 1;
		
}
int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

        i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
        if (i<0) i = -i;
        i += random(i*2/5);
        if( i < (skill2*5)) i = (int)target->query("qi",1)/3;   

        if(userp(target)) i = i* 2 / 5;
        
		return i; 
}

int help(object me)
{
   write(WHT"\n腾龙匕法「"RED"背刺"WHT"」："NOR"\n");
   write(@HELP
	腾龙匕法乃是神龙岛主夫人苏荃的不传之谜
	变化多端，防不胜防。可谓将女人的优势发
	挥的淋漓尽致。
	背刺是腾龙匕法的诡异招式，利用高身法优
	势，快速鹊起，两人交错之际，闪身到对方
	背后出招的技巧。此技巧乃苏夫人的绝技之
	一。属于典型的当面微笑，背后捅刀的典范
	注意，此招若激发和备用缠丝手则在偷袭中
	会出现大招效果。等级越高，发动越快。此
	招需要解密方可习得。
	 
	   
	perform dagger.beici

要求：
	最大内力要求 4000 以上；
	最大精力要求 2500 以上；
	当前内力要求 1500 以上；
	当前精力要求 800 以上；
	腾龙匕法等级 450 以上；
	缠丝手法等级 450 以上；
	毒龙大法等级 450 以上；
	后天身法 70 以上；
	性别需求女性。
HELP
   );
   return 1;
}
