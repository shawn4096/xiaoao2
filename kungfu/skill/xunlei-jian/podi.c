// xunlei-jian perform
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int lvl, j;
        object weapon;
        lvl = me->query_skill("xunlei-jian", 1);
        j = 1;
        if (lvl>350) j = 3;
		
		if(!userp(me)) lvl = lvl /3;

			weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        
		if( !target || !me->is_fighting(target) )
                return notify_fail("��Ѹ���Ƶء�ֻ����ս���жԶ���ʹ�á�\n");
                
        if (!weapon || weapon->query("skill_type") != "sword"
                         || me->query_skill_mapped("sword") != "xunlei-jian")
                return notify_fail("�������ʹ�ý�ʱ����ʹ����Ѹ���Ƶء�\n");
                         
		if( (int)me->query_skill("kunlun-zhang", 1) < 300 )
			return notify_fail("��������Ƶȼ�����������ʹ��Ѹ���Ƶأ�\n"); 
      
		if (me->query_skill_prepared("strike") != "kunlun-zhang"
            || me->query_skill_mapped("strike") != "kunlun-zhang")
			return notify_fail("��û���������ƣ������޷�ʹ��Ѹ���Ƶؽ��й�����\n");             
      
        if(me->query_skill("xunlei-jian", 1) < 300 )
                return notify_fail("���Ѹ�׽���������죬ʹ������Ѹ���Ƶء���\n");
		 if(me->query_dex() < 60 )
                return notify_fail("��ĺ�������������죬ʹ������Ѹ���Ƶء���\n");
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("�������������̫����ʹ������Ѹ���Ƶء���\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ������Ѹ���Ƶء���\n");



        msg = HIY"\n$N���ζ�������һֻ����Ծ����У���$n��֪����֮�ʣ��ڿ�����Ȼת����Ȼ���أ��ó�һƬ���⣡\n"
			+HIB"\n\n$Nʹ��������Ѹ��ʮ����֮"HIW"��Ѹ���Ƶء�"HIB"��������ʱһƬ�׹�ֱ��ǰ��ȥ��\n\n"NOR;
        message_vision(msg, me, target);
		if (lvl>350 && me->query("quest/kl/xlj/wuxue/pass"))
		{
			lvl=lvl+me->query_skill("force", 1)/5;
		}
		me->set_temp("xlj/podi",1);
		me->add("neili", -550); 
		me->add("jingli", -200);      
		//me->add_temp("apply/strength", lvl /10 );
		me->add_temp("apply/sword", lvl/4);
		//me->add_temp("apply/parry", lvl/3);
		me->add_temp("apply/damage", lvl /5 );
		me->add_temp("apply/attack", lvl /3);
		 
		if( random(me->query_skill("xunlei-jian",1)) > (int)target->query_skill("parry",1) *2/3)
		{ 
			message_vision(HIC"$nΪ����Ѥ�õĽ�������һʱ���飬��ʱ��Щ��æ���ҡ�\n"NOR,me,target);
			target->add_busy(1+random(2));
		}

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
		if (me->is_fighting(target))
			 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
			weapon->unequip(); 
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j); 
			weapon->wield();
		if (me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
			
      
		//me->add_temp("apply/strength", -lvl /10 );
		me->add_temp("apply/attack", -lvl /3);
		//me->add_temp("apply/parry", -lvl/3);

		me->add_temp("apply/sword", -lvl/4 );
		me->add_temp("apply/damage", -lvl /5 );

		me->start_busy(random(1)+1);
		me->delete_temp("xlj/podi");
		me->start_perform(3+random(2),"��Ѹ���Ƶء�");
		return 1;
}
string perform_name(){ return HIY"Ѹ���Ƶ�"NOR; }
int help(object me)
{
	write(HIY"\nѸ�׽���֮��Ѹ���Ƶء���"NOR"\n\n");
	write(@HELP
	Ѹ�׽��������صĳ����������ɺ����������ر仯���á�
	������ɽ��ߵغ����ױ������Ķ࣬�ɴ����򽣷��Ŀ��
	���⣬��Ҫ�������֧��,�����̤ѩ�����������绢��
	������������
	Ѹ���Ƶأ���Ѹ�׽��ĸ߼�������ģ���׵�������ʱ��
	������Ѥ�õĽ����к�Ȼ���ƣ��԰�����ɰ�Ƶ������ش�
	�Է�����Է�����ʤ���������ٶ��ּ�Ϊ�����ƻ�����
	ע�⣺350����Ѹ�׽�С�ɡ�
	
	ָ�perform sword.podi

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	Ѹ�׽����ȼ� 300  ���ϣ�
	�����Ʒ��ȼ� 300  ���ϣ�
	��Ч�ȷ��ȼ� 60   ���ϣ�
	��������ΪѸ�׽�����
	�����ұ������Ʒ���
	�ڹ����ޣ�
	�������ý���������
	350�����Ծ,����������
HELP
);
return 1;
}
