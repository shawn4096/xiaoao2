//qujian.c
//by spiderii@ty����SJ��д
//by sohu ���±�д�������վ��ں�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon, weapon2;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("��ȥ��ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 150 ) 
                return notify_fail("�����ʬ������δ���ɣ��޷�ʹ�á�ȥ�����־���\n");

    if((int)me->query_skill("sword", 1) < 150 )
                return notify_fail("��Ļ�������������죬����ʹ�á�ȥ�����־���\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("�����ʹ�ý���������ʹ����ȥ�����־�!\n");

    if(!objectp(weapon2 = target->query_temp("weapon"))||weapon2->query("skill_type")!="sword")
                return notify_fail("�Է����ڲ�û��ʹ�ý�����������ʹ�ò��ˡ�ȥ�����־�!\n");

  // if(me->query_skill_mapped("parry") != "tangshi-jianfa")
    //       return notify_fail("��ȥ�����־���Ҫʹ����ʬ�����м�һ�ез�������\n"); 

   if((int)me->query("max_neili") < 2500 )
           return notify_fail("��������Ϊ��ǳ��ʹ������ȥ�����־���\n");  

   if( (int)me->query("neili") < 500 )
           return notify_fail("����������̫����ʹ������ȥ�����־���\n");


    msg =  HIW"$N��Хһ������ֱ���еı��У������ǽ����ġ�ȥ�����־�˳�ƴ�����$n�ı�����\n"NOR;
	message_vision(msg, me, target);
    me->set_temp("tangshi/qujian",1);
    if(random(2))
		   message_vision(HIC"���ţ�$N����"+weapon->name()+HIC"��ƽ��"+weapon2->name()+HIC"��$N��"+weapon->name()+HIR"��ת����Ȧ�ӡ�\n"NOR, me,target);
    else 
		   message_vision(HIY"���ţ�$N"+weapon->name()+HIY"һ�죬��ס"+weapon2->name()+HIY"��"+weapon->name()+HIY"���н�ˮ����$n����ȫ�������෴�ķ���\n"NOR, me,target);
     if( random( (int)me->query("combat_exp",1))> target->query("combat_exp") /2 
		 || random(me->query_int())> target->query_int()/2)
	  {
	     msg =HIY"ֻ����һ���������֮�������$p��"+weapon2->name()+HIY"��$P���е�$Wһ��һ����ԶԶ�ط��˿�ȥ��\n" NOR;
         message_vision(msg, me, target);
	     weapon2->move(environment(me));
	/*
		if (me->query("quest/shenzhao/laozu"))
         {
			msg = HIR"$N����������վ�����ʫ�����ںϣ���ʹ������������ʽ˳�ƶ����������Ļ���$n��\n" NOR;
            message_vision(msg, me, target);
	  	    me->add_temp("apply/attack", lvl/3);	
	        me->add_temp("apply/damage", lvl/3);
            me->add_temp("apply/sword", lvl/3);
		 if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIC  "��ǰ���¹⣬\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
		 if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIR  "���ǵ���˪��\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
	     if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIG  "��ͷ�����£�\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
          if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIY  "��ͷ˼���磡\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }  
         me->add_temp("apply/attack", -lvl/3);	
	     me->add_temp("apply/damage", -lvl/3);
		 me->add_temp("apply/sword", -lvl)/3;
	    } */ 
      } else {
         msg += "����$p������$P����ͼ����û���ϵ���\n" NOR;
         me->start_busy(1);
         message_vision(msg, me, target);
     }
	
	//me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	if (me->query("shenzhao")<3)
		me->start_perform(1, "��ȥ��ʽ��");
	return 1;
}

string perform_name(){ return HIY"ȥ��ʽ"NOR; }

int help(object me)
{
        write(HIW"\n��ʬ����֮��ȥ��ʽ����"NOR"\n\n");
        write(@HELP
	 ����ʬ���������ǽ�ӹʮ�Ĳ����������С����Ǿ����������书
	��Ҫ���ɷ����ɫ�������Ὥ���ݳ������е�һ�ֽ�������Ϊ��
	���˶�Ŀ���ѡ���ʫ����������ﴫΪ����ʬ�����������е���
	����������Ҳ�ĳ�г���ֻ�ͬ�������֣������Ѹý�������С
	˵�����˹����ơ��ɴˣ��Զﴫ��,ʵ�˻�����֮�����
	ȥ��ʽ����Դ���Դ�ƽָ�������м�Ϊ�����һ�У����ý���
	Ӱ�죬��Ѹ�ײ����ڶ�֮ʽ����Է��Ľ���������⿪���վ�
	�����κ�������������ͷš�
	ע�⣺���н��Խ���������Ӱ�졣
	
	ָ�perform sword.qujian

Ҫ��
	��ǰ���� 2500 ���ϣ�
	������� 500 ���ϣ�
	��ʬ�����ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	�⿪���վ�����question�����з�Ծ

HELP
        );
        return 1;
}
