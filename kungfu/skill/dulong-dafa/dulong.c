// dulong.c 
// by sohu@xojh
//
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HBWHT+HIB"������"NOR;}

void remove_effect(object me, int amount);
void remove_effect2(object me, int amount);

int exert(object me)
{
        int i;
		if (!me->is_fighting())
			return notify_fail("������ֻ��ս����ʩչ���޷�ʩ�á�����������\n");
        if(!me->query("quest/sld/dldf/dulong/pass"))
               return notify_fail("����δ�⿪���������޷���ʹ��\n");
        if((int)me->query_skill("dulong-dafa",1) < 350  )
                return notify_fail("��Ķ����󷨹����������޷�ʩ�á�����������\n");
        if((int)me->query_skill("force",1) < 350  )
                return notify_fail("��Ļ����ڹ������������޷�ʩ�á�����������\n");
		if((int)me->query_skill("shenlong-yaoli",1) < 200  )
                return notify_fail("�������ҩ�����������޷�ʩ�á�����������\n");
        if((int)me->query("max_neili") < 3500 )
                return notify_fail("�����������������޷�ʹ�á�����������\n");
		if((int)me->query("neili") < 1500 )
                return notify_fail("��ĵ�ǰ�����������޷�ʹ�á�����������\n");
        if(me->query_skill("poison",1)<180 )
				return notify_fail("�����ڶ��Ʋ���������ʹ�á�����������\n");
        if(me->query_skill("qusheshu",1)<200 )
				return notify_fail("�����ڶ��Ʋ���������ʹ�á�����������\n");


    

        if((int)me->query("jingli") < 1000  )
				return notify_fail("��ľ����������޷�ʹ�á�����������\n");
        
		i = me->query_skill("dulong-dafa", 1);
	

		message_vision(HBBLU+HIG"$N��ͷ����һ�����������𡸶�����������Х֮�������ƣ����綾��˻˻���������������дʣ���������������!\n"NOR,me);
		
		me->set_temp("dldf/dulong",i);
		me->add_temp("apply/attack",i/5);
		if (me->query("gender")=="����")
		{
				me->add_temp("apply/strike",i/5);
				me->add_temp("apply/hook",i/5);
		}
		if (me->query("gender")=="Ů��")
		{
				me->add_temp("apply/hand",i/5);
				me->add_temp("apply/dagger",i/5);
				me->add_temp("apply/whip",i/5);
		}
		me->add_temp("apply/dodge",i/6);
		
		if (me->query_skill("dulong-dafa",1)<450)
		    me->start_exert(1,"����������");
		me->add("neili",-200);
		me->add("jingli",-150);
		//if (objectp(me))
			call_out("remove_dulong",1,me,(int)i/15);
		return 1;
 }      
		

void remove_dulong(object me, int count)
{
        int i;
		object target,ob;
		if (!me||!me->query_temp("dldf/dulong")) return;
		
		i=me->query_temp("dldf/dulong");
        if( count-- < 0
			||!me->is_fight())
		{ 
            me->add_temp("apply/attack",-i/5);
			if (me->query("gender")=="����")
			{
					me->add_temp("apply/strike",-i/5);
					me->add_temp("apply/hook",-i/5);
			}
			if (me->query("gender")=="Ů��")
			{
					me->add_temp("apply/hand",-i/5);
					me->add_temp("apply/dagger",-i/5);
					me->add_temp("apply/whip",-i/5);
			}
			me->add_temp("apply/dodge",-i/6);
			me->delete_temp("dldf/dulong");

			message_vision(HBBLU+HIG"$N��������ת��ϣ��������³�һ�ڻ�ɫ����������Ȼ���о綾��\n"NOR,me);
            return;
        }
		
		if (objectp(ob=present("jin she",me))
			&&random(10)>5)
		{
			if (me->query("env/����")=="����")
			{		
					message_vision(HIY"$N�������󷨶�������ʹ�Լ���С���������ָ��ָ��\n"NOR,me);
					ob->gongji();
				
			}else if (me->query("env/����")=="����")
			{				
					message_vision(HIY"$N�������󷨶�������ʹ�Լ���С�������Լ�ָ��ָ��\n"NOR,me);
					ob->huti();
			}
		}
		call_out("remove_dulong", 1, me, count);
}

int help(object me)
{
        write(WHT"\n������֮"+HIR"����������"WHT"��\n\n"NOR);
        write(@HELP
	�����������������ڹ����������ǿ�ɽ��ʦ
	������������ɶ����ķ����������������߶�
	�����ԣ�������ǿ����һ�档
	���������������������ö����󷨵Ķ����ķ�
	����ֶ�ҩ���Ϻ��ں϶��ɵ�һ���ķ�����
	���ڶ�ʱ���������Լ��Ĺ�����
	���Բ������Ʒ�������Ů�������ַ��޷�ذ��
	�ϸ����ж�����ǿ������ܷ���ʩչ��
	
	ע�⣺set ���� <����|����>

	������ָ����ָʾ�Լ�ѱ��������Э���Լ�ȥ
	�������ˣ������������趨�Լ�����Ϊ�Լ���
	��������ע�⣬���Լ�ѱ������������Ҫ��ȥ
	ѱ��һ����

	ʹ��ָ�yun dulong
		
Ҫ��
	��ǰ����Ҫ�� 2000 ���ϣ�
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����ڹ��ȼ� 350  ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	����ҩ��ȼ� 200 ���ϣ�
	��    �Ƶȼ� 180 ���ϣ�
	�� �� ���ȼ� 200 ����
	�����ڹ�Ϊ�����󷨣�
	450����busyȡ������Ծ��
HELP
        );
        return 1;
}

