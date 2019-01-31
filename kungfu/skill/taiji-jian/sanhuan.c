// sanhuan.c for tjj
// Created and Modified by snowman@SJ 23/02/2001

#include <ansi.h>

inherit F_SSERVER;
int perform1(object me, object target, object weapon, int ap, int dp, int skill, int i);
int perform2(object me, object target, object weapon, int ap, int dp, int skill, int i);



int perform(object me, object target)
{
	object weapon;
	int i, j,t, lvl = me->query_skill("taiji-jian", 1);
	if (me->query("quest/wd/tjj/sanhuan/pass"))	t=2;
	else t=3;
	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「三环套月」只能对战斗中的对手使用。\n");

	if( me->query_temp("tjj/lian") )
		return notify_fail("你正在使用连。\n");
 
    if( (int)me->query_skill("taiji-jian", 1) < 450 )
		return notify_fail("你的太极剑法功力太浅，别做梦了。\n");
 
    if( (int)me->query_skill("sword", 1) < 450 )
		return notify_fail("你的基本剑法功力太浅，别做梦了。\n");

	//if( (int)me->query_temp("tjj/chan") )
		//return notify_fail("你现在正在使用「缠」字诀。\n");

    if( (int)me->query_skill("yinyun-ziqi", 1) < 450 )
		return notify_fail("你的氤氲紫气功力太浅，别做梦了。\n");

    if( (int)me->query("max_neili") < 12500 )
		return notify_fail("你的最大内力太浅，别做梦了。\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("你的当前真气不够，别做梦了。\n");

	if( me->query_skill_mapped("force") != "yinyun-ziqi" )
		return notify_fail("你用什么为内功基础来使「三环套月」?\n");

	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("你使得了「三环套月」么?\n");

  	j = lvl /2; //原1/3
	if (lvl>350)
	   j = to_int(lvl/1.5);
	if ( lvl > 450 )
		j = to_int(lvl * lvl/825);

        if(!userp(me)) j = j/4; //降低npc的威力
	    me->set_temp("tjj/sanhuan", 3);
	    me->add_temp("apply/sword", j/t);
        me->add_temp("apply/attack", j/t);
        me->add_temp("apply/damage", j/t);
	if( wizardp(me) )
           tell_object(me, "你的「"HIW"三环套月"NOR"」增加：有效剑法 "+j/t+"；命中率 "+j/t+"；伤害 "+j/t+"。\n"NOR);

	if( (( weapon->query("material") == "wood"
	   || weapon->query("material") == "bamboo"
       || (weapon->query("id") == "songwen gujian" && weapon->query("from")=="zhang sanfeng")
       || weapon->query("material") == "paper" )
	   || weapon->query("weapon_prop/damage") < 20)
	   && !me->query_temp("tjj/sanhuan_damage"))
	    {
                   i =  me->query_skill("taiji-jian", 1)/t; //增加威力，解密后由3调整为2
			       me->add_temp("apply/damage", i);
                   me->add_temp("apply/attack", i);
			       me->set_temp("tjj/sanhuan_damage", i);
				   message_vision(HBYEL+HIW"$N手中的"+weapon->query("name")+HBYEL+HIW"无锋，在氤氲紫气辅助下，却呈柔中带刚！\n"NOR,me,target);
	               if( wizardp(me) ) 
                         tell_object(me, "你兵器无锋「"HIW"三环套月"NOR"」威力加成： "+i+"。\n"NOR);
	               target->add_busy(2); //这个修改了ADD模式，不是start
        }

         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if( me->is_fighting(target) )
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if( me->is_fighting(target) )
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	 
	 
	 
	    me->add_temp("apply/sword", -j/t);
        me->add_temp("apply/attack", -j/t);
	    me->add_temp("apply/damage", -j/t);

	if( me->query_temp("tjj/sanhuan_damage") ){
		me->add_temp("apply/damage", -me->query_temp("tjj/sanhuan_damage") );
		me->add_temp("apply/attack", -me->query_temp("tjj/sanhuan_damage") );
		me->delete_temp("tjj/sanhuan_damage");

	}
	
	me->delete_temp("tjj/sanhuan");
	me->delete_temp("tjj/sanhuan_damage");

	me->start_busy(1+random(1));
	me->add("neili", -300);
	me->add("jingli", -150);
	me->start_perform(4, "「三环套月」");
	
	
	if (objectp(target)&&me->query("quest/wd/tjj/sanhuan/pass"))
	{
		message_vision(YEL"$N对于太极剑法奥秘已至大成，灵光闪动间，将师傅所传的「连字诀」顺手施展出来！\n"NOR,me,target);
		//me->start_call_out( (: call_other, __DIR__"lian", "perform", me, 1 :), 1 );
		
		call_out("sanhuan_lian",1,me,target);
	}	    
	
	return 1;
}

int sanhuan_lian(object me, object target)
{
	string msg, dodge_skill;
	object weapon = me->query_temp("weapon");
	int ap, dp, damage, p, skill, i = 0;

	if( !target ) return 0;

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

	if( !living(target) )
		return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("你手中无剑，如何使得「连」字诀？\n");

	if( me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("你所备不是太极剑法，无法使用「连」字诀。\n");

	if( me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("你必须以太极剑法为招架才能使用「连」字诀。\n");  
//增加如果解开太极神功后，则可以连续出
	if( me->query_temp("tjj/chan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("你正在使用「缠」字诀。\n");

	if( (int)me->query_temp("tjj/lian") )
		return notify_fail("你现在正在使用「连」字诀。\n");

	if( (int)me->query_skill("taiji-jian", 1) <300 )
		return notify_fail("你的太极剑法修为尚不纯熟,无法使用「连」字诀！\n");             

	if( (int)me->query_skill("yinyun-ziqi",1) < 300 )
		return notify_fail("你的氤氲紫气修为尚浅，不能使用「连」字诀！\n");

	if( (int)me->query_skill("sword",1) < 300 )
		return notify_fail("你基本剑法修为尚不纯熟,不能使用「连」字诀！\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为太弱，不能使用「连」字诀！\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("你的真气太少了，不能使用「连」字诀！\n");  

	message_vision(CYN"\n$N微微一笑，使出太极剑中"+RED+"「连」"+CYN+"字诀，当下身子缓缓右转,左手持剑向上提起，剑身横于胸前，\n"
			"左右掌心相对，如抱圆球，手中"+weapon->name()+CYN"未出，已然蓄势无穷。\n"NOR,me,target);

	me->set_temp("tjj/lian",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("taiji-jian", 1);

	msg = CYN"\n$N左手"+weapon->name()+CYN"缓缓向前划出，成一弧形，一股森森寒气，直逼向$n，突然之间，$N剑交右手，寒光一闪，向$n划去。\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword") * 2;
		damage = to_int( damage * skill/100.0);
		damage = damage/2 + random(damage);
		if (damage > 4000 ) damage = 4000 + random(damage-4000)/50;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -200);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		i = 1;
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->start_perform(2, "「连」字诀");
	me->start_busy(random(2));
	me->delete_temp("tjj/lian");
	if ( skill > 150 ) {
		me->set_temp("tjj/lian", 1);
		perform1(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform1(object me, object target, object weapon, int ap, int dp, int skill,int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg =YEL"\n$N又将剑交左手，在身前划了两个圆圈，剑劲连绵护住全身，竟无半分空隙，右手捏着剑诀，\n"+
		"左手"+weapon->name()+YEL"不住的抖动，罩向$n上盘七大要穴，剑尖急颤，看不出攻向何处。\n"NOR;     

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("taiji-jian",1)+me->query_skill("yinyun-ziqi",1);
		damage = to_int( damage * skill/150.0);
		damage = damage + random(damage);
		if (damage > 4500 ) damage = 4500 + random(damage-4500)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/4, me);
		me->add("neili", -250);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		i = 0;
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->start_perform(3, "「连」字诀");
	me->delete_temp("tjj/lian");
	if ( skill > 200 ) {
		me->set_temp("tjj/lian", 1);
		perform2(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform2(object me, object target,object weapon, int ap, int dp, int skill, int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg = HIC"\n$N剑上所幻的"+RED+"光圈"+HIC+"越来越多，过不多时，全身已隐在无数"+RED+"光圈"+HIC+"之中，"+RED+"光圈"+HIC+"光圈一个未消，另一个再生，\n"
		"手中"+weapon->name()+HIC"虽使得极快，却丝毫听不到金刃劈风之声，足见剑劲之柔韧已达于化境。\n"
		HIC"$n凝视剑光所幻无数"+RED+"光圈"+HIC+"绞向自己，见无可退避，只得冒险一击，当下手臂一伸，向"+RED+"光圈"+HIC+"的中心挥刃直入。\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 5000 ) damage = 5000 + random(damage-5000)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2+random(damage/2), me);
		me->add("neili", -300);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", "手臂");
		me->start_perform(3+random(2), "「连」字诀");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_perform(3, "「连」字诀");
	}

	msg += HIY"\n$N「连」字诀运行完毕，剑交左手，收剑而立，笼罩在全身上下的大小光圈随即不见踪影。\n\n"NOR;
	me->delete_temp("tjj/lian");
	message_vision( msg, me, target);
	return 1;
}

string perform_name(){ return HIG"三环套月"NOR; }

int help(object me)
{
        write(HIG"\n太极剑法之「三环套月」："NOR"\n\n");
        write(@HELP
	太极剑乃是武当张三丰晚年巅峰之作，是以柔克刚
	的绝学，受张三丰指点后，方可修习。「三环套月」
	属于太极剑的巅峰绝技，可连续攻击三招，是武当
	剑法功夫中极具攻击性的一招，如果使用武器得法，
	威力更甚。
	若解开太极剑融合的谜题，则三环会出现质的飞跃
	请武当弟子要多跟师傅处好关系。

	perform sword.sanhuan
	
要求：
	当前内力要求 2000 以上;	
	最大内力要求 12500 以上；
	太极剑法等级 450 以上；
	氤氲紫气等级 450 以上；
	基本剑法等级 450 以上；
	激发剑法为太极剑法；
	激发招架为太极剑法；
	激发内功为氤氲紫气。

HELP
        );
        return 1;
}
