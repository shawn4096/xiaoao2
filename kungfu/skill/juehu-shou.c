// juehu-shou.c -虎爪绝户手

inherit SKILL;
#include <combat.h>
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N一式「老牛拉车」，以掌化爪，五指如钩，两眼瞪得通红，直逼$n的裆部",
	"lvl" : 0,
	"skill_name" : "老牛拉车",
	"damage_type" : "抓伤"
]),
([
	"action" : "$N四肢贴地，头部底垂，看似已无力进攻，突然四肢用力一扒已窜到$n跨下，两手猛的上戳，好一式「精疲力尽」",
	"lvl" : 130,
	"skill_name" : "精疲力尽",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N两手高高举起，运掌如风，一式「壮士断腕」，闭眼就朝$n的下体砍去",
	"lvl" : 150,
	"skill_name" : "壮士断腕",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N一跃而起，直往$n的双肩落下，双腿盘住$n的颈部，一扭腰，双手成关门之势，往$n的裆部狠狠拍去，正是一式「落叶归根」",
	"lvl" : 180,
	"skill_name" : "落叶归根",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N使一式「空前绝后」，身形一分为二，四只手掌有如熊掌般朝$n的后腰和裆部拍去",
	"lvl" : 250,
	"skill_name" : "空前绝后",
	"damage_type" : "内伤"
]),
([
	"action" : "$N全身关节啪啪作响，面如白纸，一式「断子绝孙」，无数鹰爪抓向$n全身要害，瞬间无数鹰爪又合为一爪直往$n的裆部抓落",
	"lvl" : 350,
	"skill_name" : "断子绝孙",
	"damage_type" : "抓伤"
]),
([      "action":  "$N全身关节啪啪作响，面如白纸，一式「断子绝孙」抓向$n的腰眼部位！"  ,
         "lvl" : 200,
        "skill_name" : "绝户",
        "damage_type": "抓伤"
]),
([      "action":  "$N左手向前，化抓为指，戳向$n的小腹，右手变掌，拍向$n的右腰！" ,
         "lvl" : 250,
        "skill_name" : "断子",
        "damage_type": "戳伤"
]),
([      "action": "$N身子一拧，身法陡然加快，在$n毫无准备的前提下转到$n的后方，抓向$n的双腰！"  ,
         "lvl" : 300,
        "skill_name" : "双手摘桃",
        "damage_type": "抓伤"
]),
});

mapping *action_jh = ({
([      "action": HIR "$N全身关节啪啪作响，面如白纸，一式「断子绝孙」抓向$n的腰眼部位！" NOR ,
        "force" : 0,
        "dodge" : 0,
        "lvl" : 200,
        "skill_name" : "绝户",
        "damage_type": "抓伤"
]),
([      "action": HIC "$N左手向前，化抓为指，戳向$n的小腹，右手变掌，拍向$n的右腰！" NOR ,
        "force" : 0,
        "dodge" : 0,
         "lvl" : 150,
        "skill_name" : "断子",
        "damage_type": "戳伤"
]),
([      "action": MAG "$N身子一拧，身法陡然加快，在$n毫无准备的前提下转到$n的后方，抓向$n的双腰！" NOR ,
        "force" : 0,
        "dodge" : 0,
        "lvl" : 100,
        "skill_name" : "双手摘桃",
        "damage_type": "抓伤"
]),
});
int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
	if(!me->query("quest/wudang/juehu")) return notify_fail("本武功需请教俞莲舟方可练习。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练虎爪绝户手必须空手。\n");
	if ((int)me->query_skill("yinyun-ziqi", 1) < 40)
		return notify_fail("你的氤氲紫气火候不够，无法学虎爪绝户手。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练虎爪绝户手。\n");
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
	level   = (int) me->query_skill("juehu-shou",1);
	
    if (me->query_temp("wudang/juehu"))
	{
		for(i = sizeof(action_jh); i > 0; i--) {
		  if(level > action_jh[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				//"action": action_jh[j]["action"],
				"action":HIR+action[j]["action"]+NOR,
				"lvl": action_jh[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(300),
				"parry":random(300),
				"damage":200+random(100),
			]);
		  }
	    }
	}
	else
	{
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(30),
				"dodge":random(30),
				"parry":random(30),
			]);
		  }
	 }
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 40)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练虎爪绝户手。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	//me->add("shen", -100);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"juehu-shou/" + action;
}

mixed hit_ob(object me, object target, int damage_bonus)
{
        string msg;
		int i,j;
		i=me->query_skill("juehu-shou",1);
		j=me->query_skill("yinyun-ziqi",1);
		if (random(me->query_dex(1))>target->query_con(1)/2
		&& me->query_skill("juehu-shou",1)>350
		&& me->query_skill_mapped("hand")=="juehu-shou"
		&& me->query_skill_prepared("hand")=="juehu-shou"
		&& target->query("gender")=="男性"
		&& !random(4)
		)   {
              msg = MAG"$N冷哼一声，心中恨其歹毒，手变虎爪，使出一招【虎抓手】。\n"NOR;
			  if (random(me->query_skill("hand",1)) > target->query_skill("parry",1)/2) {
                  msg += HIR"$N一抓拿捏住$n的腰眼，$n忽觉腰眼一阵剧痛传来，忍不住吐了一口鲜血。\n"NOR;      
                  target->start_busy(1+random(2));
				  target->receive_damage("qi",i+j*2,me);
				  target->receive_wound("qi",j/2,me);
                  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
				  target->apply_condition("juehu_busy",2);
				  target->apply_condition("juehu_hurt",2);
				  //target->set("gender","无性");
			  }    
			   else {
                  msg += HIC"$n识破了$N的意图，冷哼一声，闪了开去。\n"NOR;
				  me->add_busy(1+random(1));
				  }
              message_vision(msg, me, target);
        }
        return 1;
        
}
