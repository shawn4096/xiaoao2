#include <ansi.h>
inherit SKILL;

mapping *action= ({
([      "action" : "$N剑走轻灵，光闪如虹，$w疾点而出，当的一声，剑尖斜砸$n",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "刺伤",
      //  "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)
]),
([      "action" : "$N跟着纵起，凌空下击，捷若御风，$w一转，点向$n的$l，吞吐开阖之际，又飘逸又凝重",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "刺伤"
]),
([      "action" : "$N当下左足踏上，剑交左手，虚虚实实，剑尖上光芒闪烁，嗤嗤嗤的发出轻微响声",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "刺伤"
]),
([      "action" : "$N倏的跃起，飞身而前，$w一挥一掠，却是「天」字诀的一撇",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "割伤"
]),
([      "action" : "$N$w一起，使一招「谁」字诀，但见剑尖乱颤，霎时间便如化为数千个剑尖，罩住$n中盘",
        "force" : 170,
        "dodge" : 0,
        "parry" : 20,
        "damage" : 90,
        "damage_type" : "刺伤"
]),
([      "action" : "$N转身吐气，$w送出，却是「下」字诀的一直，刺向$n的$l",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "刺伤"
]),
([      "action" : "突然间$N$w使招「龙」字诀中的一钩，嗤的一响，划向$n$l",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "割伤"
]),
([      "action" : "$N双足一点，纵起丈余，使出一招「争」字诀中的一下直钩，将$w在半空中疾挥下来",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "割伤"
]),
([      "action" : "$N右手$w电光火石般连连颤动，自$n灵台穴一路顺势直下，使的是「锋」字诀中最後一笔一直，便如书法中的颤笔，疾如星火，气吞牛",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "刺伤"

]),
([      "action":"$N右掌疾探，回指反抓，左足飞起，正好踢向$n的$l",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "瘀伤"
]),
([      "action":"$N左掌拍出，右掌陡地后发先至，跟着左掌斜穿，又从後面抢了上来",
        "force" : 180,
        "dodge" : 40,
        "parry" : 20,
        "damage": 90,
        "lvl" : 112,
        "damage_type":  "瘀伤"
]),
([      "action":"$N一个左拗步、抢到了西首，右掌自左向右平平横扫，打向$n的太阳穴",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "瘀伤"
]),
([      "action":"$N倏的跃起，飞身而前，左手一挥一掠，却是「天」字诀的一撇",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "擦伤"
]),
([      "action":"$N招数一变，双掌飞舞，有若絮飞雪扬，软绵绵不着力气，用的正是「莫」字诀",
        "force" : 200,
        "dodge" : 0,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "内伤"
]),
([      "action":"$N转身吐气，左拳送出，却是「下」字诀的一直，拍的一声，击向$n的$l",
        "force" : 220,
        "dodge" : 30,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "瘀伤"
]),
([      "action":"$N神定气足，挥洒自如，蓦地右手倏出，使一个「龙」字诀中的一钩，刺向$n",
        "force" : 240,
        "dodge" : 80,
        "parry" : 20,
        "damage": 120,
        "damage_type":  "刺伤",
	  //  "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)

]),
([      "action":"$N双足一点，纵起丈余，使出一招「争」字诀中的一下直钩，右手在半空中疾挥下来",
        "force" : 260,
        "dodge" : 10,
        "parry" : 20,
        "damage": 100,
        "weapon": "右手",
        "damage_type":  "割伤"
]),
([      "action":"$N长啸一声，右掌直划下来，当真是星剑光芒，如矢应机，霆不暇发，电不及飞，这一直乃是「锋」字的最後一笔",
        "force" : 200,
        "dodge" : 40,
        "parry" : 20,
        "damage": 100,
        "weapon": "右掌",
        "damage_type":  "割伤"

])
});
int valid_enable(string usage) {
	if (this_player()->query("quest/yttlg/pass"))
		return usage == "sword" || usage == "parry"|| usage == "brush";
}

