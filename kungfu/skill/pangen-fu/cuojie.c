// pangen-fu ,cuojie ���־�
#include <ansi.h>
#include <combat.h>

#define CUO "��" HIR "���־�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int level,i;
	string msg;

        if (userp(me) && !me->query("quest/tls/pgf/pangen/pass"))
                return notify_fail("��ֻ����˵�����У�������ʹ�����ֹ��ܡ�\n");
		level=me->query_skill("pangen-fu",1);
		i=(int)level/200;
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) 
            ||(string)weapon->query("skill_type") != "axe")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" CUO "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ( me->query_skill("pangen-fu", 1) < 300)
                return notify_fail("���̸���ڸ�������죬����ʩչ" CUO "��\n");
		if ( me->query_skill("qiantian-yiyang", 1) < 300)
                return notify_fail("���Ǭ��һ��������죬����ʩչ" CUO "��\n");
        if ((int)me->query_skill("force",1) < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" CUO "��\n");

        if ((int)me->query("max_neili",1) < 3500)
                return notify_fail("���������Ϊ����������ʩչ" CUO "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("��������������������ʩչ" CUO "��\n");
        if ( me->query_temp("pgf/cuojie"))
                return notify_fail("������ʩչ���־���\n");
        if( me->query_str() < 50 )
            return notify_fail("��������������޷�ʹ�á��̸���ڡ�������\n");
        
		if (me->query_skill_mapped("axe") != "pangen-fu"
		   ||me->query_skill_mapped("parry") != "pangen-fu")
                return notify_fail("��û�м����̸���ڸ�������ʩչ" CUO "��\n");

        if (!living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

		msg = HIR "$N" HIR "�߾�����" + weapon->name() + HIR "����Ȼһ���Ϻȣ�����$n"
              HIR "�ͻ�������������硣���в���$n�Ĺؽ�Ҫ�����˵��������ǳ���\n" NOR;
		

        me->add("neili", -100-random(300));
        if (random(level) > (int)target->query_skill("parry", 1) / 2
			||random(me->query("combat_exp"))>target->query("combat_exp")/3
			|| random(me->query_str()) > target->query_dex()/2)
        {
		  msg += HIW "$p" HIW "��$P" HIW "������ӿ�����ò���;"
                       "���У���һ�µ�ʱ��ʧ���Ȼ���\n" NOR;
          
		  if (userp(target)) target->add_busy(1);
          else target->add_busy(3);
		  
		  //message_combatd(msg, me, target);
		  me->add_temp("apply/damage",(int)me->query_skill("pangen-fu",1)/6);
		  me->set_temp("pgf/cuojie",1);
		  call_out("check_fight",1,me,target,(int)level/20);
	    } else
        {
		  msg += CYN "����$p" CYN "����$P" CYN "��ʽ����·��б"
                       "б������ʹ����δ��˿�����á�\n" NOR;
		  
		  me->start_busy(1);
	     }
	     message_combatd(msg, me, target);
        if (me->query_skill("pangen-fu",1)<350)
		   me->start_perform(3,"���־�");
	   
		
		return 1;
}

void check_fight(object me, object target,int count)
{
       object weapon,wp2;
	   if (!me) return;
	   weapon=me->query_temp("weapon");

	   if (count<0
		 ||!objectp(target)
		 ||!weapon
		 || me->query_skill_mapped("axe") != "pangen-fu"
         || me->query_skill_mapped("parry") != "pangen-fu"
         || me->query_skill_mapped("force") != "qiantian-yiyang"
         || weapon->query("skill_type") != "axe"
		 ||!me->is_fighting())
	   {
			me->add_temp("apply/damage",-(int)me->query_skill("pangen-fu",1)/6);
	   
			me->delete_temp("pgf/cuojie");
			tell_object(me, HIW"���̸���ڸ�֮�����־���ʩչ��ϣ���������һ������\n" NOR); 
			return;
	   }
	   //���϶Է�����

		if (objectp(target))
		{
			wp2=target->query_temp("weapon");
			if (objectp(wp2)
				&& !random(3)
				&& random(me->query_str())>target->query_dex()/2)
			{
				if (weapon->query("sharpness") > wp2->query("rigidity") && wp2->query("imbued") <= 3)			
				{
					message_vision(HIR"$N���һ�����������е�"+weapon->query("name")+HIR"����$n���е�"+wp2->query("name")+HIR"�������񣬶�ʱ��Ϊ���ء�\n"NOR,me,target);
					wp2->broken("���ϵ�");
				} 
			}


		}
	

       call_out("check_fight", 2,me,target,count -1);
}


string perform_name() {return HIY"���־�"NOR;}

int help(object me)
{
   write(WHT"\n�̸���ڸ���֮��"HIY"���־�"WHT"����"NOR"\n\n");
   write(@HELP
	�̸���ڸ����Ǵ������Ը����Ĵ�����ɽ����
	���óϵĶ����似���丫����Ȼ��ʽƽ������ȴ
	��ƽ������ʽ���̲�ɱ�����������ͣ���������
	��ɱ�л��ǵ��µ���������������͡�
	
	perform axe.cuojie
   
Ҫ��: 
	������� 3500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�̸����� 300  ���ϣ�
	�������� 300  ���ϣ�
	Ǭ��һ�� 300  ���ϣ�
	������� 50   ���ϣ�
	��������Ϊ�̸�������
	�����м�Ϊ�̸�����;
	װ����ͷ��

          
HELP
   );
   return 1;
}
