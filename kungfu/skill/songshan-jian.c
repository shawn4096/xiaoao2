// songshan-jian.c  嵩山剑法
// Lklv@SJ modified 2001.10.22
// tangfeng@SJ 2004.12
// server 调整set

#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
 
int strike_hit(object me, object victim, object weapon, int damage);
 
mapping *action = ({
([
 "action" : "$N举剑过顶，弯腰躬身，恭敬一式「万岳朝宗」，手中武器向$n的$l轻轻刺去，",
 "lvl" : 0,
 "damage_type" : "刺伤"
]),
([
 "action" : "突然间剑光一吐，手中武器化作一道白虹，$N使出一式「千古人龙」，剑气古朴，直刺$n的$l",
 "lvl" : 15,
 "damage_type" : "刺伤"
]),
([
 "action" : "$N左手向外一分，右手兵器向右掠出一招「开门见山」，剑气森然地向$n的$l挥去",
 "lvl" : 30,
 "damage_type" : "刺伤"
]),
([
 "action" : "$N一剑从空中疾劈而下，招式看似平平无奇，但呼的一声响，实有石破天惊的气势，一招「独劈华山」长剑如虹地刺向$n的$l",
 "lvl" : 45,
 "damage_type" : "刺伤"
]),
([
 "action" : "$N手中兵器自半空中横过，剑身似曲似直，如一件活物一般，一式「天外玉龙」奔腾矫夭，气势雄浑地斩向$n的$l",
 "lvl" : 60,
 "damage_type" : "割伤"
]),
([
 "action" : "$N威仪整肃一式「玉井天池」，手中长剑轰然一动，犹如千军万马奔驰而来，疾疾刺向$n的$l",
 "lvl" : 75,
 "damage_type" : "刺伤"
]),
([
 "action" : "$N剑转一式「叠翠浮青」，俨然长枪大戟，黄沙千里，手中长剑宛如电闪雷鸣，将$n笼罩于重重剑气之中",
 "lvl" : 90,
 "damage_type" : "刺伤"
]),
([
 "action" : "$N剑尖向下，一招「龙啸九天」，长剑忽然急转而上，点出的剑气将$n上身要害团团围住",
 "lvl" : 120,
 "damage_type" : "刺伤"
]),
});
 
int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
 
int valid_learn(object me)
{
 object weapon;
 if (!objectp(weapon = me->query_temp("weapon"))
 || (string)weapon->query("skill_type") != "sword")
  return notify_fail("你使用的武器不对。\n");

 if ((int)me->query("max_neili") < 100)
  return notify_fail("你的内力不够。\n");

 if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
  return notify_fail("你的寒冰真气火候太浅。\n");

 return 1;
}

