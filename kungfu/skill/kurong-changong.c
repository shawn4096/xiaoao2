// By Spiderii修改标记，测试auto效果
#include <ansi.h>
#include <combat.h>

inherit FORCE;

#include "force.h"
inherit SKILL;
#include <combat_msg.h>

string *xue_name = ({
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",});

mapping *action = ({
([
	"action": "$N轻轻吟道：「常与无常」,身体旋转，右掌从胁下伸出，$w发出的劲风向$n扑去",
        "weapon" : "掌缘",
	"lvl" : 0,
	"skill_name" : "常与无常",
	"damage_type": "割伤"
]),
([
	"action": "$N双掌隐于袖中，断喝：「我与无我」，“哗”的一声衣袍冲天而起，一道气墙直击向$n",
	"lvl" : 40,
	"skill_name" : "我与无我",
	"damage_type": "瘀伤"
]),
([
	"action": "$N双掌交错，凌空拔起,高声一吼：「乐与无乐」，一掌向$n的$l拍去",
	"lvl" : 60,
	"skill_name" : "乐与无乐",
	"damage_type": "震伤"
]),
([
	"action": "$N拇指屈贴掌心，默咏：「净与无净」,右掌上抬，左掌向$n的$l插去",
	"lvl" : 80,
	"skill_name" : "净与无净",
	"damage_type": "瘀伤"
]),
([
	"action": "$N一声大喝：「非假非空」,扬手拍出一股排山倒海的气浪",
	"lvl" : 100,
	"skill_name" : "非假非空",
	"damage_type": "震伤"
]),
([
	"action": "$N似笑非笑，左掌一推，右掌一拉，一股旋转的气流将$n团团包围",
        "weapon" : "掌风",
	"lvl" : 120,
	"skill_name" : "非枯非荣",
	"damage_type": "割伤"
]),
([
	"action": "$N双手合什，吟道：「亦枯亦荣」，双掌交替快速推出，掌力重重叠叠，直逼向$n",
	"lvl" : 140,
	"skill_name" : "亦枯亦荣",
	"damage_type": "内伤"
]),
});

int valid_enable(string usage) { return usage == "force" || usage=="strike" || usage =="parry"; }

void skill_improved(object me)
{
	int i = (int)me->query_skill("kurong-changong", 1);   
//总共六层设计，最后一层需要解密
	if (i == 150)
	{
		 
	     me->set("kurong/degree",1);
		 tell_object(me, GRN"\n忽然心中灵光一闪，不由得轻轻吟道：\n"+
				"“一切有为法，如梦幻泡影”\n"+
				"“如露亦如电，应做如是观”\n"+
				"你的禅功修为到了一个新的境界！\n"NOR);
		 tell_object(me,HIW"枯荣禅功你已经修炼到半枯境界，防御力大增!\n"NOR);
		 
	}
	if (i == 250)
	{
		 tell_object(me,HIW"枯荣禅功你已经修炼到半荣境界，命中大增。\n"NOR);
	     me->add("kurong/degree",1);
	}
	if (i == 350)
    {
		tell_object(me,HIW"枯荣禅功你已经修炼到半枯半荣境界，攻防俱都得到不小提升。\n"NOR);
        me->add("kurong/degree",1);
	}
	if (i == 450)
    {
		tell_object(me,HIW"枯荣禅功你已经修炼到全枯境界，防御力得到不小提升。\n"NOR);
        me->add("kurong/degree",1);
	}
	if (i == 500)
    {
		tell_object(me,HIW"枯荣禅功你已经修炼到全荣境界，攻击力得到不小提升。\n"NOR);
        me->add("kurong/degree",1);
	}
	if (i == 550)
	{
		tell_object(me,HIW"枯荣禅功你经过长久修炼思路进入一个瓶颈，需要跟枯荣禅师请教方能最终大成。\n"
					+"方便时期可以和枯荣大师请教。\n\n");
	}
	return ;	
	
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
	int i, level, j;
	level = (int) me->query_skill("kurong-changong",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("pf_rong") && me->query("jiali") && random(2)) {
				return ([
					"action" : YEL+action[j]["action"]+NOR,
					"force" : 300 + random(200),
					"dodge": random(35),
					"parry": random(35),
					"damage": 40 + random(40),
					"damage_type" : "割伤",
				]);
			}
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"weapon": action[j]["weapon"],
				"force":150+random(300),
				"dodge":random(30),
				"parry":random(30),
			]);
		}
	}
}

