// jindao-heijian �������
/*
    ���������ϲ�����������ӽ��������������ֵ�ȴͬʱʹ�ˡ������롱������ʽ��
�𡱡���������ء�������Ʒ��̨�����С������ֽ���Ʈ����ת���Ľ���������֮�С����
��������������С��Ůȴ�����Ļţ���ӽ�ȥ�������棬��������ɷ�������������
��֪��������������ˣ�ʹһ��ȫ�潣���еġ������仨����ƽ�������������ָ������
*/
#include <ansi.h>
string perform_name(){ return HBBLU"�������"NOR; }

inherit F_DBASE;
inherit F_SSERVER;
void attack_ob(object me, object target,object weapon,object weapon2);
int perform(object me, object target)
{
		int i;
		object *inv;
		object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("�𵶺ڽ�ȫƾһ������������ת�𵶺ڽ�����ת����ʽ��\n");
		}

        if( me->query_dex() < 70 )
                return notify_fail("�������������������㣬����ʹ�õ�����ӣ�\n");
        
        if( me->query_skill("dodge",1) < 500 )
                return notify_fail("���������Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword",1) < 500 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ�õ�����ӣ�\n");
        if( me->query_skill("blade",1) < 500 )
                return notify_fail("�㵶��δ��¯����֮����������ʹ�õ�����ӣ�\n");
        if( me->query_skill("jindao-heijian",1) < 500 )
                return notify_fail("��𵶺ڽ�δ��¯����֮����������ʹ�ý�Ȧ��նԷ���\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�õ�����ӣ�\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�õ�����ӣ�\n");

        if (!weapon)
                return notify_fail("�������޽�����ʹ�õ�����ӣ���\n");
       // if (me->query_temp("jdhj/luanren",1))
         //       return notify_fail("������ʹ�����������з��޷��ٵ�����ӣ�\n");

        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("������Ƚ��ڽ����໥��ϡ�\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
		if (weapon->query("skill_type") == "blade") {
        	   if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   i = 3;
			   break;
		   }
		}
		if (weapon->query("skill_type") == "sword") {
   	        if( inv[i]->query("skill_type") == "blade" ) 
		   {
			   weapon2 = inv[i];
			   i = 2;
			   break;
		   }
		}
       }
		if (!objectp(weapon2)) return notify_fail("��ֻ��һ�ֱ������뵶����ӣ�\n");
			
			
		message_vision(HBCYN+HIW"$N���һ����������ӣ���ʱ�书��ʽ����޷����������ͣ��󿪴�ϣ��������ܣ���ˮ��©��\n"NOR, me, target);
		me->add_temp("apply/attack", me->query_skill("jindao-heijian",1)/8);
		me->add_temp("apply/damage", me->query_skill("jindao-heijian",1)/8);

		if (weapon->query("skill_type")=="blade") {
			weapon->unequip();
			weapon2->wield();
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,3);
			weapon2->unequip();
			weapon->wield();
		} else if (weapon->query("skill_type")=="sword") {
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,3);
		}
        me->add_temp("apply/attack", -me->query_skill("jindao-heijian",1)/8);
		me->add_temp("apply/damage", -me->query_skill("jindao-heijian",1)/8);

        me->add("neili", -1500);
        me->add("jingli", -500);
	//�⿪��ǧ������󵶽������������
	if (me->query("quest/tz/jdhj/daojian/pass")&&objectp(target))
		call_out("attack_ob",1,me,target,weapon,weapon2);
	me->start_perform(6,"�������");
    return 1;
}
void attack_ob(object me, object target,object weapon,object weapon2)
{
	int i;
	if (!me) return ;
	if (!weapon2||!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}
	message_vision(HIR"\n������$N����ͣ�����ֵ�ͬʱʹ�ˡ������롱������ʽ�ֽ𡱡���������ء�������Ʒ��̨�����С�\n"+
"�����ֽ���Ʈ����ת���Ľ���������֮�С�\n"+"$n������������ӽ�ȥ�������棬��"+
weapon->name()+weapon2->name()+HIR"����ɷ����������\n"NOR,me,target);
    
	me->add_temp("apply/attack", me->query_skill("jindao-heijian",1)/8);
	me->add_temp("apply/damage", me->query_skill("jindao-heijian",1)/8);

	if (weapon->query("skill_type")=="blade") {
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
	} else if (weapon->query("skill_type")=="sword") {
		weapon->unequip();
		weapon2->wield();
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		weapon2->unequip();
		weapon->wield();
	}
    me->add_temp("apply/attack", -me->query_skill("jindao-heijian",1)/8);
	me->add_temp("apply/damage", -me->query_skill("jindao-heijian",1)/8);

	return;
}


int help(object me)
{
        write(HIC"\n�𵶺ڽ�"+HBBLU"��������ӡ�"NOR"\n");
        write(@HELP
	�𵶺ڽ������˹ȹ����ƵļҴ��书�����ֽ����ֺڽ�
	������������֮�������ڽ��˴�����֮Ч�������Ը�
	��Ϊ�����ڽ�������Ϊ����������Ϻ�����˷���ʤ����
	������������ǧ�߼޸������ƺ󣬶������书ȥ���澫��
	�����ơ����ﵽ¯����֮�����������似��ȱ��Ҳ����
	Ȼ��������ǧ�����ԡ��������ơ�����������ȱ�㡣
	���Ƶ��ӿ���ƾ����ݽ����ǧ�߲������ǧ�ߵ�ָ�㣬
	����Ź��򽫸��ϲ�¥��
	�����Ľ�һ�𷢳�����ʽ���������м��ӵ��ƣ���������
	������ʽ���˵��Ǽ�Ϊ��������ʽ��
		
	ָ�perform sword(blade).daojian

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�𵶺ڽ��ȼ� 500 ���ϣ�
	�����Ṧ�ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�	
	�������ȼ� 70 ���ϣ�	
	��������Ϊ�𵶺ڽ���
	��������Ϊ�𵶺ڽ���
	�����м�Ϊ�𵶺ڽ���
	�����ڹ����ޣ�
	�ֳֵ�(��)�����������ϴ���Ӧ����������

HELP
        );
        return 1;
}
