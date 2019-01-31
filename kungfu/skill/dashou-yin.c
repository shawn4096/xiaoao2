// dashou-yin.c 密宗大手印
//  by iceland
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action" : "$N使出一招「莲花合掌印」，双掌合十，直直撞向$n的前胸",
	"skill_name" : "莲花合掌印",
	"lvl" : 0,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「合掌观音印」，飞身跃起，双手如勾，抓向$n的$l",
	"skill_name" : "合掌观音印",
	"lvl" : 10,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「准提佛母印」，运力于指，直取$n的$l",
	"skill_name" : "准提佛母印",
	"lvl" : 20,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「红阎婆罗印」，怒吼一声，一掌当头拍向$n的$l",
	"skill_name" : "红阎婆罗印",
	"lvl" : 30,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「药师佛根本印」，猛冲向前，掌如游龙般攻向$n",
	"skill_name" : "药师佛根本印",
	"lvl" : 40,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「威德金刚印」，伏身疾进，双掌自下扫向$n的$l",
	"skill_name" : "威德金刚印",
	"lvl" : 50,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「上乐金刚印」，飞身横跃，双掌前后击出，抓向$n的咽喉",
	"skill_name" : "上乐金刚印",
	"lvl" : 60,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N使出一招「六臂智慧印」，顿时劲气弥漫，天空中出现无数掌影打向$n的$l",
	"skill_name" : "六臂智慧印",
	"lvl" : 70,
	"damage_type" : "瘀伤",
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练密宗大手印必须空手。\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力太弱了，练不了密宗大手印。\n");
	if ( me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("你的龙象般若功火候太浅，不能学密宗大手印。\n");
	if ( me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功火候太浅，不能学密宗大手印。\n");
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
	level   = (int) me->query_skill("dashou-yin",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) 
		{
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("dls/dsy"))
			{
				return ([  
				"action": YEL+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage":180+random(80),
				"damage_type" : action[j]["damage_type"],
				//"weapon": action[j]["weapon"],
				"force":100+random(250),
				"dodge":random(20)-10,
				"parry":random(10),
			   ]);
			}
			else{
				return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage":50+random(50),
				"damage_type" : action[j]["damage_type"],
				//"weapon": action[j]["weapon"],
				"force":100+random(250),
				"dodge":random(20)-10,
				"parry":random(10),
				]);
			}
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("dashou-yin", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("你的体力不够，练不了密宗大手印。\n");
	if ( me->query("neili") < 10)
		return notify_fail("你的内力不够，练不了密宗大手印。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dashou-yin/" + action;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
	if (!me) return;

    j = me->query_skill("dashou-yin", 1);
	if (!target) return;

	if (!me->query("quest/dls/dsy/tianyin/pass")) return;
	
    if (objectp(target)
		&& random(me->query_con()) >= target->query_con()/4 
		&& j > 120 
		&& me->query_skill("parry",1) > 120 
		&& me->query("jingli")>300 
		//&& !target->is_busy()
		&& !random(3) 
		&& random(me->query("combat_exp")) > target->query("combat_exp")/2 
		&& me->query("neili")>500)
     {
          switch(random(2))
          {
            case 0 :
               message_vision(HIG "$N默运大手印，内劲聚于双掌攻向$n，一股霸道内劲涌入$n的手三焦经脉！\n"+
								 "$n只觉从手到心有被撕裂般的难受，显然"HIR"「心脉」"HIG"已经为$N所伤！\n"NOR,me,target); 
               target->receive_damage("qi", j*3 +random(1000),me);
               target->add_condition("dsy_poison", 1);
			   me->add("neili",-60);
               break;
            case 1 :
               message_vision(HIY "$N手捏成宝瓶状，神态庄严，巍然不动，宛如金刚怒目。$n见此恶相，不由地大吃一惊。\n"NOR,me,target);
               target->add_busy(1+random(2));
               me->add("neili",-50);
               //message_vision(msg, me, target);               
               break;
            
          }         
       //   message_vision(msg, me, target);
   }
   
}
