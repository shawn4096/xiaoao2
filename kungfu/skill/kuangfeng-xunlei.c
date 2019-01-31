//kuangfeng-xunlei.c ���Ѹ�׹�  Դ�Ի���
//������ս��ʤׯ
//���Ů�����||������·ͼ�似
//��Ϊ���ڹ���

#include <ansi.h>

inherit SKILL;
//������ʽ
mapping *action = ({
([      "action" : "$N����Ծ������$w��ӣ�ն��$n��",
        "force"  : 160,
        "attack" : 35,
        "parry"  : 40,
        "dodge"  : 80,
        "damage" : 125,
        "lvl"    : 0,
        "skill_name" : "��ƽ�˾�",
        "damage_type" : "����"
]),
([      "action" : "$N����$w�����������Σ���$n���ұ����ն��",
        "force"  : 180,
        "attack" : 55,
        "parry"  : 52,
        "dodge"  : 95,
        "damage" : 148,
        "lvl"    : 30,
        "skill_name" : "������ӿ",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����ˢˢˢˢ������������$n�أ������������Ĵ�����",
        "force"  : 220,
        "attack" : 81,
        "parry"  : 18,
        "dodge"  : 123,
        "damage" : 195,
        "lvl"    : 60,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����Х��б����ǰ��$w����ֱ����Ѹ���ޱȣ�����$n��$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 200,
        "lvl"    : 90,
        "skill_name" : "������ɢ",
        "damage_type" : "����"
]),
([      "action" : "$Nһ��ִ$w������һ��ԲȦ��˳�ƺ��������ֳ�$n�ֵ������¶��ϣ�һ��Ҹ�·�������$n��$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 220,
        "lvl"    : 90,
        "skill_name" : "������ɢ",
        "damage_type" : "����"
]),
});
//��������ʽ���ַ�
mapping *action_hand = ({
([      "action" : "$N����Ծ��,˫�ֻ���һƬ��Ӱ�������ó����У�����$n�󾱡�ǰ�ء���������Ѩλ",
        "force"  : 160,
        "attack" : 35,
        "parry"  : 40,
        "dodge"  : 80,
        "damage" : 125,
        "lvl"    : 0,
        "skill_name" : "��籩��",
        "damage_type" : "����"
]),
([      "action" : "$N����бб���ϣ��ʰ뻡״������ȥ���γ������Ļ��Σ���$n���ұ������ȥ",
        "force"  : 180,
        "attack" : 55,
        "parry"  : 52,
        "dodge"  : 95,
        "damage" : 148,
        "lvl"    : 30,
        "skill_name" : "���紵",
        "damage_type" : "����"
]),
([      "action" : "$N����һ�������ζ�ת��ר��$n�ı��������ָ������$n�أ������������Ĵ���Ѩ",
        "force"  : 220,
        "attack" : 81,
        "parry"  : 18,
        "dodge"  : 123,
        "damage" : 195,
        "lvl"    : 60,
        "skill_name" : "�ƾ�����",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����Х��б����ǰ�����ֺ���ֱ����Ѹ���ޱȣ����ֻ���ָ����ʽ����$n��$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 200,
        "lvl"    : 90,
        "skill_name" : "������ɢ",
        "damage_type" : "����"
]),
([      "action" : "$N���ο��ټ��ߣ�Χ��$n����ת��һȦ����������$n�ĺ��ģ�һ�мȳ���������������Ѹ���ޱ�",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 230,
        "lvl"    : 90,
        "skill_name" : "���Ѹ��",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "brush" || usage == "parry"|| usage == "hand"; } 

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 200)
                return notify_fail("������������Ϊ����100�����޷���ϰ���Ѹ�׹���\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("��Ļ����Ṧ�����100�����޷���ϰ���Ѹ�׹���\n");

        if ((int)me->query_dex() < 60)
                return notify_fail("��ĺ�����������60���޷���ϰ���Ѹ�׹���\n");
        if ((int)me->query_skill("hand",1) < 20)
                return notify_fail("��Ļ����ַ�����20���޷������Ѹ�׹���\n");
		if ((int)me->query_skill("brush",1) < 20)
                return notify_fail("��Ļ����ʷ�����20���޷������Ѹ�׹���\n");
        if ((int)me->query_skill("brush", 1) < (int)me->query_skill("kuangfeng-xunlei", 1))
	        return notify_fail("��Ļ����ʷ�ˮƽ���ޣ��޷���������Ŀ��Ѹ�׹���\n");
        
		if ((int)me->query_skill("hand", 1) < (int)me->query_skill("kuangfeng-xunlei", 1))
	        return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������Ŀ��Ѹ�׹���\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        if (!this_player()->query_temp("weapon"))
        {
			for (i = sizeof(action_hand) - 1; i >= 0; i--)
                if (level >= action_hand[i]["lvl"])
                        return action_hand[i]["skill_name"];
        }
		else {
			for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
		}
}

mapping query_action(object me, object weapon)
{
        int i, j,level;

		weapon=me->query_temp("weapon");
        
		level = (int) me->query_skill("kuangfeng-xunlei",1);
		if (this_player()->query_temp("weapon"))
		{
			if (me->query_temp("kfxl/kfjg"))
			{
				for (i = sizeof(action); i > 0; i--)
				{
					if (level > action[i - 1]["lvl"])
					{
						j = NewRandom(i, 20, level/5);
						return([  							
							"action" :MAG+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,							
							"force" : action[j]["force"],
							"dodge": action[j]["dodge"],
							"damage": action[j]["damage"],
							"parry": action[j]["parry"],
							"attack" : action[j]["attack"],
							"lvl" : action[j]["lvl"],
							"skill_name" : action[j]["skill_name"],
							"damage_type" : random(2)?"����":"����",/**/
						]);
					}
				}
			}
			for (i = sizeof(action); i > 0; i--)
    	        if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
		}
		else {
			for (i = sizeof(action); i > 0; i--)
    	        if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

		}
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "brush")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 65)
                return notify_fail("����������������Ѹ�׹���\n");

        if ((int)me->query("neili") < 40)
                return notify_fail("����������������Ѹ�׹���\n");
        if ((int)me->query_skill("force",1) < 20)
                return notify_fail("��Ļ����ڹ�����20���޷������Ѹ�׹���\n");

        me->receive_damage("qi", 60);
        me->add("neili", -36);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kuangfeng-xunlei/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
	
        if (random(10) > 7
			&&me->query_temp("kfxl/xlg")) 
        {
			switch (random(3))
			{
				case 0:
					message_vision(MAG"$N��Ȼһ����ǣ��������ը�ף���ʱ$n��Щ����Ŀѣ֮�У�\n"NOR,me,victim);
					victim->receive_damage("jing",200+random(400),me);
					victim->receive_wound("jing",100+random(200),me);
					break;
				case 1:
					message_vision(HIY"$N������ϣ����ֱ�����������������ָ�㡢�����أ�����$n�ġ���������Ѩ��$n��Ѫһ��!\n"NOR,me,victim);
					victim->add_busy(1);
					victim->apply_condition("no_exert",1);
					break;
				case 2:
					message_vision(HIR"$N�����Ц�������������˵��һͨ����·���������һ�㣡ʹ��$n��������Ӱ�죡\n"NOR,me,victim);
					if (victim->query("jingli")<1200) victim->set("jingli",0);
					
					victim->receive_damage("jingli",1000+random(200),me);
					break;
			}
        	
        }
}

