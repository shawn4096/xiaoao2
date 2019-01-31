// luohan-quan.c 罗汉拳

#include <ansi.h>
#include <combat.h>

inherit SKILL;

#include <combat_msg.h>

mapping *action = ({
([
	"action" : "$N连续上步，一式「黄莺落架」，左右手分靠，变拳为掌，击向$n的$l",
	"lvl" : 0,
	"skill_name" : "黄莺落架",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左脚虚踏，全身右转，一招「丹凤朝阳」，右掌猛地插向$n的$l",
	"lvl" : 10,
	"skill_name" : "丹凤朝阳",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双手大开大阖，宽打高举，使一招「洛钟东应」，双拳向$n的$l打去",
	"lvl" : 20,
	"skill_name" : "洛钟东应",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左掌圈花扬起，屈肘当胸，虎口朝上，一招「偏花七星」打向$n的$l",
	"lvl" : 30,
	"skill_name" : "偏花七星",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N使一招「苦海回头」，上身前探，双手划了个半圈，击向$n的$l",
	"lvl" : 40,
	"skill_name" : "苦海回头",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双掌划弧，一记「挟山超海」，掌出如电，一下子切到$n的$l",
	"lvl" : 50,
	"skill_name" : "挟山超海",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N施出「慑服外道」，双拳拳出如风，同时打向$n头，胸，腹三处要害",
	"lvl" : 60,
	"skill_name" : "慑服外道",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左脚内扣，右腿曲坐，一式「三入地狱」，双手齐齐按向$n的$l",
	"lvl" : 70,
	"skill_name" : "三入地狱",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) {
	if(this_player()->query_skill("wuxiang-zhi", 1) >= 200
	&& this_player()->query_skill("luohan-quan",1) >= 200
	&& this_player()->query_con(1) > 45
	&& this_player()->query_int(1) > 45)
		return combo=="wuxiang-zhi";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练罗汉拳必须空手。\n");
	if ( me->query_skill("yijin-jing", 1) < 20&& me->query_skill("hunyuan-yiqi", 1) < 20)
		return notify_fail("你的易筋经或混元一气内功火候不够，无法学罗汉拳。\n");
	if ( me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练罗汉拳。\n");
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
	level = (int) me->query_skill("luohan-quan",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_skill("wuxiang-zhi", 1))
				return ([
					"action": action[j]["action"],
					"damage_type": action[j]["damage_type"],
				    "damage":100+random(100),
					"lvl": action[j]["lvl"],
					"force": 200 + random(350),
					"dodge": random(30)-10,
					"parry": random(20),
				]);
				else return ([
					"action": action[j]["action"],
					"damage_type": action[j]["damage_type"],
					"damage":80+random(80),
					"lvl": action[j]["lvl"],
					"force": 100 + random(250),
					"dodge": random(20)-10,
					"parry": random(10),
				]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("luohan-quan", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练罗汉拳。\n");
	if ( me->query_skill("wuxiang-zhi", 1)) {
		me->receive_damage("jingli", 40);
		me->add("neili", -15);
	}
	else {
		me->receive_damage("jingli", 20);
		me->add("neili", -5);
	}
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j,dam;
    //解开萧峰的返璞归真后，威力大增
	//if( damage_bonus < 100 ) return 0;
	j = me->query_skill("luohan-quan", 1)+me->query_skill("wuxiang-zhi", 1)+me->query_skill("force", 1);
    j=j/2;
	if ( random(10) > 4
	 //&& !victim->is_busy()
	 && j > 450
	 && me->query_skill_mapped("cuff") == "luohan-quan"
	 && me->query_skill_prepared("cuff") == "luohan-quan"
	 && me->query_skill_mapped("finger") == "wuiang-zhi"
	 && me->query_skill_prepared("finger") == "wuxiang-zhi"
	 && me->query("neili") > 3000
	 && me->query("max_neili") > 20000
	 && me->query("quest/天龙八部/武功/quanli")
	 && random(j) > victim->query_skill("dodge",1)/2 ) 
	{
		
		if (random(2)){
		   message_vision(HIW"$N已经洞悉这普通罗汉拳的精意，立即双手反转，左掌贴于神道穴，右掌贴于筋缩穴，掌心向外，\n"+
			"掌力疾吐，那神道穴是在至阳穴之上，筋缩穴在至阳穴之下，双掌掌力交织成一片屏障，刚好将至阳要穴护住，手法巧妙之极"NOR,me,victim);
		   dam=j*me->query_str();
		   dam=dam+random(dam);
		   if (dam>8000) dam=8000+random(dam/2);//暂时考虑别太狠了		
		   victim->receive_damage("qi",dam,me);
		   victim->receive_wound("qi",dam/4,me);
		   
		}else {
		   message_vision(HIY"$n见$N这一招配合得丝丝入扣，倒似招者故意凑合上去，要$N一显身手一般，又似是同门师兄弟拆招，\n"+
			"这正是无衣无缝 一招来得太过突然。一时不查，顿时陷入手忙脚乱之中。\n"NOR,me,victim);
           if (userp(victim))
		      victim->add_busy(2+random(2));
		   else victim->add_busy(4+random(2));
		
		}
       return;

	}
}
int help(object me)
{
        write(HIB"\n罗汉拳：简介"NOR"\n\n");
        write(@HELP
        罗汉拳，相传创自天竺僧人达摩。梁大通丁未，达摩赤足入中原，在少林寺演说禅宗，
		见众僧个个面黄肌瘦、精神不振，甚有萎靡盹睡、病体夭折者，慨然曰：“出家人虽不
		以躯壳为重，然亦不容不澈解于性，使灵魂离散也。欲悟性，必先强身，则躯壳强而灵
		魂易悟也。”于是创罗汉拳十八手，授以僧众，修炼不过数月，则个个精力充沛，此其
		起始也。在当时所谓罗汉拳者，只此十八手，亦并无先天后天之名目。
		罗汉拳，即其起始之十八手也，是少林各师派之正统宗法，法止十八手，精华所荟，不
		失本真。自达摩禅师出世来，名家巨手多有承传发挥，其理论基础是初祖达摩所传的禅
		法：“不立文字，教外别传，直指人心，见性成佛。”在其练法中，始终体现着“无念为宗”
		的禅宗精神，侧重于呼吸吐纳，气行六脉，守心住缘，止心不乱，故也称“少林心法罗汉拳”。
		有诗曰：“达摩西来一字无，全凭心意用功夫，若要经上寻佛法，笔尖蘸干洞庭湖。”先天
		罗汉拳元始十八手，每个单势都是炼气的桩功，即可使精气神力充足，又可使下盘稳固，
		既内又外，既神又形，既静又动，易筋洗髓功夫无不在也，可获性命双修之效。


        要求：
			最大内力 50;
			罗汉拳若和无相劫指配合会有组合auto攻击出现。	
               
               

HELP
        );
        return 1;
}

string perform_action_file(string action) 
{ 
       return __DIR__"luohan-quan/" + action; 
} 
