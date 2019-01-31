// lingbo-weibu.c �貨΢��
// Modify By River@SJ 2000.3.1
// By Spiderii@ty ����
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$n����һ�����ģ���������б���벽��ǡ�������貨΢���С��������塹�Ĳ��ӣ����˿�����\n" ,
        "dodge"  : 120
]),
([      "action" : "$nʹ���������ѩ������бб���˼������ƺ������·���ȴ�ڼ䲻�ݻ��Ŀ�϶�ж����$N�Ĺ��ơ�\n",
        "dodge"  : 100
]),
([      "action" : "$N����ʽ�������԰�$nΧס����֪���ģ�$nһʽ�����Ʊ��¡���������Ȱ�Ŀ����Ȧ��\n",
        "dodge"  : 150
]),
([      "action" : "$nһʽ���������ҡ���հ֮��ǰ�������ں�$N��ʽ������$n���Ӽ��������֮�\n",
        "dodge"  : 180
]),
([      "action" : "$n����������ͻȻת��ʹ���ˡ������ϡ���$N�ӽ����ƣ����޷�����$nһƬ�½ǡ�\n",
        "dodge"  : 130
]),
([      "action" : "$n���һ����ʹ����է������������������̤��������̤ʵ֮ʱ�����������������ϡ�\n",
        "dodge"  : 210
]),
([      "action" : "$nһʽ��Ʈ�����񡹣�����б�����������ȼá���������δ�á������ü��������۵�$N�����\n",
        "dodge"  : 230
]),
([      "action" : "$nһʽ����Ѹ���ɡ����ƺ��Թ��Ե�̤����������ᣬÿһ����̤�ڱ������벻�������ڡ�\n",
        "dodge"  : 130
])
});

mapping query_action(object me,object weaoib)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("lingbo-weibu");

        if (level < 80 )
                zhaoshu--;

        if (level < 60 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
//        if(this_player()->query("quest/dali/shanlu") && this_player()->query("quest/dali/pass"))
//�޸ı�־
        if(this_player()->query("quest/�����˲�/�书/yuxiang") 
			&& this_player()->query("quest/�����˲�/�书/pass") 
			|| this_player()->query("quest/xiaoyao/pass")
			|| (this_player()->query("family/family_name")=="��ң��"))
		return usage == "dodge";
}

int valid_learn(object me)
{
//ת����־
        if ( !me->query("quest/�����˲�/�书/yuxiang") && !me->query("quest/xiaoyao/pass") && me->query("family/family_name")!="��ң��")
             return notify_fail("��û�п�ͷ��������ô��͵ѧ�貨΢����\n");
        if ( !me->query("quest/�����˲�/�书/pass") && (me->query("family/family_name")!="��ң��"))
             return notify_fail("��û�гɹ��о�����ô��͵ѧ�貨΢����\n");
        if ((int)me->query_skill("literate", 1) < 300)
             return notify_fail("���֪ʶ����300���޷�����貨΢����\n");
        if (me->query("gender")=="����")
             return notify_fail("�������������޷�����貨΢����\n");
        if (me->query_dex()<20)
             return notify_fail("�������������20���޷�����貨΢����\n");

		if ((int)me->query_int(1) < 50)
             return notify_fail("������Բ���50���޷�����貨΢����\n");
        if (me->query_skill("lingbo-weibu",1) < 180) 
             return notify_fail("����貨΢����û�дﵽ����������ϰ�ĵز���\n");
		return 1;
}
/*
string query_dodge_msg(object me,object weapon)
{
        mapping action;

        action = query_action(me);

        return action["action"];
}
*/
void skill_improved(object me)
{
	if(me->query_skill("lingbo-weibu",1) >= 80
	 && !me->query("lbwb")
	 && me->query_skill("literate",1) > 80){
		tell_object(me, HIY"\n�㰴�ղ�������������һ������������ֻ���������泩����֪���������������ۡ�\n"NOR);
		me->add("max_neili", random(80)+80);
		me->add("lbwb",1);
	}
	if(me->query_skill("lingbo-weibu",1) >= 120
	 && me->query("lbwb") == 1 
	 && me->query_skill("literate",1) > 100){
		tell_object(me, HIM"\n����ʮ�������꣬�պ�����һ����Ȧ���ص�ԭ�أ��������\n"NOR);
		me->add("max_neili", random(80)+100);
		me->add("lbwb",1);
	}
	if(me->query_skill("lingbo-weibu",1) >= 160
	 && me->query("lbwb")==2 
	 && me->query_skill("literate",1) > 120){
		tell_object(me, CYN"\n��Խ��Խ�죬��Ϣ���Ų�����ס��ת������Ȼ�Լ��������Ѿ�������ߣ�\n"NOR);
		me->add("max_neili", random(80)+120);
		me->add("lbwb",1);
	}
	if(me->query_skill("lingbo-weibu",1) >= 200
	 && me->query("lbwb")==3 
	 && me->query_skill("literate",1) > 140){
		tell_object(me,RED"\n�㲽����죬����̤�����Ų���Բ��ֻ��������ˬ��ȫ����������\n"NOR);
		me->add("max_jingli", random(140)+140);
		me->add("lbwb",1);
	}
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}


