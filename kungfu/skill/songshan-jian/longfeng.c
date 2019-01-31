// longxiang.c ��������
// by xiaoyao 4/19/2k

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl, j, focus;
        object weapon;

	lvl = me->query_skill("songshan-jian", 1) + me->query_skill("hanbing-zhenqi", 1) + me->query_skill("sword", 1) ;
	focus = me->query_temp("ss/focus") + 1;
	weapon = me->query_temp("weapon");

	if (!target ) target = offensive_target(me);

	if (!objectp(target) 
	|| !me->is_fighting(target) )
		return notify_fail("���������衹ֻ����ս���жԶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("�����ʹ�ý�����ʹ�á��������衹��\n");

	if (me->query_skill("songshan-jian", 1) < 450 )
		return notify_fail("�����ɽ������������죬ʹ�������������衹������\n");

	if (me->query_skill("hanbing-zhenqi", 1) < 450 )
		return notify_fail("��ĺ���������������죬ʹ�������������衹������\n");

	if ( me->query_skill("force") < 450 )
		return notify_fail("����ڹ��ȼ�������ʹ�������������衹������\n");

	if ( me->query_str(1) < 35)
		return notify_fail("�������������ǿ����ʹ�������������衹������\n");
	if ( me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian")
		return notify_fail("�����ڵ�״̬ʹ�������������衹������\n");

	if ( me->query_temp("ss_lf"))
		return notify_fail("������ʹ�á��������衹�أ�\n");

	if ( me->query("max_neili") < 2500 )
		return notify_fail("����������̫����ʹ�������������衹��\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("����������̫����ʹ�������������衹��\n");

	if ( me->query("jingli") < 1000 )
		return notify_fail("�����ھ���̫����ʹ�������������衹��\n");

	msg = HIR"\n$N�������Ĵָ��ʳָ����ָ������ָ����ס�˽��⣬����һ�ɣ�"+weapon->name()+HIR"ͻȻ���𣬽�����ǰ����ס�ػζ���\nͻȻ$N����$n���ٹ������˽���һ������һ�������ڿն����԰���к��������������ֱ��ٿ������$n��\n\n"NOR;
	message_vision(msg, me, target);
	if(me->query_temp("ss/hb"))
			message_vision(HIB"\n$N�����������������ӵ����쾡�£����ܺ����ʢ��\n" NOR,me,target);

	me->set_temp("ss_lf", 1);

	if ( focus > 15) focus = 15;

	j = lvl / 15;                          //�ȼ���1/5  

	if ( lvl > 350 )
		j = to_int( lvl/12.0 * lvl/ 350.0);  //�ȼ���1/4�ӷ�Ծ����
		j += focus * 3;                      //����������Ч��������΢���� 
	
	if(target->is_busy()) j += j / 4;      //��PK�Ĳ������� 
		
    if(!userp(me)) j = j / 4;          //��������֮�µ���Ҳ���Ŷ��

		
	
	me->add_temp("apply/attack", j );
	me->add_temp("apply/sword",  j/2 );
	me->add_temp("apply/strength", j/20 );


    if(me->query_temp("ss/hb"))
	{
	   me->add_temp("apply/damage", j / 4 );  //��ʱ���־���,���������� j = ((�ȼ�*5/16 )*(��Ծϵ��) +random(45)) * 5/4  ,Լ1/3ǿ 
	   me->set_temp("longfeng/hanbing",1);
	}
	//me->add_temp("apply/damage", j /4);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//me->add_temp("apply/damage", -j/4);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->unequip();
    COMBAT_D->do_attack(me, target, 0, 3);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->wield();
	//me->add_temp("apply/damage", j /4);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lvl<350)?1:3);
	//me->add_temp("apply/damage", -j/4);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->unequip();
    COMBAT_D->do_attack(me, target, 0, 3);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->wield();

	//��Ծ����1hit 
	if ( lvl > 450 ){
		me->add_temp("apply/damage", j/4);
		message_vision(HIY"$N����Ծ�𣬰���������ת�ۣ�������$n����һ����������Ϊ���ͣ�������ɽ������������!\n"NOR,me,target);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage", -j/4);
	}
	
	if(me->query_temp("longfeng/hanbing"))
	{
	   me->add_temp("apply/damage", -j /4);
	   me->delete_temp("longfeng/hanbing");
	}
	me->add_temp("apply/attack", -j );
	me->add_temp("apply/sword",  -j/2 );
    me->add_temp("apply/strength",   -j /20);

	me->delete_temp("ss_lf");
	me->add("neili", -500);
	me->add("jingli", -200);
	me->start_busy(random(2));
    me->start_perform(4+random(2),HIR"���������衹"NOR);
	return 1;
}

string perform_name(){ return HIR"��������"NOR; }

int help(object me)
{
        write(HIR"\n��ɽ����֮���������衹��"NOR"\n\n");
        write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ��ܹ�ʮ��·���̿����Ľ���
	Ӧ�о��С���������������ħ��ʮ�������Ȼ�ս��ɽ����������
	�ĺ������˴��������ɽ�������ྪ�����������ɸ��ֶ����š�
	��ɽ�������������Ἧ���ɲд�����ϣ����������ǵõĽ��в�
	�۴־�������¼�����������һ�����ס�
	����������ʽ����ɽ�ɵľ���֮һ��ÿһ�ж��̺�������������
	ɽ�����ļ������ʽ�������ǲд潣�����������һ�С�

	ָ�perform sword.longfeng

Ҫ��  
	��ǰ�������� 1500 ���ϣ�
	����������� 2500 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ɽ�����ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	��Ч�ڹ��ȼ� 450 ���ϣ�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	�����书�������ֱֳ�����
HELP
        );
        return 1;
}
