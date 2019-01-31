// fumo.c ����ȭ perform ��շ�ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void check_fight(object me,int count);

int perform(object me, object target)
{
      string msg;                                   
      int improve,skill;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("����շ�ħ��ֻ����ս���жԶ���ʹ�á�\n");
             
      if( objectp(me->query_temp("weapon")) )
         return notify_fail("��������ʹ�á���շ�ħ����\n");
      
      if( skill=(int)me->query_skill("jingang-quan",1) < 350 )
         return notify_fail("��Ĵ���ȭ������죬����ʹ�á���շ�ħ����\n");
      
      if( (int)me->query_skill("yijin-jing",1) < 350 )
         return notify_fail("����׽�ڹ��ȼ�����������ʹ�á���շ�ħ����\n");  
      if( (int)me->query_skill("cuff",1) < 350 )
         return notify_fail("��Ļ���ȭ���ȼ�����������ʹ�á���շ�ħ����\n");  
      if( (int)me->query_str() < 60 )
         return notify_fail("��ı�������ǿ������ʹ�á���շ�ħ����\n");
      
      if( (int)me->query("max_neili") < 3500 )
         return notify_fail("�������̫��������ʹ�á���շ�ħ����\n");
      
      if( (int)me->query("neili") < 1500 )
         return notify_fail("�������̫���ˣ��޷�ʹ�ó�����շ�ħ����\n");   
                                                                                 
      if (me->query_skill_prepared("cuff") != "jingang-quan"
        || me->query_skill_mapped("cuff") != "jingang-quan")
                return notify_fail("�������޷�ʹ�á���շ�ħ�����й�����\n");                                                                                 
      
      if( me->query_temp("fumo"))
          return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");
       
      msg = HIR"$NͻȻȫ��������죬����Ĭ���շ�ħ��������" +
               "�׽������һ���ɫ��ȫ�������ʹ���������һ����\n" NOR;
      
      message_vision(msg, me, target); 
	  skill = me->query_skill("jingang-quan");
      if (me->query("quest/sl/yjj/powerup"))
      {
		  skill = me->query_skill("jingang-quan",1)+me->query_skill("yijin-jing",1)/2;
      }
	  
      improve = skill/5 + random(skill/5);
      if ( improve > 100 ) improve = 100 + random(improve-100) / 10;
      
	  me->add_temp("apply/strength", improve);
	  me->add_temp("apply/attack", improve*2);
	  me->add_temp("apply/cuff", improve);
	  me->add_temp("apply/damage", improve);
      me->set_temp("fumo", improve);  
      me->add("neili", - 300+ random(300));
      me->add("jingli", - 250);  
      call_out("check_fight", 1, me, skill/3);
      if (me->query_skill("jingang-quan",1)<449)
	  {
		  me->start_busy(2);
      }
      return 1;
}

void check_fight(object me,int count)
{
      int j;
      if (!me) return;
      if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query_skill_prepared("cuff") !="jingang-quan"){
        j = me->query_temp("fumo");
        me->add_temp("apply/strength", - j);
		me->add_temp("apply/attack", -j*2);
	    me->add_temp("apply/cuff", -j);
	    me->add_temp("apply/damage",-j);
        me->delete_temp("fumo");
        tell_object(me, HIR"��ġ���շ�ħ���˹���ϣ������ɫ�ÿ����ˡ�\n"NOR);
        return;
      }
      if (count < 1 || !me->is_fighting()) {
        j = me->query_temp("fumo");
        me->add_temp("apply/strength", - j);
		me->add_temp("apply/attack", -j*2);
	    me->add_temp("apply/cuff", -j);
	    me->add_temp("apply/damage",-j);
        me->delete_temp("fumo");
        tell_object(me, HIR"��ġ���շ�ħ���˹���ϣ������ɫ�ÿ����ˡ�\n"NOR);
        return;
      }
      else {
//        me->start_perform(1,"����շ�ħ��");
        call_out("check_fight", 1, me, count-1);
      }
}

string perform_name(){ return HIR"��շ�ħ"NOR; }

int help(object me)
{
        write(HIB"\n�������ȭ֮����շ�ħ����"NOR"\n");
        write(@HELP
		�򷨹��ڣ��޷�һ�ա������������ڵ������ģ�ǿ�����ң��Կ�Ϊ��߾��磬�����й�����ʱ�޿̲��ں͸���
		ħ��������������ħͷ������ħͷ����ν��ħ��ħ������Ҫ��������Ҫ�������������׽ǿ���壬���ڽ��ȭ
		�Խ�շ�ħ��������������ʮ�������и�����ѧ����ǿ�������͸���ļ�������ʩչ��
				
		��λ�����־�ɱ��ϼ���֮һ������Ϊ��Ҫǿ��������������Խ������Խ��

		Ҫ��  
			����������� 3500 ���ϣ�      
			��ǰ�������� 1500 ���ϣ�  
			�����Ƶȼ�   350  ���ϣ�
			����ȭ���ȼ� 350  ���ϣ�
			�׽�ȼ� 350 ���ϣ�
			����ȭ��Ϊ�������ȭ��
			��Ч��������С��60��
			�����ޱ�����
			��շ�ħ450���Ծ��ȡ��busy�����Ժ�������������ϣ����輤��cuff��
			���⿪�׽���Ķ����⣬����ȭ����������һ��̨�ס�
                
HELP
        );
        return 1;
}
