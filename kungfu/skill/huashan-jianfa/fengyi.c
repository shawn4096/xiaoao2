//fengyi.c 有凤来仪 Write By lsxk@hsbbs 2007/7/25
//根据原著，该招有5个后招而来。grin lsxk
//这是我见过最变态的pfm..修改下。。。 by spiderii@ty
inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>
#include <combat_msg.h>

string perform_name() {return HIM"有凤来仪"NOR;}

string *xue_name = ({
"玉堂穴","大横穴","幽门穴","章门穴","晴明穴","紫宫穴","风池穴","百汇穴","太阳穴","长强穴","灵台穴"
});

int perform(object me, object target)
{       
        object weapon = me->query_temp("weapon");

        
        if( !target ) target = offensive_target(me);
 
     //   if(!objectp(target)|| !target->is_fighting(me) )
     //           return notify_fail("「有凤来仪」只能对战斗中的对手使用。\n");
// By Spiderii@ty lsxk你写的不太全面,我补充下,加强下判断
        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("「有凤来仪」只能对战斗中的对手使用。\n");

        if (!weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你现在无法使用「有凤来仪」攻击敌人。\n");

        if((int)me->query_skill("huashan-jianfa", 1) < 100
         ||(int)me->query_skill("sword", 1) < 100
         ||(int)me->query_str() < 25   
         ||(int)me->query_dex() < 25)  
                return notify_fail("你的基本剑法或华山剑法还不够娴熟，不会使用「有凤来仪」。\n");

        if((int)me->query_skill("huashan-qigong", 1) < 100 
			&&(int)me->query_skill("zixia-gong", 1) < 100)
                return notify_fail("你的特殊内功修为不够，无法领悟「有凤来仪」的精髓。\n");

        if(me->query_skill_mapped("force") != "huashan-qigong"
         &&me->query_skill_mapped("force") != "zixia-gong" )
            return notify_fail("你的特殊内功不对，无法使用「有凤来仪」！\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力太弱，无法使用出「有凤来仪」！\n");
        
        if( (int)me->query("neili") < 200 )
                return notify_fail("你的真气不够！\n");

		if( me->query_temp("hsjf/fengyi"))
                return notify_fail("你正在使用「有凤来仪」！\n");

        me->start_perform(2, "「有凤来仪」");
        message_vision(HIM"\n$N使出「有凤来仪」，剑势飞舞而出，轻盈灵动，手中"+weapon->query("name")+HIM+"闪烁不定，直逼$n!\n"NOR, me, target);
        message_vision(HIM"这招「有凤来仪」乃是华山剑法的精妙招数，一招即出，更藏有五个后招，变化精妙绝伦！\n"NOR, me);
        me->set_temp("hsjf/fengyi/wait",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		//me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/4);
        if (objectp(target)&&objectp(me)&&me->is_fighting()&&weapon)
			call_out("fengyi1", 1, me , target, weapon);
		else me->delete_temp("hsjf/fengyi");
        return 1;
}

int fengyi1(object me, object target, object weapon)
{
	string xue,msg;
	int t_exp,m_exp,t_dodge,m_skill,damage;
	if (!me) return 1;
	if (!target)
	{
		me->delete_temp("hsjf/fengyi");
		return 1;
	}
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "sword"
        ||me->query_skill_mapped("sword") != "huashan-jianfa"
        ||me->is_busy()
		||(int)me->query("neili")< 500
		||(int)me->query("jingli")< 150){
			me->delete_temp("hsjf/fengyi");
			me->start_perform(1, "「有凤来仪」");
			return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「有凤来仪」！\n"NOR);
	}

   if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
		me->delete_temp("hsjf/fengyi");
		me->start_perform(1, "「有凤来仪」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		me->delete_temp("hsjf/fengyi");
		me->start_perform(1, "「有凤来仪」");
		return 1;
	}

    t_exp = (int)target->query("combat_exp");
    m_exp = (int)me->query("combat_exp");
    t_dodge = (int)target->query_skill("dodge",1);
    m_skill = (int)me->query_skill("huashan-jianfa",1);
    damage = 0;
	
    xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIY"\n$N见$n欲拆招破解，立时一个变招，手中"+weapon->query("name")+HIY"在半途中竟巧妙地转了回来"+
                  "，异常精准地疾刺$n的「"HIR+xue+HIY"」!\n"NOR, me, target);
    if ( random(m_exp) > t_exp/3
	|| random(m_skill) > t_dodge/3){
           damage = m_skill*(int)me->query("int")/2;
           if (userp(target)&&damage > m_skill*8) damage = m_skill*8;
           if (wizardp(me) && me->query("env/fengyi")) write("damage is "+damage+"!\n");
		me->receive_damage("neili",50);
		me->receive_damage("jingli",50);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
           msg = HIY"$n哪里料得到$N竟可以如此变招，惊讶之下，全身一震，「"HIR+xue+HIY"」已然被刺中，受伤颇重!\n"NOR;
		   msg += COMBAT_D->damage_msg(damage,"刺伤");
           msg = replace_string( msg, "$l", "「"+HIR+xue+NOR"」" );
           msg = replace_string( msg, "$w", weapon->name());
		   message_vision(msg,me,target);
		if(userp(me) && me->query("env/damage")) 
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
	 
		if(userp(target)&& target->query("env/damage")) 
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
			COMBAT_D->report_status(target, 1);
		me->set_temp("hsjf/fengyi/first","命中");
		//新增2
		if (me&&me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
        if (me&&target&&weapon)
			call_out("fengyi2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
		
	}
	else{
		message_vision(HIG"只是$N变招速度奇快，而$n闪躲速度更快，只见$n双脚轻轻一点，十分轻巧地闪了开去！\n"NOR,me,target);
		me->set_temp("hsjf/fengyi/first","未中");
		//me->receive_damage("neili",200);
		//me->receive_damage("jingli",100);
		call_out("fengyi2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}

    return 1;
}

int fengyi2(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg;
	int busy,damage;
	if (!me) return 1;
	if (!target)
	{
		me->delete_temp("hsjf/fengyi");
		return 1;
	}
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "sword"
        ||me->query_skill_mapped("sword") != "huashan-jianfa"
        ||me->is_busy()
		||(int)me->query("neili")< 500
		||(int)me->query("jingli")< 150){
		if (userp(me))
	    me->delete_temp("hsjf/fengyi");
	    me->start_perform(3, "「有凤来仪」");
            return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「有凤来仪」！\n"NOR);
	}

   if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}
	
	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return 1;
	}

	if(m_skill >= 120){
		if(me->query_temp("hsjf/fengyi/first")=="命中"){
			message_vision(HIW"\n$N一击命中，后招便源源不断，只见$N手中"+weapon->query("name")+HIW"随手一指，"+
			"竟快捷无比的刺向$n"HIR"丹田"HIW"处！\n"NOR, me, target);
			    if ( random(m_skill) > t_dodge/4){
                    busy = m_skill/100;
                    if (busy > 2) busy = 2+random(3);
					    target->add_busy(busy);
                    if (wizardp(me)&&me->query("env/fengyi")) write("busy is "+busy+"!\n");
					me->receive_damage("neili",100);
					me->receive_damage("jingli",60);
					target->add("neili",-m_skill*6);
					msg = HIC"$N这招使的炉火纯青，$n哪里还招架的住，直觉"HIR"丹田"HIC"一麻，内力流失极多！\n"NOR;
					message_vision(msg,me,target);
					me->set_temp("hsjf/fengyi/second","命中");
					//新增3
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
                    call_out("fengyi3", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			}
			else{
				message_vision(HIM"$n只觉这招凶狠无比，连忙就地一滚，狼狈地闪了开去！\n"NOR,me,target);
				me->set_temp("hsjf/fengyi/second","未中");
				//me->receive_damage("neili",100);
				//me->receive_damage("jingli",60);
				call_out("fengyi3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			}
		}
		else{
			message_vision(HIW"\n$N料定$n必然往这一方向闪躲了开去，当下施展轻功，手中"+weapon->query("name")+
			HIW"竟朝$n当头劈了下去！\n"NOR, me, target);
			    if ( random(m_skill) > t_dodge/4){
                    damage = m_skill*(int)me->query("int")/3;
                    if (damage > m_skill*10) damage = m_skill*10;
					damage = damage+random(damage/2);
                    if (wizardp(me)&&me->query("env/fengyi")) write("damage is "+damage+"!\n");
					me->receive_damage("neili",50);
					me->receive_damage("jingli",50);
					target->receive_damage("qi",damage,me);
					target->receive_wound("qi",damage*7/10,me);
					msg = HIR"$n闪避不及，已被重重砍伤。\n"NOR;
					msg += COMBAT_D->damage_msg(damage,"砍伤");
					message_vision(msg,me,target);
			if(userp(me) && me->query("env/damage"))
			  tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
		  
			if(userp(target)&& target->query("env/damage"))
			  tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
		      COMBAT_D->report_status(target, 1);
			  me->set_temp("hsjf/fengyi/second","命中");
			  //新增4
			  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
              call_out("fengyi3", 2+random(2), me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
				else{
					message_vision(CYN"$n大吃一惊，暗催内劲，终于招架住了这致命一击！\n"NOR,me,target);
					me->set_temp("hsjf/fengyi/second","未中");
					//me->receive_damage("neili",80);
					//me->receive_damage("jingli",40);
					call_out("fengyi3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
		}
	}
	else{
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
            	return 1;
	}
    //me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/4);
	return 1;
}

int fengyi3(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	if (!me) return 1;
	if (!target)
	{
		me->delete_temp("hsjf/fengyi");
		return 1;
	}
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "sword"
        ||me->query_skill_mapped("sword") != "huashan-jianfa"
        ||me->is_busy()
		||(int)me->query("neili")< 700
		||(int)me->query("jingli")< 350){
	    me->delete_temp("hsjf/fengyi");
	    me->start_perform(1, "「有凤来仪」");
            return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「有凤来仪」！\n"NOR);
	}

   if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(1, "「有凤来仪」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(1, "「有凤来仪」");
		return 1;
	}

	if(m_skill<180){
		if (userp(me))
	    me->delete_temp("hsjf/fengyi");
	    me->start_perform(1, "「有凤来仪」");
            return 1;
	}

	if(!me->is_fighting()){
		message_vision(HIB"\n$N默不作响，却暗催内力，只听“唰唰”两声清啸，瞬间便攻出两招!\n"NOR, me, target);
		me->add("neili",-300);
		me->add("jingli",-150);
		me->add_temp("apply/attack",m_skill/10);
		me->add_temp("apply/dodge",m_skill/10);
		if (me->query_temp("zxg/zixia")){
			message_vision(HIM"$N更暗暗连催"+chinese_number(m_skill/30)+HIM"道紫霞内劲，剑招威力实乃大增!\n"NOR, me);
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
	me->start_perform(1, "「有凤来仪」");
   call_out("fengyi4", 2+random(2), me, target, weapon, t_exp, m_exp, t_dodge, m_skill);

    return 1;
}

int fengyi4(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg,xue;
	int damage;
	if (!me) return 0;
		
	if (!target)
	{
		me->delete_temp("hsjf/fengyi");
		return 1;
	}
	if (!objectp(weapon)
		||!objectp(target)
        ||weapon->query("skill_type") != "sword"
        ||me->query_skill_mapped("sword") != "huashan-jianfa"
        ||me->is_busy()
		||(int)me->query("neili")< 700
		||(int)me->query("jingli")< 350)
	{
	    me->delete_temp("hsjf/fengyi");
	    me->start_perform(3, "「有凤来仪」");
            return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「有凤来仪」！\n"NOR);
	}

   if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return 1;
	}

   if(m_skill<230||me->query("quest/hsjf/fengyi4")!="pass"){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
                return 1;
	}
	
	xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIR"\n但见$N再次跃起，右手"+weapon->query("name")+HIR"平平刺出，剑招毫无花俏，一股凌厉剑气直奔"+
                     "$n的「"+HIY+xue+HIR+"」!\n"NOR, me, target);
    if ( random(m_exp) > t_exp/2
	|| random(m_skill) > t_dodge*3/5){
            damage = m_skill*(int)me->query("int")/3;
            damage = damage*3/2 + random(damage/2);
       if (wizardp(me)&&me->query("env/fengyi")) write("damage is "+damage+"!\n");
	    me->receive_damage("neili",400);
	    me->receive_damage("jingli",200);
	    target->receive_damage("qi",damage,me);
	    target->receive_wound("qi",damage*7/10,me);
            msg = RED"$n早已被$N的攻势吓的全身僵硬，哪还有半点还手之力？!\n"NOR;
	    msg += COMBAT_D->damage_msg(damage,"刺伤");
		if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR); 
		if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); ;
		   msg = replace_string( msg, "$l", "「"+HIY+xue+NOR"」" );
		   msg = replace_string( msg, "$w", weapon->name());
	    message_vision(msg,me,target);
	    COMBAT_D->report_status(target, 1);
	    target->add_busy(3+random(3));
	    target->apply_condition("no_perform",1);
	    target->apply_condition("no_exert",1);
	    me->set_temp("hsjf/fengyi/forth","命中");
	    me->start_perform(3, "「有凤来仪」");
	    call_out("fengyi5", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	else{
           message_vision(MAG"$n哪里见过如此精妙绝伦的剑招？一个大意，便处处守制！\n"NOR,me,target);
		me->set_temp("hsjf/fengyi/first","未中");
		//me->receive_damage("neili",200);
		//me->receive_damage("jingli",100);
		target->apply_condition("no_force",1);
		target->apply_condition("no_perform",2);
		target->apply_condition("no_exert",2);
		me->start_perform(3, "「有凤来仪」");
		call_out("fengyi5", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	return 1;
}

int fengyi5(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	if (!me) return 0;
	
	if (!target)
	{
		me->delete_temp("hsjf/fengyi");
		return 1;
	}
	if (!objectp(weapon)
		||!objectp(target)
        ||weapon->query("skill_type") != "sword"
        ||me->query_skill_mapped("sword") != "huashan-jianfa"
        ||me->is_busy()
		||(int)me->query("neili")< 700
		||(int)me->query("jingli")< 350){
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
                return notify_fail(HIR"你觉得招式无法连贯，体力透支过度，无法继续使用「有凤来仪」！\n"NOR);
	}

   if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return notify_fail(HIR"你刚想继续攻击对手，却发现已经没有这个必要了！\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
		return 1;
	}

   if(m_skill<300||me->query("quest/hsjf/fengyi5")!="pass"){
   	if (userp(me))
		me->delete_temp("hsjf/fengyi");
		me->start_perform(3, "「有凤来仪」");
                return 1;
	}

    message_vision(HIM"\n$N乘胜追击，手中"+weapon->query("name")+HIM"舞得快捷无比，$n已经根本看不清$N的招数，只觉四周劲风无数！\n"+
		"$N突然仰天一声清啸，右脚轻轻一点向前疾速跃出，"+weapon->query("name")+HIM"闪出的阵阵寒光宛如凤凰展翅！\n"+
           "$N微微一笑，手中"+weapon->query("name")+HIM"却依旧舞地极快，刹那间，“唰唰唰”三声，闪出三道剑光奔向$n！\n"NOR, me, target);
		me->add_temp("apply/attack",m_skill);
           if(me->query_temp("zxg/zixia")){
			message_vision(MAG"$N更暗暗连催"+chinese_number(m_skill/30)+MAG"道紫霞内劲，剑招威力已非寻常!\n"NOR, me);
			me->add_temp("apply/damage",m_skill/2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			me->add_temp("apply/damage",-m_skill/2);
		}
		else{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(4)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		}
	me->add_temp("apply/attack",-m_skill);
	me->add("neili",-400);
	me->add("jingli",-200);
  if (userp(me))
	me->delete_temp("hsjf/fengyi");
	me->start_perform(3, "「有凤来仪」");

	return 1;
}

int help(object me)
{
    write(WHT"\n华山剑法「"HIM"有凤来仪"WHT"」："NOR"\n");
    write(@HELP
    五岳剑派乃各有所长，华山剑法更以轻巧、灵活、多变而著称。这招
    「有凤来仪」虽为入门招式，可一招过后却有五个后招，华山弟子往
    往要练上几个月才知其中变化，而真正能在实战中灵活运用的，又需
    几载苦练方成绝技！一式含五变，一变强似一变，华山剑法有成者使
    用该招，效果惊人无比！注意，身法很重要。
    
	指令：perform sword.fengyi

要求：
	华山气功 或者 紫霞神功100级
	华山剑法 100 级，
	基本剑法 100 级，
	后天身法 25  以上，
	后天膂力 25  以上，
	当前内力 700 以上，
	当前精力 350 以上，
	最大内力 1200以上，

说明：
	华山剑法120级时领会第二后招，
	华山剑法180级时领会第三后招，
	华山剑法230级并通过解迷后，领会第四后招，
	华山剑法300级并通过解迷后，领会第五后招。
	若配合紫霞神功某个特技一起使用，效果绝佳！

HELP
	);
	return 1;
}
