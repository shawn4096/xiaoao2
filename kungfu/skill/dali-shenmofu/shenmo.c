// shenmo.c �������Ե��似 ��ħ��

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return RED"��ħ��"NOR; }

int perform(object me, object target)
{
      int lvl,lvl1;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("dali-shenmofu", 1);
      lvl1=(int)me->query_skill("xixing-dafa", 1);
  
    if( !target ) target = offensive_target(me);
     
      if( !target ||!living(target)|| !me->is_fighting(target) )
        return notify_fail("����ħ����ֻ����ս���жԶ���ʹ�á�\n");

      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "dali-shenmofu")
        return notify_fail("��ʹ�õı��в���ȷ���޷�ʹ�á���ħ������\n");             
      if( me->query("quest/hmy/dlsmf/jueji")!="pass" )
        return notify_fail("��֪��������ħ��������δ�ڻ��ͨ������ʹ�á���ħ������\n");
      if( (int)me->query_skill("dali-shenmofu",1) < 350 )
        return notify_fail("��Ĵ�����ħ��������죬����ʹ�á���ħ������\n");
      
      if( (int)me->query_skill("axe",1) < 350 )
        return notify_fail("��Ļ��������ȼ�����������ʹ�á���ħ������\n");  
      if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 

       if(me->query_skill("xixing-dafa", 1)<350)
          if(me->query_skill("tianmo-gong", 1) < 350)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ��������ħ������\n");  


      if(me->query_skill_mapped("parry")!="dali-shenmofu")
        return notify_fail("����мܲ���������ʹ�á���ħ������\n");

      if( (int)me->query("max_neili") < 5000 )
        return notify_fail("�������̫��������ʹ�á���ħ������\n");
      
      if( (int)me->query("neili") < 1000)
        return notify_fail("�������̫���ˣ��޷�ʹ�ó�����ħ������\n");   
      if( me->query_temp("dlf/shenmo"))
        return notify_fail("������ʹ�á���ħ������\n");                                                                             
      message_vision(HIY"\n$N�ڹ���ת����������𣬰��̴�����ħ������ħ��������������ת��Ϣ��������ħ������$N����ȫ������������������\n"NOR, me,target);
      if (weapon)
         message_vision(YEL"\n$N��������ע�����е�"+weapon->query("name")+YEL"�У�"+weapon->query("name")+YEL"����������һ������������\n"NOR, me);

	  me->add("neili", - 500);
      me->add("jingli", -50);      
      if (userp(me))
      {
		  lvl = lvl /3;
      } else lvl=lvl/8;
      if (me->query_skill_mapped("force")=="xixing-dafa"&&me->query_skill("xixing-dafa",1)>450)
      {
		  message_vision(BLU"$N���Ǵ󷨾�������������"+weapon->query("name")+BLU"�������ƣ�\n"NOR,me);
		  lvl=lvl+lvl1/6;
      }
	  me->add_temp("apply/strength", lvl /10);
	  
me->add_temp("apply/attack", lvl/2 );
	  
me->add_temp("apply/damage", lvl/3 );

	  me->add_temp("apply/axe", lvl/2 );

	  me->set_temp("dlf/shenmo", lvl);
	  
      //COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
   /*   if (present(target,environment(me)) && me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);*/
     call_out("remove_effect", 1, me, weapon, lvl);     
     /*
	 if (userp(me)&&!userp(target))
	  {
		 target>add_temp("apply/attack", -lvl);
	     target->add_temp("apply/damage", -lvl );
	  }*/
     if (me->query_skill("dali-shenmofu",1)<350)
      {
		   me->start_busy(1);
		   me->start_perform(2,"����ħ����");
      }
	 if (me->query_skill("dali-shenmofu",1)<450)
      {
		   me->start_perform(1,"����ħ����");
      }      
      return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(!me->is_fighting()
         || !weapon
         || me->query_skill_mapped("axe") != "dali-shenmofu"
         || me->query_skill_mapped("parry") != "dali-shenmofu"
         || count < 1 ){
          i = me->query_temp("dlf/shenmo");
          me->add_temp("apply/axe", -i/2);
          me->add_temp("apply/damage", -i/3);
		  me->add_temp("apply/attack", -i/2);
          me->add_temp("apply/strength", -i/10);
          me->delete_temp("dlf/shenmo");
	      message_vision(HIY"\n$N�����Ѵ�ƿ������ʱ������й����æ�������⣬ѹ�Ʒ��ڲ��ѵ���Ѫ��\n"NOR, me);
		 if (weapon)
		    message_vision(HIY"\n$Nһ�ס�������ħ����ʹ�꣬����"NOR+weapon->name()+HIY"�ϵĹ�â����Ҳ��ʧ�ˡ�\n"NOR, me);
          return;
        }
        else {
         // me->start_perform(1,"��������ħ����");
          call_out("remove_effect", 1, me, weapon, count -2);
        }
}


int help(object me)
{
        write(RED"\n������ħ��֮����ħ������"NOR"\n\n");
        write(@HELP 
	������ħ��֮��������ħ��������������ʮ���ϴ�����ħ���ɾ�����
	ǿ����ʹȫ������һ����ʱ���ڱ�����ͷ������������뵱��ʮ��
	���ϱ�����ɽʯ�ڣ������Դ˴�ͷһ·��ɽ��·���н�ʮ���ף�����
	��ʣ���һ��ͷ������ʯ�ڣ���ϧ���������������ɼ�����ħ����������
	ע�⣺350��С�ɣ�450�����ɡ�
	Ҫ��  
		��ǰ���� 1000 ���ϣ�
		������� 5000 ���ϣ�
		��ǰ���� 500 ���ϣ�
		���������ȼ� 350 ���ϣ�
		������ħ���ȼ� 350 ���ϣ�
		��������Ϊ������ħ������
		�����м�Ϊ������ħ������
		�����ڹ�Ϊ��ħ�������Ǵ󷨡�
HELP
        );
        return 1;
}