// meinu-quan 美女拳法
// Modify By River
// Modified by darken@SJ

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([
	"action" : "$N使一招「貂禅拜月」，右手一挥，向$n的$l绕去，掌缘在$n的$l一斩",
	"skill_name" : "貂禅拜月",
	"lvl" : 0,
	"damage_type" : "内伤"
]),
([
	"action" : "$N双拳抱胸，忽地右手使一招「西施捧心」，向$n的$l插去",
	"skill_name" : "西施捧心",
	"lvl" : 10,
	"damage_type" : "震伤"
]),
([
	"action" : "$N右手五指弹起，仿似弹习琵琶一般，一招「昭君出塞」五指轮番向$n弹去", 
	"skill_name" : "昭君出塞",
	"lvl" : 20,
	"damage_type" : "震伤"
]),
([
	"action" : "$N侧身一闪，双手合拳向上抬去，一招「麻姑献寿」击向$n的$l",
	"skill_name" : "麻姑献寿",
	"lvl" : 30,
	"damage_type" : "内伤"
]),
([
	"action" : "$N施出「天女织梭」，右手挥左，做投梭织布之状，一挥一送，击向$n的$l",
	"skill_name" : "天女织梭",
	"lvl" : 50,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N施出「则天垂帘」，身子前扑，双掌以垂帘之势削将下来，斩向$n的$l",
	"skill_name" : "则天垂帘",
	"lvl" : 70,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N脸露微笑，伸手往头上一梳，手指如「丽华梳妆」，软软挥将出去，拍向$n的$l",
	"skill_name" : "丽华梳妆",
	"lvl" : 90,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双手互拍，闪电般击出，俨然一招「红玉击鼓」，轮番击向$n$l",
	"skill_name" : "红玉击鼓",
	"lvl" : 110,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N一招「弄玉吹箫」，一指擎天，一指对地，闭目垂首，忽手腿齐出，攻向$n的$l",
	"skill_name" : "弄玉吹箫",
	"lvl" : 120,
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("空手方能练习美女拳法。\n");
	if ( me->query_skill("yunu-xinjing", 1) < 10)
		return notify_fail("玉女心经领悟不够，无法修习美女拳法。\n");
	if ( me->query_skill("dodge", 1) < 20)
		return notify_fail("你的轻功太差，无法练美女拳法。\n");
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
	int i, j, level, flag = (me->query("gender") == "女性");
	string msg;

	level = (int) me->query_skill("meinu-quanfa",1);         

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("mnqf")){
				msg = MAG"$N悄退数步，右手支颐，左手轻轻挥出，长叹一声，脸现寂寥之意，$n不由得呆了，用充满爱慕的的眼光看着$N"NOR;
				me->delete_temp("mnqf");
				return ([
					"action" : msg,
					"force" : flag?250+random(350):180+random(300),
					"dodge": flag?random(30)-5:random(25),
					"parry": flag?random(30):random(35),
					"lvl" : action[j]["lvl"],
					"damage_type" : action[j]["damage_type"],
					"damage" : 180+random(50),
				]);
			}
			if ( me->query_temp("mnq_shexin")) {
				return ([
					"action" : action[j]["action"],
					"force" : flag?250+random(350):200+random(300),
					"dodge": flag?random(30):random(35),
					"parry": flag?random(30):random(35),
					"lvl" : action[j]["lvl"],
					"damage_type" : action[j]["damage_type"],
					"damage" : 150+random(50),
					
				]);
			}
			return ([
				"action" : action[j]["action"],
				"force" : flag?200+random(350):150+random(300),
				"dodge": flag?random(30)-10:random(30),
				"parry": flag?random(20):random(30),
				"lvl" : action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				//"damage" : 100+random(50),
			]);
		}
	}
}

string perform_action_file(string action)
{
	return __DIR__"meinu-quanfa/" + action;
}

int practice_skill(object me)
{
	if (me->query("jingli") < 40)
		return notify_fail("你的体力太低了。\n");
	if (me->query("neili") < 20)
		return notify_fail("你的内力不够练美女拳法了。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int extra, level, i, per, g = 2;
	if ( damage_bonus < 100 ) return 0;

	extra = (me->query("gender") == "女性"? 2:1);
	level = me->query_skill("meinu-quanfa",1);
	per = me->query("per");

	if( !userp(me) ) per -= 4;

	i = random(3) + 1;

	if( !userp(me) && userp(victim) ) g = 1;

	if( per > 24
	 && random(10) > 5
	 && level > 120
	 && random(me->query("combat_exp", 1)) > victim->query("combat_exp", 1)/g
	 && me->query("neili") > 500
	// && !victim->query_temp("mnq")
	// && !victim->query_temp("shexin")
	// && !victim->is_busy()
	 && random(me->query_per()*extra) > victim->query_per()/2 ){
		victim->add_temp("apply/parry", -level/5);
		victim->add_temp("apply/defense", -level/5);
		victim->add_temp("apply/dodge", -level/5);
		victim->set_temp("mnq", level/5);
		victim->add_busy(i);
		me->add("neili", -50);
		me->set_temp("mnqf", 1);
		call_out("reset_temp", 1, me, victim, i*2+1);
		return damage_bonus/2;
	}
	return 0;
}

void reset_temp(object me,object victim, int count)
{
	int skill;
	if (me)
		me->delete_temp("mnqf");
	if (!victim) return;
	if (!me
	|| !me->is_fighting(victim)
	|| count -- < 0) {
		skill = victim->query_temp("mnq");
		victim->add_temp("apply/parry", skill);
		victim->add_temp("apply/defense", skill);
		victim->add_temp("apply/dodge", skill);
		victim->delete_temp("mnq");
		if (me && living(victim) && ! victim->is_ghost())
			message_vision(HIW"\n$n激嶙嶙打了个寒战，心智为之一清。\n"NOR, me, victim);
		return;
	}
	call_out("reset_temp", 1, me, victim, count);
}
int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 40 )
		return combo=="tianluo-diwang"; 
}