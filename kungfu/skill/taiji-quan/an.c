// an.c ̫��ȭ�����־�����
// by snowman@SJ 06/06/2000

inherit F_SSERVER;

#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {       return 1;}

string perform_name(){ return HIB"���־�"NOR; }

int perform(object me, object target)
{ 
	object ob;
	if( !target ) target = offensive_target(me);

	if( !objectp(target) 
	|| !target->is_character() 
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( userp(me) 
	&&( me->query_skill_mapped("parry") != "taiji-quan"
	&& me->query_skill_mapped("parry") != "taiji-jian") )
		return notify_fail("�����־�����������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("����ڹ���ȭ�����ԣ��������ܷ��ӳ������־��������ơ�\n");  

	if( me->query_skill_prepared("cuff") != "taiji-quan"
	|| me->query_skill_mapped("cuff") != "taiji-quan")
		return notify_fail("����붮��̫��ȭ������ʩչ�����־�����\n");  

	if( me->query_skill("taiji-quan", 1) < 450 )
		return notify_fail("���̫��ȭ������죬��������ᡸ���־���֮���ϣ�\n");
    if( me->query_skill("yinyun-ziqi", 1) < 450 )
		return notify_fail("���������������죬��������ᡸ���־���֮���ϣ�\n");
	if( (int)me->query("neili", 1) < 5000 )
		return notify_fail("����������������ǿ��ʹ�á����־����Ƿ��Ӳ������������ģ�\n");    
	if( (int)me->query("jingli", 1) < 3000 )
		return notify_fail("����������������ǿ��ʹ�á����־����Ƿ��Ӳ������������ģ�\n");    

	if( me->query_temp("weapon"))
		return notify_fail("���ȷ������е�������˵�ɣ���\n");     

	if( me->query_int(1) < target->query_int(1)/3*2 )
		return notify_fail("�����յе��������¶���ô�����Ķ��ֲ��ʺϰɣ���\n");     

	if( target->is_busy())
		return notify_fail("�Է����Թ˲�Ͼ�أ��㲻æʹ�á����־�����\n");

	if( objectp(ob = me->query_temp("tjq/an")) ) {
		if( ob->is_fighting(me) || me->is_fighting(ob))
			return notify_fail("���Ѿ�׼����ʱ�Դ˶���ʹ�á����־����ˡ�\n");
		else me->delete_temp("tjq/an");
	}
	return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
	|| me->query("neili") < 1500 || me->query("jingli") < 300 || me->query_temp("weapon")
	|| me->query_skill("taiji-quan", 1) < 350 )
		return 0;     
                
	if(intp(me->query_temp("tjq/"+target->query("id")) > 7))
		me->add_temp("tjq/"+target->query("id"), -7);
	else me->delete_temp("tjq/"+target->query("id"));
       
	msg = HIB"\n��˫�۶�ȻȦת������ֻ�ز�����������Ϣ������̫��ȭ��"RED"�����־�����"HIB;
        
	if(me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill("yinyun-ziqi", 1) < 100){
		msg += "˫�۾���������$n��\n"NOR;
	}        
        
	else msg += "˫������̫�������ھ������ص�����ƴ�����\n"NOR;
 
	tell_object(me, msg);
	if (me->query_skill("taiji-quan",1)<550)
	{
		me->start_perform(2, "�����־���");
	}
	me->set_temp("tjq/an", target);
	me->add("neili", -150);
	//me->start_busy(random(1)); ����pfmbusy�Ϳ�����
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), me->query_int()/2);      
	return 1;
}

void remove_effect(object me)
{
	if( !me ) return;
	if( !me->query_temp("tjq/an") ) return;
	
	me->delete_temp("tjq/an");
	if( me->is_fighting() ){
		tell_object(me, HIB"\n��������ã��޷�֧�ţ�ֻ��ɢȥ�����־����ľ�����\n"NOR, me);
		if( !me->query_perform() )
			me->start_perform(1);
	}
}

int help(object me)
{
	write(WHT"\n̫��ȭ��֮"HIB"�����־�����"NOR"\n");
	write(@HELP
	̫��ȭ������仯��ˣ�����Ϊһ�ᡣ����������򶮾����ɶ������׼�������
	�����־�����Ҫ������ѹ�У��Ƶ�������������̩ɽѹ��֮��ʤ�������м�
	����������������Ϊһ�壬��̫��ȭ֮������
	̫��ȭ��֮�����־�����̫��ȭ��Ҫ�ĸ��������似��550�����ɡ�
	Ҫ��	
		��ǰ���� 5000 ���ϣ�      
		��ǰ���� 3000 ���ϣ�  
		̫��ȭ�ȼ� 450 ���ϣ�
		�������� 450 ���ϣ�
		����̫��ȭ�����ޱ�����
HELP
	);
	return 1;
}
