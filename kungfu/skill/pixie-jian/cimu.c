// ci.c �����Ŀ

#include <ansi.h>
string perform_name(){ return RED"�����Ŀ"NOR; }

inherit F_SSERVER;

void back(object target);

int perform(object me, object target)
{
        int skill;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( me->query("gender")!="����")
                return notify_fail("�����и�֮�ˣ�����ܶ��ñ�а�������⣿\n");
		
        if( (int)me->query_skill("pixie-jian", 1) < 350 )
                return notify_fail("��ı�а����������죬����ʹ�÷����Ŀ��\n");
		if( (int)me->query_skill("sword", 1) < 350 )
                return notify_fail("��ı�а����������죬����ʹ�÷����Ŀ��\n");
		if( (int)me->query("neili", 1) < 1000 )
				return notify_fail("�������������㣡\n");  
		if( (int)me->query("max_neili", 1) < 5000 )
				return notify_fail("��������Ϊ���㣡\n");  
        if( (int)me->query_dex() < 30  )
                return notify_fail("�����̫�ͣ�����ʹ�÷����Ŀ��\n");
       
        if (!weapon || !(weapon->id("needle"))
        || me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("�������޷�ʹ�÷����Ŀ��\n");

        if( (int)target->query_temp("cimu") ) 
                return notify_fail("���Ѿ��������ˣ�\n");
		if (   me->query_skill_mapped("sword") != "pixie-jian"
	          || me->query_skill_mapped("parry") != "pixie-jian"
	          || me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("�㲻ʹ�ñ�а����,���ʹ���ˡ������Ŀ����\n");       
        
		skill = (int)me->query_skill("pixie-jian", 1);                
        //skill = skill/15;

        me->add("neili", -350);
        me->add("jingli", -200);

        message_vision(RED"$Nһ����Ц������һ�ź��ư��۽�$n������ϸ�����$n˫Ŀ��\n"NOR, me, target);
        message_vision(RED"$nһ����æ˫�ۻ�ת���뻤ס˫�ۣ�\n"NOR, me, target);;

     if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 &&
       me->query_dex(1) > random((int)target->query_dex(1))) 
	{
         if (target->query_skill_mapped("sword") != "dugu-jiujian" 
             || target->query_skill("dugu-jiujian", 1) < 99) 
		{
                message_vision(HIR"\nֻ��$n�ҽ�һ����ֻ����˿ϸѪ��$n���������������Ѿ���$N����˫Ŀ�ˣ�\n"NOR, me, target);
                tell_object(target, HIY "��������Ȼ������˫�ۣ���ϸ�뻹�Ǵ����������Ƥ����������Ѿ�ģ�������ˣ�\n" NOR);
                target->set_temp("cimu", 1);
                target->add_temp("apply/attack", - 100);
                target->add_temp("apply/dodge", - 100);
                target->add_temp("apply/parry", 50);
                target->receive_damage("qi", skill,me);
                target->receive_wound("qi", (int)skill/2,me);
                target->kill_ob(me);
                target->set_temp("block_msg/all",1);
				if (objectp(target))
				    call_out("back", 3 + skill, target);
         }
         else { message_vision(HIR"\n$n�������ǣ����ֻ�ָΪ��Ҳ��$N����Ŀ���̣��������ܾ��˵Ĵ򷨡�\n"NOR, me, target);
                tell_object(target, HIR "�㵫�����ü��΢΢һʹ��֪���Լ���ü��Ϊ���廨�������У������ұܿ����۾�Ҫ����\n" NOR);
                target->receive_damage("qi", 100,me);
                target->receive_wound("qi", 40,me);
                target->kill_ob(me);
                me->start_busy(1+random(2));
               }
     } else {
                message_vision(HIY"$n��ͷ����һ������������㿪��$N��һ�С�\n"NOR, me, target);
                me->start_busy(3);
                target->kill_ob(me);
        }
      
        return 1;
}

void back(object target)
{
	if(!target) return;
        target->add_temp("apply/attack", 100);
        target->add_temp("apply/dodge", 100);
        target->add_temp("apply/parry", - 50);
        target->set_temp("block_msg/all", 0);
        if(living(target)) 
              tell_object(target, HIW "��������˫Ŀû�б��������ˣ����ֿ��Կ�����������\n" NOR);
        target->delete_temp("cimu");
}

int help(object me)
{
   write(WHT"\n��а������"RED"�����Ŀ"WHT"����"NOR"\n");
   write(@HELP
	��������˽�������Ҫ��һ��а����֯������ȫƾ���˺ö�
	���г����似�������������а�����������ν�����������
	�ľ��������������������ְ汾�������ڱ�а���������ɡ�
	���������ơ�
	�������Ŀ�����ֳ��廨�룬�ڶ��ַ���ʤ��֮�ʣ��Թ���
	����������Է��������Ϲ�Է�˫Ŀ����Ϊ������
    
	ָ�perform cimu

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 5000 ���ϣ�
	��а���� 350 ���ϣ�
	�������� 350 ���ϣ�
	������ 30  ���ϣ�
	����������а����
	�����мܱ�а����
	�����Ṧ��а����
	���ֳ�����������

HELP
   );
   return 1;
}
