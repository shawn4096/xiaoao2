// yinyang.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>
int exert(object me)
{
	int improve = (int)me->query_skill("force",1) * 3;

	if( (int)me->query_skill("linji-zhuang", 1) < 350 )
		return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

	if( me->query("class") != "bonze" && me->query("family/generation") > 4)
		return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ��������־���\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("�������������\n");

	if( me->query_temp("ljz/yinyang")   )
		return notify_fail("�����������ټ�ʮ��ׯ�ġ��������־���\n");

	message_vision(HIW"ֻ��$N��ȡ���֮���"HIR"����"HIW"��������Ȼ����������\n"NOR,me);
/*
	me->add("max_qi", improve);
	me->add("eff_qi", improve);
	me->add("qi", improve);
   */ 
	me->add_temp("apply/armor",me->query_skill("linji-zhuang",1)/6);
	me->add_temp("apply/parry",me->query_skill("linji-zhuang",1)/6);

	if (me->query("emjy/pass"))
    {
	  message_vision(HIC"$N��������Ķ��Ҿ�������������գ���������Ԫ��Ȧ���������֣�\n"NOR,me);
	  me->add_temp("apply/armor",me->query_skill("linji-zhuang",1)/4);

	  me->add_temp("apply/parry",me->query_skill("linji-zhuang",1)/4);
	  me->add_temp("apply/defense",me->query_skill("linji-zhuang",1)/4);
    }
//	�޸���ǰ��ֱ�ӻָ���Ѫ
/*
	me->add("max_jing", improve);
	me->add("eff_jing", improve);
	me->add("jing", improve);
*/
//	���Ӿ�Ѫ

	me->set_temp("ljz/yinyang", improve);
	me->add("neili", - 500);
	//if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(1, "�����־�");
//	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), improve );
	call_out("remove_effect",1,me,improve/60);
	return 1;
}

void remove_effect(object me,int count)
{      
	int improve;
	//if( me->is_ghost() ) return;

	if( !me || !me->query_temp("ljz/yinyang") ) return;
	
	if (!me->is_fighting()
		||count<0)
	{
		improve = me->query_temp("ljz/yinyang");
		me->delete_temp("ljz/yinyang");
		/*
		if (me->query("qi")<improve)
		{
			me->set("qi",1);
			me->add("max_qi", - improve);
		}else me->add("max_qi", - improve);

		if (me->query("jing")<improve)
		{
			me->set("jing",1);
			me->add("max_jing", - improve);
		}
		else me->add("max_jing", - improve);	
    
	// �޸�ԭ���ָ���������
		if( me->query("eff_qi") > me->query("max_qi") )
			me->set("eff_qi", me->query("max_qi") );
		if( me->query("qi") > me->query("max_qi") )
			me->set("qi", me->query("max_qi") );

		if( me->query("eff_jing") > me->query("max_jing") )
			me->set("eff_jing", me->query("max_jing") );
		if( me->query("jing") > me->query("max_jing") )
			me->set("jing", me->query("max_jing") );
*/
		me->add_temp("apply/armor",-me->query_skill("linji-zhuang",1)/6);
		me->add_temp("apply/parry",-me->query_skill("linji-zhuang",1)/6);

		if (me->query("emjy/pass"))
		{
			me->add_temp("apply/parry",-me->query_skill("linji-zhuang",1)/4);
			me->add_temp("apply/defense",-me->query_skill("linji-zhuang",1)/4);
			me->add_temp("apply/armor",-me->query_skill("linji-zhuang",1)/4);

		}


		tell_object(me, HIC"����ټ�ʮ��ׯ"HIR"��������"HIC"�־��˹���ϣ��ټ�ׯ�Ļ���Ч���ظ���������\n"NOR);
		return;
			
	}
	if (objectp(me))
		call_out("remove_effect",1,me,count--);
	
}

string exert_name(){ return HIC"�����־�"NOR; }

int help(object me)
{
    write(HIC"\n�ټ�ʮ��ׯ�������־�����"NOR"\n\n");
    write(@HELP
	�ټ�ʮ��ׯ�˶����������ڹ��ķ����ǿ�ɽ��ʦ�����ں����Լ�һ��
	�������ŵ������ڹ����ķ����ں϶��ɣ����о����񹦵ĸ��ͣ�����
	�����澭��������ᣬ�˵��������ķ���ϵ��
	�������־�����Ҫ��ͨ����ʹ�ټ�ׯ�ķ����������ķ�����ϵ����
	���˶�ü��������ɴ���������������

ָ�exert yinyang

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 1500 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 350 ���ϣ�
	���һ��׼��������ӡ�

HELP
        );
        return 1;
}
