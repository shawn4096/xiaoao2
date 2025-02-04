// tiezhang-zhangfa 铁掌掌法
// BY BOBO@SJ 
// Update By lsxk@hsbbs 2007/5/15

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N右掌一拂而起，一招「推窗望月」，左掌自侧面连消带打，登时将$n的力道带斜，右掌一挥，拍向$p$l",
	"lvl": 0,
	"damage_type": "瘀伤",
	"skill_name": "推窗望月"
]),
([
	"action": "$N使一招「分水擒龙」，右臂突伸抓向$n，左掌陡然沿着伸长的右臂，飞快的一削而出，斩向$n的$l",
	"lvl": 20,
	"damage_type": "瘀伤",
	"skill_name": "分水擒龙"
]),
([
	"action": "$N突然使一式「白云幻舞」，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪，掌势一推，压向$n",
	"lvl": 40,
	"damage_type": "瘀伤",
	"skill_name": "白云幻舞"
]),
([
	"action": "$N一招「掌中乾坤」，一掌拍出以后，猛地侧过身来，右臂自左肋下疾翻而出，拇，中两指扣圈猛弹$n的$l",
	"lvl": 60,
	"damage_type": "内伤",
	"skill_name": "掌中乾坤"
]),
([
	"action": "$N一招「落日赶月」，伸掌一拍一收，一拍无丝毫力道，一收之间，一股阴柔无比的力道才陡然发出",
	"lvl": 80,
	"damage_type": "瘀伤",
	"skill_name": "落日赶月"
]),
([
	"action": "$N身行暴起，一式「蛰雷为动」，双掌横横切出，掌缘才递出，呜呜呼啸之声狂作，铁掌之名，由此而出",
	"lvl": 100,
	"damage_type": "内伤",
	"skill_name": "蛰雷为动"
]),
([
	"action": "$N一招「天罗地网」，左掌大圈而出，右掌小圈而出，两股奇异的力道一会之下，巨大的内劲压向$n的$l",
	"lvl": 120,
	"damage_type": "瘀伤",
	"skill_name": "天罗地网"
]),
([
	"action": "$N一招「五指幻山」，猛一吐气，单掌有如推门，另一掌却是迅疾无比的一推即收，双劲合一，去势如虎",
	"lvl": 140,
	"damage_type": "内伤",
	"skill_name": "五指幻山"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me,object weapon)
{
	int i, level, j;
	string msg;

	level = me->query_skill("tiezhang-zhangfa",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			//铁掌合一
			if ( me->query_temp("tz/heyi")) {
				switch(me->query_temp("tz/heyi")){
					case 3: msg = HIB"$N突然脚下一晃，欺进$n，右掌一翻，运起铁掌罡气，单掌向$p顶门直拍而下"NOR; break;
					case 2: msg = HIR"紧接着$N身体一转，到了$n身旁，左掌顺力拍出，这一招看似平和，实是内涵罡气，威力无比"NOR; break;
					case 1: msg = HIW"最后$N猛一吐气，单掌有如推门，另一掌却是迅疾无比的一推即收，双劲合一，去势如虎"NOR; break;
					default : msg = HIB"$N突然脚下一晃，欺进$n，右掌一翻，运起铁掌罡气，单掌向$p顶门直拍而下"NOR; break;
				}
				me->add_temp("tz/heyi", -1);
				return ([
					"action": msg,
					"force": 250 + random(350),
					"parry": random(20)+10,
					"dodge": random(20)+10,
					"damage": 100 + random(100),
					"damage_type": "瘀伤"
				]);
			}
			//铁掌掌法招数且铁掌特技
            if (me->query_temp("tzzf")){
                     if (me->query_temp("tz/tiezhang")){
                       me->add("neili", -500);
                           return ([
                                   "action" : BLU+action[j]["action"]+NOR,
                                   "force" : 400 + random(400),
                                   "damage": random(100)+150,
                                   "dodge": action[j]["dodge"]+random(20),
                                   "parry": random(20)+10,
                                   "lvl" : action[j]["lvl"],
                                   "damage_type" : action[j]["damage_type"],
                           ]);
                     }
                     else {
 				           return ([
					               "action" : WHT+action[j]["action"]+NOR,
 					                "force" : 350 + random(350),
 					                "damage": random(100)+50,
 				                	"dodge": action[j]["dodge"]+random(20),
 					                "parry": random(20)+10,
					                "lvl" : action[j]["lvl"],
 					                "weapon" : "铁掌",
					                "damage_type" : "割伤",
				                   ]);
                         }
              }
			 //解开融合且非合一状态，银钩笔法,
			//修改银钩笔法，改为铁掌
			if( random(me->query_skill("strike", 1)) > 100 
			 && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
			 && me->query("max_pot",1) >450 
			 && !random(3)
			 && me->query("neili") > 30 
             && me->query("quest/tzauto/over") == 1   
			 && !me->query_temp("tz/heyi")) {
				me->add("neili", -20);
				return ([
					"action": HIW"$N右掌忽然变得轻灵，左掌却凝重如山，$n正招架不暇，忽的$N招式一换，双掌先后挥出，铁掌掌法中阴阳合一的招式！"NOR,
					"force": 400 + random(300),
					"parry": 30,
					"dodge": 30,
                    "damage": 160 +random(140),

					"damage_type": "刺伤"
				]);
			}
			
            //融合一柳叶刀
            if (random(me->query_skill("strike", 1)) > 100 
			 && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
			 && (me->query_skill("liuye-daofa") > 100 || me->query("max_pot",1) >450 )
			 && !random(3)
			 && me->query("neili") > 30 
             && me->query("quest/tzauto/over") == 1
			 && !me->query_temp("tz/heyi")) {
				me->add("neili", -20);
				return ([
					"action": HIR"$N忽然立掌如刀，招式一变，用的却是柳叶刀法中的两刀一掌的功夫！"NOR,
					"force": 400 + random(300),
					"parry": 30,
					"dodge": 30,
                    "damage": 120 +random(100),
	
					"damage_type": "割伤"
				]);
			}
			//裂天斧招式
           if (random(me->query_skill("strike", 1)) > 100 
			 && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
             && (me->query_skill("lietian-fu") > 200 || me->query("max_pot",1) >320)
			 && !random(3)
             && me->query("quest/tzauto/pass") == 1
			 && me->query("neili") > 30 
			 && !me->query_temp("tz/heyi")) {
				me->add("neili", -20);
				return ([
					"action": HIY"$N忽然左掌虚晃，右掌却悄悄运力，宛如提着一把大斧，呼的一声当头朝$n劈下，却是一招“离魂斩”！"NOR,
					"force": 400 + random(300),
					"parry": 30,
					"dodge": 30,
                    "damage": 140 +random(100),

					"damage_type": "劈伤"
				]);
			}
			//黑沙掌
			if (random(me->query_skill("strike", 1)) > 100 
			 && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
             && (me->query_skill("lietian-fu") > 200 || me->query("max_pot",1) >320)
			 && !random(3)
             && me->query("quest/tzauto/pass") == 1
			 && me->query("neili") > 30 
			 && !me->query_temp("tz/heyi")) {
				me->add("neili", -20);
				
				return ([
					"action": HIY"$N双手一错，一上一下向$n的胸口及丹田击到！却是铁掌掌法中极为险恶的「黑砂掌」招式！"NOR,
					"force": 400 + random(300),
					"parry": 30,
					"dodge": 30,
                    "damage": 150 +random(100),
					"damage_type": "劈伤"
				]);
			}
            //铁掌招式，和其他招式
            if (me->query_temp("tiezhang")) {
                           me->add("neili", -300);
                          return ([
                                   "action": CYN + action[j]["action"] + NOR,
                                   "lvl": action[j]["lvl"],
                                   "damage_type" : action[j]["damage_type"],
                                   "force":300+random(350),
                                   "dodge":random(30)-10,
                                   "parry":random(20),
                                   ]);
            } 
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":200+random(350),
				"dodge":random(30)-10,
				"parry":random(20),
			]);
		}
	}
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练铁掌掌法必须空手。\n");
	if ((int)me->query_skill("force", 1) < 35)
		return notify_fail("你的内功火候不够，无法练铁掌掌法。\n");
	if ((int)me->query_skill("guiyuan-tunafa", 1) < 35)
		return notify_fail("你的归元吐纳法火候不够，无法练铁掌掌法。\n");
	if ((int)me->query("max_neili") < 40)
		return notify_fail("你的内力太弱，无法练铁掌掌法");
	return 1;
}

