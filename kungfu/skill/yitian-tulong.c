#include <ansi.h>
inherit SKILL;

mapping *action= ({
([      "action" : "$N�������飬������磬$w�������������һ��������б��$n",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "����",
      //  "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)
]),
([      "action" : "$N������������»����������磬$wһת������$n��$l�����¿���֮�ʣ���Ʈ��������",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "����"
]),
([      "action" : "$N��������̤�ϣ��������֣�����ʵʵ�������Ϲ�â��˸�������͵ķ�����΢����",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "����"
]),
([      "action" : "$Nٿ��Ծ�𣬷�����ǰ��$wһ��һ�ӣ�ȴ�ǡ��졹�־���һƲ",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "����"
]),
([      "action" : "$N$wһ��ʹһ�С�˭���־������������Ҳ�����ʱ����绯Ϊ��ǧ�����⣬��ס$n����",
        "force" : 170,
        "dodge" : 0,
        "parry" : 20,
        "damage" : 90,
        "damage_type" : "����"
]),
([      "action" : "$Nת��������$w�ͳ���ȴ�ǡ��¡��־���һֱ������$n��$l",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "����"
]),
([      "action" : "ͻȻ��$N$wʹ�С������־��е�һ�����͵�һ�죬����$n$l",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "����"
]),
([      "action" : "$N˫��һ�㣬�������࣬ʹ��һ�С������־��е�һ��ֱ������$w�ڰ���м�������",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "����"
]),
([      "action" : "$N����$w����ʯ��������������$n��̨Ѩһ·˳��ֱ�£�ʹ���ǡ��桹�־�������һ��һֱ�������鷨�еĲ��ʣ������ǻ�����ţ��",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "����"

]),
([      "action":"$N���Ƽ�̽����ָ��ץ�����������������$n��$l",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$N�����ĳ������ƶ����κ���������������б�����ִ�������������",
        "force" : 180,
        "dodge" : 40,
        "parry" : 20,
        "damage": 90,
        "lvl" : 112,
        "damage_type":  "����"
]),
([      "action":"$Nһ�����ֲ������������ף�������������ƽƽ��ɨ������$n��̫��Ѩ",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$Nٿ��Ծ�𣬷�����ǰ������һ��һ�ӣ�ȴ�ǡ��졹�־���һƲ",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$N����һ�䣬˫�Ʒ��裬��������ѩ������಻���������õ����ǡ�Ī���־�",
        "force" : 200,
        "dodge" : 0,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "����"
]),
([      "action":"$Nת����������ȭ�ͳ���ȴ�ǡ��¡��־���һֱ���ĵ�һ��������$n��$l",
        "force" : 220,
        "dodge" : 30,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "����"
]),
([      "action":"$N�����㣬�������磬�������ٿ����ʹһ���������־��е�һ��������$n",
        "force" : 240,
        "dodge" : 80,
        "parry" : 20,
        "damage": 120,
        "damage_type":  "����",
	  //  "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)

]),
([      "action":"$N˫��һ�㣬�������࣬ʹ��һ�С������־��е�һ��ֱ���������ڰ���м�������",
        "force" : 260,
        "dodge" : 10,
        "parry" : 20,
        "damage": 100,
        "weapon": "����",
        "damage_type":  "����"
]),
([      "action":"$N��Хһ��������ֱ���������������ǽ���â����ʸӦ��������Ͼ�����粻���ɣ���һֱ���ǡ��桹�ֵ�����һ��",
        "force" : 200,
        "dodge" : 40,
        "parry" : 20,
        "damage": 100,
        "weapon": "����",
        "damage_type":  "����"

])
});
int valid_enable(string usage) {
	if (this_player()->query("quest/yttlg/pass"))
		return usage == "sword" || usage == "parry"|| usage == "brush";
}

int valid_learn(object me)
{
        if( me->query_skill("yitian-tulong", 1) < 100 )
                return notify_fail("���������������δ�ڻ��ͨ,����������ϰ��\n");
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
                                        "weapon" : random(2)?"����":"����",
                                        "damage_type" : random(2)?"����":"����",
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
                                        "weapon" : random(2)?"����":"����",
                                        "damage_type" : random(2)?"����":"����",
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
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("�����������������������\n");
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
    //���ϲ����йٱ���Ч��
	if (objectp(target)||!me->is_fighting()) return;

	if (!objectp(weapon2)||!objectp(weapon1)) return ;
   
	i= me->query_skill("yitian-tulong",1)+me->query_skill("brush",1)+me->query_skill("art",1);
    
	me->add_temp("apply/attack", i/3);
   
	if(objectp(target)&& random(8) > 6 && i > 350 )
     {
       message_vision(HIW"$N������������»����������磬"+weapon1->query("name")+HIW"һת������$n�ļ�����硰�족�ֵ�һ��.\n"NOR,me,target);
       message_vision(HIC"$N����"+weapon2->query("name")+HIW"˳��һ��������$n���������Ѩ�����硰�����ֵ�һƲ.\n"NOR,me,target);

       me->set_temp("yttl",1);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	   me->delete_temp("yttl");
	   
     }
    else if( objectp(target)&&weapon2 && !random(3)){                      
	   message_vision(MAG"$N��Ȼ�ó�һ��"+weapon2->query("name")+MAG"���󲦵�$n����ʽ��˳�Ƶ���$n�Ĺ�ԪѨ����ʽ�پ������ǡ��С�����һƲ��\n"NOR,me,target);
       message_vision(HIY"$nһ��С��Ϊ���е������Ѩ�������ζ�ʱ���ơ�\n"NOR,me,target);
	   target->add_busy(2+random(3));
       //me->set_temp("yttl",1); 
       //COMBAT_D->do_attack(me, target,weapon2, userp(me)?3:1);
	   //me->delete_temp("yttl");
	  
	  }
	else if (objectp(target)&&weapon1->query("style")=="sword"&&!random(5))
	  {
	   message_vision(HIG"$N��$næ�ң�����"+weapon1->query("name")+HIG"�������ɷ����Ĵ󿪴�ϣ����ǡ������ֵ����һ�ʣ�"NOR,me,target);
       message_vision(HIY"$nû��ʶ��Σ�գ�Ϊ$Nһ���̴���$n�����ߣ���Ѫ���ܡ�\n"NOR,me,target);
	   target->receive_damage("qi",i*3,me);
	   target->receive_wound("qi",i/2,me);
       me->set_temp("yttl",1);
	   COMBAT_D->do_attack(me, target,me->query_temp("weapon"), userp(me)?3:1);
	   me->delete_temp("yttl");
	  }
	  me->add_temp("apply/attack", -i/3);
	  return ;
}