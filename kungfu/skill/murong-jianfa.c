#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N捏个剑指，一式「洗耳恭听」，双脚后退三步，接着手中$w一晃，直点$n$l",
	"lvl" : 0,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N踏前数步，将手中$w虚点数次，避虚就实，右手使一式「明察秋毫」，直刺$n的$l",
	"lvl" : 30,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「甜言蜜语」，$w抖起五朵洁白的剑花，有急有缓，分别刺向$n的全身大穴",
	"lvl" : 60,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N剑身横摆，剑尖指向$n的脸部，一招「望尘莫及」，宛若万马千军一般，横扫$n的$l",
	"lvl" : 90,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N双脚离地，使出草上飞，身行直奔$n，一招「骑虎难下」，剑出中宫，平削$n的$l",
	"lvl" : 120,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N长笑一声，将$w横削竖切，一招「抛砖引玉」，拉出一道雪亮的剑光，宛若一道闪电，直逼$n而去",
	"lvl" : 150,
	"damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 20)
		return notify_fail("你的神元功火候太浅。\n");
	if ((int)me->query_skill("parry", 1) < 10)
		return notify_fail("你的基本招架火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	level   = (int) me->query_skill("murong-jianfa",1);    
    if( me->query_temp("qixing1") > 0)
       {
              return ([
                        "action" : HIW"星转一斗："WHT"〖"HIY"天枢星"WHT"〗\n\n"HIG"只见$N手中之剑势一抖，笔直刺入$n的"HIC"『天门穴』"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 200 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
            } 
         
             if( me->query_temp("qixing2") > 0)
             {
              return ([
                        "action" : HIM"星斗又见："WHT"〖"HIY"天眩星"WHT"〗\n\n"HIG"只见$N剑势再抖，笔直刺入$n的肩头，$n只觉身上一痛，随即"HIC"『肩井穴』"HIG"传来一阵剧烈刺痛"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 250 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
             } 
         
             if( me->query_temp("qixing3") > 0)
             {
              return ([
                        "action" : MAG"转星见斗："WHT"〖"HIY"天机星"WHT"〗\n\n"HIG"只见$N剑随势上，三剑又出，竟然绝不可能的刺入$n的足底！$n只觉轻微一痛，随即"HIC"『涌泉穴』"HIG"传来一阵剧烈疼痛"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 300 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
             }          
             if( me->query_temp("qixing4") > 0)
             {
              return ([
                        "action" : YEL"星转四斗："WHT"〖"HIY"天权星"WHT"〗\n\n"HIG"只见$N剑抖四星，笔直刺入$n的身体，$n只觉身上被一阵乱刺，随即感到"HIC"『任脉四穴』"HIG"传来一阵剧烈疼痛\n"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 350 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
             } 
             if( me->query_temp("qixing5") > 0)
             {
              return ([
                        "action" : HIB"五星在中："WHT"〖"HIY"玉衡星"WHT"〗\n\n"HIG"只见$N剑走偏锋，笔直刺入$n的腰侧，$n只觉腰上一痒，随即"HIC"『齐门穴』"HIG"竟然喷出血花"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 400 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
             } 
             if( me->query_temp("qixing6") > 0)
             {
              return ([
                        "action" : RED"星聚遇斗："WHT"〖"HIY"开阳星"WHT"〗\n\n"HIG"只见$N抖剑而上，由上而下刺入$n的头顶，$n突然觉得全身真力不续，随即重穴"HIC"『百汇穴』"HIG"竟然疼痛无比"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 450 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
             } 
             if( me->query_temp("qixing7") > 0)
             {
              return ([
                        "action" : HIR"斗转星移："WHT"〖"HIY"谣光星"WHT"〗\n\n"HIG"只见$N剑花连抖，如众星捧剑，任$n奋力闪躲，亦将$n的第一重穴"HIC"『太阳穴』"HIG"刺了两道血迹"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 500 ,
                        "parry": 0 ,
                        "weapon" : "剑气",
                        "damage_type" : "割伤",
                     ]);
          }    


	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/4);
			if (me->query_temp("mrjf/lianhuan") > 0) {
				return ([
					"action" : HIC+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR,
					"force" : 200 +random(100),
					"dodge": random(35),
					"parry": random(35),
					"damage" : 120 + random(100),
					"damage_type" : "刺伤",
				]);
			}
			if (me->query_temp("qixing") > 0) {
				return ([
					"action" : HIB+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR,
					"force" : 200 +random(100),
					"dodge": random(35),
					"parry": random(35),
					"damage" : 100 + random(80),
					"damage_type" : "刺伤",
				]);
			}
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
				"damage": 50 +random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("murong-jianfa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ((int)me->query("jingli") < 40)
		return notify_fail("你的体力不够练慕容剑法。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的体力不够练慕容剑法。\n");
	me->receive_damage("jingli", 30);
	me->receive_damage("neili", 10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"murong-jianfa/" + action;
}

void lianhuan(object me, object victim)
{
	object weapon;
	/*int lh;
	if (me->query_temp("lianhuan"))
     	lh=3;
	else lh=1;*/
	
	if (!me || !victim || !me->is_fighting(victim))
		return;
	weapon = me->query_temp("weapon");
	if(me->query_temp("mrjf/lianhuan")
		&& !me->query_temp("lianhuan_hit")
		&& me->query_skill_prepared("finger") == "canhe-zhi"
		&& me->query_skill_mapped("finger") == "canhe-zhi"
		&& objectp(weapon))
	{
		me->set_temp("lianhuan_hit", 1);
		weapon->unequip();
		if (me->query("shenyuan/super")&&me->is_fighting(victim))
		{   
			//me->add_temp("apply/damage",me->query_skill("canhe-zhi",1)/2);
		    me->add_temp("apply/finger",me->query_skill("canhe-zhi",1)/2);
			me->add_temp("apply/attack",me->query_skill("canhe-zhi",1)/2);
			COMBAT_D->do_attack(me, victim, 0, userp(me)?3:1);
			//me->add_temp("apply/damage",-me->query_skill("canhe-zhi",1)/2);
		    me->add_temp("apply/finger",-me->query_skill("canhe-zhi",1)/2);
			me->add_temp("apply/attack",-me->query_skill("canhe-zhi",1)/2);
		}
		else 
			COMBAT_D->do_attack(me, victim, 0, 1);
		weapon->wield();
		me->add("neili", -30);
		me->delete_temp("lianhuan_hit");
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string *limbs,buwei;
	int damage;
	limbs=victim->query("limbs");
	buwei=limbs[random(sizeof(limbs))]; 
	//连环攻击
	damage=me->query_skill("murong-jianfa",1)+me->query_skill("shenyuan-gong",1)+me->query_skill("douzhuan-xingyi",1);
	damage=damage*2+random(damage);
	if(me->query_temp("mrjf/lianhuan"))
		call_out((: lianhuan :), 1, me, victim);
	//柳絮随机攻击，牵制类
	if (me->query_temp("shenyuan")&&me->query_temp("mrjf/liuxu")&&objectp(victim)&&random(10)>7)
	{
		message_vision(WHT"$N剑招互变，施展出「柳絮剑法」的精意，轻飘飘的没有声响，令$n防不胜防！\n"NOR,me,victim);
		if (random(me->query_skill("murong-jianfa",1))>victim->query_skill("parry",1)/2)
		{
			message_vision(WHT"$n一不小心为这招「柳絮剑法」刺中"+HIR+buwei+WHT",顿时鲜血直流！\n"NOR,me,victim);
			victim->add_busy(1);
			victim->receive_damage("qi",damage,me);
		}
	}

}
