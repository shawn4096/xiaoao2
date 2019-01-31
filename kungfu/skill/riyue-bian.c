// riyue-bian.c 日月鞭法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([
	"action": "$N端坐不动，一式「阿那律刺」，手腕力抬，$w滚动飞舞，宛如灵蛇乱颤，前缠后绕，其力沾粘不散",
	"lvl" : 0,
	"skill_name" : "阿那律刺",
	"damage_type":  "拉伤"
]),
([
	"action": "$N一式「目捷连刺」，将手$w中抖得笔直，“呲呲”声中向$n疾刺而至，所挟劲风已令$n一阵气窒",
	"lvl" : 30,
	"skill_name" : "目捷连刺",
	"damage_type":  "刺伤"
]),
([
	"action": "$N内劲到处，将$w抖动转成两个圆圈，一式「舍利佛刺」，跃起从半空中往$n$l缠下",
	"lvl" : 60,
	"skill_name" : "舍利佛刺",
	"damage_type":  "拉伤"
]),
([
	"action": "$N劲走螺旋，一式「富楼那刺」，$w在$n眼前上圈下钩，左旋右转，连变了数种招式，忽然从$n$l处倒卷上来",
	"lvl" : 90,
	"skill_name" : "富楼那刺",
	"damage_type":  "拉伤"
]),
([
	"action": "$N一声高喝，吸气催力，一式「迦旋延刺」，$w急速转动，鞭影纵横，直中有圆，圆中有直，似真似幻，绞向$n",
	"lvl" : 120,
	"skill_name" : "迦旋延刺",
	"damage_type":  "拉伤"
]),
([
	"action": "$N含胸拔背、沉肩坠肘，一式「弘忍能刺」，力道灵动威猛，虚实分明，劲力从四面八方向$n挤压出去",
	"lvl" : 150,
	"skill_name" : "弘忍能刺",
	"damage_type":  "拉伤"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if(!me->query("family") || me->query("family/family_name")!="少林派" )
		return notify_fail("你不是少林弟子，如何能用这日月鞭法？\n");

	if ( me->query_skill("ranmu-daofa",1)
	 || me->query_skill("weituo-chu",1) 
	 || me->query("pass_xin"))
		return notify_fail("你如果有达摩老祖的修为，方可同时学习少林三绝技。\n");

	if ( me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为不足，没有办法练日月鞭法。\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("ranmu-dao", 1)
		 || me->query_skill("weituo-chu", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘兵器功夫。\n");
	}
	if ((int)me->query_skill("yijin-jing", 1) < 130)
		return notify_fail("你的易筋经神功火候太浅。\n");

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

mapping query_action(object me, object target)
{
	int i, level, j;
     
	if(me->query_temp("ryb/riyue"))
	{
		if (me->query_temp("ryb/rilun"))
		{
			return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":HIY+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"HIY)+NOR,
				"damage": 250 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"拉伤",
			]);
		}
		if (me->query_temp("ryb/yuelun"))
		{
			return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":HIW+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"HIW)+NOR,
				"damage": 300 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"拉伤",
			]);
		}
		return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":BLU+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"BLU)+NOR,
				"damage": 200 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"拉伤",
		]);
	}
