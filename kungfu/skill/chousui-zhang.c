// chousui-zhang.c, 抽髓掌
// by pishou
// Modified by Lklv 2002.1.30

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N催动内力，衣袖挥动，双掌挟着一股腥臭之气一前一后拍向$n的$l",
	"lvl" : 0,
	"damage_type": "瘀伤"
]),
([
	"action": "$N双脚一曲一弯，身体旋转起来, 突然间双掌飞舞着拍向$n的$l",
	"lvl" : 20,
	"damage_type": "瘀伤"
]),
([
	"action": "$N身形飘动，围着$n一圈圈游走，同时双掌连拍，激起阵阵劲风吹向$n",
	"lvl" : 40,
	"damage_type": "内伤"
]),
([
	"action": "$N突然厉声大喝，跃于半空，立掌如斧，上上下下向$n连连劈出数掌",
	"weapon" : "掌风",
	"lvl" : 60,
	"damage_type": "割伤"
]),
([
	"action": "$N身形微晁抢前一步，运起十成功力，大喝一声，须发戟张，呼的一掌又向$n推去",
	"lvl" : 90,
	"damage_type": "内伤"
]),
([
	"action": "$N面露诡异的笑容，猛地向前冲出，对准$n的$l就是一招阴毒无比的「抽髓掌」",
	"lvl" : 120,
	"damage_type": "瘀伤"
]),
([
	"action": "$N心念一转，计上心来，一招「三阴蜈蚣爪」，招招连环，连珠般抓向$n的$l",
	"weapon" : "手爪",
	"lvl" : 150,
	"damage_type": "抓伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-zhua"; }

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me,object weapon)
{
	string msg;
	int i, level, j;
	level   = (int) me->query_skill("chousui-zhang",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			//冰蚕毒掌
			if ( me->query_temp("csz/bingcan")){
				switch(me->query_temp("csz/bingcan")){
					case 5:	msg =HIC"$N纵身上前，一掌拍出。$n急忙举手挡格，喀喇喇几声响，$n臂骨、肋骨齐断，招式寻常，但威力却大的出奇"NOR;	break;
					case 4:	msg =HBWHT+HIB"$N更不打话，左手凌空劈出，右掌跟着迅捷之极的劈出，左手掌力先发后到，右手掌力后发先到，两股力道交错而前，诡异之极"NOR;			break;
					case 3:	msg =HBGRN+HIB"$N每一拳击出、每一掌拍出，都是满含阴寒之气。$n以全力和$N相拚之际，不由得寒气袭体，大为难当"NOR;	break;
					case 2:	msg =HIG"$N的冰蚕毒掌发动，内力既强，劲道阴寒，怪异之极，而且蕴有剧毒$n防不胜防"NOR;	break;
					case 1:	msg =HIB"$N惶急之下，右掌用力挥出，要想推开对方，拍的一声，正中$n的左肩,这一掌来势劲力大得异乎寻常"NOR;			break;
					case 0:	msg =HBYEL+HIG"$N踏上一步，接了$n这一招，叫道：“纳命来！”呼呼呼呼，连出四掌，每出一掌，便跨上一步"NOR;	break;
					default:msg =HIB"$N单脚在地上一顿，右掌立即拍出，一股阴寒之气随伴着掌风直逼而至$n的$l"NOR;	break;
				}
				me->add_temp("csz/bingcan", -1);
				return ([
					"action":	msg,
					"poison":	action[j]["poison"],
					"damage_type":	random(2)?"震伤":"内伤",
					"weapon":	action[j]["weapon"],
					"force":	150+random(200),
					"dodge":	random(30),
					"damage":	250+random(100),
					"parry":	random(30),
				]);
			}			
			//抽髓掌
			if ( me->query_temp("csz/chousui")){
				switch(me->query_temp("cxz/chousui")){
					case 3:	msg =HIB"$N咬破舌尖，口中喷血，聚集全身的力量将毒质运至右手，突然一转身往$n的$l拢去"NOR;	break;
					case 2:	msg =HIB"$N脸上露出诡异的笑容，身影忽前忽后，隐隐泛出绿色的双掌扫向$n的$l"NOR;			break;
					case 1:	msg =HIB"$N突然身形旋转起来扑向$n，双掌飞舞着挟着一股腥臭之气，阴毒无比地拍向$n的$l"NOR;	break;
					default:msg =HIB"$N突然身形旋转起来扑向$n，双掌飞舞着挟着一股腥臭之气，阴毒无比地拍向$n的$l"NOR;	break;
				}
				me->add_temp("csz/chousui", -1);
				return ([
					"action":	msg,
					"damage_type":	random(2)?"震伤":"内伤",
					"weapon":	action[j]["weapon"],
					"force":	150+random(200),
					"dodge":	random(30),
					"damage":	150+random(100),
					"parry":	random(30),
				]);
			}
			return ([  
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"weapon":	action[j]["weapon"],
				"force":	200+random(350),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
		}
	}
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("空了手才能练抽髓掌。\n");
	if ((int)me->query_skill("huagong-dafa", 1) < 10)
		return notify_fail("你还是先练好化功大法吧。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你内力修行太差, 练不了抽髓掌。\n");
	return 1;
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chousui-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练抽髓掌。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int poison, i,skill,damage;
	skill=me->query_skill("chousui-zhang",1);
	poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/5;
	poison += me->query_skill("chousui-zhang",1)/10;
	damage=skill+poison+me->query_skill("huagong-dafa",1);
	damage=damage*me->query_str()/20;
	if (damage>6000) damage=6000;
	
	if ( userp(victim)) {
		poison /= 3;
		i = 120;
	}
	else
		i = 50;
	
	//碧烟后暴击招式
	if (me->query_temp("csz/biyan")
		&& victim
		&& random(10)>6
		&& present("huo yan",environment(me)))
	{
		message_vision(HIG"$N化功大法劲气汹涌，一脚踢向地上的火焰，“噗”地一声溅起一股绿幽幽的火苗飞向$n！\n"NOR,me,victim);
		victim->add_busy(1);
		victim->receive_damage("qi",damage,me);
		victim->receive_wound("qi",damage/4,me);
	}
//中毒招式
	if(random(me->query_skill("huagong-dafa", 1)) > i
	&& me->query_skill("chousui-zhang", 1) > 50
	&& me->query_skill("poison", 1) > 50
	&& me->query("env/化功大法") != "内敛"
	&& random(me->query_skill("poison", 1)) > random( victim->query_skill("medicine", 1))
	&& victim->query_condition("xx_poison") < 200
	&& me->query("neili") > 200
	&& !victim->query("job_npc")) {
		if (me->query("env/化功大法") == "散毒") {
			poison += random(poison/2);
			me->add("neili",-100-random(50));
			me->add("jingli",-20-random(30));
			message_vision(BLU"$N内力一催，手爪上蓝气大盛！\n"NOR, me);
		}
		if (!userp(victim)) victim->add_condition("xx_poison", poison);
		else victim->add_condition("xx_poison", 2);
		message_vision(BLU"$N一中爪，身子一晃，看来已经中了毒！\n"NOR, victim);
		if (victim->query_condition("xx_poison") > 50)
			message_vision(HBRED"$N体内积毒已深，恐怕有生命危险！\n"NOR, victim);
		
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && ! me->query_temp("revenge/"+victim->query("id"))
		 && !victim->query_condition("killer")
               && (!me->query_temp("special_die") || !victim->query_temp("special_die")))
			me->add_condition("killer", 5);
	}
//解开天蚕后效果释放

	if( me->query_temp("csz/bingcan")  && random(10)>6  )        
    {  
              
			if ( random(skill) > 50 && random(me->query_dex()) > victim->query_dex()/4) 
			{
                message_vision(BLU+BWHT "眼见$n越战越勇，$N却丝毫不放在心上，举手投足间平平挥出一掌，带起一股怪异的寒气包裹向$n\n"
                                   "$n见来势怪异，掌风中竟夹杂着刺骨的寒气，不禁打了个冷战。 \n"NOR,me,victim);
                if(userp(victim))
				{
					victim->add_busy(1+random(3));
					victim->add_condition("cold_poison", 2);
				}
				else 
				{
					victim->add_busy(2+random(4));
					victim->add_condition("cold_poison", 5);
				}                    
                       
			}
			else if (random(skill) > 350 && random(me->query_str()) > victim->query_str()/2)
			{
                message_vision(HIW "$N趁机踏步上前，向$n面门前虚晃一招，$n还未抵挡，不料后招又至，正中$n小腹。\n" NOR,me,victim);
                message_vision(WHT "$n只觉丹田中真气似被冻结一般，无法凝聚，顿时出了一身冷汗。\n" NOR,me,victim);
				
				if(userp(victim))
				{
                      victim->add("jing",- poison); 
                      victim->add("neili",- poison); 
                      victim->add("jingli",- poison); 
                      victim->apply_condition("no_perform", 1);
                      victim->apply_condition("no_exert", 1);
                      victim->add_condition("cold_poison", 2);
				}
				 else
				{
                      victim->add("jing",- poison*2); 
                      victim->add("neili",- poison*2); 
                      victim->add("jingli",- poison*2); 
                      victim->apply_condition("no_perform", 2+ random(4));
                      victim->apply_condition("no_exert", 2+ random(4));
                      victim->add_condition("cold_poison", 30);
				
                }  
			

			}
	}
		 
}

string perform_action_file(string action)
{
	return __DIR__"chousui-zhang/" + action;
}