int practice_skill(object me)
{
        if ( !me->query("quest/�����˲�/�书/pass") && (me->query("family/family_name")!="��ң��"))
             return notify_fail("����ô��͵ѧ�貨΢����\n");
        
	if( (int)me->query_skill("lingbo-weibu",1) < 40 )
		return notify_fail("����貨΢������δ�죬�޷�����������\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("���������Ϊ̫�ǿ���貨΢��ֻ���߻���ħ��\n");

        if( (int)me->query("jingli") < 40 )
                return notify_fail("�������̫���ˣ��������貨΢����\n");
        if( (int)me->query("jing") < 25 )
                return notify_fail("�������̫���ˣ��������貨΢����\n");
        if( (int)me->query("qi") < 20 )
                return notify_fail("�������̫���ˣ��������貨΢����\n");
        if( (int)me->query("neili") < 20 )
		return notify_fail("�������̫���ˣ��������貨΢����\n");

	me->receive_damage("jing", 15, "�����߻���ħ");
	me->receive_damage("jingli", 35);
	me->receive_damage("qi", 10, "�����߻���ħ");
	me->receive_damage("neili", 10);
	return 1;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int skill, neili, neili1;
	int j = 0;
	skill = me->query_skill("lingbo-weibu", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if (!me->query_temp("lbwb/ls")) return 0;
	
	if(damage>1000 && me->query_temp("lingbo-weibu")){
		me->delete_temp("lingbo-weibu");
		switch(random(3)){
			case 0:
				tell_object(ob, HIR "��ֻ����ǰһ���������˶��ֵ���Ӱ��հ֮��ǰ�������ں�\n" NOR);
				break;
			case 1:
				tell_object(ob, HIC "���κ�����ң���㱲������ƺ����μ���׽����\n" NOR);
				break;
			case 2:
				tell_object(ob, HIW "����֮�ʣ���Ȼһ��ԭ��תȦ������Ӳ����ƾ�հ��𣬷�����У�\n" NOR);
				break;
		}
		//tell_object(ob, HIW "�����\n" NOR);
		if (me->is_busy())
		{
			message_vision(HIW "$N�������㣬���ݺ��裬շת������$n�����ǣ��˲��ʧЧ��\n" NOR,me,ob);
			me->start_busy(-1);
		}
		return -damage ;
	}

	if(random(skill)> ob->query_skill("dodge", 1)/3
	 || me->query("combat_exp") > ob->query("combat_exp")/3	 
	 && me->query_skill_mapped("dodge") == "lingbo-weibu"
	 && me->query("env/�貨΢��")=="����"
	 && neili > 400
	 && skill > 80 ) {
		me->add_temp("lingbo-weibu", 1);
		
		msg =random(2)? HIW + action[random(sizeof(action))]["action"]+NOR :
				HIC + action[random(sizeof(action))]["action"]+NOR ; 
		

		if(neili >= neili1/3){
			msg += "���$N���������㿪�ˣ�\n", 
			//j = -(damage*2+skill*3);
			j=-damage;
		}
		else if(neili > neili1+damage){
			msg += "���$N�������������һ�룡\n", 
			j=-damage/2;               
		}
		else {
			msg += "���$nֻ�����$N��һС��������\n", 
			j = -(damage/2+random(damage/2)); 
		}
		message_vision(msg, ob, me);
		return j;
	
	
	}
	return j;   
}

