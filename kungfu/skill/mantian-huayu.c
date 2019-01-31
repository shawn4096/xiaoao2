//mantian-huayu.c 漫天花雨，日月绝技，黑白子、向问天、曲洋
//cre by sohu@xojh
#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
string	*msg = ({
"$N身子左侧，一式「月下踏径」，右手$w从身体下方突然甩出，直射向$n的$l",
"$w破空飞出，一式「长虹经天」，缓缓一个弧线，由左自右，绕向$n的$l，",
"$N双手连扬，一式「破云见日」，两把$w向$n撒出，笼罩$n的全身上下",
"$N向空中一撒，却是$n一招「秋日落叶」，十多枚$w由空中缓缓落下",
"$N身形急速向前滑动，一式「雪地追踪」，三枚$w向$n的胁下射去",
"$N一式「回首沧桑」，身体一转，反手掷出数枚$w，飞向$n的背部",
"$N凌空一纵，一招「雨打浮萍」，居高临下，手中$w疾射，直向$n的$l",
"$N一招「流星电闪」，手指弹出五枚$w，一点黑光射向$n的头部",
});

int valid_enable(string usage)
{
	return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	  
	if (me->query_temp("mthy/xingluo"))
	{
		   	
	   return ([
		"action":YEL+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$W"), "$W", "$w"YEL)+NOR,
		"damage": 100 + random(60),
		"damage_type":"刺伤",
		"dodge": random(20)-10,
		"parry": random(10),
		"force": 100 + random(250),
		//"post_action": (: call_other, WEAPON_D, "throw_weapon" :)
	    ]);
	}
	
	
	return ([
		"action":msg[random(sizeof(msg))],
		"damage": 60 + random(60),
		"damage_type":"刺伤",
		"dodge": random(20)-10,
		"parry": random(10),
		"force": 100 + random(250),
		//"post_action": (: call_other, WEAPON_D, "throw_weapon" :)
	]);
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 30 || me->query("neili") < 10)
		return notify_fail("你的体力不够练漫天花雨。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "throwing")
		return notify_fail("你使用的武器不对。\n");
	if ( me->query("max_neili") < 1000)
		return notify_fail("你的内力不够。\n");

	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"mantian-huayu/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
     object weapon = me->query_temp("weapon");

    	if (!weapon) return;
		//增加解密后效果
     	if(((string)weapon->query("id")=="xiuhua zhen" ||(string)weapon->query("id")=="zhen" || (string)weapon->query("id")=="qijue zhen" || weapon->id("needle"))  
      	&& random(me->query_str()) > victim->query_str()/2){
			  victim->receive_wound("qi", me->query_str(1)*random(200),me);
		 message_vision(HIR "只听「嗤」一声，一缕血丝从"+victim->name()+"被刺的针孔处喷出！\n" NOR,me,victim);
		}
		//身带黑血神针效果
		if (!victim->is_busy()&&weapon->query("id")=="heixue shenzhen"&&me->query("hmy/quest/heixue")&&random(10)>6)
		{
          message_vision(HIY"$N趁$n不备，忽然甩出几根黑血神针，$n一不小心为神针刺中穴道，顿时身形受制。\n"NOR,me,victim);
		  victim->add_busy(2+random(3));
		  victim->apply_condition("heixue_poison",1+random(2));

		}
		//三尸毒，身带三尸丹毒
        if (present("sanshi dan",me)&&me->query("hmy/quest/sanshi")&&random(10)>5)
        {
			message_vision(HIB"\n$N从口袋中摸出一粒三尸脑神丹，趁$n张口大喝之际，猛然掷出，一道虹影飞向$n的口中！\n"NOR,me,victim);
		    if (!victim->is_killing(me))
                me->kill_ob(victim);
			if( random(me->query("combat_exp")) > (int)victim->query("combat_exp")/2
                && me->query_str() > (int)victim->query_dex()/2){ 
               message_vision(HIG"\n$n见此怪异的招数，一时间手足无措，躲闪无及，下意识的吞下了这粒药丸。\n"NOR, me, victim);
               me->add("max_neili", -random(1));
		       me->add("neili", -random(1000));
	        if (userp(victim))
		       me->add_condition("killer", 90);
           victim->set_temp("last_damage_from", "三尸脑神毒入脑");
		   victim->apply_condition("sanshi_poison", 5+random(3));
           victim->receive_wound("jing",random(1000),me);
		   message_vision(HIC"$n一口吞下毒丹，心中不禁惴惴不安，大脑中宛如有小虫子在蠕动的感觉，心中不由大骇！\n"NOR,me,victim);
		   victim->apply_condition("no_exert",1);
           return ;  
         }
         else if(random(me->query("combat_exp")) > (int)victim->query("combat_exp")/3
         || random(me->query("neili")) > victim->query("neili")/2){
          message_vision(HIB"\n$n见事不好，连忙纵身直起，三尸脑神丹从身下掠过，没有打中。\n"NOR,me,victim);
          tell_object(victim,HIB"\n你虽然及时避开了毒尸，但一股腥臭气入鼻，你已中了三尸脑神毒了。\n"NOR);
          me->add("neili", -400);
	      if (userp(victim))
		     me->add_condition("killer", 15);
          victim->apply_condition("sanshi_poison", 3+random(3));
          me->start_busy(1);
          victim->add_busy(1);
          return ;
         }

      }

	return;
				
}