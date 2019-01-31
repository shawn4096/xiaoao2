//    /kungfu/skill/suixing-tui.c 如影随形腿

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N纵身向前，忽然伸出左腿，一式「仗义执言」，直踢$n的头部",
	"lvl" : 0,
	"skill_name" : "仗义执言",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N身形一闪，双足点地，一式「七星伴月」，在空中连踢七脚，直本$n的头、胸、臂",
	"lvl" : 40,
	"skill_name" : "七星伴月",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N身体前倾，左脚画圆，右腿使出一式「佛界无边」，扫向$n的腰部",
	"lvl" : 80,
	"skill_name" : "佛界无边",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左足倏地弹出，连环六腿，分踢$n的头部，胸部和裆部，正是一式「转世轮回」",
	"lvl" : 120,
	"skill_name" : "转世轮回",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左足独立，右腿随身形反转横扫，一招「西天极乐」，踢向$n的$l",
	"lvl" : 150,
	"skill_name" : "西天极乐",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N跃起在半空，双足带起无数劲风，一式「佛祖慈悲」迅捷无伦地卷向$n",
	"lvl" : 180,
	"skill_name" : "佛祖慈悲",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ((int)me->query_int(1) > 40)
		return combo=="qianye-shou"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("学如影随形腿时手里不能拿武器。\n");
	if ( me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("你的易筋经内功火候不够，无法学如影随形腿。\n");
	if ( me->query_skill("leg", 1) < 350)
		return notify_fail("你的基本腿功尚未小飞，不足350级，无法学如影随形腿。\n");
	if ( me->query_skill("shaolin-tantui", 1) < 350)
		return notify_fail("你的少林弹腿功尚未小飞，不足350级，领悟不了如影随形腿。\n");

	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("yizhi-chan", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("longzhua-gong", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的佛法领悟力不够，无法同时学习两种以上的上乘空手功夫。\n");
	}

	if ((int)me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法练如影随形腿。\n");
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
	string msg;
	level   = (int) me->query_skill("ruying-suixingtui",1);
        
	if (me->query_temp("sl_rysxt")){
		switch(me->query_temp("sl_rysxt")){
			case 5: msg = HIY"$N忽然跃起，左脚一勾一弹，霎时之间踢出一招「如」字诀的穿心腿，直袭$n前胸"NOR; break;
			case 4: msg = HIY"紧接着$N左腿勾回，将腰身一扭，那右腿的一招「影」字诀便紧随而至，飞向$n"NOR; break;
			case 3: msg = HIY"只见$N右脚劲力未消，便凌空一转，左腿顺势扫出一招「随」字诀，如影而至"NOR; break;
			case 2: msg = HIY"半空中$N脚未后撤，已经运起「形」字诀，内劲直透脚尖，在$n胸腹处连点了数十下"NOR; break;
			case 1: msg = HIR"这时$N双臂展动，带起一股强烈的旋风，双腿霎时齐并，「如影随形」一击重炮轰在$n胸膛之上"NOR; break;
		}
		me->add_temp("sl_rysxt", -1);                  
		return([
			"action": msg,
			"force" : 300+random(200),
			"dodge" : random(35),
			"parry" : random(35),
            "damage": 140 + random(140),

			"damage_type" : me->query_temp("sl_rysxt")?"内伤":"瘀伤",
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
				"damage": 80 + random(80),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("ruying-suixingtui", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("yizhi-chan", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("longzhua-gong", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘空手功夫。\n");
	}
	if ((int)me->query("jingli") < 40)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练如影随形腿。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"ruying-suixingtui/" + action;
}

mixed hit_ob(object me, object target)
{
	string msg;
	int i,j,damage;
	j = me->query_skill("ruying-suixingtui", 1);
    i=me->query_skill("shaolin-tantui",1);
	damage=i+j;
	damage=damage+me->query_skill("yijin-jing",1)+me->query_skill("leg",1);
	damage=damage*me->query_dex()/10;
	if (!me->query("quest/sl/rysxt/tiezhou/pass")) return;
	
	if (!me || !target) return;

	if( random(20) >= 12 
	&& j > 200 
	&& me->query("neili") > target->query("neili")
	&& me->query("neili") > 1000 
	&& me->query("max_neili") > 1500
	&& me->query_skill("shaolin-tantui",1)>450)
	//&& random(j) > random(target->query_skill("dodge",1))
	{
		
		switch(random(4))
		{
			case 0 :
			if (me->query_skill("shaolin-tantui",1)>450)
			{
				
				msg = HIC"$N身形闪动，一式"HIR"「少林弹腿」"HIC"，凌空飞起之际，陡然间踢向$n的胸口！\n";
				msg += "$n只觉轰然一响，已被这一招「弹腿」踢中！\n"NOR; 
				target->add_busy(random(1));
				target->receive_damage("qi",damage/3,me);
				
			}
				break;
			case 1 :
				if (me->query_skill("shaolin-tantui",1)>450)
				{	
					msg = HIW"$N双腿连续踢出，一式"HIR"「鸳鸯连环腿」"HIW"，一片腿影轰向$n的胸腹间！\n";
					msg += "结果$n气血翻涌，顿时气血不畅,功力大损。\n"NOR;
					if (damage>target->query("neili"))
					{
						target->set("neili",0);
					}else
						target->add("neili",-damage);

					target->add_condition("no_exert",1);
					target->receive_wound("qi",damage/2,me);
				}
				break;
			case 2 :
				if (me->query_skill("ruying-suixingtui",1)>450)
				{	
					msg = MAG"$N急速奔向$n，步伐越来越快，随着跃起，一式"HIC"「迷踪腿」"MAG"，趁$n躲避之际，一脚戳向$n的膻中！\n";
					msg += "结果$n感觉浑身酸软无力，丝毫提不起力气来。\n"NOR;
					target->add_busy(1);
					target->add_condition("no_perform",1);
					target->receive_wound("qi",damage/2,me);
				}
				break;
			case 3 :
				if (me->query_skill("ruying-suixingtui",1)>500)
				{	
					msg = WHT"$N纵身跃起，急速转动，双腿旋转带动阵风，形成一股旋风，正是"HIB"「旋风腿」"MAG"的招式！\n";
					me->add_temp("apply/damage",me->query_skill("ruying-suixingtui",1)/4);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					me->add_temp("apply/damage",-me->query_skill("ruying-suixingtui",1)/4);

				}
				break;
		}
		message_vision(msg, me, target);
	}
}
