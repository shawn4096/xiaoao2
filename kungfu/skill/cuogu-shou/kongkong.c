// kongkong.c ���ֿտ�
// Modified by sohu@xojh
// ͵�Է���������

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBWHT+HIW"���ֿտ�"NOR; }

int perform(object me, object who)
{
     
		object target;
		target = present(who,environment(me));
        
       if( !objectp(target)
			|| !target->is_character())
             return notify_fail("�����ֿտա�ֻ�ܶ�ͬһ�ص�Ļ���ʹ�á�\n");
         if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á����ֿտա���\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("�����ֹ���ԡ�\n");
		
		if( (int)me->query_skill("cuogu-shou", 1) < 350 )
                return notify_fail("��ķֽ�����ֲ�����죬�޷�ʩչ�������ֿտա���\n");
		if( (int)me->query_skill("stealing", 1) < 200 )
                return notify_fail("������ֿտղ�����죬�޷�ʩչ�������ֿտա���\n");
        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ʩչ�������ֿտա���\n");
        if ( (int)me->query("max_neili") < 5000)
                return notify_fail("�����������������޷�ʩչ�������ֿտա���\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ�������ֿտա���\n");
		if (me->query_dex() < 60)
                return notify_fail("��ĺ��������������޷�ʩչ�������ֿտա���\n");
        if (me->query_skill_prepared("hand") != "cuogu-shou"
		    || me->query_skill_mapped("parry") != "cuogu-shou"
            || me->query_skill_mapped("hand") != "cuogu-shou")
                return notify_fail("�����ڼ������ԣ��޷�ʹ�á����ֿտա����й�����\n");
        if (me->query_temp("cgs/kongkong"))
                return notify_fail("������ʹ�á����ֿտա�������\n");
        
        if( !wizardp(me) && wizardp(target) )
                return notify_fail("��Ҳ��ܶ���ʦʹ�ô˼��ܡ�\n");


		if ( userp(me) && userp(target) && me->query("no_pk"))
			return notify_fail("���Ѿ�����ϴ���ˣ��Ͳ�Ҫ͵���˶����ˡ�\n");

		if ( userp(me) && userp(target) && target->query("no_pk"))
			return notify_fail(target->name()+"�Ѿ�����ϴ���ˣ��Ͳ�Ҫ͵���Ķ����ˡ�\n");
		
		if ( target->query("job_npc") || target->query("no_quest"))
			return notify_fail(target->name()+"������ûʲô��ˮ������͵�ˡ�\n");

		if( !target->is_character() || target->is_corpse() || target->is_container() )
            return notify_fail(target->name()+"��Ķ����õ���͵������þ����ˡ�\n");

	    if( me->is_busy()) return notify_fail("����æ���ء�\n");


		message_vision(WHT"$N�����Ṧ������������ɫ����Ȼ�ӽ�$n�����ߣ�\n"NOR,me, target);
		
		if (random(me->query_skill("cuogu-shou",1)+me->query_skill("stealing",1))>target->query_skill("parry",1)/2
			||random(me->query_int(1))>target->query_int(1)/2)
		{
			message_vision(HBYEL"$n����һ�٣�Ϊ$N�������裬���ɵ�����һ�ͣ�\n"NOR,me, target);
			
			target->add_busy(1);
			me->set_temp("cgs/kongkong",1);
		//	if (objectp(me)&&objectp(target))
			call_out("start_steal",1,me,target);
		}	
		else{
			message_vision(HIY"$n��Ȼ����$N���������Լ��İ�������ʱ��ŭ��\n"NOR,me, target);
			me->add_busy(2);
			target->kill_ob(me);
		}
		me->add("neili",-150);
		me->add("jingli",-100);

        return 1;	
}

void start_steal(object me, object target)
{
        object ob,*inv;
		int i;
        if (!me) 
return;
		me->delete_temp("cgs/kongkong");
		
		if (!target) return;
		
		message_vision(RED "$nֻ���ƺ���$N����ײ��һ�£���Ȼ̧ͷ��ȥ��ȴ��$N�Ѿ�ƮȻԶȥ��\n"NOR,me, target);
		inv = all_inventory(target);
		
		for (i=0;sizeof(inv);i++ )
		{
			ob=inv[random(sizeof(inv))];
			switch (me->query("env/���ֿտ�"))
			{
				  case "�ƽ�":
					if (ob->query("id")=="gold")
					{
						ob->move(me);
						message_vision(HBYEL "$n����ʶ��һ���������Լ��Ļƽ𲻼��ˣ���ʱ���д�ŭ����$nԶȥ�ı�Ӱ�ƿڴ��\n"NOR,me, target);
						
					}
					break;
				 case "����":
					if (ob->query("id")=="silver")
					{
						ob->move(me);
						message_vision(HBYEL "$n����ʶ��һ���������Լ��İ��������ˣ���ʱ���д�ŭ����$nԶȥ�ı�Ӱ�ƿڴ��\n"NOR,me, target);
						
					}
					break;
				case "����":
					if (ob->query("treasure"))
					{
						ob->move(me);
						message_vision(HBYEL "$n����ʶ��һ���������Լ���"+ob->query("name")+"���ﲻ���ˣ���ʱ���д�ŭ����$nԶȥ�ı�Ӱ�ƿڴ��\n"NOR,me, target);
					}
					break;
				case "ϡ��Ʒ":
					if (ob->query("unique"))
					{
						ob->move(me);
						message_vision(HBYEL "$n����ʶ��һ���������Լ���"+ob->query("name")+"�����ˣ���ʱ���д�ŭ����$nԶȥ�ı�Ӱ�ƿڴ��\n"NOR,me, target);
					}
					break;
				default:break;
			}

		}

		me->start_perform(2, "���ֿտ�");
		return;
}
int help(object me)
{
        write(HIG"\n�ֽ�����֮�����ֿտա���"NOR"\n");
        write(@HELP
	�ֽ�������ǽ����߹�֮��ʥ��������ϵľ��������
	�ַ�����Էֽ��ǽ��Է���Ѩ��������Ҫ������˲
	�佫�Է���ס�������ش���
	ע�⣺�˼���Ϊ�����������Ҿ���������ܷ�����ϰ��

	set ���ֿտ� (�ƽ𡢰��������ϡ��Ʒ)����˫����
	��֮�ʣ�˳��ǣ���ȥ��ʵ�˽�����һ���о���������
	����Ϊ������ʿ�������Ҽ����������˼��ޣ��м��мǣ�

	ָ�perform hand.cuogu

Ҫ��
	�����ڹ��ĵȼ� 350  ���ϣ�
	�ֽ�����ֵȼ� 350  ���ϣ�
	�����ַ��ĵȼ� 350  ���ϣ�
	���ֿտյĵȼ� 200  ���ϣ�
	��������Ҫ�� 5000 ���ϣ�
	��ǰ������Ҫ�� 500  ���ϣ�
	����������Ҫ�� 60   ���ϣ�
	�����ұ��ַ�Ϊ�ֽ�����֣�
	�����ұ��ַ�Ϊ�ֽ�����֣�
	�ڹ����ޡ�

HELP
        );
        return 1;
}