int valid_learn(object me)
{
	int i, l;
	int t = 1, j;
	mapping myfam = (mapping)me->query("family");
	for (j = 1; j < i / 10; j++) t *= 2;

	i = (int)me->query_skill("kurong-changong", 1);
	l = (int)me->query_skill("buddhism", 1);

	if (i > 120 && i <180 && l < i - 10)
		return notify_fail("枯荣禅功需要深厚的佛学造诣，你的佛学不够！\n");

	if (!me->query_skill("kurong-changong", 1))
	if (me->query_skill("qiantian-yiyang",1) < 140)
		return notify_fail("你的乾天一阳功火候还不够，无法领会枯荣禅功。\n");

	if ( me->query_skill("qiantian-yiyang", 1)
	 && me->query_skill("kurong-changong", 1) > me->query_skill("qiantian-yiyang", 1))
	 	return notify_fail("你不散掉乾天一阳功，如何能修习枯荣禅功。\n");

	if ( me->query("gender") != "男性" )
		return notify_fail("你非童男之体，不能练习枯荣禅功内功。\n");

	if (me->query("class") != "bonze" || me->query("menggu"))
		return notify_fail("你非我佛弟子，不可修习枯荣禅功。\n");

	if (me->query_skill("yiyang-zhi",1) < 140)
		return notify_fail("枯荣禅功需要一阳指神功作为后盾。\n");

	if ((int)me->query_skill("kurong-changong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("kurong-changong", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	if ( !mapp(myfam) || myfam["master_name"] != "枯荣长老")
		return notify_fail("你辈份不够，只能跟枯荣长老学习，不可以修习枯荣禅功。\n");
	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("kurong-changong", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("kurong-changong", me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高枯荣禅功了。\n");
	}
	else return notify_fail("枯荣禅功不可随便练习。\n");
}

string exert_function_file(string func)
{
	return __DIR__"kurong-changong/" + func;
}


mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIG + me->name()+"面带凝涩之气，双目低垂内视" NOR,
		"start_my_msg" : "你盘膝坐下，垂目合什，默运枯荣禅功，只觉冷热两股真气开始在体内缓缓游动。\n",
		"start_other_msg" : me->name()+"盘膝坐下，垂目合什，周身似乎笼罩在一层青气之中。\n",
		"halt_msg" : "$N双掌一分，屈掌握拳，两股真气迅速交汇消融。\n",
		"end_my_msg" : "你真气在体内运行了一个周天，冷热真气收于丹田，慢慢抬起了眼睛。\n",
		"end_other_msg" : "只见"+me->name()+"慢慢睁开眼睛，周身笼罩的青气逐渐隐去。\n"
	]);
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;

	if( damage < 100) return 0;

	neili = me->query("neili");
	neili1 = ob->query("neili");

	if(me->query_temp("kurong-changong")) {
		me->delete_temp("kurong-changong");
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_skill("parry",1) < 350
//	 || me->query_skill_mapped("parry") != "kurong-changong"
	 || me->query_skill_mapped("force") != "kurong-changong"
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

	if ( me->query_temp("krcg_kurong"))
		dp += ap/2 + random(ap/2);
    if (me->query_temp("pf_ku"))
        dp += random(ap/2);
	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));

	if( random(dp) > ap && random(3)) {
		msg = WHT "$N默运枯荣禅功的「枯」字大法，半边身子的隐隐透出青气，内力全部集中在$N的这半边身上。\n" NOR;
		tell_object(ob, WHT "你只见对手突然身子一侧，将半边身子迎了上来！\n" NOR);
		msg +=WHT "$n一招打在$N的身上，只觉似乎打在一块朽木上。\n"NOR;
		if(neili >= neili1*2 + random(damage)) {
			msg +=WHT "结果$n的攻击被$N的枯荣禅功化掉了！\n"NOR,
			j = -damage;
		}
		else if( neili > neili1 + random(damage) ) {
			msg += WHT"结果$n的攻击被$N化掉了一半！\n"NOR,
			j = -damage/3*2;
		}
		else {
			msg += WHT"结果$N只化掉了$n的一小半力道！\n"NOR,
			j = -damage/2;
		}
		message_vision(msg, me, ob);
		return j;
	}
}
