// beiming.c
// modified by action@SJ 2009/2/5
//updated by Zmud@Sjmud 12/3/2009
//edit by sohu@xojh
	//���ݽ⿪��ڤ����ζ�ż�Ϊ��ң�ɵ���
	//if (me->query("family/family_name") == "��ң��") {
		//}
	//��ڤ������һ�Σ��⿪�������ң�ɵ��ӣ�����ʽ�ڹ�������һ�㡣
	//��ڤ�����ڶ��Σ�����ɽ����
	//��ڤ���������Σ�����ˮ+ͯ�ѵĹ�������,Ԥ��С����ӿ�

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int count);

string exert_name(){ return HIC"��������"NOR; }

int exert(object me, object target)
{
	int skill;

    if( me->query("max_neili") < 10000 )
		return notify_fail("����������������\n");
	if( me->query("neili") < 1000 )
		return notify_fail("��ĵ�ǰ����������\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("��ĵ�ǰ����������\n");
    if( me->query_skill("beiming-shengong", 1) < 350 )
		return notify_fail("��ı�ڤ�񹦵ȼ�������\n");
	if( me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ�������\n");
	if( me->query_skill_mapped("force") != "beiming-shengong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("bmsg/bm") )
		return notify_fail("���Ѿ����ˡ������������ˡ�\n");

	skill = (int)me->query_skill("beiming-shengong", 1);

	
	message_vision(HIB "\n$N����ڤ�񹦿���Ĭ��"NOR"��"HIB"����������̨���������أ��麣�����ڻ�������["HIG"����"HIB"]���γ�һ�ɺƵ�֮����\n" NOR, me);
	

	me->set_temp("bmsg/bm", skill); 
	
	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/intelligence",skill/30);
	me->add_temp("apply/dexerity", skill/20);
	
	me->add_temp("apply/armor", skill/3); 	
	me->add_temp("apply/defense", skill/4);
	me->add_temp("apply/parry", skill/3);
	me->add_temp("apply/dodge", skill/4);

	if (me->query("quest/beiming/second/pass"))
	{
		message_vision(HBBLU+HIW "\n$N��ת��Ϣ������˲��¡��������$N�����γ�һ�����֡�\n" NOR, me);
		me->add_temp("apply/attack", skill/4);

		me->add_temp("apply/armor", skill/4); 	
		me->add_temp("apply/defense", skill/4);
		me->add_temp("apply/parry", skill/4);
		me->add_temp("apply/dodge", skill/4);
		me->add_temp("apply/damage",skill/5);
	}
	if (me->query("quest/beiming/third/pass"))
	{
		message_vision(HBWHT+HIG "\n$N��ڤ�������ˣ�����Ͷ��䷢��Ī�������,��ڤ�񹦵Ĵ��������˷��ԡ�\n" NOR, me);
		me->add_temp("apply/attack", skill/4);
		me->add_temp("apply/constitution", skill/10);
		me->add_temp("apply/strength", skill/15);
		me->add_temp("apply/damage",skill/5);
	}
	if (me->query_skill("beiming-shengong",1)<350)
		me->start_busy(random(2));
	if( me->query_skill("beiming-shengong",1)<450)
		me->start_exert(1, "��������");		
	me->receive_damage("neili", -500);
	me->receive_damage("jingli", -300);

	call_out("remove_effect",60,me);

	return 1;
}

void remove_effect(object me, int count)
{
	int skill;
	write(count);
	
	if (!objectp(me)||!me->query_temp("bmsg/bm")) return;	
	
	skill=me->query_temp("bmsg/bm");	
	
	//if(count<1) 
//	{
		
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/intelligence",-skill/30);
		me->add_temp("apply/dexerity", -skill/20);
	
		me->add_temp("apply/armor", -skill/3); 	
		me->add_temp("apply/defense", -skill/4);
		me->add_temp("apply/parry", -skill/3);
		me->add_temp("apply/dodge", -skill/4);
		if (me->query("quest/beiming/second/pass"))
		{
			me->add_temp("apply/attack", skill/4);

			me->add_temp("apply/armor", skill/4); 	
			me->add_temp("apply/defense", skill/4);
			me->add_temp("apply/parry", skill/4);
			me->add_temp("apply/dodge", skill/4);
			me->add_temp("apply/damage",skill/5);
		}
		if (me->query("quest/beiming/third/pass"))
		{
			me->add_temp("apply/attack", skill/4);
			me->add_temp("apply/constitution", skill/10);
			me->add_temp("apply/strength", skill/15);
			me->add_temp("apply/damage",skill/5);
		}
		
		me->delete_temp("bmsg/bm");
		message_vision(HBWHT+HIG "\n$N�����չ�������ڤ�������뵤������֮�С�\n" NOR, me);
		return;
//	}

//	call_out("remove_effect", 1, me, count--);
}
int help(object me)
{
	write(HIW"\n��ڤ��֮��������������"NOR"\n\n");
        write(@HELP
	ׯ�ӡ���ң�Ρ����ƣ����֮����ڤ���ߣ����Ҳ�������ɣ�
	�����ǧ�δ��֪����Ҳ�������ƣ����ҷ�ˮ֮��Ҳ����
	���为����Ҳ����������ˮ������֮�ϣ����Ϊ֮�ۣ��ñ�
	���򽺣�ˮǳ���۴�Ҳ�����ǹʱ����书���Ի�������Ϊ��
	һҪ�塣�����Ⱥ������书�޲�Ϊ�����ã���֮��ڤ����
	��С���޲��أ�����С���޲��ݡ��ǹ�����Ϊ��������Ϊĩ��
	������ͼ������������ϰ��
	
	ע�⣺��ڤ�񹦷�Ϊ������ƹ滮������Ҳ����֮�����仯
	��һ�Σ��⿪�������⣬ʦ���ᴫ���㱱ڤ�����ͱ�ڤ�񹦣�
	        ��ڤ������ΪƤë����һ�����ֱ�ڤ�ķ����ص㡣
	�ڶ��Σ��⿪����ɽ�������⣬��ñ�ڤ����������
			��ڤ����������ɡ��ڶ������ֱ�ڤ�Ĺ����ص㡣
	�����Σ��⿪��ɽͯ�Ѻ�����ˮ�����⣬���ն��˹���������
			��ڤ��������Բ������ڤ���״�ɡ�
	
	ָ�exert beiming

Ҫ��
	�������  10000 ���ϣ�
	��ǰ����  1000  ���ϣ�
	��ǰ����  1000  ���ϣ�
	��ڤ��  350   ���ϣ�
	�����ڹ�  350   ���ϣ�
	
HELP
        );
        return 1;
}
