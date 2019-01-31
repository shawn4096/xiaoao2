// qianjin.c for tjj
// By KinGSo 四两拨千斤 01 25 2007

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
int remove_mujian(object me,object weapon);

int perform(object me, object target)
{
	int damage, p,i;
	object weapon;
	int qianjin,ap,dp;
	string msg;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);

    if (!weapon) return notify_fail("你手中无剑，如何施展「四两拨千斤」。\n");  
	
	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("「四两拨千斤」只能对战斗中的对手使用。\n");

	if( me->query_temp("tjj/lian"))
		return notify_fail("你正在使用连。\n");

	if( (int)me->query_skill("taiji-jian", 1) < 500 )
		return notify_fail("你的太极剑法功力太浅，别做梦了。\n");

	if( (int)me->query_skill("taiji-quan", 1) < 500 )
		return notify_fail("你的太极拳法功力太浅，别做梦了。\n");

	if( (int)me->query_skill("sword", 1) < 500 )
		return notify_fail("你的基本剑法功力太浅，别做梦了。\n");

	if( (int)me->query_skill("cuff", 1) < 500 )
		return notify_fail("你的基本拳法功力太浅，别做梦了。\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) < 500 )
		return notify_fail("你的氤氲紫气功力太浅，别做梦了。\n");

	if( !me->query("quest/wd/tjj/qianjin/pass"))
		return notify_fail("你只是听说过太极四两拨千斤之术，但现在无法使用「四两拨千斤」。\n");

	if( (int)me->query_skill("force", 1) < 500 )
		return notify_fail("你的内功功力太浅，别做梦了。\n");

	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("你的最大内力太浅，别做梦了。\n");

	if (me->query_skill_prepared("cuff") != "taiji-quan"
	|| me->query_skill_mapped("cuff") != "taiji-quan"
	|| me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_mapped("sword") != "taiji-jian")
		return notify_fail("你现在无法使用四两拨千斤！\n");

	if( (int)me->query("neili") < 3000 )
		return notify_fail("你的当前真气不够，别做梦了。\n");

	//木剑威力加成
	if(((weapon->query("material") == "wood"
	|| weapon->query("material") == "bamboo"
	|| (weapon->query("id") == "songwen gujian" && weapon->query("from")=="zhang sanfeng")
	|| weapon->query("material") == "paper")
	|| weapon->query("weapon_prop/damage") < 20)
	&& !me->query_temp("tjj/mujianadd"))
	{
		i = me->query_skill("taiji-jian", 1)/3; //增加威力，由3调整为2
		me->add_temp("apply/damage", i);
		me->add_temp("apply/attack", i);
		me->set_temp("tjj/mujianadd", i);
		if( wizardp(me) ) 
			tell_object(me, "你兵器无锋「"HIW"四两拨千斤"NOR"」威力加成： "+i+"。\n"NOR);
		target->add_busy(2);//这个修改了ADD模式，不是start
		call_out("remove_mujian", 1, me, weapon);
	}
	
	msg =  BCYN HIW "\n\n$N" HIW "淡然轻笑，左手轻轻剑指斜引，右手"+weapon->query("name")+BCYN+HIW"划了数个圈子，顿时四周的气流波动，源源不断的被牵引进来。\n"
					"\n已然真正达到“一羽不能加，一蝇不能落的境界”。$n只觉得自己被套进这无形的气旋中，难以抽身。\n" NOR;

	ap=me->query("combat_exp")/100000;
	dp=target->query("combat_exp")/200000;
	if (random(me->query_skill("force",1)*3) > target->query_skill("dodge",1)/2 || random(ap) > dp)
	{
		//me->start_busy(1);
		qianjin = (int)me->query_skill("yinyun-ziqi",1) /40;
		damage = (int)me->query_skill("force",1)+me->query_skill("taiji-jian",1)+me->query_skill("sword",1);
		damage += random(me->query("jiali") * 100);
		damage *= 3;

		if(target->query("neili") < me->query("neili")) damage *= 2;
		if (damage>6500) damage = 6500+(damage-6500)/100;  

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		target->receive_damage("jing", damage/6, me);

		if (target->query("jingli")>damage/3)
			target->add("jingli", -damage/3);
		else 
			target->set("jingli",1);

		target->apply_condition("neishang", qianjin);
		target->start_busy(2);

		//娘的，难道要破对方最大内力？
		//target->add("max_neili", -random(50)); 
		me->add("neili", -200);
		if (me->query("neili") < 0)
			me->set("neili",0);
		p = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg += HBRED HIY "\n只听见两声闷响，$n哇的一声吐出一蓬鲜血,显然是受了很重的内伤。\n"NOR;
		msg += "( $n"+eff_status_msg(p)+" )\n"; 

		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		if((int)me->query_skill("force", 1) > 350 && (int)me->query_skill("taiji-quan", 1) > 350 && (int)me->query_skill("taiji-jian", 1) > 350)
			call_out("perform2", 1, me, target, p, damage); 
	}
	else {
		me->start_busy(1);
		me->add("neili", -100);
		target->add("max_neili", -random(50));                            
		target->start_busy(1);
		target->add("neili", -random(1000));
		msg += HIW"$n眼见就要陷入这气旋的中央，一咬牙，不惜损耗真元，抽身急退。\n"NOR;
		if((int)me->query_skill("force", 1) > 350 && (int)me->query_skill("taiji-quan", 1) > 350 && (int)me->query_skill("taiji-jian", 1) > 350)
			call_out("perform2", 1, me, target, p, damage); 
	}

	message_vision(msg, me, target);
	me->start_perform(4,"四两拨千斤");
	return 1;
}


