// haotian-zhang 昊天掌
// Modified by action@SJ 2008/09/15

#include <ansi.h>

inherit SKILL;  
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([      "action" : "$N使一招"+(order[random(13)])+"「春江潮水」"NOR"，双手划了个半圈，按向$n的$l",
        "skill_name" : "春江潮水",
        "lvl" : 0,
        "damage_type" : "内伤"
]),
([      "action" : "$N使一招"+(order[random(13)])+"「海上明月」"NOR"，左手轻轻一挥，劈向$n的$l",
        "skill_name" : "海上明月",
        "lvl" : 5,
        "damage_type" : "内伤"
]),
([      "action" : "$N右手掌心向外，由右向左，使一招"+(order[random(13)])+"「滟滟随波」"NOR"，向$n的$l打去",
        "skill_name" : "滟滟随波",
        "lvl" : 10,
        "damage_type" : "内伤"
]),
([      "action" : "$N使一招"+(order[random(13)])+"「江流宛转」"NOR"，分击$n的胸口和$l",
        "skill_name" : "江流宛转",
        "lvl" : 15,
        "damage_type" : "内伤"
]),
([      "action" : "$N使一招"+(order[random(13)])+"「月照花林」"NOR"，左右掌同时击出，在空中突然左右掌方向互变",
        "skill_name" : "月照花林",
        "lvl" : 20,
        "damage_type" : "内伤"
]),
([      "action" : "$N左手不住晃动，右掌一招"+(order[random(13)])+"「空中流霜」"NOR"，向$n的$l打去",
        "skill_name" : "空中流霜",
        "lvl" : 25,
        "damage_type" : "内伤"
]),
([      "action" : "$N左手变掌为啄，右掌立掌如刀，一招"+(order[random(13)])+"「汀上白沙」"NOR"，劈向$n的$l",
        "skill_name" : "汀上白沙",
        "lvl" : 30,
        "damage_type" : "内伤"
]),
([      "action" : "$N左脚退后半步，右掌使一招"+(order[random(13)])+"「江天一色」"NOR"，横挥向$n",
        "skill_name" : "江天一色",
        "lvl" : 35,
        "damage_type" : "内伤"
]),
([      "action" : "$N一招"+(order[random(13)])+"「皎皎孤月」"NOR"，左掌先发而后至，右掌后发而先至",
        "skill_name" : "皎皎孤月",
        "lvl" : 40,
        "damage_type" : "内伤"
]),
([      "action" : "$N双掌缩入袖中，双袖飞起扫向$n的$l，却是一招"+(order[random(13)])+"「长江流水」"NOR"，仪态潇洒",
        "skill_name" : "长江流水",
        "lvl" : 45,
        "damage_type" : "内伤"
]),
([      "action" : "$N左手虚按，右手划道弧线使一招"+(order[random(13)])+"「白云悠悠」"NOR"，向$n的$l插去",
        "skill_name" : "白云悠悠",
        "lvl" : 50,
        "damage_type" : "内伤"
]),
([      "action" : "$N双手变掌做拳，向前向后划弧，一招"+(order[random(13)])+"「青枫浦上」"NOR"击向$n的$l",
        "skill_name" : "青枫浦上",
        "lvl" : 55,
        "damage_type" : "内伤"
]),
([      "action" : "$N左手虚划，右手变掌为钩一记"+(order[random(13)])+"「楼月蜚回」"NOR"击向$n的$l",
        "skill_name" : "楼月蜚回",
        "lvl" : 60,
        "damage_type" : "内伤"
]),
([      "action" : "$N施出"+(order[random(13)])+"「玉户帘中」"NOR"，右掌向外挥出，左掌同时攻向$n",
        "skill_name" : "玉户帘中",
        "lvl" : 65,
        "damage_type" : "内伤"
]),
([      "action" : "$N由臂带手，在面前缓缓划过，使一招"+(order[random(13)])+"「鸿雁长飞」"NOR"，挥向$n的$l",
        "skill_name" : "鸿雁长飞",
        "lvl" : 70,
        "damage_type" : "内伤"
]),
([      "action" : "$N负身就地，右掌使一招"+(order[random(13)])+"「鱼龙潜跃」"NOR"，自下而上向$n的$l击去",
        "skill_name" : "鱼龙潜跃",
        "lvl" : 75,
        "damage_type" : "内伤"
]),
([      "action" : "$N右手由钩变掌，双手掌心向上，右掌向前推出一招"+(order[random(13)])+"「月华流照」"NOR"",
        "skill_name" : "月华流照",
        "lvl" : 80,
        "damage_type" : "内伤"
]),
([      "action" : "$N右掌不住向外扫出，是一式"+(order[random(13)])+"「闲潭落花」"NOR"，左掌旋转着向$n攻去",
        "skill_name" : "闲潭落花",
        "lvl" : 85,
        "damage_type" : "内伤"
]),
([      "action" : "$N右手经腹前经左肋向前撇出，使一招"+(order[random(13)])+"「江水流春」"NOR"，向$n的$l锤去",
        "skill_name" : "江水流春",
        "lvl" : 90,
        "damage_type" : "内伤"
]),
([      "action" : "$N使一招"+(order[random(13)])+"「斜月沉沉」"NOR"，左掌连划三个大圈，右掌从圈中穿出击向$n",
        "skill_name" : "斜月沉沉",
        "lvl" : 95,
        "damage_type" : "内伤"
]),
([      "action" : "$N左手向上划弧拦出，右手使一招"+(order[random(13)])+"「碣石潇湘」"NOR"，手掌不住晃动，不离$n头顶方寸之间",
        "skill_name" : "碣石潇湘",
        "lvl" : 100,
        "damage_type" : "内伤"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }

int valid_combine(string combo) 
{
	if (this_player()->query("quest/qz/combine/pass"))
		return combo == "yuanyang-lianhuantui";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练昊天掌必须空手。\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 20)
                return notify_fail("你的先天气功火候不够，无法学昊天掌。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{ 
	int i, j, level,xtg;
	level = me->query_skill("haotian-zhang",1);
	xtg = me->query_skill("xiantian-gong", 1);

	for(i = sizeof(action); i > 0; i--){
		if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("htz/ju") && random(2)) { 
				return ([  
					"action" :random(2)? HIW+action[j]["action"]+NOR :HIY+action[j]["action"]+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			if( me->query_temp("htz/lianhuan")){
				return ([  
					"action":HIW+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIW), NOR, HIW)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
					"damage":40 + random(60) + random((level+xtg)/4),
					"parry": random(15)+xtg/10,//原来是15
					"weapon" : random(2)?"掌风":"掌力",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			return ([
				"action": action[j]["action"],
				"force" : 100 +random(250),
				"dodge": random(20)-10,
				"parry": random(10),
				"damage": 100 +random(120),
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
			]);
		}
	}
}
//混合攻击

mixed hit_ob(object me, object target, int damage_bonus, int factor)
{
	object weapon;
	int wap,wdp;
	
	weapon= target->query_temp("weapon");
	
//若对方手持武器
	
    if( objectp(weapon))
	{
		wap =   me->query("force")/5
		+ (int)me->query("haotian-zhang")/5
		+ (int)me->query_str()
		+ (int)me->query("jiali");

		wdp = (int)weapon->weight() / 500
		+ (int)target->query_str()
		+ (int)target->query("jiali")
		+ (int)target->query_skill("parry")/3;

		wap = wap/2 + random(wap/2);

		if( wap > 3 * wdp ) {
			message_vision(HIY"只见$N身上的$n"+HIY+"已被一掌震断。\n"NOR, target, weapon);
			weapon->unequip();
			weapon->move(environment(target));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			target->reset_action();
			me->add("neili", -150); // to break weapon takes more neili
		} else if( wap > 2 * wdp ) {
			message_vision(HIW"$N只觉得手中" + weapon->name() + "被一掌震得把持不定，脱手飞出！\n" NOR, target);
			weapon->unequip();
			weapon->move(environment(target));
			target->reset_action();
			me->add("neili", -120); // to break weapon takes more neili
		} else if( wap > wdp ) {
			message_vision("$N只觉得手中" + weapon->name() + "一震，险些脱手！\n", target);
			me->add("neili", -100); // to break weapon takes more neili
		}
	}
}


int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练昊天掌。\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"haotian-zhang/" + action;
}