mapping query_action(object me, object weapon)
{
 int i, level, j;
 string msg;
 int focus = me->query_temp("ss/focus");
 level = me->query_skill("songshan-jian",1);
 
  
 if (me->query_temp("ssj_songyang")){
  switch(me->query_temp("ssj_songyang")){
   case 4: msg = CYN"$N略微一低身形，使一招「旭日升」剑光凛冽，由下而上，如朝阳初升，迅捷无比地砍向$n"NOR; break;
   case 3: msg = CYN"$N双手舞剑，宛如蟠龙回旋，正是一式「蟠龙剑」，嵩山剑沉，配合深厚内力压向$n"NOR; break;
   case 2: msg = CYN"$N将剑收在背后，使一招「千丈渊」左手突然化拳为掌，劲气十足，闪电般地由上而下劈向$n"NOR; break;
   case 1: msg = CYN"紧跟着$N猛喝一声，一式「观胜峰」，右掌挟带着狂风，向前斜推，掌势如劈山排云般压向$n"NOR; break;
   default: msg= CYN"$N轻身纵起，使一招「劈华山」左手突然化拳为掌，劲气十足，闪电般地由上而下劈向$n"NOR; break;
  }
  me->add_temp("ssj_songyang", -1);
  return ([
   "action": msg,
   "dodge": random(30),
   "parry": random(30),
   //增加内功效果
   //"damage": 130 + random(140),
   //注意focus 最大值15，可以参照yun juhan设定
   "damage": 130 + random(140)+ random(focus*6),
   "force": 350+ random(300),
   "damage_type": "劈伤"
  ]);
 }
 for(i = sizeof(action); i > 0; i--) {
  if(level > action[i-1]["lvl"]) {
   j = NewRandom(i, 20, level/5);
    if (me->query_temp("ssj/chaozong1"))
     {
       msg = YEL"\n$N微微一下，施展的正是正宗的嵩山剑法「万岳朝宗」，剑势平缓但却蓄势无穷，似乎后招有绵绵不绝之意。"NOR;
  
       return ([
        "action": HIY+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w"HIY)+NOR+msg,
        "dodge": random(30),
        "parry": random(30),  
        "damage": 100 + random(100),
        "force": 100+ random(100),
        "damage_type": random(2)?"劈伤":"刺伤",       
      ]);
    }
	//雷霆绝杀技能

    if (me->query_temp("ssj/leiting"))
     {
       msg = YEL"\n$N内力鼓荡之下，连衣袖都欲胀裂，直是非同小可，当下一剑全力向着$n刺出。"NOR;
  
       return ([
        "action": HIR+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w"HIB)+NOR+msg,
        "dodge": random(30),
        "parry": random(30), 
        "damage": 180 + random(180) + focus*8,
        "force": 350+ random(300),
        "damage_type": random(2)?"劈伤":"刺伤",
        "post_action": (: strike_hit :),
       ]);
      }
     //增加飞舞效果
	 if (me->query_temp("ss/feiwu"))
     {
       return ([
        "action": WHT+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w"WHT)+NOR,
        "dodge": random(30),
        "parry": random(30),
        "damage": 160 + random(140) + focus*6,
        "force": 350+ random(300),
        "damage_type": random(2)?"劈伤":"刺伤",
        
         ]);

      }
                   //450级别，pfm longfei增加威力
      if(level>=450 && me->query_temp("ss_lf"))
                   return ([
                           "action": HIB+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w"HIB)+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 300 +random(250)+ random(focus*3),
                           "dodge": random(30),
                           "parry": random(20)+20,
                           "damage": 150 + random(150)+ focus*3,
		                   "post_action": (: strike_hit :),
                   ]);
                   //350级别，pfm longfei增加威力
      if(me->query_temp("ssj/zhbh2"))
                     return ([
                           "action":HIC+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w")+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 250 +random(300),
                           "dodge": random(30),
                           "parry": random(20)+20,
                           "damage": 150 + random(100)+ random(focus*3),
        ]);
	   if(me->query_temp("ssj/zhbh1"))
                     return ([
                           "action": HIR+replace_string(replace_string(action[j]["action"], "$w", "$w"), "$w", "$w")+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 250 +random(300),
                           "dodge": random(30),
                           "parry": random(20)+20,
                           "damage": 200 + random(100)+ random(focus*3),
        ]);
   return ([
    "action": action[j]["action"],
    "lvl": action[j]["lvl"],
    "damage_type": action[j]["damage_type"],
    "force": 200 +random(350),
    "dodge": random(30),
    "parry": random(20)+20,
    "damage": 120 + random(100),
   ]);
  }
 }
}
int practice_skill(object me)
{
 int lvl = me->query_skill("songshan-jian", 1);
 int i = sizeof(action);
 while (i--) if (lvl == action[i]["lvl"]) return 0;
 if ((int)me->query("jingli") < 50)
  return notify_fail("你的体力不够练嵩山剑法。\n");
 if ( me->query("neili") < 20 )
  return notify_fail("你的内力不够练嵩山剑法。\n");
 me->receive_damage("jingli", 40);
 me->add("neili", -15);
 return 1;
}

int strike_hit(object me, object victim, object weapon, int damage)
{
 int ap, dp, lvl,damage1,focus;
 focus = me->query_temp("ss/focus");
 lvl = (me->query_skill("songshan-jian", 1)+ me->query_skill("strike") )/2;
        //if(!me->query_temp("ssj/leiting")) return 0;
 if(!victim
 || !weapon
 || me->query("neili") < 3000
 || lvl < 200
 || !present(victim, environment(me))
 || !victim->is_character()
 || !me->is_fighting(victim)
 || !living(victim)
 || me->query_skill_mapped("force") != "hanbing-zhenqi"
 || me->query_skill_mapped("strike") != "hanbing-shenzhang"
 || me->query_skill_prepared("strike") != "hanbing-shenzhang"
 || me->query_skill_mapped("parry") != "songshan-jian")
  {
                 me->delete_temp("ssj/leiting");
                 return 0;
                   }
  me->add_temp("apply/damage", lvl);
  victim->set_temp("must_be_hit", 1);
  weapon->unequip();
  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),3);   
  weapon->wield();
  me->add_temp("apply/damage", -lvl);
  damage1 = (me->query("neili")- victim->query("neili"))* me->query("max_qi")/me->query("eff_qi");
           if(damage1<0 ) damage1 = - damage1/(2* (random(focus)+1));
             else damage1=damage1*( random(focus)+2);
           if(!userp(me))   damage1 =damage1/3;
           if( wizardp(me)) 
                    tell_object(me, "参考数值"+damage1+"。\n"NOR);
          
                                 victim->receive_damage("qi", damage1 , me);
                                 victim->receive_wound("qi", damage1/3 , me);
                                 me->add("neili",-1000); 
                                 me->add("jingli", -50);

            victim->delete_temp("must_be_hit");
            return 1;
}
 
