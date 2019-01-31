// canhe-zhi.c 参合指
// by leontt 1/5/2000

#include <ansi.h>
inherit SKILL;
void back(object target);
mapping *action = ({
([
	"action" : "$N劲风激荡，双指错落搭置，一招「目不识丁」凶狠地向$n的$l插去",
	"lvl" : 0,
	"skill_name" : "目不识丁",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N大吼一声，十指上下分飞，一招「画龙点睛」，双指直取$n的$l",
	"lvl" : 20,
	"skill_name" : "画龙点睛",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N十指互错，虚幻虚实，一招「扑朔迷离」，前后左右，瞬息间向$n攻出了六招",
	"lvl" : 40,
	"skill_name" : "扑朔迷离",
	"damage_type" : "刺伤",
]),
([
	"action" : "$N身行腾空而起，一招「受宠若惊」，来势奇快，向$n的$l猛插下去",
	"lvl" : 60,
	"skill_name" : "受宠若惊",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N身行一闪，若有若无捱到$n身前，一招「滔滔不绝」，插向$n的$l",
	"lvl" : 70,
	"skill_name" : "滔滔不绝",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「退避三舍」，右手一拳击出，左掌化指，一掌一指凌空击向$n的$l",
	"lvl" : 80,
	"skill_name" : "退避三舍",
	"damage_type" : "内伤"
]),
([
	"action" : "$N双掌化指，指中带掌，双手齐推，一招「卧薪尝胆」，一股排山倒海的内力，直扑$n$l",
	"lvl" : 90,
	"skill_name" : "卧薪尝胆",
	"damage_type" : "内伤"
]),
([
	"action" : "$N突然身行急转，一招「相煎何急」，十指飞舞，霎时之间将$n四面八方都裹住了",
	"lvl" : 100,
	"skill_name" : "相煎何急",
	"damage_type" : "震伤"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练参合指必须空手。\n");
	if ( me->query_skill("shenyuan-gong", 1) < 15)
		return notify_fail("你的神元功火候不够，无法学参合指。\n");
	if ( me->query("family/master_name")!="慕容博")
		return notify_fail("参合指只能跟慕容博方可修习。\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练参合指。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("canhe-zhi",1);
   

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
            //凌空虚点
			if( me->query_temp("chz/ch")){
				return ([  
					"action": HIR+action[j]["action"]+NOR,
					"lvl" : action[j]["lvl"],
                    "force" : 150 + random(100),
                    "dodge": random(30)- 5 ,
                    "damage": 200 + random(50),
                    "parry": random(150),
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			if( me->query_temp("chz/ci")){
				return ([  
					"action": CYN+action[j]["action"]+NOR,
					"lvl" : action[j]["lvl"],
                    "force" : 150 + random(100),
                    "dodge": random(30)- 5 ,
                    "damage": 180 + random(50),
                    "parry": random(150),
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			//剑指连环
			if (me->query_temp("mrjf/lianhuan") && (int)me->query_skill("canhe-zhi",1) > 349) {
                   return ([
                           "action": HIG+action[j]["action"]+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 350 + random(350),
                           "dodge": 20+random(35),
                           "parry": 10+random(20),
					       "damage": 150+random(50),
                   ]);
			}
            else {
				return ([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 100+random(50),
				]);
			}
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("canhe-zhi", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("你的精力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练参合指。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{        
	return __DIR__"canhe-zhi/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	string msg;
	int j;
	j = me->query_skill("canhe-zhi", 1);
	
	if (!objectp(victim)) return;

	if (me->query("shenyuan/powerup"))
	{
		j=j+me->query_skill("shenyuan-gong", 1);
	    j=j+random(j);
	}
	//if ( me->query_temp("mr_ci") ) return 0;
  
	if ( random(me->query_str(1)) >= victim->query_dex(1)/3
		&&j > 120 
		&& random(10) > 5
	 	&& random(me->query("combat_exp")) > victim->query("combat_exp")/2
		&& me->query("neili") > 500
		&& me->query("canhe/pass")) 
       {
		switch(random(6)) {
			case 0 :
				message_vision( HIW"$N一招「拈花指」使出，指风轻飘飘地点向$n，形成无声无息的内劲绕向$n周身大穴！\n",me,victim);
				message_vision( HIR"$n只觉全身一麻，已被一招点中「膻中穴」！\n"NOR,me,victim); 
				victim->add_busy(1+random(3));
				me->add("neili",-random(300));
				break;
			case 1 :
				message_vision(CYN"$N指风犀利，「修罗指」似一道无形剑气，将$n笼罩于内！$n只觉胸口一痛，全身真气狂泻而出。\n"NOR,me,victim);
				victim->recevied_damage("neili", j);
				if ( victim->query("neili") < 0 )
					victim->set("neili", 0);
				me->add("neili",-random(500));
				break;

            case 2 :
				message_vision(HIR"$N演化成「大力金刚指」之势，简单朴实无华，直接戳向$n的胸口。\n",me,victim);
			    message_vision(RED"$n只觉心口为其一指戳中，一股剧痛传来，鲜血狂喷而出！\n"NOR,me,victim); 
				victim->recevied_damage("qi", random(1500),me);
				victim->recevied_wound("qi", random(500),me);
				me->add("neili",-random(200));
				break;
		    case 3 :
				message_vision(HIY"$N又形成「多罗叶指」，从小指到拇指依次展开，宛如花开。袭击向$n的「太阳穴」。\n",me,victim);
			    message_vision(RED "$n忽然大脑两侧宛如遭到雷击般，轰鸣作响，同时传来一阵眩晕！\n"NOR,me,victim); 
				victim->recevied_damage("jing", random(500),me);
				victim->recevied_wound("jing", random(200),me);
				me->add("neili",-random(300));
				break;
            case 4 :
				message_vision(HIG"$N轻飘飘转到$n的身后，「一指禅」劲力涌出，化作乾坤一击，戳向$n的「大椎穴」\n",me,victim);
			    message_vision(HIR"$n忽然周身一阵酸麻，宛如成千成万的蚂蚁在身上爬咬般的难受！\n"NOR,me,victim); 
				victim->recevied_damage("jingli", random(800),me);
				victim->recevied_wound("jingli", random(300),me);
				me->add("neili",-random(300));
				break;
			case 5 :
				message_vision(HIR"$N顺接上式，招式又变为「二指禅」功夫，戳向$n的「双目」，令$n目不暇接。\n"NOR,me,victim);
			    if (random(me->query_str(1))>victim->query_dex(1)/3)
			    {
					message_vision(HIY"$n忽然双目为二指禅指风劲力所伤，一阵酸痛传来，顿时陷入一片黑暗之中！\n"NOR,me,victim); 		

					victim->set_temp("chuomu", 1);
                    victim->add_temp("apply/attack", - 200);
                    victim->add_temp("apply/dodge", - 200);
                    victim->add_temp("apply/parry", -150);
                    victim->receive_damage("qi", random(1500),me);
                    victim->receive_wound("qi", random(800),me);
                    victim->set_temp("block_msg/all",1);
                    call_out("back", 20+random(10), victim);
			    }
				else {
					
					message_vision(HIC "$n急忙向旁边闪开这招致命的杀招，但全身却不禁被吓得冷汗淋淋！\n"NOR,me,victim); 
                    me->add_busy(1+random(1));
				}
			    
				me->add("neili",-random(150));
				break;
		  }
		//message_vision(msg, me, victim);
	}
}


void back(object target)
{
	if(!target) return;
        target->add_temp("apply/attack", 200);
        target->add_temp("apply/dodge", 200);
        target->add_temp("apply/parry", 150);
        target->set_temp("block_msg/all", 0);
		
        if(living(target)) 
              tell_object(target, HIW "啊！总算双目没有被真正刺伤，你又可以看见事物啦！\n" NOR);
        target->delete_temp("chuomu");
	return;
}