int valid_learn(object me)
{
        if( me->query_skill("yitian-tulong", 1) < 100 )
                return notify_fail("你的倚天屠龙功还未融会贯通,不能自行练习。\n");
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
        int i, j, level,lv2;
		level = me->query_skill("yitian-tulong",1);
        lv2 = me->query_skill("sword", 1)/2;
        weapon->query_temp("weapon");
               for(i = sizeof(action); i > 0; i--){
                 if(level > action[i-1]["lvl"]){
                        j = NewRandom(i, 20, level/5);

                        if( me->query_temp("yttl")){
                                return ([  
                                        "action":HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
                                        "lvl" : action[j]["lvl"],
                                        "force" : 120 + random(250) + lv2/10,
                                        "dodge": random(20)- 5 +lv2/15,
                                        "damage": 160 + random(80) ,
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"剑气":"剑锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
						
                        if( me->query_temp("yttlg/tulong")){
                                return ([  
                                        "action":MAG+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG), NOR, MAG)+NOR,
                                        "lvl" : action[j]["lvl"],
                                         "force" : 120,
                                        "dodge": 20,
                                        "damage": 170 + random(100),
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"剑气":"剑锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
                        return ([
                                "action": action[j]["action"],
                                "force" : 100 +random(250),
                                "dodge": random(20)-10,
                                "parry": random(10),
                                "damage": 80 +random(80),
                                "lvl": action[j]["lvl"],
                                "damage_type": action[j]["damage_type"],
                                ]);
                       
                   }
           }
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || ((string)weapon->query("skill_type") != "sword" && (string)weapon->query("skill_type") != "brush" ))
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力不够练倚天屠龙。\n");
        me->receive_damage("jingli", 20);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yitian-tulong/" + action;
}

mixed hit_ob(object me, object target)
{
    int i;
   	object weapon1,weapon2;
	weapon1=me->query_temp("weapon");
	weapon2=present("brush",me);
    //身上不带判官笔无效；
	if (objectp(target)||!me->is_fighting()) return;

	if (!objectp(weapon2)||!objectp(weapon1)) return ;
   
	i= me->query_skill("yitian-tulong",1)+me->query_skill("brush",1)+me->query_skill("art",1);
    
	me->add_temp("apply/attack", i/3);
   
	if(objectp(target)&& random(8) > 6 && i > 350 )
     {
       message_vision(HIW"$N跟着纵起，凌空下击，捷若御风，"+weapon1->query("name")+HIW"一转，刺向$n的肩膀，宛如“天”字的一横.\n"NOR,me,target);
       message_vision(HIC"$N左手"+weapon2->query("name")+HIW"顺势一戳，点向$n的任脉诸大穴，宛如“不”字的一撇.\n"NOR,me,target);

       me->set_temp("yttl",1);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	   me->delete_temp("yttl");
	   
     }
    else if( objectp(target)&&weapon2 && !random(3)){                      
	   message_vision(MAG"$N忽然拿出一把"+weapon2->query("name")+MAG"向左拨挡$n的招式，顺势点向$n的关元穴，笔式遒劲，正是“倚”字中一撇。\n"NOR,me,target);
       message_vision(HIY"$n一不小心为这招点中左臂穴道，身形顿时受制。\n"NOR,me,target);
	   target->add_busy(2+random(3));
       //me->set_temp("yttl",1); 
       //COMBAT_D->do_attack(me, target,weapon2, userp(me)?3:1);
	   //me->delete_temp("yttl");
	  
	  }
	else if (objectp(target)&&weapon1->query("style")=="sword"&&!random(5))
	  {
	   message_vision(HIG"$N趁$n忙乱，右手"+weapon1->query("name")+HIG"宛如龙飞凤舞般的大开大合，正是“龙”字的最后一笔！"NOR,me,target);
       message_vision(HIY"$n没意识到危险，为$N一剑刺穿了$n的左肋，鲜血淋淋。\n"NOR,me,target);
	   target->receive_damage("qi",i*3,me);
	   target->receive_wound("qi",i/2,me);
       me->set_temp("yttl",1);
	   COMBAT_D->do_attack(me, target,me->query_temp("weapon"), userp(me)?3:1);
	   me->delete_temp("yttl");
	  }
	  me->add_temp("apply/attack", -i/3);
	  return ;
}
