// jingang-liantishu

#include <ansi.h>
inherit SKILL;
#include <combat.h>
mapping *action = ({
([
	"action" : "$N一式「韦陀献杵」，双臂直上直下，猛攻而前，打向$n的$l",
	"lvl" : 0,       
	"damage_type" : "内伤"
]),
([
	"action" : "$N双目一瞪，宛如金刚，上身前倾，右拳直出呼的一声打向$n，正是一招「金刚怒目」",
	"lvl" : 10,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N使招「佛法降魔」，右手向上一扬，左手握拳打向$n",
	"lvl" : 20,
	"damage_type" : "内伤"
]),
([
	"action" : "$N双拳连续打出数招，口中念念有词，一招「神咒三界」击向$n",
	"lvl" : 30,
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N跳起往左旋身一转，「诸邪不侵」左脚落地后双拳齐出，捣向$n的$l，",
	"lvl" : 40,
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { 
	// mapping fam;
     //if (this_player()->query("family"))  
	  return usage=="cuff" || usage=="strike"|| usage=="leg"|| usage=="parry"; 
	 //else return "只有普通百姓方能修习本门武技。\n";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练金刚炼体术必须空手。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练功。\n");
	return 1;
}
int practice_skill(object me)
{

        if (me->query_temp("weapon"))
			return notify_fail("只有空手才能修炼金刚炼体术");
     

        if ((int)me->query("neili") < 40)
       	        return notify_fail("你的内力不足，没有办法练习金刚炼体术。\n");

        if ((int)me->query("qi") < 50)
        	return notify_fail("你的体力不够练金刚炼体术。\n");
		if (me->query_skill("jingang-liantishu",1)==100 && me->query("xuedao/jingmai")!="1")
		{
			//me->add("max_neili",2+random(3));
			me->set("xuedao/jingmai",1);
			message_vision(CYN"“波”的一声，奇经八脉第一条经脉打通，你修炼金刚炼体术已有小成！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==200 && me->query("xuedao/jingmai")!="2")
		{
			//me->add("max_neili",4+random(4));
			me->set("xuedao/jingmai",2);

			message_vision(HIC"“波”的一声，奇经八脉第二条经脉打通，你修炼金刚炼体术初有成效！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==300 && me->query("xuedao/jingmai")!="3")
		{
			//me->add("max_neili",8+random(8));
			me->set("xuedao/jingmai",3);

			message_vision(HIC"“波”的一声，奇经八脉第三条经脉打通，你修炼金刚炼体术小镜圆满！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==400 && me->query("xuedao/jingmai")!="4")
		{
			//me->add("max_neili",16+random(16));
			me->set("xuedao/jingmai",4);

			message_vision(HIC"“波”的一声，奇经八脉第四条经脉打通，你修炼金刚炼体术登堂入室！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==500 && me->query("xuedao/jingmai")!="5")
		{
			//me->add("max_neili",25+random(25));
			me->set("xuedao/jingmai",5);

			message_vision(HIC"“波”的一声，奇经八脉第五条经脉打通，你修炼金刚炼体术颇有心得！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==550 && me->query("xuedao/jingmai")!="6")
		{
			//me->add("max_neili",30+random(30));
			me->set("xuedao/jingmai",6);

			message_vision(HIC"“波”的一声，奇经八脉第六条经脉打通，你修炼金刚炼体术登峰造极！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==600 && me->query("xuedao/jingmai")!="7")
		{
			//me->add("max_neili",50+random(50));
			me->set("xuedao/jingmai",7);

			message_vision(HIC"“波”的一声，奇经八脉第七条经脉打通，你修炼金刚炼体术圆转如意！\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==700 && me->query("xuedao/jingmai")!="8")
		{
			//me->add("max_neili",100+random(100));
			me->set("xuedao/jingmai",8);

			message_vision(HIC"“波”的一声，奇经八脉第八条经脉打通，你修炼金刚炼体术已入化境！\n"NOR,me);
		}
        me->receive_damage("qi", 50);
		//修炼炼体术，增加少许内力
        me->add("neili",5);
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
	level   = (int) me->query_skill("jingang-liantishu",1);
	
	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if (me->query_temp("jglts/jingang"))
			{
				return ([  
				"action":	HIY+action[j]["action"]+NOR,
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	100+random(250),
				"dodge":	random(20)-10,
				"damage":	150+random(50),
				"parry":	random(10),
			     ]);
			}
			
			return ([  
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	100+random(250),
				"dodge":	random(20)-10,
				"parry":	random(10),
			     ]);
		     
		}
	}
}



string perform_action_file(string action)
{
	return __DIR__"jingang-liantishu/" + action;
}


//金刚炼体术的抵消功效


int ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;

	if( damage < 100) return 0;

	neili = me->query("neili");
	neili1 = ob->query("neili");
	//不开谜题，没有防御效果
	if(!me->query("quest/xd/jglts/jingang/pass")) {
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_skill("parry",1) < 350
	 || me->query_skill_mapped("parry") != "jingang-liantishu"
	 || me->query_skill_mapped("force") != "xuedao-jing"
	 || me->query("combat_exp") < ob->query("combat_exp")/3
	 || neili < 400 ) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
        
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;   
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
         
	if ( random(10) < 3 ) me->set_temp("fanzhen", 1);

	ap = ABS(ap);
	dp = ABS(dp);

	if ( me->query_temp("xdj/yuxue"))
		dp += ap/2 + random(ap/2);
	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));

	if( random(dp) > ap && random(3)) {
		msg = RED "$N默运血刀经的「金刚」意，$N身子隐隐腾起一层淡淡的血气之色。\n" NOR;
		tell_object(ob, RED "你只见对手突然身子一侧，竟然不躲不避用身体迎了这一招！\n" NOR);
		msg +=RED "$n一招打在$N的身上，只觉似乎打在一块石头上一样。\n"NOR;
		if(neili >= neili1*2 + random(damage)) {
			msg +=WHT "结果$n的攻击被$N的「金刚体魄」化掉了！\n"NOR,
			j = -damage;
		}
		else if( neili > neili1 + random(damage) ) {
			msg += WHT"结果$n的攻击被$N的「金刚体魄」化掉了一半！\n"NOR,
			j = -damage/2;
		}
		else {
			msg += WHT"结果$N只化掉了$n的一小半力道！\n"NOR,
			j = -damage/4;
		}
		message_vision(msg, me, ob);
		return j;
	}
}
//增加有效激发parry
int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

		if (me->query_skill_mapped("parry")=="金刚炼体术"&&me->query("family/family_name")=="血刀门")
		
        lvl = me->query_skill("jingang-liantishu", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 85;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
		if (me->query("quest/xd/xdj/xuedao/pass")) return 120; 
		
}
