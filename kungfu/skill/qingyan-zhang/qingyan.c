//by snowyu
//updated by lara 2001/12/07
//����������
/*
   ����������վ�������������������б����쬵�һ�����죬���һ֦������
�Ʒ���𣬸����������б��������һ֦����ȻϨ������������ƣ���Ϩ����
֦�����۹�ʼ����ǰ������ȴ��������ˮ������֮����
ľ���循�������⡭�����ǡ����������ơ���������ôҲ�᣿��
*/
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	string weapon;
	int strike, force, amount; 
	strike = me->query_skill("strike",1);
	force  = me->query_skill("force",1);
	amount = (strike+force)/4;
	
    if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	if ( me->query_temp("weapon") )
                return notify_fail("�������̱�����ַ���ʩչ��\n");

   // if( me->query_temp("piaomiao") ) 
			//	return notify_fail(HIW "������ʹ������Ʈ�죡\n"); 
	
  	if( me->query_skill_mapped("strike") != "qingyan-zhang" )
                return notify_fail("�����ò�������������!");

	if( me->query_skill_prepared("strike") != "qingyan-zhang" )
                return notify_fail("��������������������!");
          
    //if( me->query_skill_prepared("cuff") != "jinyu-quan" )
      //          return notify_fail("����������ͽ���ȭ���ʹ��!");

	if( me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("�������ڹ��ķ�����,�޷�ʩչ�������̣�\n");

	if( me->query_skill("kurong-changong",1) < 350 &&
            me->query_skill("qiantian-yiyang",1) < 350)
				return notify_fail("����ڹ���Ϊ�������޷�ʩչ�������̣�\n");
	if( me->query_skill("strike",1) < 350 )
				return notify_fail("������Ʒ������������޷�ʩչ�������̣�\n");
	if( me->query_skill("qingyan-zhang",1) < 350 )
				return notify_fail("�����������ƹ����������޷�ʩչ�������̣�\n");
		
	if (me->query("dali/betrayer")>=1)
				return notify_fail("�����ѳ�����������˼ʹ�ô����ѧ��\n");   
	
	//if (!me->query("can_perform/qingyan-zhang/qingyan") )
	  //      return notify_fail("��δ��������ָ�㣬����ʹ���������̣���\n");
	   
	if( (int)me->query("max_neili") <15000)
				return notify_fail("���������Ϊ���㣬�޷�ʩչ�������̣�\n");
	        
	if( me->query("neili") < 1500 )
				return notify_fail("�����������ʹ���������̣�\n");

    if( me->query("jingli") <1000 )
				return notify_fail("��ľ�������ʹ���������̣�\n");
    if( me->query_temp("qyz/qingyan") )
				return notify_fail("������ʹ���������̣�\n");  
               

    message_vision(MAG "$NͻȻ������Խ�𣬺����������б���������������б����˲����$n��������,����ȴ��������ˮ������֮��!\n\n" NOR, me, target);
    message_vision(YEL "�����ƴ�������������ֵ����̣���$n�������������������������е�"HIM"���������̡�"YEL"����!\n\n" NOR, me, target);

	if (userp(target))
    {
		amount = amount/2; 
    }   
        
	me->add_temp("apply/damage", amount/3); //����һ���˺�
	me->add_temp("apply/attack", amount); //����һ�빥��
	me->set_temp("qyz/qingyan",5);	
   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
    if (me->is_fighting()&&objectp(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		
        me->add("neili", - amount+random(80));
        me->add("jingli",-amount+random(40));

	me->start_busy(1 + random(2));

    me->add_temp("apply/damage", -amount/3);
	me->add_temp("apply/attack", -amount);
	me->start_perform(4,"��������");
	me->delete_temp("qyz/qingyan");	
	return 1;
}
string perform_name() {return BLU"��������"NOR;}

int help(object me)
{
        write(BLU"\n����������֮���������̡���"NOR"\n\n");
        write(@HELP
	�������������Ǵ�����Ͼ���������������������������
	�������𽭺������Ҵ����Լ������ˡ���״�����̣�����
	�����Ƶ���ʵ���ۻ�������������Ʒ��з��������˷�
	��ʤ����
	
ָ�perform strike.qingyan

Ҫ��
	��ǰ���� 1000  ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 1000  ���ϣ�
	�����Ʒ� 350   ����
	�������� 350   ����
	Ǭ��һ�� 350   ����
	�����Ʒ�Ϊ���������ƣ�
	�����м�Ϊ���������ƣ�
	���Ʒ�Ϊ���������ƣ�
	�ҿ��֡�

HELP
        );
        return 1;
}
