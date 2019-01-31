// wudu-bian 五毒鞭 五毒教绝技

#include <ansi.h>

inherit SKILL;
#include <skill.h>


mapping *action = ({
([     "action":   "$N身形不动，一招「飞龙夺珠」，手中$w直奔$n的双目而去",
       "dodge":        10,
       "parry":        20,
       "damage":       20,
       "force":        80,
       "lvl" : 0,
       "skill_name" : "飞龙夺珠",
       "damage_type":  "刺伤"
]),
([     "action":   "$N一招「攀龙附凤」，手中$w如影附形，向$n的颈部卷去",
       "dodge":     15,
       "parry":     20,
       "damage":    30,
       "force":     100,
       "lvl" : 20,
       "skill_name" : "攀龙附凤",
       "damage_type":  "瘀伤"
]),
([     "action":   "$N突然反身后退，待$n迫近时，反手一招「神龙摆尾」，手中$w如离弦之箭，直奔$n的前胸而去",
       "dodge":     10,
       "parry":     12,
       "damage":    50,
       "force":     120,
       "lvl" : 40,
       "skill_name" : "神龙摆尾",
       "damage_type":  "刺伤"
]),
([     "action":   "$N猛地一抖，手中$w化出无数圆环，一招「乌龙绞柱」，圈向$n的上身",
       "dodge":     12,
       "parry":     20,
       "damage":    60,
       "force":     140,
       "lvl" : 60,
       "skill_name" : "乌龙绞柱",
       "damage_type":  "瘀伤"
]),
([     "action":  "$N身形拔起，力贯鞭梢，一招「天龙下凡」，手中$w晃出无数鞭影，朝$n迎头击下",
       "dodge":    15,
       "parry":    20,
       "damage":   80,
       "force":    160,
       "lvl" : 80,
       "skill_name" : "天龙下凡",
       "damage_type":  "瘀伤"
]),
([     "action":  "$N忽地就地一滚，一招「地龙打滚」，手中$w以迅雷不及掩耳之势扫向$n的双腿",
       "dodge":    20,
       "parry":    20,
       "damage":   80,
       "force":    180,
       "lvl" : 100,
       "skill_name" : "地龙打滚",
       "damage_type":  "瘀伤"
]),
([     "action": "$N身形伏低，一招「游龙归巢」，手中$w抖出无数鞭影，对准$n的下身攻去",
       "dodge":   20,
       "parry":   30,
       "damage":   90,
       "force":   200,
       "lvl" : 120,
       "skill_name" : "游龙归巢",
       "damage_type":  "瘀伤"
]),
([     "action": "$N猛地抖直手中的$w，一招「金龙出海」，沿着$n的脚跟直撩而上，直奔$n的头部而去",
       "dodge":   25,
       "parry":   30,
       "damage":  90,
       "force":   210,
       "lvl" : 120,
       "skill_name" : "金龙出海",
       "damage_type":  "瘀伤"
])
});
int valid_enable(string usage) { 
	if (this_player()->query("gender")=="女性")
	{
		return (usage == "whip") || (usage == "parry"); 
	}
}
int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("你的内力不足，没有办法练五毒鞭, 多练些内力再来吧。\n");
       if (me->query("family/family_name")!="日月神教")
               return notify_fail("你非日月神教弟子，领悟不了其中狠辣神韵。\n");
       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你必须先找一条鞭子才能练鞭法。\n");
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
        int i, level;
		string str;
		if (!me) return;
		level=(int) me->query_skill("wudu-bian",1);      

		weapon=me->query_temp("weapon");

		if(me->query_temp("wdb/wudu"))
		{
			switch(me->query_temp("wdb/wudu"))
			{
				case 4: str = HIB"$N手中的"+weapon->query("name")+HIB"，「五毒鞭」的一招厉害招式「"HIG"神龙出洞"HIC"」拧成一股，状若长枪，刺向$n的咽喉"NOR; break;
				case 3: str = HIC"$N身子忽然蹲伏，双脚发力，状如蛤蟆，一式「"HIY"蟾蜍吞"HIC"」向$n使出，将「五毒鞭」由上而下撩向$n"NOR; break;
				case 2: str = HIY"$N急速转身，双手连续挥舞，千手千脚之状，以「五毒鞭」中"HIR"百变蜈蚣"HIY"」招式甩开，鞭尾晃动，抽向$n的周身"NOR; break;
				case 1: str = HIG"$N身子左右忽然急速疾驰，甩动手中的长鞭，将五毒鞭法中「"HIC"蜘蛛爬丝"HIG"」的招式顺势而出"NOR; break;
				default: str = HIR"$N转身奔跑，见$n随后尾随而至，「"HIY"蝎甩尾"HIR"」将手中"+weapon->query("name")+HIR"陡然从胯下飞出，刺向$N的心脏部位"NOR; break;
			}
			me->add_temp("wdb/wudu", -1);
			return ([
				"action":str,
				"damage": 200 + random(50),
				"damage_type": "刺伤",
				"dodge": random(30),
				"parry": random(30),
				"force": 250 + random(250),
			]);
		}

