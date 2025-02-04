// Modified by Darken@SJ
//update by master@zitan
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
string *xue_name1 = ({ 
        "大锥穴",
        "百会穴",
        "志室穴",
        "肩井穴",
        "劳宫穴",
        "内关穴",
        "外关穴",
        "会宗穴",
});
string *xue_name2 = ({
        "曲池穴",
        "冲阳穴",
        "臂儒穴",
        "白海穴",
        "灵台穴",
        "风府穴",
        "神风穴",
        "玉书穴",
}); 
string *xue_name3 = ({
        "青门穴",
        "商阳穴",
        "丝空竹穴",
        "气海穴",
        "冲门穴",
        "大椎穴",
        "百里穴",
        "槐阳穴",
}); 

mapping *action_finger = ({
([      "action" : "$N中指微屈，突然弹出，一式「指点江山」，一缕劲风直袭$n的$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -5,
        "lvl" : 0,
        "skill_name" : "指点江山",
        "damage_type" : "刺伤"
]),
([      "action" : "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！直袭$n的$l",
        "force" : 300,
        "dodge" : 0,
        "parry" : 10,
        "lvl" : 60,
        "skill_name" : "如来神指",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右臂挥动，中指连弹，在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "force" : 400,
        "dodge" : 8,
        "parry" : -8,
        "lvl" : 120,
        "skill_name" : "一衣带水",
        "damage_type" : "割伤"
]),
([      "action" : "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」铺天盖地般向$n涌去",
        "force" : 450,
        "dodge" : -3,
        "parry" : -10,
        "lvl" : 180,
        "skill_name" : "弹指惊雷",
        "damage_type" : "刺伤"
]),
});

