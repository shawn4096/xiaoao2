
//sandu.c ɢ��
//ɢ�������߶�
//����������
//by sohu

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>



string perform_name(){ return HBBLU"ɢ��"NOR; }

int perform(object me, object target)
{
		string msg;
		string str;
		string* po;
		int skill;
		str = (string)me->query("env/���߲�˿��"); 		
        
		po=me->query("sld/poison");		
		skill=me->query_skill("chansi-shou",1);

		if (!po)
			return notify_fail("������û���κ��߶���Ρ�ɢ����?��\n");		
		if (!str)
			return notify_fail("����ɢ�����߶���set ���߲�˿�� xxx������\n");		
		
		
		if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ɢ����ֻ����ս��ʱ�ã�\n");		
        		
		if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�ɢ������\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 400 )
                return notify_fail("��Ľ��߲�˿�ֻ�������죬ʹ������ɢ����������\n");
		if (me->query("gender")!="Ů��")
				return notify_fail("���Ů�ԣ�ʹ������ɢ����������\n");        
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("�������޷�ʹ�á�ɢ�������й�����\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 400 )
                return notify_fail("��Ķ����󷨵ȼ���������ʹ������ɢ����������\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("����ڹ������޷�ʹ�á�ɢ������\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("����������̫����ʹ������ɢ������\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ������ɢ������\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ���̫����ʹ������ɢ������\n");
		if (me->query_temp("chss/sandu"))
			return notify_fail("������ʩչ��ɢ������\n");
		if (!me->query("quest/sld/chss/sandu/pass"))
			return notify_fail("����δ�õ���˿���洫��\n");	
		
		msg = HBBLU"\n$Nƽʱ���������������붾��Ϊ�飬���ڻ���ĸ����߶�������衣\n"NOR;
        msg+= HBBLU"�˿������ǰ��$N�������������ڶ��رƳ��߶�����������,���ƴ���!\n"NOR;
		msg+=HBBLU"$NͻȻ��ƮƮһ���ĳ������ƺܻ�����ʵ����޿ɱܡ��Ʒ����һ�ɶ��ĵ��ȳ�ζ��\n"NOR;
		message_vision(msg, me, target);
		me->set_temp("chss/sandu",1);
		call_out("remove_effect",1+skill/50,me);
		return 1;
}
int remove_effect(object me)
{
	if (!me||!me->query("chss/sandu")) return 0;
	me->delete_temp("chss/sandu");
	message_vision(BLU"$N�����³�һ�ڰ���������Ķ����³�����!\n"NOR,me);
	return 1;
}
int help(object me)
{
   write(WHT"\n��˿��֮��"RED"ɢ��"WHT"����"NOR"\n");
   write(@HELP
	��˿��������������֮һ������ɢ������Ҫ
	�����ǽ��Լ�ƽʱ���������ĸ����߶�����
	�������ڣ�ͨ����˿�ַ����ж��Ƴ�����ʹ
	�öԷ����߶�������Ů�ԡ�
	Ŀǰ���ŵ��߶��У��߶������߶����岽��
	������Ѫ�߶�����Ѫ�߶��������߶�������
	���������߶���

	perform hand.sandu

Ҫ��
	�������Ҫ�� 5000 ���ϣ�
	�����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	���Ƶȼ�     200  ���ϣ�
	��˿�ַ��ȼ� 450 ���ϣ�
	�����󷨵ȼ� 450 ���ϣ�
	����ҩ��ȼ� 200 ���ϣ�
	���֣�
HELP
   );
   return 1;
}
