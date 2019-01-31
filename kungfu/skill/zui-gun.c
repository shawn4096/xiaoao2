// zui-gun.c -少林醉棍

#include <ansi.h>
inherit SKILL;
inherit F_SSERVER;
mapping *action = ({
([
	"action":"「蓝采和，提篮劝酒醉朦胧」，$N手中$w半提，脚下蹒跚，缓缓划向$n的$l",
	"lvl" : 0,
	"skill_name" : "蓝采和，提篮劝酒醉朦胧",
	"damage_type":"挫伤"
]),
([
	"action":"「何仙姑，拦腰敬酒醉仙步」，$N摆姿扭腰，右臂挟$w顺势猛地扫向$n的$l",
	"lvl" : 10,
	"skill_name" : "何仙姑，拦腰敬酒醉仙步",
	"damage_type":"挫伤"
]),
([
	"action":"「曹国舅，千杯不醉倒金盅」，$N往前一晃，倒竖$w起，指天打地，向$n的$l劈去",
	"lvl" : 20,
	"skill_name" : "曹国舅，千杯不醉倒金盅",
	"damage_type":"挫伤"
]),
([
	"action":"「韩湘子，铁棍提胸醉拔萧」，$N摇头晃脑，横提$w，棍端划了个半圈，击向$n的$l",
	"lvl" : 40,
	"skill_name" : "韩湘子，铁棍提胸醉拔萧",
	"damage_type":"挫伤"
]),
([
	"action":"「汉钟离，跌步翻身醉盘龙」，$N手中棍花团团，脚步也摇摇摆摆，扫起疾风般向卷向$n",
	"lvl" : 60,
	"skill_name" : "汉钟离，跌步翻身醉盘龙",
	"damage_type":"挫伤"
]),
([
	"action":"「铁拐李，踢倒金山醉玉池」，$N单腿支地，另一腿踢在$w根部荡起，甩向$n的$l",
	"lvl" : 90,
	"skill_name" : "铁拐李，踢倒金山醉玉池",
	"damage_type":"挫伤"
]),
([
	"action":"「张果老，醉酒抛杯倒骑驴」，$N扭身反背，摇摇欲坠，$w从胯底钻出，戳向$n的胸口",
	"lvl" : 120,
	"skill_name" : "张果老，醉酒抛杯倒骑驴",
	"damage_type":"挫伤"
]),
([
	"action":"「吕洞宾，酒醉提壶力千钧」，$N醉眼朦胧，但却举重若轻，手中$w挟千钧之力压向$n",
	"lvl" : 150,
	"skill_name" : "吕洞宾，酒醉提壶力千钧",
	"damage_type":"挫伤"
]),
});

string  *msg = ({
HIG"「蓝采和，提篮劝酒醉朦胧」，$N手中$w"HIG"半提，脚下蹒跚，缓缓划向$n的$l"NOR,
HIY"$P顺势接着「何仙姑，拦腰敬酒醉仙步」，摆姿扭腰，右臂挟$w"HIY"顺势猛地扫向$n的$l"NOR,
HIM"然后一式「曹国舅，千杯不醉倒金盅」，往前一晃，倒竖$w"HIM"起，指天打地，向$n的$l劈去"NOR,
HIC"紧跟着一招「韩湘子，铁棍提胸醉拔萧」，$P摇头晃脑，横提$w"HIC"，棍端划了个半圈，击向$n的$l"NOR,
HIW"接着一招「汉钟离，跌步翻身醉盘龙」，$P手中棍花团团，脚步也摇摇摆摆，扫起疾风般向卷向$n"NOR,
HIB"顺势一试「铁拐李，踢倒金山醉玉池」，$P单腿支地，另一腿踢在$w"HIB"根部荡起，甩向$n的$l"NOR,
HIR"然后「张果老，醉酒抛杯倒骑驴」，$P扭身反背，摇摇欲坠，$w"HIR"从胯底钻出，戳向$n的胸口"NOR,
HIC"最后一式「吕洞宾，酒醉提壶力千钧」，$P醉眼朦胧，但却举重若轻，手中$w"HIC"挟千钧之力压向$n"NOR,
});

int valid_enable(string usage) { return (usage == "club") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "club")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("yijin-jing", 1) < 70)
		return notify_fail("你的易筋经内功火候太浅。\n");
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
	int i, level, j; 
	level   = (int) me->query_skill("zui-gun",1);
	
	if ((int)me->query_temp("zuijiu")) {
		return([
			"action": msg[(int)me->query_temp("zuijiu")-1],
			"force" : 200 + random(300),
			"dodge" : random(35),
			"damage": 180 + random(100),
			"parry": random(35),
			"damage_type" : "砸伤",
		]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"dodge": random(30),
				"damage": 60 + random(100),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("zui-gun", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40 || me->query("neili") < 20)
		return notify_fail("你的体力不够练少林醉棍。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zui-gun/" + action;
}

mixed hit_ob(object me, object target, int damage_bonus)
{
	int i,drunk;

	i = me->query_skill("zui-gun", 1)+me->query_skill("yijin-jing",1)/2;
    drunk=me->query_condition("drunk");
    if(i>=150
	&& random(20)>17
	&& drunk>0)
	  	{
	      
		   message_vision(HIG "只见$N喷出一口酒气，一式「八仙醉酒」，围着$n一摇一摆地走动着。酒气飘来，$n感觉甚是恶心。\n" NOR, me, target);
		   target->receive_damage("jing",drunk); 
		  }           
    
     if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 
		 && drunk>0
		 && random(i)>=350
		 && random(10)>=8)
		 {
             message_vision(HIB" $N脚下看似颠倒不堪，步法紊乱，但却是暗含八卦，防不胜防，出招完全出乎$n意料之外！\n"+HIY"$n不由地心中一慌。\n" NOR, me, target);
             target->start_busy(1+random(3));
		     target->receive_damage("jing",i);
	       } 
       /*else if( (int)random(me->query_str()) > (int)target->query_dex()/2
		  && drunk>0
		  && random(i)>=450) {
             message_vision(HIR " 却见$N脚步向左滑动，但身子却是向后方仰倒，而手中的却是一个横扫千军向$n的双腿扫了过来！\n" NOR, me, target);
		     message_vision(HIW " $n见$N的棍影重重，不知道该王何处躲避，顿时觉得碍手碍脚不得出招！\n" NOR, me, target);
		     target->apply_condition("no_perform",1);
          // target->start_busy(1+random(2));
	       }
	       else {
             // message_vision( CYN "可是$n看破了$N的招数，向后纵了开去。\n" NOR, me, target);
             // me->start_busy(1);
           }
		//}*/
    return 1;
   
}
