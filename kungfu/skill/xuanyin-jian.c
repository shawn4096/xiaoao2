// 玄阴剑法
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : HIB"$N一举手中的$w"+HIB+"，向前直攻，正是一招「阴阳绝路」直指$n"+HIB+"的$l"NOR,
	"skill_name" : "阴阳绝路",
	"lvl" : 0,
	"damage_type" : "刺伤"
]),
([
	"action" : HIM"$N使出「阴阳轮回」，$w"+HIM+"左右摇摆不定，摇摇晃晃得刺向$n"+HIM+"的$l"NOR,
	"skill_name" : "阴阳轮回",
	"lvl" : 30,
	"damage_type" : "割伤"
]),
([
	"action" : HIW"$N一招「阴风袭体」，$n"+HIW+"一呆，$l已经被$N击中"NOR,
	"skill_name" : "阴风袭体",
	"lvl" : 50,
	"damage_type" : "刺伤"
]),
([
	"action" : HIC"$N跃起丈余，手中$w"+HIC+"画了个弧线，斜斜划下，「阴徊九天」，击向$n"HIC"的$l"NOR,
	"skill_name" : "阴徊九天",
	"lvl" : 70,
	"damage_type" : "割伤"
]),
([
	"action" : HIG"$N剑交左手，突然挥$w"+HIG+"反撩而上，一式「玄阴剑」，迅捷无比的攻向$n"+HIG+"的$l"NOR,
	"skill_name" : "玄阴剑",
	"lvl" : 90,
	"damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if (!(weapon = me->query_temp("weapon")))
		return notify_fail("空手时无法练玄阴剑法。\n");
	if ((string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对，无法练玄阴剑法。\n");
	if ((int)me->query("max_neili") < 60)
		return notify_fail("你的内力不够。\n");
	if ( me->query_skill("xuanyin-jian", 1) < 150 )
		return notify_fail("你的玄阴剑法等级还不够练习。\n");
	if ((int)me->query_skill("jiuyin-zhengong", 1) < 50)
		return notify_fail("你的九阴真功火候太浅。\n");
	if (me->query_skill_mapped("force") != "jiuyin-zhengong")
		return notify_fail("修习玄阴剑法必须有九阴真气配合。\n");
	return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}


mapping query_action(object me, object weapon)
{
	int i, j, level;

	level   = (int) me->query_skill("xuanyin-jian",1);
	for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			
			
			
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"damage":	200 + random(180),
				"force":	300 + random(350),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 60 || me->query("neili") < 30)
		return notify_fail("你的体力不够练玄阴剑法。\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuanyin-jian/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	object wp,wp1;
	string msg;
	int p,j,skill, neili, neili1, exp, exp1;
	wp = me->query_temp("weapon");
	wp1 = ob->query_temp("weapon");
	skill = me->query_skill("xuanyin-jian", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");
	exp = me->query("combat_exp");
	exp1 = ob->query("combat_exp");

	if( me->query("jiali") 
	&& skill+50 > random(ob->query_skill("parry", 1)/3)
	&& wp 
	&& skill > 100
	&& me->query_skill_mapped("parry") == "xuanyin-jian"
	&& living(ob)
	&& !me->is_busy()){
		if(wp1){
			msg = HIW"$N剑刃一封，运起九阴真功一震！\n"NOR;
			msg = replace_string(msg, "$w", wp1->name());
			if(neili >= random(neili1+damage)){
				if(random(me->query_str(1)) > ob->query_str(1)/3 && skill > 120){
					msg += HIW"$n手中"+wp1->name()+HIW"被$N一震，险些落手！\n"NOR;
					ob->add_busy(2+random(2));
					j = -(damage);
				}
				else{
					ob->receive_damage("qi", damage/10, me);
					ob->receive_wound("qi", damage/10, me);
					p = ob->query("qi")*100/ob->query("max_qi");
					msg += COMBAT_D->damage_msg(damage/20, "伤害");
					msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
					j = -(damage/2+skill/2);
				}
			}
			else if(neili >= random(neili1)+damage){
				msg += "结果把$n的攻势阻了一阻。\n";              
				j = -(damage/2+skill/2);
			}
			else{
				j = damage/2+random(damage/2);
				if(j<damage/2) msg += "结果九阴真气把$n大半的力道消解了去。\n";
				else msg += "结果以九阴真气把$n大半的力道消解了去。\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
		else{
			msg = HIY"$N剑刃一转，向$n中宫直进！\n"NOR;
			if(neili >= neili1+random(neili1)+damage){
				ob->receive_damage("qi", damage/10, me);
				ob->receive_wound("qi", damage/10, me);
				p = ob->query("qi")*100/ob->query("max_qi");
				msg += COMBAT_D->damage_msg(damage, "内伤");
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
				j = -(damage*2+skill);
			}
			else if(neili >= random(neili1)+damage){
				msg += "结果将$n的攻势阻了一阻。\n";              
				j = -(damage+skill);
			}
			else{
				j = damage/2+random(damage/2); 
				if(j<damage/2) msg += "结果九阴真气把$n一些力道转移开去。\n";
				else msg += "结果九阴真气把$n一些力道转移开去。\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
	}
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weap,weap1;
	int ap, dp,skill,skill1;
	weap = victim->query_temp("weapon");
	weap1 = me->query_temp("weapon");
	skill=me->query_skill("jiuyin-zhengong",1);
    skill1=me->query_skill("xuanyin-jian",1);
//打兵器
	if( me->query_temp("jiuyin/powerup")
	 && me->query_skill("xuanyin-jian", 1) > 450
	 && me->query("neili") > 2000
	 && victim->query_temp("weapon")
	 && random(me->query_skill("xuanyin-jian",1)) > victim->query_skill("dodge", 1)/2 
	 && random(10) > 3) {
		message_vision(HBBLU+WHT"只见$N"+ weap1->name() + HBBLU+WHT"在九阴真气作用下，形成无数个劲气暗流，" + weap->name() +HBBLU+WHT"顿觉有把持不住的趋势！\n" NOR, me );
		
		ap = me->query("combat_exp", 1) /1000 * me->query_int(1);
		dp = victim->query("combat_exp", 1) /1000 * victim->query_int(1);
		if (random(ap + dp ) > dp ) {
			message_vision(HIC"$n劲力被这么一带，登时身不由主，连转了几个七八个圈子，"+ weap->name()+ HIY"脱手而去。\n" NOR, victim );
			weap->move(environment(me));
			victim->add_busy(2);
			//victim->reset_action();
		}
		else {
			message_vision(HIY"$n暗运巧劲，"+ weap->name()+ HIY"顺着方向快速旋转数下，解开了"+weap1->name()+HIY"的缠绕。\n" NOR, victim );
			victim->add("neili", -50);
		}
		me->add("neili", -(20+random(30)));
	}
	//断手断脚
    //移魂效果
	if (me->is_fighting()&&objectp(victim)&&me->query_temp("jiuyin/powerup")&&!random(3))
	{
	
	  switch (random(4)) {
	    case 0:
			message_vision(HIR"$N暗哼一声，九阴真气附着在"+weap1->query("name")+HIR"上，威力陡增。\n"NOR,me,victim);
          if (random(me->query_str(1))>victim->query_str(1)/4)
          {
		    message_vision(HIR"$N心中舒畅，剑气纵横，数招连发。\n"NOR,me,victim);
			me->add_temp("apply/damage",skill/6);
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			//COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			me->add_temp("apply/damage",-skill/6);
          }else {
			message_vision(HIY"$n武功娴熟无比，疾攻数招以求缓解压力。\n"NOR,me,victim);
            
		   }
	    break;
	    case 1:
		 message_vision(HIG"$N九阴身法运转如意，快如闪电，奔赴往来，趁$n忙碌之际，反手一剑刺向$n。\n"NOR,me,victim);
	     if (random(me->query_dex(1))>victim->query_dex(1)/4)
          {
		    message_vision(HIR"$n哪里料到这剑法竟然如此诡异，匆忙间躲闪不及，被一剑刺中胸口。\n"NOR,me,victim);
			victim->receive_damage("qi",skill1*4,me);
          }else {
			message_vision(CYN"$n轻功了得，急忙铁板桥功夫躲开，但却吓了一身冷汗。\n"NOR,me,victim);
            me->add_busy(2);
			victim->add_busy(1);
		   }

	    break;
	    case 2:
         message_vision(HIM"$N忽然间施展出玄阴十二剑的招式，宛如狂风暴雨。\n"NOR,me,victim);
	     if (random(me->query_int(1))>victim->query_int(1)/3)
          {
		    message_vision(RED"$n顿觉剑气弥漫，顿觉处处受制，恍惚间为$N一剑砍中手腕。\n"NOR,me,victim);
            victim->set_temp("must_be_hit", 1);
		    COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
		    victim->delete_temp("must_be_hit");
            victim->apply_condition("broken_arm",1); 
			victim->apply_condition("no_perform",2);
          }else {
			message_vision(MAG"$n见多识广，看破了$N的企图，闪身躲开。\n"NOR,me,victim);
            me->add_busy(1);
			victim->add_busy(1);
		   }
	    break;
        case 3:
         message_vision(HIM"$N九阴真气汹涌澎湃，剑势灵动，婉转如意,全是$n所难以料到的方位。\n"NOR,me,victim);
	     if (random(me->query("combat_exp"))>victim->query("combat_exp")/3)
          {
		    message_vision(BLU"$N的"+weap1->query("name")+BLU"竟然发出阵阵颤音，$n只觉心烦意乱，精力消耗在加快。\n"NOR,me,victim);
            victim->receive_damage("jingli",random(skill1),me);
			victim->receive_damage("jing",random(skill1)/2,me);
          }else {
			message_vision(HIC"$n暗运真气，抵消了$N玄阴剑的影响。\n"NOR,me,victim);         
		   }
	    break;
	   }
     }
	return 1;
}