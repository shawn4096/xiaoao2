#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name() {return HBGRN+HIW"������"NOR;}

int perform(object me, object target)
{			

		object weapon,tweapon;
        string msg;
        int lv,skill; 		
		tweapon = target->query_temp("weapon");
		lv=me->query_skill("canglang-goufa",1);
		skill=me->query_skill("canglang-goufa",1)+me->query_skill("dulong-dafa",1)/5;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("������ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("������ֻ�а��˽���������ã�\n");

        if( !objectp(weapon=me->query_temp("weapon")) ||weapon->query("skill_type")!="hook") 
		{
                              
                return notify_fail("��������Ź������ò����⣡\n");
        }
        if(!me->query("quest/sld/clgf/canglang/pass"))
                return notify_fail("��ֻ����˵�������⾳�����������á������⡹��\n");

        if( (int)me->query_skill("huagu-mianzhang", 1) < 250 )
                return notify_fail("��Ļ������ƻ���������������ʹ�ò����⣡\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("ֻ��ʹ�û�������ʱ����ʹ�ò����⣡\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 250 )
                return notify_fail("��������ȷ�����������������ʹ�ò����⣡\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�ò����⣡\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 250 )
                return notify_fail("��Ĳ��˹�������������������ʹ�ò����⣡\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("ֻ��ʹ�ò��˹���ʱ����ʹ�ò����⣡\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("��Ķ����󷨹������㣬�����ò����⡣\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("ֻ��ʹ�ò��˹���ʱ����ʹ�ò����⣡\n");

        if( (int)me->query_skill("hook", 1) < 250 )
                return notify_fail("��Ļ�����������������������ʹ�ò����⣡\n");
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("������������Ϊ�еͣ�����ʹ�ò����⣡\n"); 

        if((int)me->query("eff_jingli", 1) < 2500) 
                return notify_fail("�����ھ�����Ϊ�еͣ�����ʹ�ò����⣡\n"); 

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�ò����⣡\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�ò����⣡\n");  

		if( weapon->query("clgf/canglang") ) 
                return notify_fail("�����е������Ѿ�ע�뾢��������ʩչ�����⾳�С�\n");
		if( weapon->query_temp("clgf/canglang") ) 
                return notify_fail("������ʩչ�����⾳�С�\n");

        if(me->query("gender")!= "����") 
                return notify_fail("ֻ�����˲���ʹ�á������⡹��\n");      
 
        me->add("jingli",-100);
        me->add("neili",-200);

        msg = HBGRN+HIW "$N���Ǻ�������ڵĲ����⾳����������Ц��,���������龳�磬������"+weapon->query("name")+HBGRN+HIW"ͻȻ�����£�\n"NOR;
		msg+=HBGRN+HIW"ɲ�Ǽ䣬"+weapon->query("name")+HBGRN+HIW"��Լ��������֮�⡣\n"NOR;

		message_vision(msg,me,target);
		weapon->set("clgf/canglang",1);
		me->set_temp("clgf/canglang",skill);
		
		weapon->set("s_rigidity",(int)weapon->query("rigidity"));
        weapon->set("s_sharpness",(int)weapon->query("sharpness"));
        weapon->add("rigidity",10);
        weapon->add("sharpness",20);
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/8);
		me->add_temp("apply/hook", skill/8);
		call_out("remove_effect",1,me,target,weapon,(int)lv/20);
		
        return 1;
}

void remove_effect(object me,object target,object weapon,int lv)
{
		string msg;
		int skill;
		object tweapon;

		tweapon = target->query_temp("weapon");
		skill=me->query_temp("clgf/canglang");
		if(!objectp(weapon)) return;

		if (!weapon->query("clgf/canglang")) return;

		if (weapon->query("broken")) return;

		if (!me){
     
           weapon->set("rigidity",(int)weapon->query("s_rigidity"));
           weapon->set("sharpness",(int)weapon->query("s_sharpness"));
           weapon->delete("clgf/canglang");
           return ;
       }

       if (me->query_temp("weapon") != weapon
         ||!me->is_fighting()
         || lv<1
         ||me->query_skill_mapped("force") != "dulong-dafa"
         ||me->query("neili")<200 ){
             message_vision(weapon->query("name")+HBGRN+HIW"�����ǲ����޵Ĺ�â������ȥ,�ָֻ���ƽ��!\n"NOR,me);
             
             weapon->set("rigidity",(int)weapon->query("s_rigidity"));
             weapon->set("sharpness",(int)weapon->query("s_sharpness"));
             weapon->delete("clgf/canglang");
			 me->add_temp("apply/attack",-skill/3);
			 me->add_temp("apply/damage",-skill/8);
			 me->add_temp("apply/hook",-skill/8);
			 me->delete_temp("clgf/canglang");
             return ;
         }

		call_out("remove_effect",2,me,target,weapon,lv--);
	
		return ;
}

int help(object me)
{
   write(WHT"\n���˹�����"HBGRN+HIW"������"WHT"����"NOR"\n");
   write(@HELP
	���˹�������������������������Լ�����ѧ�似
	��������������һ�׹����似��ȥ���ͼ򣬹���Ϭ
	��������ʤ����������ڱ����ϴ��е��Ӷ��ԣ���
	�Ƿǳ�ʵս�Ĺ������в��������ǲ��˹�����Ҫ
	�ĸ��������似�������Լ��Ķ����ڹ��ͷ��ţ���
	����������ʱ���ڴ�����Ӳ�Ⱥͷ����ȣ��Ե�ʵ
	ʩ��Ч���,�������������̡�

	ע�⣺set ���˹��� �� �⿪����������Ч
	
	perform hook.canglang
	
Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	�������Ƶȼ� 350 ���ϣ�
	�����ȷ��ȼ� 350 ���ϣ�
	���˹����ȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����ұ��Ʒ�Ϊ�������ƣ�
	�����ȷ�Ϊ�����ȷ���
	��������Ϊ���˹�����
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ���������
	�Ա����� ���ԡ�
HELP
   );
   return 1;
}