int perform2(object me, object target)
{  
	string msg, dodge_skill;
	int lev;
	lev = me->query_skill("force", 1);

	if( !target || !me || !living(me)
	|| !me->is_fighting(target) 
	|| environment(target)!=environment(me) || !living(target)
	|| (int)me->query("neili") < 500)
		return 0;

	message_vision(BCYN HIC"紧跟着$N一声清啸,左手为剑指，右手化出一个个圆圈，如环抱太极，剑光如环，一波波的阴劲圈向$n周身。\n"NOR,me, target);
	message_vision(BCYN HIB"太极剑的以柔克刚的柔劲发出，在和$n对战的过程中竟然没有任何接触，但$n却感觉到宛如深陷淤泥之中。\n"NOR,me, target);

	if (random(me->query_skill("force",1)) > target->query_skill("dodge",1)/2 || random(me->query_int())>target->query_int()/2)      
	{
		msg = BCYN HIR "此刻$N招招借力打力，一化一推手之间，竟将$n的招数全部反弹引向$n自己。\n"NOR;

		target->add_temp("apply/attack",lev*2);

		target->add_temp("apply/dodge",- lev/2);
		target->add_temp("apply/parry",- lev/2);

		target->add_busy(2);
		me->add("neili", -200);
		me->add("jingli", -100);                              
		COMBAT_D->do_attack(target, target, target->query_temp("weapon"), random(2)?1:3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), random(2)?1:3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);

		target->add_temp("apply/attack",-lev*2);
		target->add_temp("apply/dodge", lev/2);
		target->add_temp("apply/parry", lev/2);  

		//me->start_busy(1);
		if (me->query("neili") < 0)
			me->set("neili",0);

		me->add("neili", -100);
		me->add("jingli", -100);             

	} 
	else 
	{
		msg = HIY "$n" HIY "强提一口真气，如滚地葫芦般，狼狈的躲了开去。\n" NOR; 

		me->add("neili", -100);
		me->add("jingli", -100);  
		target->add("max_neili", -random(50));                            
		target->start_busy(1);
		target->add("neili", -random(500));

		me->start_busy(2);
		if (me->query("neili") < 0)
		me->set("neili",0);
		if (target->query("neili") < 0)
		target->set("neili",0);
	}
	if(random(10) > 3 &&(int)me->query_skill("force", 1) > 450 &&(int)me->query_skill("taiji-quan", 1) > 450 && (int)me->query_skill("taiji-jian", 1) > 450)
		call_out("perform3", 1, me, target);

	message_vision(msg, me, target); 
	me->start_perform(5, "「四两拨千斤」");
	return 1;
}


