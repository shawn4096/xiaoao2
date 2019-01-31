// longzhua-gong.c -龙爪功

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "只听“哧”的一声，急风响过，$N使一招「捕风式」，右手猛然探出，去势犹如闪电",
	"lvl"   : 0,
	"skill_name" : "捕风式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N凌空掠起，动作有如长虹惊天，一招「捉影式」，如矢应机，霆不暇发",
	"lvl"   : 10,
	"skill_name" : "捉影式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N手腕一翻，使出「抚琴式」，十指微微上下抖动，气流相交的“呲呲”声登时有如繁弦急管一般",
	"lvl"   : 20,
	"skill_name" : "抚琴式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N催动内力，双爪互错，使出「鼓瑟式」，招招连绵不绝，犹似行云流水一般",
	"lvl"   : 40,
	"skill_name" : "鼓瑟式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N使一招「批亢式」，招数纵横开阖，内力浑雄，猛地击向$n的$l",
	"lvl"   : 60,
	"skill_name" : "批亢式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N凌空翻身，右手带着凌厉风声，一招「掏虚式」击向$n的$l",
	"lvl"   : 80,
	"skill_name" : "掏虚式" ,               
	"damage_type" : "抓伤"
]),
([ 
	"action" : "$N招招进逼，一招「抢珠式」，直取$n$l，每一爪都有石破天惊，风雨大至之势",
	"lvl"   : 100,
	"skill_name" : "抢珠式" ,               
	"damage_type" : "抓伤"
]),
([
	"action" : "$N身形流转，飕飕飕连环三爪，一招「捞月式」，破空之声甚是凌厉",
	"lvl"   : 120,
	"skill_name" : "捞月式" ,               
	"damage_type" : "抓伤"
]),
/*
([
	"action" : "$N骨节“咯咯咯”一阵暴响，手臂徒长半尺，一招「抱残式」，五指猛然叉向$n胸前大穴",
	 "lvl"   : 150,
	"skill_name" : "抱残式" ,               
	"damage_type" : "抓伤"
]),
([ 
	"action" : "$N猛地一声低嗥，爪法忽变，一招「守缺式」出招随缓，但力道却凝重强劲",
	"lvl"   : 180,
	"skill_name" : "守缺式" ,               
	"damage_type" : "抓伤"
])
*/
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 40)
		return combo=="yizhi-chan"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练龙爪功必须空手。\n");
	if ((int)me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("你的易筋经内功火候不够，无法学龙爪功。\n");
	if ((int)me->query_int(1) > 30) {
		return 1;
	}
	else {
		if ( me->query_skill("banruo-zhang", 1)
		 && me->query_skill("yizhi-chan", 1)
		 && me->query_skill("jingang-quan", 1)
		 && me->query_skill("nianhua-zhi", 1)
		 && me->query_skill("qianye-shou", 1)
		 && me->query_skill("ruying-suixingtui", 1)
		 && me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法练龙爪功。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	string msg;
	
	level = (int) me->query_skill("longzhua-gong",1);
	for(i = sizeof(action); i > 0; i--) 	{
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			/*
			if(me->query_temp("baocan")) {
				switch(me->query_temp("baocan")) {
					case 2: msg = HBRED"$N出招稳凝如山，似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱。\n"NOR; break;
					case 1: msg = HIR"$N眼见对方已陷入重围，再也不能全身而退，当下双掌回击，陡然圈转，呼的一响，往$n臂弯上击了下去。\n"NOR; break;
					default: msg = RED"$N出招稳凝如山，似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱。\n"NOR;break;
				}
				me->add_temp("baocan", -1);      
				return ([
					"action": msg, 
					"force" : 200 + random(300),
					"dodge": random(35),
					"parry": random(35),
					"damage": 200 + random(200),//抱残守缺是绝招
					"damage_type" : "抓伤",
				]);
			}*/
           
			if( me->query_temp("lzg/lianhuan"))
			{	        
								
			 return ([  
					"action":RED+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"RED), NOR, RED)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) ,
					"dodge": random(25) ,
					"damage":100 + random(80),
					"parry": random(25),//原来是15
					"weapon" : random(2)?"爪力":"指力",
					"damage_type" : random(2)?"戳伤":"抓伤",
				]);
			}
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"damage":80 + random(80),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("longzhua-gong", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练龙爪功。\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("ruying-suixingtui", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("qianye-shou", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘空手功夫。\n");
	}

	me->receive_damage("jingli", random(30));
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"longzhua-gong/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        string msg;
		//if (me->query_skill_mapped("finger")!="yizhi-chan" && me->query_skill_prepared("finger")!="yizhi-chan")
		  // return 0;
		int lvl = me->query_skill("yijin-jing",1)/3+ me->query_skill("longzhua-gong",1);
        if (random(lvl) > 200 
			&& random(10)>5
			&& random(me->query_str(1)) > victim->query_str(1)/2
			&& me->query_skill_mapped("finger")=="yizhi-chan"
			&& me->query_skill_prepared("finger")=="yizhi-chan"
			&& !victim->query_temp("must_be_hit")) {
                //victim->set_temp("must_be_hit", 1);
                me->add_temp("baocan",3);
				me->add_temp("shouque",3);
				//
                //call_out("remove_effect",1, victim);
               // message_vision(HBMAG"$n被$N一番疾风暴雨般的进攻弄得晕头转向，根本分不出哪招为实，哪招为虚！\n"NOR, me, victim);
                message_vision(HBMAG"$N右手拢于袖中，忽然变爪为指，突然一指点出，正是少林七十二绝技中的一指禅功夫！\n"NOR, me, victim);
				if (random(me->query_skill("finger",1))>victim->query_skill("dodge",1)/4)
				{
					message_vision(YEL"$n一个冷不防，为$N这突然而至的一指禅点中穴道，身形不由滴一滞！\n"NOR, me, victim);
					victim->add_busy(1+random(2));
					victim->apply_condition("yzc_qiankun",1);
				}else 
                 message_vision(HIW"$n早有防备，抬手竖掌握拳，迎向了这一招，将$N的一指禅劲力化于无形。\n"NOR, me, victim);
				
        }
		else{
		
		switch (random(2))
		{
		  case 0:
               if (me->query_temp("baocan")&&me->query("quest/sl/yjj/powerup"))
		       {
                  message_vision(HBRED"$N在招式中融入"+HIY"抱残式和守缺式"NOR+HBRED"的意境后，辅助易筋经的高深内力，化腐朽为神奇，已达武技的返璞归真之意。\n"NOR, me, victim);
                  victim->set_temp("must_be_hit", 1);
				  me->add_temp("apply/damage",(me->query_skill("yijin-jing",1)+lvl));
		          COMBAT_D->do_attack(me,victim, me->query_temp("weapon"), 3);
		          me->add_temp("apply/damage",-(me->query_skill("yijin-jing",1)+lvl));
				  victim->delete_temp("must_be_hit");
	    	   }
		break;
		case 1:
		  if (me->query_temp("shouque")&& random(20)>8&&userp(me))
	    	{
               msg=random(2)?MAG"$N出招稳凝如山，"+HIY"守缺式"+MAG"似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱！\n"NOR:
			   HIC"$N下意识施展出"+HIC"抱残式"NOR+HIC"的招式，将$n圈入此招中，$n发现再也不能全身而退。\n$N双爪回击，陡然圈转，呼的一响，往$n臂弯上击了下去。\n"NOR;
		       if (random(me->query_int())> victim->query_int()/2)
		        {
			     msg +=HIY"$n顿觉一股大力传来，身形立即不稳，胸口气血翻腾不已。\n"NOR;
			     victim->receive_damage("qi",lvl,me);
			     victim->receive_wound("jing",lvl,me);			   
		        }
		       else msg +=HIW"$n识破了$N的意图，身形向后一纵，避过了$N的这招陷阱。\n"NOR;
		       message_vision(msg,me,victim);
		  
		     }
		break;
		
		}	
	}
		
}

void remove_effect(object victim)
{
        if (!victim) return;
        victim->delete_temp("must_be_hit", 1);
}