/*
		if (me->query_temp("lsbf/sandou"))
		{						
			return ([
				 "action" :BLU + replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"BLU)+NOR,
				 "dodge":   25,
				 "parry":   30,
				 "damage":  190,
				 "force":   210,
				 "lvl" : 120,
			//"skill_name" : action,
				 "damage_type":  "瘀伤",
			]);						
		}   */     

		for(i = sizeof(action); i > 0; i--)			
			if(level > action[i-1]["lvl"]) 
				return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("你使用的武器不对。\n");
      // if ((int)me->query_skill("tianmo-dafa", 1) < 30)
        //       return notify_fail("你的毒龙大法火候太浅。\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("你的体力不够练五毒鞭。\n");
       me->receive_damage("jingli", 15);
       return 1;
}

string perform_action_file(string action)
{
       return __DIR__"wudu-bian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string msg;
	object weapon;
	int lvl= me->query_skill("wudu-bian", 1);
	weapon=me->query_temp("weapon");

	if (random(10)<6) return;

	if (!weapon||weapon->query("skill_type")!="whip") return;
	
	

	if(random(me->query_skill("wudu-bian", 1)) > 100
		&& me->query("neili") > 1000
		&& me->query_skill("poison",1) > 100
        && random(me->query("neili")) > victim->query("neili")/3)
	{
           // if(victim->query("neili")/3 < me->query("neili"))
			switch(random(5))
			{
				case 0:
					message_vision(BLU"$N鞭影挥动，噼啪作响，在内功激发下，一股若隐若现的「"HIG"蛇毒"BLU"」弥漫，侵入$n的奇经八脉。\n"NOR,me,victim);
					victim->add_condition("snake_poison", 1);
					break;
				case 1:
					message_vision(MAG"$N劲力吞吐，一股灰色的「"WHT"蜈蚣毒"MAG"」顺着"+weapon->query("name")+MAG"侵入$n的奇经八脉。\n"NOR,me,victim);
					victim->add_condition("wugong_poison", 1);
					break;
				case 2:
					message_vision(CYN"$N暗自运功，一股血红色的「"HIR"蝎子毒"CYN"」顺着"+weapon->query("name")+CYN"侵入$n的任脉。\n"NOR,me,victim);
					victim->add_condition("xiezi_poison", 1);
					break;
				case 3:
					message_vision(YEL"$N顺手一抽，一股蓝汪汪的「"HIB"蜘蛛毒"YEL"」顺着"+weapon->query("name")+YEL"侵入$n的奇经八脉。\n"NOR,me,victim);
					victim->add_condition("zhizhu_poison", 1);
					break;
				case 4:
					message_vision(WHT"$N凝鞭成环，推送出一股「"HIY"蟾蜍毒"WHT"」顺着"+weapon->query("name")+WHT"侵入$n的奇经八脉。\n"NOR,me,victim);
					victim->add_condition("hama_poison", 1);
					break;
			}
			
	}
	   
}
