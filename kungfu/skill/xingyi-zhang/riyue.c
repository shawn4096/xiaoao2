// riyue ����ͬ��
// by leontt
// Modify by leontt 1/05/2000
// By Spiderii fix bug

#include <ansi.h>
#include <combat.h>

string perform_name(){ return HIC"����ͬ��"NOR; }

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) ||!living(target))
                return notify_fail("������ͬ�ԡ�ֻ����ս����ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("ʹ�á�����ͬ�ԡ�ʱ������֣�\n");
        
        if( (int)me->query_skill("xingyi-zhang", 1) < 200 )
                return notify_fail("��������Ʋ�����죬ʹ����������ͬ�ԡ�������\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 200 )
                return notify_fail("�����Ԫ���ȼ�����������ʹ�á�����ͬ�ԡ���\n");

        //if (me->query_skill_mapped("force") != "shenyuan-gong")
                //return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á�����ͬ�ԡ����й�����\n");  
                        
        if( (int)me->query_int() < 30 )
                return notify_fail("������Ի�ʹ����������ͬ�ԡ�������\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
         || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("�������޷�ʹ�á�����ͬ�ԡ����й�����\n");  
        if (me->query_skill_mapped("parry") != "xingyi-zhang"
         && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("�������мܲ��ԣ��޷�ʹ�á�����ͬ�ԡ����й�����\n");                                                                                       
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("������������Ϊ̫��������ʹ�á�����ͬ�ԡ���\n");

        if( (int)me->query("neili") < 1000 )
                return notify_fail("��Ŀǰ����̫�٣�����ʹ�á�����ͬ�ԡ���\n");

        if( (int)me->query("jingli") < 200 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á�����ͬ�ԡ���\n");

        if( me->query_temp("mr_riyue"))
                return notify_fail("���ʹ�꡸����ͬ�ԡ���������ת�������޷��ٴ�ʹ�ã�\n");
                
        tell_object(me,MAG"\n��˫��һ�꣬��˫��֮���γ�һ��ҫ�۵ġ�"HIW"����"MAG"��,״���ǹ�©����\n" NOR,me, target);
        message_vision(HIY"�����������Ԫ���ӳ��£�Խ��Խ��ʵ���·�һ�������һ������$n����\n"NOR,me,target);
        
		i = (int)me->query_skill("xingyi-zhang", 1);
		if (me->query_temp("sy/shenyuan"))
		{
			i=i+me->query_skill("shenyuan-gong",1)/5;
		}
        me->add_temp("apply/attack", i/3);
        me->add_temp("apply/strike", i/4);
        //me->add_temp("apply/strength",i/15);
		me->add_temp("apply/damage", i/5);
        me->set_temp("mr_riyue", 4);
        
        COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
        if (random(me->query_str())>target->query_dex()/2)
        {
			message_vision(HIC"$n�о�$N���������죬������������Լ����β��ȣ�\n"NOR,me,target);
			if (!userp(target))
				target->add_busy(3);
			else target->add_busy(1);
        }
		me->add("neili", -100);
        if(me->is_fighting(target)){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
               // me->add("neili", -100);
        }
        if(me->is_fighting(target) && me->query_skill("xingyi-zhang", 1) >= 150){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
              //  me->add("neili", -100);
        }
        if(me->is_fighting(target) && me->query_skill("xingyi-zhang", 1) >= 200){
                COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
                //me->add("neili", -100);
        }
                  
        message_vision(YEL "\n$Nһʽ������ͬ�ԡ����ӵ����쾡�£�˫��һ�֣��������У����ı�����\n" NOR,me, target);
        me->add_temp("apply/attack", -i/3);
        me->add_temp("apply/strike", -i/4);
        //me->add_temp("apply/strength",-i/15);
		me->add_temp("apply/damage", -i/5);
        me->delete_temp("mr_riyue");
        me->start_busy(1+random(2));
        me->start_perform( 4,"������ͬ�ԡ�");
        me->add("jingli", -100);
        me->add("neili", -200);
        if(me->query("neili") < 0) me->set("neili", 0);
        return 1;
}


int help(object me)
{
        write(HIC"\n�����Ʒ�֮"+HIM+"������ͬ�ԡ�"NOR"\n\n");
        write(@HELP
	����Ľ�ݸ��ڽ�������ʱ����ʹ�õ���ʽ����������
	��������˲������ȫ���������ǹ�Ϊ��������Ԫ��
	Ϊ������Ȼ�䱬��һ��ǿ�����������е������¡�

	ָ�perform strike.riyue

Ҫ��  
	��ǰ���� 1000 ���ϣ�
	������� 2500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	��Ԫ���ȼ� 200 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƻ�ת���ƣ�
	����Ҫ�� 30 ���ϡ�
HELP
        );
        return 1;
}
