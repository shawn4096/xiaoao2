//modify By sohu@xojh
// xuesha.c ģ��������Ѫ������

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HBWHT+HIR"Ѫ  ɷ"NOR;}

int exert(object me, object target)
{

        int hits,i,skill;

        if( !target ) target = offensive_target(me);
		skill=me->query_skill("xuedao-jing",1);
		if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
        	return notify_fail("��Ѫɷ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
           
        if( (int)me->query_skill("xuedao-jing", 1) < 350 
        || (int)me->query_skill("huanxi-chan", 1) < 200 
        || (int)me->query_int() <=50 )
                return notify_fail("����Ϊ����������δ�����á�Ѫɷ����\n");
        if(!userp(me) )
                return notify_fail("��û�����ԣ�����һ��npc�����˰ɣ�\n");
        if (!me->query("quest/xd/xdj/xuesha/pass"))
                return notify_fail("����δѧ����е����÷��ţ�\n");
		if( me->query_skill("force", 1) < 350 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");
     
        if( me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ���������á�Ѫɷ����\n");
        if( me->query("max_jingli") < 2500 )
                return notify_fail("����������Ϊ���������á�Ѫɷ����\n");
        if( me->query("neili") < 1000 )
                return notify_fail("��������������������������á�Ѫɷ����\n");

        if( me->query("jingli") < 500 )
                return notify_fail("��ľ������ޣ����������á�Ѫɷ����\n");
        if( target->query_temp("xdj/xuesha"))
                return notify_fail("�Է��Ѿ�����Ѫɷ�����˺���");
        
		message_vision(HBRED+HIW"$Pһ���੹�Ц�����鼫Ϊ����������ͷ�������촽����������죬��תѪ�����ڹ�����$n����һ������\n" NOR, me , target);
        message_vision(HBRED+HIW"$n��$P���а������һ�ݣ�������$N�����鼫Ϊ��ɭ�ֲ��������̲�ס���˸����飡\n\n" NOR, me , target);
      		//��󡹦ʧЧ
 
        if( target->query_temp("hmg/nizhuan")){ 
           	message_vision("���$Pֻ��$n��ʽ����Ѫɷ�޷��ɹ���\n", me, target);
           	return 1;
        }
		//�Ծ�����ʧЧ

        if( target->query_temp("jiuyin/fast")){
           	message_vision("���$Pֻ��$n����Ʈ����������׽��Ѫɷ�޷��ɹ���\n", me, target);
        	return 1;
        }
		if( target->query_temp("jyzj/jiuyang")){
           	message_vision("���$Pֻ��$nһ�ɸ�����������������������ʱ������Ѫɷ��\n", me, target);
        	return 1;
        }

     			//�Ը�ɮʧЧ

		if( (target->query_skill("buddhism", 1) > 200||target->query_skill("taoism", 1) > 200 ) && !target->is_killing(me->query("id")) ){
     		message_vision("���$n�𷨸��Ѫɷ������$pû�ã�\n", me, target);
        	return 1;
        }
        if (target->query("gender")=="Ů��") 
        {
			if (me->query("per")>25)
			{
				i=5;
			}else if (me->query("per")>20)
			{
				i=4;
			}else i=3;
	
        }else i=2;

		if( random(me->query_int()) > target->query_int()/i )
		{
        	message_vision(HIB"���$n�ܵ�$P��Ѫɷ��Ӱ�죬ԭ�ȵĶ�־��Ȼ��ʧ��\n", me , target);
       		target->remove_all_killer();
       		target->receive_damage("jing", me->query_int()*10, me);
       		target->receive_wound("jing", me->query_int()*3, me);
        	//target �����½�
			if (!target->query_temp("xdj/xuesha"))
			{
				target->add_temp("apply/parry",-skill/2);
				target->add_temp("apply/dodge",-skill/2);
				target->set_temp("xdj/xuesha",skill);
				call_out("xdj_xuesha",1,target,skill/60);

			}

			if( !userp(target) )
        		target->add_busy(4); 
			else target->add_busy(2);

        	hits = random(60)+(me->query_dex()-target->query_dex())*5+(me->query("jingli")-target->query("jingli"))/20;
       		if (hits > 30)
			{
        		message_vision(HIR"$n�ܵ�$PѪɷ��Ӧ��Խ��Խ�Ǻ��£�������ʱ�޷�����! \n", me , target);
         		//target->apply_condition("xdj_poison", 3+random(3) );
         		target->apply_condition("no_perform", 3);
         		target->apply_condition("no_exert", 3);
         		target->set("jiali", 0);
         		me->start_busy(1);
        	}
        }
		me->add("neili",-300);
        me->add("jingli",-100);
        me->start_exert(5, "��Ѫɷ��");
        return 1;
}  
//����Ѫɷ
int xdj_xuesha(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("xdj/xuesha");
	target->add_temp("apply/parry",skill/2);
	target->add_temp("apply/dodge",skill/2);
	target->delete_temp("xdj/xuesha");
	message_vision(HIW"$N����һ����˲��ָ����ţ�ѪɷӰ�쳹����ʧ��\n"NOR,target);
	return;

}
int help(object me)
{
        write(RED"\nѪ����֮"+HBWHT+HIR"��Ѫɷ����"NOR"\n\n");
        write(@HELP
	Ѫ���������ຣ�ڽ�Ѫ���ŵ�һ��������Ѫ������������
	���ų����ֵ�һа�ɸ��֡���Ҫԭ�������Ϊ�������ص�
	�ڹ��͵������䣬��������벻����Ч����
	
	��Ѫɷ���������Ǹ���Ѫ����������а����ʽ���ݻ�����
	�ڽ��������в��Ϸ�����Ц֮���Կ��ŶԷ��������Ӷ�
	��Է�Ͷ����ʧȥս������Դ�������ѩ��һս��

	��Ѫɷ�������书�������أ���Ҫɱ�������������Ĺ�
	�̣�ɱ�����Խ�࣬�⿪�����ؼ�����Խ��
	
	ע�⣺���ж�����󡹦���������������澭���𷨸�
	����޵�������ʿʧЧ������Ů������Ч��Խ��Ư����Ů
	�����еĸ���Խ�󣨿�����Ů���������жϺ������ԡ�

	ʹ��ָ�yun xuesha
		
Ҫ��
	��ǰ����Ҫ�� 5000 ���ϣ�
	�������Ҫ�� 1000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����ڹ��ȼ� 350  ���ϣ�
	Ѫ�������ȼ� 350  ���ϣ�
	��ϲ���ĵȼ� 200 ���ϣ�
	��ǰ�������� 50 ���ϣ�
	�����ڹ�ΪѪ������
	
HELP
        );
        return 1;
}

