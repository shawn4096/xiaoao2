//modify By Ziqing  Y2k
// Modified by snowman@SJ 05/12/2000

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HBGRN+HIW"����"NOR;}

int exert(object me, object target)
{

        int hits;

        if( !target ) target = offensive_target(me);

		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("�����Ĵ󷨡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
           
        if( (int)me->query_skill("dulong-dafa", 1) < 350 
        || (int)me->query_skill("shenlong-yaoli", 1) < 190 
        || (int)me->query_int() <=50 )
                return notify_fail("����Ϊ����������δ�����á����ġ���\n");
         if(!userp(me) )
                return notify_fail("��û�����ԣ�����һ��npc�����˰ɣ�\n");
        if( me->query_skill("force", 1) < 350 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");
     
        if( me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ���������á����ġ���\n");
        if( me->query("max_jingli") < 2500 )
                return notify_fail("����������Ϊ���������á����ġ���\n");
        if( me->query("neili") < 1000 )
                return notify_fail("��������������������������á����ġ���\n");

        if( me->query("jingli") < 500 )
                return notify_fail("��ľ������ޣ����������á����ġ���\n");
        if( target->query_temp("shexin"))
                return notify_fail("�Է��Ѿ��������Ĵ���");
        message_vision(HBBLU+HIW"$P��Ȼ�����﷢����˻~~~˻~~���Ĺ���������ͬʱ�����ֹ����������죬�й������֮Ч��\n" NOR, me , target);
        message_vision(HBBLU+HIW"$n����$Pÿ��һ�䣬���о���һ�ݣ����������˵���Ϊϣ��Ź֣�ǰ��δ�У�\n\n" NOR, me , target);
       
        if( target->query_temp("hmg/nizhuan")){ 
           	message_vision("���$Pֻ��$n��ʽ�������Ĵ��޷��ɹ���\n", me, target);
           	return 1;
        }
		//��󡹦ʧЧ
        if( target->query_temp("jiuyin/fast")){
           	message_vision("���$Pֻ��$n����Ʈ����������׽�����Ĵ��޷��ɹ���\n", me, target);
        	return 1;
        }
		//�Ծ�����ʧЧ
     	if( target->query_skill("buddhism", 1) > 200 && !target->is_killing(me->query("id")) ){
     		message_vision("���$n�𷨸�����Ĵ󷨸�����$pû�ã�\n", me, target);
        	return 1;
        }
		//�Ը�ɮʧЧ
        if( random(me->query_int()) > target->query_int()/2 ){
        	message_vision("���$n�ܵ�$P�����Ĵ󷨵�Ӱ�죬ԭ�ȵĶ�־��Ȼ��ʧ��\n", me , target);
       		target->remove_all_killer();
       		target->receive_damage("jing", me->query_int()*10, me);
       		target->receive_wound("jing", me->query_int()*3, me);
        	if( !userp(target) )
        		target->add_busy(4); 
			else target->add_busy(2);
        	hits = random(60)+(me->query_dex()-target->query_dex())*5+(me->query("jingli")-target->query("jingli"))/20;
       		if (hits > 30) {
        		message_vision(HIR"$n�ܵ�$P���Ĵ󷨸�Ӧ��Խ��Խ�Ǻ��£�������ʱ�޷�����! \n", me , target);
         		target->apply_condition("sld_shexin", 3+random(3) );
         		target->apply_condition("no_perform", 3);
         		target->apply_condition("no_exert", 3);
				target->set_temp("shexin",1);
         		target->set("jiali", 0);
         		me->start_busy(1);
        	}
        }
		else
		{
			me->start_busy(2);
			message_vision("���$Pֻ��$n��Ϊ��ֹ����Ī����\n", me, target);
		}
		me->add("neili",-300);
        me->add("jingli",-100);
        me->start_exert(5, "�����ġ�");
        return 1;
}  
int help(object me)
{
        write(HIG"\n������֮"+HBBLU+HIW"�����ġ���"NOR"\n\n");
        write(@HELP
	�����������������ڹ����������ǿ�ɽ��ʦ
	������������ɶ����ķ����������������߶�
	�����ԣ�������ǿ����һ�档
	�����ġ��������Ǹ������ڽ��������в��Ϸ�
	��˻˻֮���Կ��ŶԷ���������书���Է���
	Ϊ�����������������б���״̬��
	ע�⣺���ж�����󡹦�����������𷨸�
	��Ķ���ʧЧ������շ���ʹ�ã�

	ʹ��ָ�yun shexin
		
Ҫ��
	��ǰ����Ҫ�� 5000 ���ϣ�
	�������Ҫ�� 1000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����ڹ��ȼ� 350  ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	����ҩ��ȼ� 190 ���ϣ�
	��ǰ�������� 50 ���ϣ�
	�����ڹ�Ϊ�����󷨣�
	
HELP
        );
        return 1;
}