mapping *action_throwing = ({
([      "action" : "$N中指微屈，突然弹出，一式「指点江山」，$w破空之声甚厉，直袭$n的$l",
        "force" : 130,
        "dodge" : -5,
        "parry" : -10,
        "damage" : 60,
        "lvl" : 0,
        "skill_name" : "指点江山",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！$w呼啸着直袭$n的$l",
        "force" : 170,
        "dodge" : 5,
        "parry" : -15,
        "damage" : 80,
        "lvl" : 60,
        "skill_name" : "如来神指",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N右臂挥动，中指连弹，数个$w在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "force" : 240,
        "dodge" : -5,
        "parry" : -6,
        "damage" : 110,
        "lvl" : 120,
        "skill_name" : "一衣带水",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」弹出铺天盖地的$w，向$n涌去",
        "force" : 320,
        "dodge" : 0,
        "parry" : -10,
        "damage" : 150,
        "lvl" : 180,
        "skill_name" : "弹指惊雷",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="throwing" || usage=="parry"; }

int valid_learn(object me)
{
        object weapon;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
                return notify_fail("学弹指神通必须空手或手持暗器。\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("你的碧海潮生功火候不够，无法学弹指神通。\n");
        if ((int)me->query("max_neili") < 200)
                return notify_fail("你的内力太弱，无法练弹指神通。\n");
        return 1;
}


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                if(level >= action_finger[i]["lvl"])
                        return action_finger[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("finger");

        if (random(level) > 250 || random(me->query_temp("thd/is_fast")) > 300) {
                me->add("neili", -20);
                if (!weapon)
                        return ([
                                "action": HBRED "$N一声断喝，身形开始急速晃动，绕着$n游走。$n一错愕间，只听“嗤嗤”之声连响，无数道劲风从四面八方袭向$n！" NOR,
                                "force": 200,
					            "damage": 150+random(50),
                                "dodge" : 10,
                                "parry" : 10,
                                "damage_type": "刺伤"
                        ]);
                else    return ([
                                "action": HIR "$N一声断喝，身形开始急速晃动，绕着$n游走。$n一错愕间，只听“嗤嗤”之声连响，无数" + weapon->query("unit") + weapon->query("name") + HIR"从四面八方袭向$n！" NOR,
                                "damage": 300,
                                "force": 380,
                                "dodge" : 8,
                                "parry" : 4,
                                "damage_type": "刺伤"
                        ]);
        }
        if (!weapon) {
                for(i = sizeof(action_finger); i > 0; i--)
                        if(level >= action_finger[i-1]["lvl"])
                                return action_finger[NewRandom(i, 20, level/5)];
        }
        else
                for(i = sizeof(action_throwing); i > 0; i--)
                        if(level > action_throwing[i-1]["lvl"])
                                return action_throwing[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("tanzhi-shentong", 1);
        int i = sizeof(action_finger);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["tanzhi-shentong"])
         while (i--) 
           if (lvl == action_finger[i]["lvl"])
              return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
              return notify_fail("练弹指神通必须空手或手持暗器。\n");
        if ((int)me->query("jingli") < 50)
              return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
              return notify_fail("你的内力不够练弹指神通。\n");
        me->receive_damage("jingli", 45);
        me->add("neili", -20);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tanzhi-shentong/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl = me->query_skill("finger",1)+me->query_skill("tanzhi-shentong",1);
		
        string name1,name2, name3;
        if ( me->query("thd/wuji/lingxi")) lvl=lvl*2;
		else lvl=lvl/2;
		//解密灵犀一指后，威力增强
        if ((random(lvl) > 100 && random(me->query_dex()) > victim->query_dex()/2 ||
             random(me->query_temp("thd/is_fast")) > 200) && !victim->is_busy()) {
                name1 = xue_name1[random(sizeof(xue_name1))];
                name2 = xue_name2[random(sizeof(xue_name2))];
                name3 = xue_name3[random(sizeof(xue_name3))];
                message_vision(HIR "$n被$N点中了「"HIC + name1 + HIR"」，内息大乱！\n" NOR,me,victim);
				victim->apply_condition("no_exert",1);
				victim->add("neili",-lvl);
                victim->add_busy(random(2)+1);
				victim->set_temp("faint_by",me);
                if (random(lvl) > 350&&!random(3)) {
                        message_vision(HIY "$N手指微动，又点中了$n的「"HIC + name2 + HIY"」！\n" NOR,me,victim);
                        message_vision(HIG "$n只觉得头微微晕眩，精神收到很大损害，不能集中！\n" NOR,me,victim);
                        victim->add("jing",- lvl/6); 
                        victim->add("jingli",- lvl/6); 
                }
                if (!random(5) && random(lvl) > 450 && me->query("thd/wuji/lingxi")) {
                        message_vision(HIG "$N反手使出【灵犀一指】绝技，再点向$n的「"HIC + name3 + HIG"」！\n" NOR,me,victim);
                        message_vision(HIG "$n丹田一阵剧痛，内力无法凝聚！\n" NOR,me,victim);
						victim->apply_condition("no_perform",2); //通过解密灵犀一指来增加点穴破对方内功的功效
                        victim->add("neili",- lvl*2); 
                }
        }
}

int ob_hit(object ob, object me, int damage)
{

	object weapon;
	string msg;
      int ap,dp,skill,j;

     if(!userp(me)) return 0;
      ap = ob->query_skill("parry",1)+ ob->query_skill("dodge",1);
      dp = me->query_skill("parry", 1)+ me->query_skill("tanzhi-shentong",1);
      if( random(me->query("str"))< ob->query("str")/3 ) return 0;
	if(objectp(weapon = ob->query_temp("weapon")) ) msg = weapon->query("skill_type");
     
        if (me->query_skill("tanzhi-shentong", 1) < 250
	|| me->query_skill_mapped("finger") != "tanzhi-shentong"
	|| me->query("combat_exp") < ob->query("combat_exp")/3) return 0;

        if ( me->query("neili") < ob->query("neili") * 2/3 ) return 0;
        	
	if ( me->is_busy() ) dp *= 2;
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;

	if ( skill > 550 ) dp += random(dp*2);
	else if ( skill > 450 ) dp += random(dp/2*3);
	else if ( skill > 350 ) dp += random(dp);

        if ( random(dp) > ap || random(me->query_skill("finger",1))>ob->query_skill("parry",1)/2) {
		  if( random(me->query("neili")) > ob->query("neili")/2 ) {
			  if( weapon ){
                            msg = HIG"$N突然伸指弹在"+weapon->name()+HIG"上一弹，只弹$n虎口崩裂,全身酸麻,也把持不住,只得丢下了"+weapon->name()+"！\n"NOR;
			                weapon->unequip();
		     	            weapon->move(environment(ob));
		       } else msg = HIR"$N侧身避过,紧跟着手指连弹,指风犀利如剑! 猛的弹在了$n身上！\n"NOR;
    		//ob->receive_damage("qi", damage/2 + me->query("jiali")*2, me);
			  ob->receive_damage("qi", damage/5, me);
			  ob->receive_wound("qi", me->query("jiali")+random(200), me);
			  ob->set_temp("faint_by",me);
			  j = -damage;
		}
		else {
            if( weapon ) msg = HIC"$N看准来势,毫不避让,伸手在$n的"+weapon->name()+HIC"上轻轻一弹！\n"NOR;
            else msg = HIC"$N左手一划，手指轻弹，正好阻住$n的进攻！\n"NOR;
			j = -damage;
		}

	}
	else if ( random( dp ) > ap /2 && random(me->query_dex())>ob->query_dex()/2 ) {
               if( weapon ) msg = HIR"$N身形一转，在$n递近身的"+weapon->name()+HIR"上轻轻一弹,直震得$n虎口崩裂,手臂发麻！\n"NOR;
		       else {
                  msg = HIM"$N毫不避让,中指连弹,猛的戳在了$n身上！\n"NOR;

		}
		message_vision(msg, me, ob);
		return -damage;
	}
	else if( random( dp) > ap  ) {
     if( weapon ) msg = HIW"$N情急之下，手指在$n递近身的"+weapon->name()+HIW"猛力一弹，卸掉了$p一部分劲力！\n"NOR;
                else msg = HIW"$N手指连弹,$n的攻击受挫,劲力稍减！\n"NOR;
		j = -damage/4;
	}
	else if( random( dp * 2 ) > ap ) {
        if( weapon ) msg = MAG"$N急中生智，在"+weapon->name()+MAG"猛的一弹,抵消了部分劲力！\n"NOR;
		else msg = HIY"$N慌忙间手指连弹，想要阻住$n的进攻！\n"NOR;
		j = -damage/5;
	}
	else return 0;

	message_vision(msg, me, ob);

	return j;

}