mixed hit_ob(object me, object victim, int damage)
{
 object weapon, weapon1;
 int ap, dp, focus, damage1,lvl;
 string msg;
 focus = me->query_temp("ss/focus");
        lvl = me->query_skill("songshan-jian",1);       
  if (me->query_temp("ssj/leiting"))
 {
          damage1 = (me->query("neili")- victim->query("neili"))* me->query("max_qi")/me->query("eff_qi");
        
          if(damage1<0 ) damage1 = - damage1/ (random(focus)+1);
                    else damage1 =   damage1*( random(focus)+2);
          if( wizardp(me)) 
                    tell_object(me, "参考数值"+damage1+"。\n"NOR);
          if(!userp(me)) damage1 = damage1/3;
                                 victim->receive_damage("qi", damage1 , me);
                                 victim->receive_wound("qi", damage1/3 , me);
                                 me->add("neili",-1000); 
                                 me->add("jingli", -50);
                msg = HIR"这招「"HIW"雷霆一击"HIR"」凝聚了$N毕生内力，威力无比，挡无可挡，$n只觉一股大力撞来，立时口中鲜血狂喷而出！\n"NOR;
    
                message_vision(msg, me, victim);
                me->delete_temp("ssj/leiting");
                me->set_temp("strike_hit",1);
 }
 //寒冰辅助判断
 if (me->query_temp("ss/hb") && !victim->is_busy()&&!random(3))
 {
     victim->apply_condition("cold_poison", random(focus)+ 1);
     if ( !random(4))
        victim->add("neili",-me->query_skill("force")/2);
     if (victim->query("neili") < 0) victim->set("neili",0);
    
	 msg = HIW"$n被$N这一剑砍伤，一阵寒气传来，似乎全身的血液即将冻结一般！\n"NOR;
	 
     if( !me->query_temp("ssj/db_hit")) message_vision(msg, me, victim);
   }
   if (random(me->query_skill("songshan-jian",1) < 350)) return 0;
      
	   weapon=me->query_temp("weapon");
       weapon1=victim->query_temp("weapon");

   if( lvl >= 450 
		 && !random(3)
		 && me->query("quest/ss/ssjf/jueji/pass")  //华山石壁开放
         && random(me->query_con()) > victim->query_con()/3
         && random(me->query_skill("sword",1)) > victim->query_skill("parry",1)/3 
         || me->query_temp("ss/fw")
		 || me->query_temp("ssj/zhbh")
         || me->query_temp("ss_lf") )
                         {
                if( me->query_skill_prepared("strike") == "hanbing-shenzhang"
                 && me->query_skill_mapped("strike") == "hanbing-shenzhang"
                 && me->query_skill_mapped("parry") == "songshan-jian"
                 && me->query_skill_mapped("force") == "hanbing-zhenqi"
                 && me->query_skill("hanbing-shenzhang", 1) >= 450 
				 && random(10)>7 
				 && !me->query_temp("ssj/db_hit") ) {
 message_vision(HIW"突然间寒光一闪，$N手中"+weapon->query("name")+ HIW"一剑从$n左肩直劈到右腰，跟着横向一拉，剑光带过，
这两剑势道之凌厉，端的是匪夷所思，只是闪电般一亮，$n若是闪避不开，势必被斩成四截！"NOR, me,victim);
                        me->set_temp("ssj/db_hit",1);
                        me->add_temp("apply/attack",  me->query_skill("songshan-jian", 1)/3);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
                        me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/3);
                        me->delete_temp("ssj/db_hit");
                       }
        }
     if(objectp(weapon) 
        && objectp(weapon1)
        && me->query("env/嵩山剑法") == "削") {
        ap = me->query("combat_exp")/ 1000 * me->query("str");
        dp = victim->query("combat_exp")/ 1000 * victim->query("str");
     if( random(ap + dp) > dp && weapon1->query("imbued") < 3 && weapon->query("sharpness") > 0) {
        message_vision(CYN"$N潜运内劲，只听见「唰」地一声轻响，$n手中的"+weapon1->name()+CYN"已经被"+weapon->name()+CYN"击断！\n"NOR, me, victim );
        weapon1->broken("削断的");
        return 0;
       }
     else if ( weapon->query("sharpness") > 0) {
    ap = me->query("combat_exp")/ 1000 * (me->query_str(1)+ me->query("jiali")+ me->query_skill("parry")/3);
    dp = victim->query("combat_exp")/ 1000* (victim->query_str(1)+ victim->query("jiali")+ victim->query_skill("parry")/3);
   if (random(ap+ dp) > dp) {
    message_vision(CYN "$N回剑疾撩，$n把捏不住，手中的"+weapon1->name()+CYN"直飞上天！\n"NOR, me, victim );
    victim->add_busy(random(2)+1);
    weapon1->move(environment(victim));
    victim->reset_action();
   }
  }
 }
 return 0;
}
string perform_action_file(string action)
{
 return __DIR__"songshan-jian/" + action;
}

