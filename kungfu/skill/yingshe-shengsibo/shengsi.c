// huashan_shengsi.c

// yingshe-shengsibo perform ӥ�������� 

//by daidai 2005-10-07



#include <ansi.h>

#include <combat.h>



inherit F_SSERVER;



void remove_effect(object me);



string perform_name(){ return HIR"ӥ"HIB"��"HIC"������"NOR; }



int perform(object me, object target)
{
    int exp,exp1,busy,lvl,lvl1;
      if( !target ) target = offensive_target(me);
      if( !target || !me->is_fighting(target) )
           return notify_fail("��ӥ����������ֻ����ս���жԶ���ʹ�á�\n");        

      if( objectp(me->query_temp("weapon")) )
           return notify_fail("��������ʹ�á�ӥ������������\n");     

      if( (int)me->query_skill("yingshe-shengsibo",1) < 200 )
            return notify_fail("���ӥ��������������죬����ʹ�á�ӥ������������\n");
	  if( (int)me->query_skill("hand",1) < 200 )
            return notify_fail("��Ļ����ַ�������죬����ʹ�á�ӥ������������\n");
	  if( (int)me->query_skill("claw",1) < 200 )
            return notify_fail("��Ļ���צ��������죬����ʹ�á�ӥ������������\n");

      if( (int)me->query_str() < 35 )

           return notify_fail("��ı�������35������ʹ�á�ӥ������������\n");

      if( (int)me->query("max_neili") < 3500 )
            return notify_fail("�������̫��������ʹ�á�ӥ������������\n");

      if( (int)me->query("neili") < 350 )
            return notify_fail("�������̫���ˣ��޷�ʹ�ó���ӥ������������\n");   
      if (me->query_skill_prepared("hand") != "yingshe-shengsibo"
       && me->query_skill_prepared("claw") != "yingshe-shengsibo")
            return notify_fail("�������޷�ʹ�á�ӥ�������������й�����\n");                                         
     if( me->query_temp("huashan_shengsi"))
            return notify_fail("������ʹ��ӥ�������������⹥����ӥ������������\n");

     if (target->is_busy()) return notify_fail("�Է����Թ˲�Ͼ���ŵ������ɣ�\n");   

    message_vision( HIC"\n$NͻȻ����$n����������ʹ����ɽ������������ľ���������ʮ��·��ӥ������������\n"
	                      +"��ӥ��˫ʽ��ʩ����ӥ��ʸ֮�ˣ������鶯֮�ƣ���һʽ��ͬʱ�ֳ���Ѹ�ݺ����������֮��\n" NOR, me, target);
   
    message_vision( HIR"\n$N���ֳ�ӥצ״���ܡ��á�Ť������һ��ӥץ������ʹ�ó����뻯������似��\n" NOR, me, target);                                    
    exp=me->query("combat_exp");
    exp1=target->query("combat_exp");
    lvl=me->query_skill("claw");
    lvl1=target->query_skill("dodge");
    busy=3;
    busy=busy+random(lvl)/100;
    if(busy>8) busy=8;
    if( random(exp/100*lvl)>exp1/100*lvl1/4){
        message_vision( HIW"$nһ������$Nץס�ؽ�Ҫ��֮������ʱȫ����ľ���������á�\n"NOR, me, target);
        if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
        me->set_temp("huashan_shengsi",1);  
		//message_vision("�����һ��ʩչ����ӥ�������������һ�С�����ӥצ�֡���", me, target); 
		me->add("neili", -350); 
		target->start_busy(2+random(3));
        message_vision(HIC "$N���һ��ʩչ����ӥ�������������һ�С�����ӥצ�֡�ץ��$n���ؿڴ�Ѩ��\n" NOR, me,target);
        me->add_temp("apply/damage", me->query_skill("yingshe-shengsibo", 1)/6);
		me->add_temp("apply/attack", me->query_skill("yingshe-shengsibo", 1)/4);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), userp(me)?3:1);	  
		if (random(10))
		{
		  message_vision(HIM "$N˳����ʩչ��ӥ�����������������һ�С����߳���������ʽ�����������ʱ������\n" NOR, me,target);
		  me->add_temp("apply/hand", me->query_skill("yingshe-shengsibo", 1)/4);
		  target->add_busy(busy);		  
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
		  me->add_temp("apply/hand", -me->query_skill("yingshe-shengsibo", 1)/4);
		}
       	//me->start_busy(random(2));
        me->add_temp("apply/damage", -me->query_skill("yingshe-shengsibo", 1)/6);
		me->add_temp("apply/attack", -me->query_skill("yingshe-shengsibo", 1)/4);
        //call_out("remove_effect", me->query_skill("yingshe-shengsibo") / 10 + 2, me);
        me->delete_temp("huashan_shengsi");
        tell_object(me,MAG"\n����֪���ס�ӥ���������������Ķ࣬���ֶ��������ܶ�ʹ�������ĵ�ֹͣ��ʹ�á�"NOR);
        message_vision(CYN"\n$Nһ�ס�ӥ����������ʹ����ϣ����������˿�����\n"NOR, me);
      }
      else {
        message_vision( HIG"$nһ�����ݷɳ����⣬���ݵ��ӳ���$N�Ĺ�����Χ��\n"NOR, me, target);      
    // message_vision(msg, me, target);                    
        me->start_busy(2);
        me->add("neili", - 100);
        me->start_perform(3,"��ӥ����������");   
	 }
      return 1;

}

void remove_effect(object me)
{
    if (!me) return;
    me->add_temp("apply/damage", -me->query_skill("yingshe-shengsi", 1)/10);
	me->add_temp("apply/attack", -me->query_skill("yingshe-shengsi", 1)/4);
    me->delete_temp("huashan_shengsi");
    tell_object(me,MAG"\n����֪���ס�ӥ���������������Ķ࣬���ֶ��������ܶ�ʹ�������ĵ�ֹͣ��ʹ�á�"NOR);
    message_vision(CYN"\n$Nһ�ס�ӥ����������ʹ����ϣ����������˿�����\n"NOR, me);

}


int help(object me)
{
        write(HIY"\nӥ��������֮��ӥ������������"NOR"\n");
        write(@HELP
	ӥ����������������Դ�������������У�Ϊ��ɽ�ɽ���
	�����������Ѵ�������ȭ���������������ַ�ʹӥ��
	˫ʽȭ����������ʮ��·��������Χ��������ʱ����ɽ
	�ɵ�����������ͨ���Դ˼��������̽������޼ɡ�
	
	ָ��:perform hand.shengsi

Ҫ��
	������� 3500 ���ϣ�      
	��ǰ���� 500  ���ϣ�  
	ӥ���������ȼ� 200 ���ϣ�
	�����ַ��ĵȼ� 200 ���ϣ�
	����צ���ĵȼ� 200 ���ϣ�
	�������Ϊ     35  ����
	�����ұ�צ��Ϊӥ����������
	�����ұ��ַ�Ϊӥ����������
	�����м�Ϊӥ����������
	�����ޱ�����
                
HELP
        );
        return 1;
}


