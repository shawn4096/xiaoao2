//cangzhuo.c 藏拙意 Write By sohu@xoja 2014/5/31
//针对华山剑法藏拙意，根据原著，该招有6-7个后招而来。
//克制华山剑法
//

inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>
#include <combat_msg.h>

string perform_name() {return HIM"藏拙意"NOR;}

string *xue_name = ({
"玉堂穴","大横穴","幽门穴","章门穴","晴明穴","紫宫穴","风池穴","百汇穴","太阳穴","长强穴","灵台穴"
});

int perform(object me, object target)
{       
        object weapon = me->query_temp("weapon");
        object weapon1=target->query_temp("weapon");
      
	  if (!me->query("quest/hmy/tmgcz/pass"))
		return notify_fail("你只是听说过藏拙意，但没有受人指点，不能在战斗中使用。\n");
        if( !target ) target = offensive_target(me);
 
        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("「藏拙意」只能对战斗中的对手使用。\n");

        if (!weapon
         || weapon->query("skill_type") != "club"
         || me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("你现在无法使用天魔棍「藏拙意」攻击敌人。\n");
        if (me->query("quest/hmy/tmgf/jueji")!="pass")
	            return notify_fail("你尚未融会贯通，不能使用藏拙意境！\n");
        
        if((int)me->query_skill("tianmo-gun", 1) < 500
         ||(int)me->query_skill("club", 1) < 500
         ||(int)me->query_str() < 65   
         ||(int)me->query_dex() < 40)  
                return notify_fail("你有的功夫还不够娴熟，不会使用「藏拙意」。\n");

        if((int)me->query_skill("tianmo-gong", 1) < 500 
			&&(int)me->query_skill("xixing-dafa", 1) < 500)
                return notify_fail("你的特殊内功修为不够，无法领悟「藏拙意」的精髓。\n");

        if(me->query_skill_mapped("force") != "tianmo-gong"
         &&me->query_skill_mapped("force") != "xixing-dafa" )
            return notify_fail("你的特殊内功不对，无法使用「藏拙意」！\n");

        if( (int)me->query("max_neili") < 12000 )
                return notify_fail("你的内力太弱，无法使用出「藏拙意」！\n");
        
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你的真气不够！\n");

	   if( me->query_temp("tmgf/cangzhuo"))
                return notify_fail("你正在使用「藏拙意」！\n");

        me->start_perform(3, "「藏拙意」");
		if (weapon1)
		{
	      message_vision(HIC"\n但见$N使出天魔棍法的「藏拙意」，手中"+weapon->query("name")+HIC+"之端直指对方手中的"+weapon1->query("name")+HIC+"!姿式显得异常笨拙。\n"NOR, me, target);
		}
        else message_vision(HIW"\n但见$N使出天魔棍法的「藏拙意」，手中"+weapon->query("name")+HIW+"之端直指对方!姿式显得异常笨拙。\n"NOR, me, target);
		message_vision(HIG"这招「藏拙意」乃是天魔棍法的精妙招数，笨拙之中却含着有余不尽、绵绵无绝之意。一招即出，更藏有六七个后招！\n"NOR, me);
        me->set_temp("tmgf/cangzhuo/wait",1);
		/*if (target->query_skill_mapped("sword")=="huashan-jianfa")
		{

		}*/
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		//me->add_temp("apply/attack",me->query_skill("tianmo-gun",1)/4);
       // if (me->is_fighting(target)) //直接调用，去掉变量参数
           call_out("cangzhuo1", 0, me , target, weapon);
		   
		//me->delete_temp("tmgf/cangzhuo");
        return 1;
}
//第二个变招，打中穴道
int cangzhuo1(object me, object target, object weapon)
{
	string xue,msg;
	int t_exp,m_exp,t_dodge,m_skill,damage;
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 500
	    ||(int)me->query("jingli")< 150){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "「藏拙意」");
        return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「藏拙意」！\n"NOR);
	}


    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "「藏拙意」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}
	if (!me->is_fighting(target)){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "「藏拙意」");
		return 1;
	}
    
    t_exp = (int)target->query("combat_exp");
    m_exp = (int)me->query("combat_exp");
    t_dodge = (int)target->query_skill("dodge",1);
    m_skill = (int)me->query_skill("tianmo-gun",1);
    damage = 0;
	
    xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIR"\n$N见$n欲拆招破解，早已料到，手中"+weapon->query("name")+HIR"顺势外一分，悠然回转"+
                  "，戳向$n的「"HIY+xue+HIR"」!\n"NOR, me, target);
    if ( random(m_exp) > t_exp/3
	|| random(m_skill) > t_dodge/3){
           damage = m_skill*(int)me->query("int")/2;
           if (userp(target)&&damage > m_skill*8) damage = m_skill*8;
           if (wizardp(me) && me->query("env/fengyi")) write("damage is "+damage+"!\n");
		me->receive_damage("neili",150);
		me->receive_damage("jingli",50);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		target->add_busy(1+random(2));
           msg = HIB"$n哪里料得到$N竟可以如此变招，惊慌之余，「"HIY+xue+HIB"」已然被戳中，身形顿时一滞!\n"NOR;
		   msg += COMBAT_D->damage_msg(damage,"戳伤");
           msg = replace_string( msg, "$l", "「"+HIY+xue+NOR"」" );
           msg = replace_string( msg, "$w", weapon->name());
		   message_vision(msg,me,target);
       if(userp(me) && me->query("env/damage")) 
		  tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
	   
if(userp(target)&& target->query("env/damage")) 
		  tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
	 	
		//COMBAT_D->report_status(target, 1);
		me->set_temp("tmgf/cangzhuo/first","命中");
		//新增2
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
        call_out("cangzhuo2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	else{
		message_vision(HIY"$n运使轻功，双脚轻轻一点，十分轻巧地闪了开去！\n"NOR,me,target);
		me->set_temp("tmgf/cangzhuo/first","未中");
		//me->receive_damage("neili",200);
		//me->receive_damage("jingli",100);
		call_out("cangzhuo2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}

    return 1;
}
//第三个变招，打中手腕，掉兵器或受伤
int cangzhuo2(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg;
	int busy,damage;
	object tweapon=target->query_temp("weapon");
	
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 500
	    ||(int)me->query("jingli")< 150){
		if (userp(me))
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(3, "「藏拙意」");
        return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「藏拙意」！\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
     if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}
	
	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return 1;
	}

	if(m_skill >= 350){
		if(me->query_temp("tmgf/cangzhuo/first")=="命中"){
			message_vision(HIW"\n$N一击命中，见$n身形滞缓，后招顺势变化，手中"+weapon->query("name")+HIW"竟快捷无比的砸向$n的"HIR"手腕"HIW"处！\n"NOR, me, target);
			if ( random(m_skill) > t_dodge/4){
                    busy = m_skill/100;
                    if (busy > 2) busy = 2+random(3);
					    target->add_busy(busy);
                    if (wizardp(me)&&me->query("env/fengyi")) write("busy is "+busy+"!\n");
					    me->receive_damage("neili",100);
					    me->receive_damage("jingli",60);
					    target->add("qi",-m_skill*6);
					
					//msg = HIC"$N这招使的炉火纯青，$n哪里还招架的住，直觉"HIR"手腕"HIC"一麻，内力流失极多！\n"NOR;
					if (tweapon)
					{
						message_vision(HIC"$n手腕一阵剧痛，手一松，"+tweapon->query("name")+"掉落地上！\n"NOR,me,target);
						tweapon->move(environment(me));
					}
					//message_vision(msg,me,target);
					me->delete_temp("tmgf/cangzhuo/first");
					me->set_temp("tmgf/cangzhuo/second","命中");
					//新增3
					if (me->is_fighting(target))
						COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
						
                    call_out("cangzhuo3", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			   }
			   else{
				    message_vision(HIC"$n虽觉这招凶狠无比，连忙就地一滚，狼狈地闪了开去！\n"NOR,me,target);
				    me->set_temp("tmgf/cangzhuo/second","未中");
				    me->delete_temp("tmgf/cangzhuo/first");
					
				    call_out("cangzhuo3", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			        }
		}
		else{
			message_vision(HIB"\n$N早已料定$n必然往这一方向闪躲了开去，手中"+weapon->query("name")+
			HIW"竟然忽然间抡圆了朝$n当头砸了下去！\n"NOR, me, target);
			    if ( random(m_skill) > t_dodge/4){
                    damage = m_skill*(int)me->query("str")/3;
                    if (damage > m_skill*10) damage = m_skill*10;
					damage = damage*2+random(damage);
                    if (wizardp(me)&&me->query("env/fengyi")) write("damage is "+damage+"!\n");
					me->receive_damage("neili",150);
					me->receive_damage("jingli",50);
					target->receive_damage("qi",damage,me);
					target->receive_wound("qi",damage*7/10,me);
					msg = HIR"$n闪避不及，正中脑门，顿时鲜血横流，已被重重砸伤。\n"NOR;
					msg += COMBAT_D->damage_msg(damage,"砸伤");
					
					message_vision(msg,me,target);
                    if(userp(me) && me->query("env/damage"))
			           tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
		            
if(userp(target)&& target->query("env/damage"))
			           tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
		            //COMBAT_D->report_status(target, 1);
			         me->set_temp("tmgf/cangzhuo/second","命中");
			  //新增4
					if (me->is_fighting(target))
			            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                     call_out("cangzhuo3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
				else{
					message_vision(CYN"$n大吃一惊，暗催内劲，终于招架住了这致命一击！\n"NOR,me,target);
					me->set_temp("tmgf/cangzhuo/second","未中");
					//me->receive_damage("neili",80);
					//me->receive_damage("jingli",40);
					call_out("cangzhuo3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
		}
	}
	else{
		if (userp(me))
		   me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
        return 1;
	}
    //me->add_temp("apply/attack",-me->query_skill("tianmo-gun",1)/4);
	return 1;
}
//第三招后招，
int cangzhuo3(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        //||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(1, "「藏拙意」");
            return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「藏拙意」！\n"NOR);
	}
    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "「藏拙意」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "「藏拙意」");
		return 1;
	}

	if(m_skill< 450){
		if (userp(me))
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(1, "「藏拙意」");
        return 1;
	}
	if(me->is_fighting(target)){
		message_vision(HIY"\n$N默不作响，却暗催内力，只听“唰唰”两声清啸，瞬间便攻出数招,正是以快破快的功夫!\n"NOR, me, target);
		me->add("neili",-300);
		me->add("jingli",-150);
		me->add_temp("apply/attack",m_skill/10);
		me->add_temp("apply/dodge",m_skill/10);
		if (me->query_temp("xxdf/xixing")){
			message_vision(HIM"$N连催"+chinese_number(me->query_skill("xixing-dafa",1)/100)+HIM"道吸星大法劲力，天魔棍威力顿时大增!\n"NOR, me);
			me->add_temp("apply/damage",m_skill/10);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			
			me->add_temp("apply/damage",-m_skill/10);
		}
		else{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			
		}
		me->add_temp("apply/attack",-m_skill/20);
		me->add_temp("apply/dodge",-m_skill/20);
	}
	else{
		message_vision(HIC"\n$N刚想发招，却发现自己处处受制，只好撤招防守!\n"NOR, me, target);
	}
	me->start_perform(1, "「藏拙意」");
    call_out("cangzhuo4", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);

    return 1;
}
//第四个后招
int cangzhuo4(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg,xue;
	int damage;

	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(3, "「藏拙意」");
            return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「藏拙意」！\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	 if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return 1;
	}

    if(m_skill<450
		//||me->query("quest/tmgf/cangzhuo4")!="pass"
	){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
                return 1;
	}
	
	xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIR"\n但见$N再次跃起，右手"+weapon->query("name")+HIR"虚点五个方位，恰好封死了$n的后招变化。\n"NOR, me, target);
    if ( random(m_exp) > t_exp/2
	    || random(m_skill) > t_dodge*2/5){
            damage = m_skill*(int)me->query_str()/3;
            damage = damage*2 + random(damage);
        if (wizardp(me)&&me->query("env/cangzhuo")) write("damage is "+damage+"!\n");
	        me->receive_damage("neili",400);
	        me->receive_damage("jingli",200);
	        target->receive_damage("qi",damage,me);
	        target->receive_wound("qi",damage*7/10,me);
            msg = RED"$n顿时缚手缚脚，陷入绝无抗御的余地!\n"NOR;
	        msg += COMBAT_D->damage_msg(damage,"砸伤");
            if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR); 
			
if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
			msg = replace_string( msg, "$l", "「"+HIY+xue+NOR"」" );
            msg = replace_string( msg, "$w", weapon->name());
	        message_vision(msg,me,target);
	        //COMBAT_D->report_status(target, 1);
	        target->add_busy(3+random(3));
	        target->apply_condition("no_perform",1+random(1));
	        //target->apply_condition("no_exert",1);
	        me->set_temp("tmgf/cangzhuo/forth","命中");
			//me->delete_temp("tmgf/cangzhuo/");
	        me->start_perform(3, "「藏拙意」");
	        call_out("cangzhuo5", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	else{
           message_vision(MAG"$n哪里见过如此犀利狠辣的招式？一个大意，便处处守制！\n"NOR,me,target);
		   me->set_temp("tmgf/cangzhuo/forth","未中");
	
		   target->apply_condition("no_exert",1);
		   me->start_perform(3, "「藏拙意」");
		   call_out("cangzhuo5", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	return 1;
}
//第五个后招
int cangzhuo5(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{

	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
		
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
                return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「藏拙意」！\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
		return 1;
	}
 
    if(m_skill<300
		//||me->query("quest/tmgf/cangzhuo5")!="pass"
	){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "「藏拙意」");
                return 1;
	}
    message_vision(HIR"\n但见$N"HIR"缩成一团，姿式极不雅观，一副招架无方的挨打神态，手中"+weapon->query("name")+HIR"棍棒的还招软弱无力，纯系守势！\n"+
		               "$n"HIR"正觉好笑，突然之间，脸上笑容僵硬了起来，背上一阵冰凉，寒毛直竖。他目不转瞬的凝视$N"HIR"手中所持"+weapon->query("name")+"\n"
	  	               HIR"越看越觉得这棍棒所处方位实是巧妙到了极处！$n"HIR"知道自己招式势必都击在这棍棒之上，\n"+
                       "这棍棒骤看之下似是极拙，却乃极巧，形似奇弱，实则至强，当真到了“以静制动，以拙御巧”的极诣！\n"NOR, me, target);
   me->add_temp("apply/attack",m_skill);
           if(me->query_temp("xxdf/xixing")&&me->query("xixing",1)>1){
			message_vision(MAG"$N吸星大法自然运转"+chinese_number(m_skill/100)+MAG"道吸星大法内劲勃发!\n"NOR, me);
			me->add_temp("apply/damage",m_skill/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			me->add_temp("apply/damage",-m_skill/3);
		   }
		   else{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		   }
	me->add_temp("apply/attack",-m_skill);
	me->add("neili",-400);
	me->add("jingli",-200);
 
	me->delete_temp("tmgf/cangzhuo");
	me->start_perform(4, "「藏拙意」");

	return 1;
}

int help(object me)
{
    write(WHT"\n天魔棍之「"HIM"藏拙意"WHT"」："NOR"\n");
    write(@HELP
    天魔棍乃是日月神教十大神魔之”金猿神魔“张乘风和”白猴神魔“张乘云
	兄弟二人所创棍法，威震江湖。后来十长老围攻华山后下落不明，使得
	这门绝技从此失传。不过有人听说在华山后山石洞发现过天魔棍招式。
	具体情况有待于玩家自己探索。
    「藏拙意」乃是天魔棍精华所在，看似笨拙无比，实则精妙绝伦，一招
	过后却有无数个后招，日月神教弟子往往要练上几个月才知其中变化，
	而真正能在实战中灵活运用的，又需几载苦练方成绝技！一式含五变，
	一变强似一变。
    指令：perform cangzhuo
	注意：set 藏拙 有特殊功效
    要求：天魔功或吸星大法500级
          天魔棍法 500 级，
          基本棍法 500 级，
          后天身法40以上，
          后天膂力法65以上，
          当前内力1500以上，
          当前精力350以上，
          最大内力12000以上，
   

HELP
	);
	return 1;
}
