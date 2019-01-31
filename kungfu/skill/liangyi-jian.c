// liangyi-jian.c (kunlun) 昆仑派正两仪剑法
//update by cool 981104

#include <ansi.h>
inherit SKILL;
//mixed hit_ob(object me, object victim, int damage_bonus, int factor);

mapping *action = ({
([
	"action":"$N一式「顺水推舟」，$N手中$w指向自己左胸口，剑柄斜斜向右外，缓缓划向$n的$l",
	"lvl" : 0,
	"skill_name" : "顺水推舟",
	"damage_type":"刺伤"
]),
([
	"action":"$N身形微侧，左手后摆，右手$w一招「横扫千军」，直向$n的腰间挥去",
	"lvl" : 10,
	"skill_name" : "横扫千军",
	"damage_type":"刺伤"
]),
([
	"action":"$N纵身近前，$w斗然弯弯弹出，剑光爆长，一招「峭壁断云」，猛地刺向$n的胸口",
	"lvl" : 20,
	"skill_name" : "峭壁断云",
	"damage_type":"刺伤"
]),
([
	"action":"$N左手捏个剑决，平推而出，决指上仰，右手剑朝天不动，一招「仙人指路」，刺向$n",
	"lvl" : 40,
	"skill_name" : "仙人指路",
	"damage_type":"刺伤"
]),
([
	"action":"$N剑招忽变，使出一招「雨打飞花」，全走斜势，但七八招斜势中偶尔又挟着一招正势，教人极难捉摸",
	"lvl" : 60,
	"skill_name" : "雨打飞花",
	"damage_type":"刺伤"
]),
([
	"action":"$N手中$w剑刃竖起，锋口向下，一招「大漠平沙」，剑走刀势，劈向$n的$l",
	"lvl" : 80,
	"skill_name" : "大漠平沙",
	"damage_type":"劈伤"
]),
([
	"action":"$N一招「木叶萧萧」，$N横提$w，剑尖斜指向天，由上而下，劈向$n的$l",
	"lvl" : 100,
	"skill_name" : "木叶萧萧",
	"damage_type":"劈伤"
]),
([
	"action":"$N抢前一步，$w微微抖动，剑光点点，一招「江河不竭」，终而复始，绵绵不绝刺向$n",
	"lvl" : 120,
	"skill_name" : "江河不竭",
	"damage_type":"刺伤"
]),
([
	"action":"$N左手剑鞘一举，快逾电光石光，一招「高塔挂云」，用剑鞘套住$n手中兵器，$w直指$n的咽喉",
	"lvl" : 140,
	"skill_name" : "高塔挂云",
	"damage_type":"刺伤"
]),
([
	"action":"$N翻身回剑，剑诀斜引，一招「百丈飞瀑」，剑锋从半空中直泻下来，罩住$n上方",
	"lvl" : 160,
	"skill_name" : "百丈飞瀑",
	"damage_type":"刺伤"
]),
([
	"action":"$N一式「雪拥蓝桥」，$N手中剑花团团，一条白练疾风般向卷向$n",
	"lvl" : 180,
	"skill_name" : "雪拥蓝桥",
	"damage_type":"刺伤"
]),
([
	"action":"$N腾空而起，突然使出一招「无声无色」，悄无声息地疾向$n的背部刺去",
	"lvl" : 200,
	"skill_name" : "无声无色",
	"damage_type":"刺伤"
]),
});
mapping *action_fh = ({
([
	"action":"$N一式「雨打飞花」，$N手中$w忽然由斜转正，居然是是一式正两仪剑的招式，$w缓缓划向$n的$l",
	"lvl" : 200,
	"skill_name" : "雨打飞花",
	"damage_type":"刺伤"
]),
([
	"action":"$N一式「风摆荷叶」，$w在双手弯曲后，呈弓之态，忽然松开，由斜转正，$w划过一道弧光，刺向$n的$l",
	"lvl" : 250,
	"skill_name" : "风摆荷叶",
	"damage_type":"刺伤"
]),
([
	"action":"$N一式「荷叶轻摇」，$w忽然化作极为柔软之态，弯弯曲曲，极难看准剑势，$w嚯地一声陡然间刺向$n的$l",
	"lvl" : 250,
	"skill_name" : "荷叶轻摇",
	"damage_type":"刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if ( me->query("max_neili") < 1000)
		return notify_fail("你的内力不够。\n");
	//if ( me->query("family/master_id")!="he zudao"||me->query("family/master_name")!="何足道")
	//	return notify_fail("你得不到何足道亲自传授，无法修习两仪剑。\n");
	if ( me->query_skill("xuantian-wuji", 1) < 160)
		return notify_fail("你的玄天无极功火候太浅。\n");

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
	int i,level,j,n;
    string msg;
	level = (int) me->query_skill("liangyi-jian",1);
	//雨打飞花辅助进攻，厉害杀招
	for (i = sizeof(action_fh); i > 0; i--) {
		if (level >= action_fh[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("lyj/feihua1") ) {
				return ([
					"action": HIR+replace_string(replace_string(replace_string(action_fh[j]["action"], "$w", "$W"), "$W", "$w"HIR), NOR, HIR)+NOR,
					"lvl": action_fh[j]["lvl"],
					"damage_type": action_fh[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 200 +random(50),
				]);
			}
		}
	}

//峭壁断云
       if( intp(n = me->query_temp("lyj/duanyun")) && n > 0 ){
                switch(n){
                   case 4: msg = WHT"$n看到剑光偏左，疾侧身右转，但只这一刹，$N剑光忽然抖动，竟然刹时袭向右首！"NOR;break;
                   case 3: msg = WHT"$n看到剑光偏右，疾侧身左转，但只这一刹，$N剑光忽然抖动，竟然袭向左首！"NOR; break;
                   case 2: msg = WHT"$n看到剑光偏上，疾侧身下转，但只这一刹，$N剑光忽然抖动，竟然袭向下身！"NOR;break;
                   case 1: msg = WHT"$n看到剑光偏下，疾侧身上转，但只这一刹，$N剑光忽然抖动，竟然袭向上身！"NOR; break;
				   default:break;
                }
				n=n-1;
                return ([
                        "action":msg,
                        "damage_type":"割伤",
                        "dodge": 20,
				    	"damage":me->query("xtwj/wuji")?(200+random(50)):(120+random(50)),
                       
						"force": level + me->query("jiali"),
                        "skill_name" : "峭壁断云",
                ]);
        }

	 for (i = sizeof(action); i > 0; i--) {
		if (level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
		//迅雷
		if( me->query_temp("lyj/xunlei1") ) {
				return ([
					"action": WHT+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"WHT), NOR, WHT)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 180 +random(50),
				]);
		}
		if( me->query_temp("lianhuan") ) {
				return ([
					"action": BLU+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"BLU), NOR, BLU)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 180 +random(50),
				]);
		}
		if( me->query_temp("ly_hebi") ) {
				return ([
					"action": HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 140 +random(50),
				]);
			}
		if( me->query_temp("lyj/feihua") ) {
				return ([
					"action": HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 120 +random(50),
				]);
			}
		return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(350),
				"dodge": random(30)-10,
				"parry": random(20),
				"damage": 80 +random(140),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("liangyi-jian", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练两仪剑法。\n");
	if ( me->query("jingli") < 50)
		return notify_fail("你的体力不够练两仪剑法。\n");
	me->receive_damage("jingli", 40);
	me->add("neili",  -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liangyi-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int i;
	string msg;
	object weapon,weapon2;
	weapon=me->query_temp("weapon");
	weapon2=present("blade",me);
	i = me->query_skill("liangyi-jian",1)/5;
	if (me->query_skill_mapped("sword")!="liangyi-jian")
		return 0;
	
	if( me->query_temp("ly_hebi")
	 && !me->query_temp("hebi_hit") 
	 && random(10) > 5
	 && me->query_skill_mapped("parry") == "liangyi-jian") {
		me->set_temp("hebi_hit", 1);
		me->add_temp("apply/attack", i);
		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);  
		me->add_temp("apply/attack", -i);
		me->delete_temp("hebi_hit");
	}
	//两仪剑--两仪决
   if( me->query_temp("lyj/liangyi")
	 &&	objectp(weapon2)
	 && random(10) > 7
	 && me->query_skill_mapped("sword") == "liangyi-jian"
	 && me->query_skill_mapped("parry") == "liangyi-jian") 
	{		
		
		switch (random(5))
		{
			case 0:
				message_vision(HIB"$N大喝一声朗声喝道“混沌生两仪，混沌一破”！右手从背囊中拿出一把"+weapon2->query("name")+HIB",然后挥刀从背后反划了个弧形，弯弯曲曲的斩向$n。\n"
								HIC+"$N因为深悟两仪决要领，随后又接口道：“太乙生萌，两仪合德”，左手将手中"+weapon->query("name")+HIC"剑招源源不绝递出。\n"NOR,me,victim);
				if (random(me->query("combat_exp"))>victim->query("combat_exp")/2)
				{
					message_vision(HIY"$N将正两仪剑和反两仪刀的招式组合在一起后，配合得天衣无缝，犹似一个人一生寂寞，突然间遇到了知己般的喜欢。$n顿时手忙脚乱起来。\n"NOR,me,victim);
					victim->add_busy(2);
					victim->apply_condition("no_exert",2);
				}
				break;
			case 1:
				message_vision(HIB"$N反两仪刀法发动，道“万劫不复”！右手的"+weapon2->query("name")+HIB",如跗骨之蛆，悄然发动，已经施展了反两仪的的极致，刀剑相交。\n"
									HIC+"$N手中"+weapon->query("name")+HIC"出招的手法迅捷无伦，正两仪剑中'金针渡劫'，在一瞬之前，剑尖离$n肩头不及半尺。$n顿时大惊。\n"NOR,me,victim);
		        victim->receive_damage("qi",damage_bonus,me);
				message_vision(HIR"$n一时不查为$N的正两仪剑所刺伤！\n"NOR,me,victim);
				victim->receive_wound("qi",damage_bonus/4,me);
				message_vision(HIY"紧接着$N刀锋又砍中了$n的臂膀。\n"NOR,me,victim);
				
				break;

			case 2:
				message_vision(HIB"$N左手"+weapon2->query("name")+HIB"反两仪刀出招攻敌，右手"+weapon->query("name")+"的正两仪剑正好埋伏在$n的退路上,\n"
								+"两仪剑法和两仪刀法虽然正反有别，但均是从八卦中化出，再回归八卦，可说是殊途而同归。一刀一剑越使越顺手，两刀双剑配合得严密无比。\n"NOR,me,victim);
				victim->apply_condition("no_perform",2);
				message_vision(HIG"$n只觉的前后左右均为两仪决所封锁，无法出招！\n"NOR,me,victim);

				break;
			case 3:
				message_vision(HIB"两仪化四象，四象化八卦，正变八八六十四招，正奇相合，六十四再以六十四倍之，共有四千零九十六种变化。\n"NOR,me,victim);
				message_vision(HIY"$n只觉的前后左右均为两仪决所封锁，无法出招！刀剑组成了一片光幕，四面八方的密密包围，\n"NOR,me,victim);
				victim->add_busy(1);
				COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);  
				COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3); 
				break;
			case 4:
				message_vision(HIB"$N轻吟道，”天地定位，山泽通气，雷风相薄，水火不相射，八卦相错。数往者顺，知来者逆“！\n"
								+"同时将正两仪剑法，自震位至乾位的顺，而反两仪刀法则是反其道而行之，当真是圆中有方，阴阳相成。\n"NOR,me,victim);
				message_vision(HIG"$n心中大急，左冲右突，但每一处均为$N所封锁，不多久精力大损！\n"NOR,me,victim);

				victim->receive_damage("jingli",damage_bonus/2,me);
				victim->receive_damage("jing",damage_bonus/4,me);
				break;
		}
/*
		me->add_temp("apply/attack", i);
		me->add_temp("apply/sword", i);
		me->add_temp("apply/damage", i);
		message_vision(HIR"$N手中的剑势全部均为歪歪斜斜，但在这些斜势剑势中陡然会出现一二招正势，令$n防不胜防。\n"NOR,me,victim);
		victim->add_busy(1);
		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);  
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/sword", -i);
		me->add_temp("apply/damage", -i);	*/
		


	} 


}