//如果设置日月鞭法
	if(me->query("env/日月鞭法") =="环套"
		&& me->query_skill("parry",1) > 500 
		&& me->query("neili") > 1000 
		&& me->query("jingli") > 300 
		&& me->query("jiali") > 100
		&& random(me->query_str(1)) >= 40 
		&& random(me->query_skill("riyue-bian",1)) > 500)
	{
		me->add("neili", -10);
		if (random(me->query_str(1)) >= 45 
			&& me->query_skill("riyue-bian",1)> 200) 
		{           
			me->add("neili", -10);
			target->add_busy(1+random(2));
			target->receive_damage("jing",1000+random(1000),me);
			target->receieve_damage("jingli",1000+random(1000),me);
			return ([
				"action": HIR "$N把手中$w"HIR"抖动成圈，绕着$n越转越急，越转越快，$p登时身不由主，被套得连转了几身，眼冒金星，即将摔倒！"NOR,
				"force": 400 + random(300),
				"dodge": 30,
				"parry": 30,
				"damage" : 180 + random(100),
				"damage_type": "摔伤"
			]);
		}
		return ([
			"action": HIR "$N手腕一抖，但见飞舞的$w"HIR"从天而下和$n缠在一起，一股排山倒海的内劲无声息的向$n胸口撞去！"NOR, 
			"force": 300 + random(350),
			"dodge": 30,
			"parry": 30,
			"damage" : 130 + random(140),
			"damage_type": "内伤"
		]);
	}
	level   = (int) me->query_skill("riyue-bian",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 200 + random(350),
				"dodge": random(30)-10,
				"damage": 80 + random(140),
				"parry": random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("riyue-bian", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力不够练日月鞭法。\n");

	if ((int)me->query("neili") < 20 )
		return notify_fail("你的内力不够练日月鞭法。\n");
    if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("ranmu-dao", 1)
		 || me->query_skill("weituo-chu", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘兵器功夫。\n");
	}
          
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
	object weapon, weapon1;    
	int ap , dp;

	weapon=me->query_temp("weapon");
	weapon1=victim->query_temp("weapon");
	if (!me->query_temp("ryb/fumoquan")) return 0;
	
	if (victim->query("shen")<-10000
		||(victim->query_skill_mapped("dagger")=="shenghuo-lingfa" && objectp(weapon1)&&weapon1->query("skill_type")=="dagger")
		&&random(10)>7)
	{
			victim->add_busy(1);
			message_vision(YEL"$N施展的是正宗的佛门功法,正好克制了$n的功法，$n顿觉心浮气躁，忍不住仰天大笑三声！\n"NOR,me,victim);
	}

	if(objectp(weapon) && objectp(weapon1))
	{
		if (random(me->query_skill("riyue-bian",1)) <100) return 0;
		if (random(10)>4 ) return 0;

		ap = me->query("combat_exp") /100000 * me->query("str");
		dp = victim->query("combat_exp")/ 100000 * victim->query("str");

		if( random(ap + dp ) > dp && weapon1->query("imbued") < 3 && weapon1->query("rigidity") < 5){
			message_vision(HIY"只听见「唰」地一声轻响，$N手中的"+weapon1->name()+HIY"已经被"+weapon->name()+HIY"卷为两截！\n"NOR, victim );
			weapon1->broken("断掉的");
			return 0;
		}
		else if ( weapon1->query("rigidity") < 5 )  {
			ap = me->query_str(1)+ me->query("jiali") +  me->query_skill("parry")/3;         
			dp = victim->query_str(1)+ victim->query("jiali") + victim->query_skill("parry")/3;
			ap *= me->query("combat_exp") /1000;
			dp *= victim->query("combat_exp")/1000;
			if (random(ap + dp) > dp ) {
				message_vision(HIY "只见「呼呼」连响，$N手中的"+weapon1->name()+HIY"已经被"+weapon->name()+"卷中一个把持不定脱手飞出！\n"NOR, victim );
				victim->add_busy(random(2)+ 2);
				weapon1->move(environment(victim));
				victim->reset_action();
			}
		}
	}
	return 0;
}


int ob_hit(object ob, object me, int damage)
{
	//string msg;
	int j;
	object weapon;
	j = me->query_skill("riyue-bian", 1);
	if (!objectp(weapon=me->query_temp("weapon"))
		||weapon->query("skill_type")!="whip") 
		return 0;

	if (!objectp(ob)) return 0;
	
	if (me->query("yjj/powerup"))
	{
		j=j+me->query_skill("yijin-jing", 1);
	    j=j+random(j/2);
	}
	//if ( me->query_temp("mr_ci") ) return 0;
  
	if ( random(me->query_str(1)) >= ob->query_dex(1)/3
		&&j > 120 
		&& random(10) > 5
	 	&& random(me->query("combat_exp")) > ob->query("combat_exp")/2
		&& me->query("neili") > 500) 
       {
		  switch(random(3)) {
			case 0 :
				message_vision( HIW"$N反手趁机一抖，一招"HIG"「直刺诀」"HIW"使出，鞭头忽然由软变直，宛如长枪大戟，戳向$n！\n",me,ob);
				message_vision( HIR"$n只觉「膻中穴」一痛，顿时被打中，哇地吐出一口鲜血！\n"NOR,me,ob); 
				ob->add_busy(1+random(3));
				ob->receive_damage("qi",2000+random(2000),me);
				me->add("neili",-random(300));
				break;
			case 1 :
				message_vision(CYN"$N将九阴真经的功夫运使出来，鞭子借力打力，一招"HIR"「飞龙诀」"CYN"，将$n圈住，鞭影如山，将$n笼罩于内！\n"NOR,me,ob);
				ob->recevied_wound("qi", 3000+random(2000),me);
				ob->add_condition("no_perform",1);
				
				if (ob->query("neili") < 0 )
					ob->set("neili", 0);
				me->add("neili",-random(500));
				break;

            case 2 :
				
				message_vision(HIR"$N见$n冲到面前，忽然换成空手招式，简单朴实无华，一掌拍向$n的胸口。\n",me,ob);
			    message_vision(RED"$n只觉心口为其拍中，一股剧痛传来，鲜血狂喷而出！\n"NOR,me,ob); 
				ob->recevied_damage("qi", 1000+random(1500),me);
				ob->recevied_wound("qi", 1000+random(500),me);
				me->add("neili",-random(200));
				break;
		  
		  }
		
	}
}
string perform_action_file(string action)
{
	return __DIR__"riyue-bian/" + action;
}