int perform3(object me, object target)
{  
	string msg, dodge_skill;
	int lev;
	lev = me->query_skill("taiji-jian", 1);

	if( !target || !me || !living(me)
	|| !me->is_fighting(target) 
	|| environment(target)!=environment(me) || !living(target)
	|| (int)me->query("neili") < 500)
		return 0;

	message_vision(BYEL HIW "$N趁着$n旧力已竭，新力不济的间隙，太极剑势如长江大河，滔滔不绝，连招抢攻，痛下杀手！\n"NOR,me, target);
	message_vision(BYEL HIR "$N已然将「三环套月」的招式融入到四两拨千斤中连环三招发出！\n"NOR,me, target);

	if (random(me->query_skill("force",1)) > target->query_skill("dodge",1)/2
	||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)        
	{
		msg = BCYN HIW "\n此时的$n根本难以招架$N这轮凌厉的进攻。不由得心中暗自叫苦！\n"NOR;
		me->add_temp("apply/cuff", lev/4);
		//me->add_temp("apply/sword", lev/3);
		me->add_temp("apply/attack", lev/2);
		me->add_temp("apply/damage", lev/6);
		//me->add_temp("apply/strength", lev/8);
		me->set_temp("tjj/sanhuan", 3);
		me->add("neili", -200);
		me->add("jingli", -200);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target) )
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		//me->add_temp("apply/strength", -lev/8);
		me->add_temp("apply/cuff", -lev/4);

		//me->add_temp("apply/sword", -lev/3);

		me->add_temp("apply/attack", -lev/2);
		me->add_temp("apply/damage", -lev/6);
		me->delete_temp("tjj/sanhuan");
		target->start_busy(1);
		me->start_busy(2);
		if (me->query("neili") < 0)
			me->set("neili",0);

		me->add("neili", -200);
		me->add("jingli", -200);
	} 
	else 
	{
		msg = HIY "$n" HIY "见对方是下了决心要取自己性命，哪敢怠慢！强提一口真气，狼狈的躲了开去。\n" NOR; 

		me->add("neili", -100);
		me->add("jingli", -200);  
		target->add("max_neili", -random(100));                            
		target->start_busy(1);
		target->add("neili", -random(2000));

		me->start_busy(3);
		if (me->query("neili") < 0)
			me->set("neili",0);
		if (target->query("neili") < 0)
			target->set("neili",0);
	}

	message_vision(msg, me, target); 
	me->start_perform(6, "「四两拨千斤」");
	return 1;
}

//消除木剑无锋加成效果
int remove_mujian(object me,object weapon)
{
	int i;
	object wep;
	if (!me) return 1;
	i = me->query_temp("tjj/mujianadd");
	wep = me->query_temp("weapon");
	if (!me->query_temp("tjj/mujianadd")) return 0;

	if (!me->is_fighting()
	||!wep
	||wep->query("id")!=weapon->query("id")
	||me->query_skill_mapped("sword") != "taiji-jian"	)
	{
		me->add_temp("apply/damage", -i);
		me->add_temp("apply/attack", -i);
		me->delete_temp("tjj/mujianadd");
		message_vision(HIW"$N氤氲紫气缓缓收功，手中兵器逐渐恢复原样。\n"NOR,me);
		return 1;
	}
	call_out("remove_mujian", 1, me, weapon);
	
}

string perform_name(){ return BCYN+HIC"四两拨千斤"NOR; }

int help(object me)
{
        write(BCYN HIC"\n武当太极剑绝学之「四两拨千斤」："NOR"\n\n");
        write(@HELP
	武当太极剑绝学之「四两拨千斤」此招乃太极绝学之奥义，
	需要领悟到太极的真谛方可施展。属于太极剑终极绝世武技
	乃是太极剑之大成招式。
	
	perform sword.qianjin

要求：
	当前内力需求 3000 以上;
	最大内力需求 15000 以上；
	太极剑法等级 500 以上；
	太极拳法等级 500 以上；
	基本内功等级 500 以上；
	基本剑法等级 500 以上；
	基本拳法等级 500 以上；
	氤氲紫气等级 500 以上；
	激发剑法为太极剑法；
	激发拳法为太极拳法；
	激发内功为氤氲紫气；
	激发招架为太极剑；
	级别300时可出第一招;
	级别350时可出第二招;
	级别450时有可能出第三招;

HELP
        );
        return 1;
}
