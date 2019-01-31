// ningxue-shenzhua.c 凝血神抓

#include <ansi.h>
inherit SKILL;  

mapping *action = ({
([
"action": "$N双掌平平提到胸前，神色沉重的缓缓施出「"HIG"苍龙探爪"NOR"」抓向$n的$l",
"lvl" : 0,
"damage_type": "瘀伤"
]),
([
"action": "$N突然身形飞起，双手居高临下一招「"HIC"飞鹰拨兔"NOR"」抓向$n的$l",
"lvl" : 30,
"damage_type": "瘀伤"
]),
([
"action": "$N右手一招「"HIB"黑虎掏心"NOR"」，迅捷无比地抓向$n的$l",
"lvl" : 80,
"damage_type": "瘀伤"
]),
([
"action": "$N双手施出一招「"HIY"泰山压顶"NOR"」，隐隐带着风声抓向$n的$l",
"lvl" : 130,
"damage_type": "瘀伤"
]),
([
"action": "$N左手聚成虎爪状，右手一招「"HIR"凝血神抓"NOR"」缓缓抓向$n的$l",
"lvl" : 200,
"damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{
	return usage=="claw" ||  usage=="parry"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练凝血神抓必须空手。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练凝血神抓。\n");
	if ( me->query_skill("ningxue-shenzhua", 1) < 150 )
		return notify_fail("你现在的凝血神抓还只能通过读书才能提高。\n");
	return 1;
}
int practice_skill(object me)
{
		if ( me->query("jingli") < 60)
			return notify_fail("你的精力不够练此武功。\n");
		if ( me->query("neili") < 30)
			return notify_fail("你的内力不够练此武功。\n");
		me->receive_damage("jingli", 50);
		me->add("neili", -20);
		return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);

	while (i--)
	if(level > action[i]["lvl"])
		return action[i]["skill_name"];
}

mapping query_action(object me,object weapon)
{
	int i, j, level;
	string msg;
	level = me->query_skill("ningxue-shenzhua",1);
	//连环神抓
	
	if( me->query_temp("nxsz/shenzhua")) 
	{
				
		switch(me->query_temp("nxsz/shenzhua"))
		{
			case 1: msg = YEL"$N忽然跃起，左手虚按，霎时之间右手呈虎爪状，以"HIR"「凝字诀」"YEL"直袭$n的前胸"NOR; break;
			case 2: msg = CYN"紧接着$N右手收回，将腰身一扭，那双手虚控"HIG"「控字诀」"CYN"便紧随而至，按向$n的双臂"NOR; break;
			case 3: msg = MAG"只见$N左爪劲力未消，便凌空一转，右手瞬间血红一片，一招"HIC"「血字诀」"MAG"幻起漫天抓影，如影而至"NOR; break;
			case 4: msg = BLU"$N默运玄功，暗劲运使双手，抓向$n的脚踝，正是"HIY"「捏字诀」"BLU"的精义"NOR; break;
			case 5: msg = RED"双手晃动，抓影如山，运起"HIM"「拍字诀」"RED"招式，直袭$n"NOR; break;
			case 6: msg = WHT"心中冷哼一声，紧绷双臂，暗劲如潮，劲气汹涌，"HIR"「擒字诀」"WHT"如影而至"NOR; break;
			case 7: msg = HBYEL+HIR"$N身形在空中转了个大圈，忽然反身向后，双爪幻出「抓字诀」，内劲直透$n胸腹处"NOR; break;
			case 8: msg = HBWHT+HIR"这时$N双臂展动，带起一股强烈的旋风，霎时齐并，「连环神抓」招式如潮般的抓在$n胸膛之上"NOR; break;
		}
		        

				
		return ([
				"action":msg,
				"damage_type":"抓伤",
				"dodge":random(35),
				"parry":random(35),
				"force":350 + random(350),
				"damage":250 + random(50),
		]);

    }

	for(i = sizeof(action); i > 0; i--)
	{
		if(level > action[i-1]["lvl"])
		{
			j = NewRandom(i, 20, level/5);
				
			return ([
				"action":action[j]["action"],
				"damage_type":action[j]["damage_type"],
				"lvl":action[j]["lvl"],
				"force":300 + random(350),
				"dodge":random(30),
				"parry":random(30),
				"damage":150 + random(50),

				]);
		}
	}
}
/*
void ningxue(object me, object victim)
{
	if (!me || !victim || !me->is_fighting(victim))
	return;

	if( random(me->query_skill("ningxue-shenzhua", 1)) > 150 
	&& me->query("neili") > 1500 
	&& !me->query_temp("weapon")) 
	{
		message_vision(HIR"\n$N趁$n躲避闪躲之际，右步踏前，左手横摆成抓式猛攻$n数招！\n"NOR, me, victim);
		me->set_temp("nxsz_pfm", 1);
		me->add_temp("apply/claw", me->query_skill("ningxue-shenzhua", 1)/3);
		COMBAT_D->do_attack(me, victim, 0, random(3)?1:3);
		if (me->is_fighting(victim))
		COMBAT_D->do_attack(me, victim, 0, random(2)?1:3);
		me->add_temp("apply/claw", -me->query_skill("ningxue-shenzhua", 1)/3);
		me->delete_temp("nxsz_pfm");
	}
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if ( !me->query_temp("nxsz_pfm"))
		call_out((: ningxue :), 1, me, victim);
}
*/
string perform_action_file(string action)
{
	return __DIR__"ningxue-shenzhua/" + action;
}
