//wuxiang.c 
// creat by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include <skill.h>
inherit F_SSERVER;

int perform(object me, object target)
{
      string msg;
      int improve,lvl,lvl2;

      if( !target ) target = offensive_target(me);
     
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
          return notify_fail("��Ҫ��˭ʹ�á�����١���\n");

        if( me->query("family/family_name")!="������" )
                return notify_fail("�㲻�����ֵ��ӣ������ʹ�����־�����\n");
  
		if( !me->query("wxjz/jueji") )
                return notify_fail("����Ȼ��˵�������ָ��������������ʹ�á�\n");
		if( me->query_skill("buddhism",1)<200 )
                return notify_fail("��𷨲��㣬����ʹ�ôȱ�Ϊ���������书��\n");
        if(me->query_condition("killer")>500)
                return notify_fail("�����ӷ�ɱ��̫���ˣ����Ѿ��޾��ˣ�һ�ղ���������ɱ����ˡ�\n");
        if(environment(me)->query("no_fight"))
                return notify_fail("���ﲻ�ܹ������ˡ�\n");
        if(target->query("combat_exp")<2000000)
                return notify_fail("������ô����ˣ��õ�����˷Ѿ�ô��\n");
                
        if( me->query("no_pk") && userp(target) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail("���Ѿ��˳���������������ʵʵ�İɡ�\n");

        if( target->query("no_pk") && userp(me) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail( target->name()+"�Ѿ��˳������ˣ������˴������˰ɣ�\n");
          
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("��������ʹ�á�����١���\n");
      
        if( (int)me->query_skill("wuxiang-zhi",1) < 550 )
               return notify_fail("��������ָ������죬����ʹ�á�����١���\n");
   
        if( (int)me->query_skill("yijin-jing",1) < 550 )
              return notify_fail("����׽�ڹ��ȼ�����������ʹ�á�����١���\n");  
      
        if( (int)me->query("max_neili") < 15000 )
              return notify_fail("����������̫��������ʹ�á�����١���\n");
      
        if( (int)me->query("neili") < 3000 )
              return notify_fail("�������̫���ˣ��޷�ʹ�ó�������١���\n");   
                                                                                 
        if (me->query_skill_prepared("finger") != "wuxiang-zhi"
            || me->query_skill_mapped("finger") != "wuxiang-zhi"
			|| me->query_skill_mapped("parry") != "wuxiang-zhi")
           return notify_fail("�������޷�ʹ�á�����١����й�����\n");                                                                                 
        if (!me->query("yjj/powerup"))
        {
			if( me->query_temp("slpfm/jgqbrz") )
                return notify_fail("������ʹ�����־�����"+me->query_temp("slpfm/jgqbrz")+"����\n");
            if( me->query_temp("slpfm/rytqys") )
                return notify_fail("������ʹ�����־�����"+me->query_temp("slpfm/rytqys")+"����\n");
            if( me->query_temp("slpfm/lzgyzc") )
                return notify_fail("������ʹ�����־�����"+me->query_temp("slpfm/lzgyzc")+"����\n");
        }
		
        if( target == me )
                return notify_fail("�Լ����Լ�����\n");

        if (target->is_corpse() || !target->is_character())
               return notify_fail("�ǲ��ǻ���Ү��\n");
        if(!living(target))
                return notify_fail("�Է��������ˣ����õ�����ô�Ѿ�ô��\n");

       if (!me->query("quest/sl/yjj/powerup"))
           {
            /*  me->set_temp("slpfm/lzgyzc","�����");
             me->set_temp("slpfm/jgqbrz","�����");
             me->set_temp("slpfm/rytqys","�����");*/
			 me->start_perform(5, "�����");
			 lvl=me->query_skill("wuxiang-zhi",1);
           }
		 else 
	     { 
			 lvl=me->query_skill("wuxiang-zhi",1)+me->query_skill("yijin-jing",1)/2;
			 me->start_perform(2,"�����");

		 }
         msg=HIW"$N��ȫ��������һָ������һԾ�������ָ�����������ڻ��ͨ��ʩչ��������١�����������"NOR; 
		 message_vision(msg, me, target);  
  /*    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
			||random(me->query_str())>target->query_dex()/2
			||random(me->query_int())>target->query_int()/2)
        {*/
       
		     me->add_temp("apply/attack",lvl);
             me->add_temp("apply/finger",lvl/3);
		     me->add_temp("apply/damage",lvl/3);
             me->set_temp("wxz_wuxiang", 6);
//��һ�У�����ʽ������
	         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	          me->add("neili", -80);
//�ڶ���	    
	    	if(me->is_fighting(target)){
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	    	   me->add("neili", -80);
     	     }
//������
		    if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 250){
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		      me->add("neili", -80);
	         }
//������
	        if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 350){
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		      me->add("neili", -100);
	         }
//������
	// 5th kick is type_super. cannot be done in normal fight.
	         if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 450) {
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		        me->add("neili", -150);
	          }
//������
             if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 550) {
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		       me->add("neili", -150);
	          }
			 

          	 me->add_temp("apply/attack",-lvl);
             me->add_temp("apply/finger",-lvl/3);
		     me->add_temp("apply/damage",-lvl/3);
      //  message_vision(msg, me, target);  
        me->add("neili", -800);
        me->delete_temp("wxz_wuxiang");
		me->start_perform(6, "�����");
		me->add_busy(3);
      return 1;
}

void remove_effect(object me, int improve)
{
        me->delete_temp("slpfm/lzgyzc");
        me->delete_temp("slpfm/rytqys");
        me->delete_temp("slpfm/jgqbrz");
}

string perform_name(){ return HIY"�����"NOR; }

int help(object me)
{
        write(HIR"\n�����ָ֮������١���"NOR"\n\n");
        write(@HELP 
	���Խ�ӹС˵�С������˲���������������ʮ������֮һ��
	Ψ������������ʦϰ�á������ָȫƾһ�ɴ����������ȷ�
	��������֮�˱ض�ȫ���������һ�㡣����Ϊ������ʥɮ
	�Ħ��ʩչ��������Ȼ�������ڣ�������ȴ�Ƿ���
		
	˵����������������ָ��һʽ����ʽ���������࣬�����
	������ʵ��Ϊ��������ʽ��
��
	perform finger.wuxiang

Ҫ��
	��ǰ���� 3000 ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 2500 ���ϣ�
	�����ָ 550 ���ϣ�
	�����ڹ� 550 ���ϣ�
	����ָ�� 550 ���ϣ�
	���ڷ� 200 ��
	����ָ��Ϊ�����ָ��
	�����м�Ϊ�����ָ��
	�����ڹ����ޡ�
HELP
        );
        return 1;
}