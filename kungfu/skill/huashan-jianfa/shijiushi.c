// shijiushi.c ��Ůʮ��ʽ
// Update by lsxk@hsbbs �������ں�����ʹ��Ч����

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
string perform_name() {return HIW"��Ůʮ��ʽ"NOR;}

int perform(object me, object target)
{
        string weapon;
        int i,j;
        j=19; //������ʽ
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��Ůʮ��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
       //�������ڱ����ж��ڹ��������ǽ�������Բ��ж��ڹ�����
		if (me->query("huashan/quest") == "����")
        {
           if (me->query_skill_mapped("force") != "zixia-gong"
               &&me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("����ڹ������޷�ʹ�á���Ůʮ��ʽ����\n");
        }       

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ����Ůʮ��ʽ��\n");
        
        if( me->query_skill("zixia-gong", 1) < 350
         && me->query_skill("huashan-qigong", 1) < 350)
                return notify_fail("��������ڹ����δ�����޷�ʩչ��Ůʮ��ʽ��\n");

        if( (int)me->query_skill("huashan-jianfa",1) < 350 )
                return notify_fail("��Ļ�ɽ��������㣬�޷�ʹ�þ�����׵���Ůʮ��ʽ��\n");

        if( me->query_skill("dodge") < 350 )
                return notify_fail("��Ůʮ��ʽ��Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 350 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("�����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ����Ůʮ��ʽ��\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("������������Ůʮ��ʽ��\n");

      if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("�������޽�����ʹ����Ůʮ��ʽ����\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N�˽���磬����ǳ��ġ���Ů��ʮ��ʽ��һʽʽʩչ������" + weapon + HIC"����������,���������⣡\n" +
        "���֮�䣬$N������Ůʮ�Ž�������ʮ��ʽ��������һ���ǳɵ�ʹ�˳������������б���һ�У�����֮�죬ֱ�Ƿ�����˼��\n" NOR, me, target);
        me->set_temp("hsj_19",1);
        //Ů�����ӷ���
		if(me->query("gender")=="Ů��")
	      { 
			me->add_temp("apply/dodge",me->query_skill("huashan-jianfa",1)/3);
			me->add_temp("apply/parry",me->query_skill("huashan-jianfa",1)/3);
			me->add_temp("apply/dexerity",me->query_skill("huashan-jianfa",1)/5);
			me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/5);
			message_vision(HIW"$N˫���ս��������ˮ������̬Ʈ�ݣ������貨���ӣ����еĽ���ȴ���Դ�������������������\n"NOR,me);
		  }
		//������������,��ʽ����
		if(me->query("quest/huashan")=="����")
	    {
			me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/4);
			me->add_temp("apply/sword",me->query_skill("huashan-jianfa",1)/6);
            j= 10;
		}
        j=random(j);
		if (j<7 && me->query("quest/huashan")=="����") j=7;
		else if (j< 5 && me->query("quest/huashan")=="����") j=5;
		//else j=j;
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/4);
        for( i = 0; i < j; i ++ ) {        
          //���������˺�
		  if (me->query("quest/huashan") == "����"){
             me->add_temp("apply/damage",(int)me->query_skill("huashan-jianfa",1)/4);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->add_temp("apply/damage",-(int)me->query_skill("huashan-jianfa",1)/4);
          } 
		  else if(me->query("quest/huashan") == "����"){
             if(!random(3)) target->set_temp("must_be_hit",1);
             if(!target->is_busy()){
                 message_vision(HIW"\n$N������ڹ��������������е�"+weapon+HIW+"�ϣ�$nֻ��һ�ɾ���Ϯ�������������쳣!\n"+
                     HIC"$n�о��Լ���������һƬ����֮�У��پ��Ĵ����ƣ�\n"NOR,me,target);
                 target->start_busy(2+random(3));
				 //�������ӶԷ�busy
			  }			
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
             target->delete_temp("must_be_hit");
          }		 
		  else              
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:2);
             //me->add("neili",-100);    
      
      }
        me->add("neili", -300);
        if(me->query("quest/huashan")=="����")
	     { 
			 me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/4);
		     me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
		 }
        if(me->query("gender")=="Ů��")
	      { 
		  me->add_temp("apply/dodge",-me->query_skill("huashan-jianfa",1)/3);
          me->add_temp("apply/parry",-me->query_skill("huashan-jianfa",1)/3);
          me->add_temp("apply/dexerity",-me->query_skill("huashan-jianfa",1)/5);
		  me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/5);
		  }
		me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/4);
		me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(4+random(2));
        me->start_busy(2+random(2));
        return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"HIW"��Ůʮ��ʽ"WHT"����"NOR"\n");
   write(@HELP
	���С���Ůʮ��ʽ�����ɽ�ȱ���Ѫ��������ɽ���ڣ����ڶ�����
	��ȴ��������ͬ�����ڽ���������ӯ���ɣ�������ˮ��������ȴ����
	���������Ԧ��������������һ�м��������޲���֮����ˣ�����
	ʹ�ã��������Լ�������ǿ�����ڣ�������ʹ�ã���������Զ���ڽ�
	�ڣ����м����õ���æ�ҡ���Ҫע��������ڱȽ�ǿ���ڹ�����Ҫ��
	����ע�ؽ��е���������ˣ����ڲ�̫���Ӵ����Ƿ���ڹ���ƥ�䡣
	ע�⣺�����˽��ھ���������ʹ�ñ������ж������ơ�
	
	ָ�perform sword.shijiushi

Ҫ��
	��ɽ���� ���� ��ϼ�� 350��,���ڲ���
	���������� 60
	��ɽ�������� 350 ����
	������������ 350 ����
	�����Ṧ���� 350 ����
	��ǰ�������� 2000 ���ϣ�
	��ǰ�������� 1000 ���ϡ�
HELP
   );
  return 1;
}
