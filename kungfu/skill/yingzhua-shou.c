// qingzhua-shou.c 鹰爪擒拿手
#include <ansi.h>
inherit SKILL;
mixed hit_ob(object me, object target, int damage);

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
}); 

string *limb=({
"颈部","后心","右腿","头部","小腹","胸口","腰间","裆部","右肩","右臂","右脚",
});
mapping *action = ({
([
	"action" : "$N一式「金针渡线」，右手抬起，左手暗藏，突然拍向$n的$l",
	"lvl" : 0,
	"skill_name" : "金针渡线",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N侧身一晃，一式「双阳沓手」，左手拿向$n的肩头，右拳打向$n的胸口",
	"lvl" : 10,
	"skill_name" : "双阳沓手",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N一式「飞鹰现爪」，双手环拢成爪，左手护体，右手扣向$n的$l",
	"lvl" : 20,
	"skill_name" : "飞鹰现爪",
	"damage_type" : "抓伤"
]),
([
	"action" : "$N身形住回一撤，一个斜身塌式，一式「大鹏展翅」，右掌向$n扫下",
	"lvl" : 30,
	"skill_name" : "大鹏展翅",
	"damage_type" : "抓伤"
]),
([
	"action" : "$N使一式「孔雀剔翎」，一个闪身，左脚飞起，向$n的裆部踹去",
	"lvl" : 40,
	"skill_name" : "孔雀剔翎",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N右手一伸，一式「猿猴摆手」，手臂突然长了数倍，在$n的$l一拂",
	"lvl" : 50,
	"skill_name" : "猿猴摆手",
	"damage_type" : "抓伤"
]),
([
	"action" : "$N双手抱拳，一式「自在飞花」，左手慢慢的拍出，飘逸绝纶的拍向$n的$l",
	"lvl" : 60,
	"skill_name" : "自在飞花",
	"damage_type" : "内伤"
]),
([
	"action" : "$N一式「雨打飞花」，整个身体歪歪斜斜，右手斜斜的拍向$n的$l",
	"lvl" : 70,
	"skill_name" : "雨打飞花",
	"damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练鹰爪擒拿手必须空手。\n");
	if ( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 20)
		return notify_fail("你的圣火神功火候不够，无法学练鹰爪擒拿手。\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练鹰爪擒拿手。\n");
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
	level   = (int) me->query_skill("yingzhua-shou",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if (me->query_temp("yzs/yingyang"))
			{
				return ([
				"action": HIY+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"damage":me->query("mj/quest/yzs")?180+random(80):130+random(50),
				"dodge": random(30),
				"parry": random(30),
				]);

			}
			
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"damage":100+random(50),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("yingzhua-shou", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 30)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("你的内力不够练鹰爪擒拿手。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}
mixed hit_ob(object me, object target, int damage)
{
     object weapon = me->query_temp("weapon");
	 string msg,name,dodge_skill,limb;
	 int ap,dp,lvl;
	 if (!me || !target) return;
	 lvl=me->query_skill("yingzhua-shou", 1);
     if( me->query_skill("yingzhua-shou",1 ) > 200
	 	 && me->query_skill_mapped("hand") == "yingzhua-shou"
		 && me->query_skill_prepared("hand") == "yingzhua-shou"
		 && !random(3)
		 && !target->is_busy()){
			name = xue_name[random(sizeof(xue_name))];
			message_vision(HIC"\n$N紧跟着上前一步，乘对方不备之际，左手变掌为鹰爪之势，自左向右抓向$n的"+HIG+name+HIC"。\n"NOR,me,target);

			ap = me->query("combat_exp")/ 1000 ;
			dp = target->query("combat_exp") / 1000;
            target->start_busy(1);
			if( (random(ap + dp) > dp && me->query("mj/quest/yzs"))) {
				me->add("neili", -100);
				message_vision(CYN"结果$n的"+name+"被抓个正着，全身不由自主的一颤，顿时不可动弹。\n"NOR,me,target);
				target->add_busy( random((int)lvl/50) + 2);
				
				//if (weapon) weapon->unequip();
                me->add_temp("apply/hand",lvl/8);
				me->add_temp("apply/damage",lvl/8);
				message_vision(HIY"\n$N对$n大喝一声，施展出白眉鹰王的拿手绝技【鹰抓手】！\n"NOR,me,target);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                me->add_temp("apply/hand",-lvl/8);
				me->add_temp("apply/damage",-lvl/8);
				//weapon->wield();
			   }
         
			else {
				dodge_skill = target->query_skill_mapped("dodge");
				if( !dodge_skill ) dodge_skill = "dodge";
				//msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
				me->add("neili", -50);
			   }
			
		
		  }
 }
string perform_action_file(string action)
{
	return __DIR__"yingzhua-shou/" + action;
}
