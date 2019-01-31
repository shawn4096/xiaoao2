// bihai-chaosheng.c
#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) {
	if (this_player()->query("family/family_name")!="�һ���")
	{
		return notify_fail("�̺����������һ���������а���ش��ķ���û�еõ����Ĵ��ڣ��޷�ʹ��!\n");
	} 
	return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ���������������������ı̺������񹦡�\n");
	if (this_player()->query("family/family_name")!="�һ���")
	{
		return notify_fail("�̺����������һ���������а���ش��ķ���û�еõ����Ĵ��ڣ��޷�ʹ��!\n");
	} 
	if ((int)me->query_skill("bihai-chaosheng", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bihai-chaosheng", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
	if ((int)me->query_skill("bihai-chaosheng", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bihai-chaosheng", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("bihai-chaosheng", 1) >= 200 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("bihai-chaosheng", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������̺߱��������ˡ�\n");
	}
	else return notify_fail("�����ڵı̺���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return SKILL_D("bihai-chaosheng/") + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name() + "�������£�������Ԩ��������������" NOR,
		"start_my_msg" : "���������£�˫Ŀ΢�գ�˫���������������̫�������˺�һ���������顣\n",
		"start_other_msg" : me->name() + "�������£�˫Ŀ΢�գ�˫���������������̫������紵����" + me->name() + "���ϵ����۾�Ȼ��Ϊ������\n",
		"end_my_msg" : "�㽫��Ϣ������һ��С���죬�������뵤�˫��һ��վ��������\n",
		"end_other_msg" : me->name() + "�����Ϻ��է�֣���������ȥ���漴˫��һ��վ��������\n",
		"heal_msg" : HIC"$N����������Ϣ������������ȫ�����ߣ�ǡ�Ʊ̺����ΰ������𱻷⾭����\n"NOR,
		"heal_finish_msg" : HIC"$N��ɫ��������滺����������֮��תֱ�£��������š�\n"NOR,
		"heal_unfinish_msg" : HIR"$N��Ϣ΢��������Ϊ�ã�����ļȻ�߿�������ʧ������֮վ���͵��³�һ����Ѫ��\n"NOR,
		"heal_halt_msg" : HIC"$Nͻ�������ʣ���ϢȫȻ��������ָ������æֹͣ���࣬������Ȼ��ֹ��\n"NOR,
	]);
}

mixed hit_ob(object me, object ob, int damage)
{
	//�߶�Ч��
	//����Ч��
	//�����˾�Ч��

	int lvl,num,dam;
	object weapon,tweapon;
	string msg;
	if (!me) return;
	weapon=me->query_temp("weapon");
	tweapon=ob->query_temp("weapon");
	
	lvl=me->query("bihai-chaosheng",1);
	num=ob->query_temp("thd/fugu");
	dam=lvl+me->query_skill("qimen-bagua",1);
	dam=dam+random(dam);
	//�ڹ��ںϺ󿪷�
	if (me->query("thdjj/ronghe")!="pass") return;
	
	if (random(10)>7
		&& objectp(ob)
		&& me->is_fighting())
	{
		switch (random(3))
		{
	 	   case 0: //����
		
				if(!ob->is_busy() || !ob->query_temp("thd/maze")) {

					message_vision(HIY"$N�ۼ�$n�������Լ������õ�����������˳�ּ��𼸿�שͷ����֦���²����˸�С������!\n"+
						"�γɴ�������Ƕ��С�����Ч���������½�$n��������֮�У�\n"NOR,me,ob);
					ob->add_busy(2);
				
					ob->add("jingli",-dam);
				}

			 	break;
			case 1: //�߶�
				if (weapon
					&& weapon->query("id")=="xiao"
					&& ob->query_temp("thd/fugu")
					&&me->query("env/�̺�����")=="�߶�")
				{
					message_vision(HBCYN"$N�ۼ�$nӦ�Ӳ�Ͼ���û������е�"+weapon->query("name")+HBCYN"������ߣ����Ĵ���!\n"+
					"$n�����Լ����ϲ������Ϊ$N���������µġ�"HIB+"���Ƕ�"+HBCYN"�����˿�ʼ������ʹ����ǣ�\n"NOR,me,ob);
					ob->receive_wound("qi",random(lvl)*num,me);
					if (!ob->query_condition("fugu_poison"))
						ob->apply_condition("fugu_poison",num);
					message_vision(HIB"$N�о��������Ҵܣ���Ѫ��ӿ����Ϊʹ����\n"NOR,ob);
					ob->add("neili",-damage);
				}
				break;
			case 2://play 
				if (weapon
					&& weapon->query("id")=="xiao"
					&& me->query("env/�̺�������"))
				{
					message_vision(HBMAG+HIW"$N�������ʵش����𡰱̺���������������������������������ˡ�\n"NOR, me,ob);
					if (random(me->query_skill("qimen-bagua",1)*me->query("pur"))>ob->query_skill("qimen-bagua",1)*ob->query("pur")/2)
					{
						message_vision(HIW"$S��Ȼ���������࣬�������ţ����ҡ�����������١�\n"NOR, me,ob);
						ob->receive_damage("jing",damage/2,me);
						ob->receive_wound("jing",damage/5,me);
						ob->apply_condition("no_exert",1);
					}else {
						message_vision(HIW"$Sʶ��$N����ʽ�����ص����һ��������Ƶ�$N������������Ĺ�����\n"NOR, me,ob);
						me->add_busy(2);
					}

				}
				break;
		}

	}
	
	  

}
