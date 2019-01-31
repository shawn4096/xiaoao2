// shendao.c  Ѫ���� [��Ӱ��]
// changed by cloudy@zt

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIB"��Ӱ��"NOR; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, weaname;
        int lvl,damage,i,ap,dp;
    
        if( !me->is_fighting() )
                return notify_fail("����Ӱ�񵶡�ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 15)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("dodge") < 100)
                return notify_fail("����Ṧ��Ϊ����, ����ʹ�á���Ӱ�񵶡���\n");
 
        if((int)me->query_skill("xuedao-daofa",1) < 100)
                return notify_fail("���Ѫ��������Ϊ������ Ŀǰ����ʹ�á���Ӱ�񵶡�! \n");

        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á���Ӱ�񵶡�! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ����������ʹ�á���Ӱ�񵶡��ľ�����\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-dafa")
	    	  return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ��������ִ�������ʹ������Ӱ�񵶡��ľ�����\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("���������Ϊ������\n");
        if((int)me->query("neili")<600)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("��ľ���������\n"); 

        ob = me->select_opponent();

        //if( !userp(me) && userp(ob) )
          //      return notify_fail("����Ӱ�񵶡�ֻ�������ʹ�ã�\n");

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        msg = HIY "\n$N����Ѫ�����еĸ������Ӱ�񵶡�������"NOR+weaname+HIY"�������뵽һƬ��â֮�У�\n"NOR;
        message_vision(msg, me);

        me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);

        if(lvl>350){
            i = 3;
            me->add_temp("apply/attack", lvl/3);
            me->add_temp("apply/damage", lvl/4);
            }
        else i=0;
		ap=me->query("combat_exp",1);
        dp=ob->query("combat_exp",);
		//me->query_skill("xuedao-jing",1)
        if (random(ap)>dp/2 || random(me->query_skill("blade",1))>ob->query_skill("parry",1)/3)
        {
			message_vision(HBYEL"\n$nΪ��Ƭ�����Ѫ�����Ի��ƺ��ŵ�һ��Ī�������㣬��ʼ��æ����������\n",me,ob);
			ob->start_busy((int)lvl/50);
			if(lvl >350)
		    ob->add_temp("apply/defense",-lvl/5);
			me->add_temp("apply/attack", lvl/3);
			if (present(ob,environment(me)) && me->is_fighting(ob))
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), i);
			ob->add_temp("apply/defense",lvl/5);
			me->add_temp("apply/attack", -lvl/3);
        }
		else 
	    {
			message_vision("\n$n����$N����ͼ�����һ�������˿�ȥ��\n",me,ob);
            me->start_busy(random(2));

	    }
		
        me->add("neili", -100-random(100));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
        me->start_busy(random(2));
        if (me->query_skill("xuedao-jing",1)<449)
        {
			me->start_perform(4,"��Ӱ��");
        }
		        
        me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);

        
        if(lvl>350){
            me->add("neili", -100-random(100));
            me->add_temp("apply/attack", -lvl/3);
            me->add_temp("apply/damage", -lvl/4);
        }
        if(me->query_temp("xuedao/yuxue")) {
            me->add_temp("apply/damage", -damage);
        }
        return 1;
}

int help(object me)
{
	write(HIR"\nѪ��������֮����Ӱ�񵶡���"NOR"\n\n");
        write(@HELP
˵����
	��Ӱ������Ѫ����������似�����Ī��ĵ�������������
	����ת���棬ʹ������������������Ļ�Ӱ�������Ի���֡�
	�������ֿ��Ʋ�͸�������������ᵼ����Ͼ������������
	
ָ��: perform blade.wuying

Ҫ��
	�������  1200 ���ϣ�
	��ǰ����  1000  ���ϣ�
	Ѫ����  100  �����ϣ�
	350����С�ɣ�
	450���Ϊ����ʽ��

HELP
        );
        return 1;
}