int practice_skill(object me)
{
	int lvl = me->query_skill("tiezhang-zhangfa", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练铁掌掌法。\n");

	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tiezhang-zhangfa/" + action;
}



mixed hit_ob(object me, object victim, int damage)
{
  

        int lvl,attack,lb,j;
		j = me->query_skill("tiezhang-zhangfa", 1);
        lvl= me->query_skill("tiezhang-zhangfa",1) +  me->query_skill("lietian-fu",1) +  me->query_skill("liuye-daofa",1) + me->query_skill("yingou-bifa",1);
        lvl = lvl/4;
        lb = random(10);
       //增加黑沙掌中毒，
	   //聚毒掌
	   //旋风快掌
	   //轰雷
	   //盘根 $N毫不容情，双手犹似两把铁钳，往$n咽喉扼去！
		if (me->query_skill("tiezhang-zhangfa",1)<500) return;
		
        if (!me->query("quest/tzauto/over")) return;
        

		if (!random(10)&& me->query_skill("tiezhang-zhangfa",1)>550)
		{
			message_vision(HBBLU "\n$N蓦地里转身，使出铁掌掌法中的「轰雷双掌」绝技对$n胸口双掌推出！\n"NOR,me,victim);
			if (random(me->query_dex()) > victim->query_dex()/2)
			{
				message_vision(HIR"\n结果一击命中，$n向后飞出足足三四丈远，口中鲜血狂喷！\n"NOR,me,victim);
				j *= 10;
				j += me->query("jiali")*10;
				j -= victim->query_con()*20;
				j = j*2/3 + random(j);
				victim->receive_damage("qi", j,me);
				victim->receive_wound("qi",j/2,me);				
			} 
		}
		
		//黑沙掌中毒
		else if (random(10)>6&& me->query_skill("tiezhang-zhangfa",1)>450)
		{
			message_vision(HIB"$N双手一错，一上一下向$n的胸口及丹田击到！却是铁掌掌法中极为险恶的「黑砂掌」招式！\n"NOR,me,victim);
			if (random(me->query_dex(1)) > victim->query_dex(1)/2 
			|| random(me->query_int(1)) > victim->query_int(1)/2)
			{
               message_vision(HIR"结果$N双双击中，$n真气一窒，内息再也无法自由运转！\n"NOR,me,victim);
               victim->add_busy(1);
               victim->add_condition("no_force",1);
			   victim->add_condition("tz_poison",2);
			}
		}
        else if (random(10)>5 && me->query_skill("tiezhang-zhangfa",1)>350)
        {
			message_vision(HIC"\n$N双臂圈拢，施展出「枯树盘根」绝技，毫不容情，双手犹似两把铁钳，往$n咽喉扼去！\n"NOR,me,victim);
			if (random(me->query_int(1)) > victim->query_int(1)/2) 
			{
				message_vision(HIR"$n暗暗心惊，翻身后退，只听得$N“嘿”的一声，$n双手已落入$N掌握之中。\n"NOR,me,victim);
				victim->add_busy(1);
				if (!userp(victim)) victim->add_busy(2);
				else victim->add_busy(1);
			}
        }/**/
//解开融合后功效
        if( !me->query_temp("tzrh/auto") && userp(me)&& me->query("quest/tzauto/over") )   	
      	{  

 		 if(  lb> 7 &&  me->query_temp("tiezhang") ) 
          {
             message_vision(HBBLU "$N武技早已臻登峰造极之境，铁掌武技烂熟于心，一双肉掌或劈或砍或点，使的居然全是长兵刃的招式!\n" NOR,me,victim);
             victim->start_busy(random(2));
                         me->set_temp("tzrh/auto", 1);
                         me->add_temp("apply/attack",  me->query_skill("lietian-fu", 1)/6);
                         COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(4)?1:3);
                        me->add_temp("apply/attack", -me->query_skill("lietian-fu", 1)/6);
                        me->delete_temp("tzrh/auto");
                        victim->apply_condition("no_perform", 2+ random(2));
         } 
         else if(  lb> 5 &&  me->query_temp("tiezhang") ) 
          {
        	message_vision(HBRED "这铁掌连环绝技乃是$N看家本领，招招穷追猛打，不死不休！" NOR, me,victim);
        	victim->start_busy(random(2));
            me->set_temp("tzrh/auto", 1);
                         me->add_temp("apply/attack",  me->query_skill("liuye-daofa", 1)/6);
                         COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(4)?1:3);
                        me->add_temp("apply/attack", -me->query_skill("liuye-daofa", 1)/6);
                        me->delete_temp("tzrh/auto");

        }

         else if( lb>3 || me->query_temp("tiezhang") )
         {
					  message_vision(HBMAG "$N灵光一闪，平生所学刹那间融会贯通，紧跟着又拍出一掌。\n" NOR,me, victim);
				      victim->start_busy(random(attack+1));
                      me->set_temp("tzrh/auto", 1);
                      me->add_temp("apply/attack",  me->query_skill("yingou-bifa", 1)/6);
                      COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(4)?1:3);
                      me->add_temp("apply/attack", -me->query_skill("yingou-bifa", 1)/6);
                      me->delete_temp("tzrh/auto");
 
           }

        }

}
