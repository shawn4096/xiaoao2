// mianzhang.c �䵱����
// By sohu#xojh

#include <ansi.h>

inherit F_SSERVER;
//int check_fight(object me);
int perform(object me, object target)
{
        int i,j,p,k,z,damage;
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("���ƾ���ֻ����ս����ʹ�á�\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("�ȷ������е�������˵�ɣ�\n");
       // if( me->query_temp("mz_mian"))        
               //return notify_fail("�Է��Ѿ�����������ƾ�����\n");
        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("��Ļ����Ʒ�̫�ͣ��޷�ʹ������֮������\n");  
        if((int)me->query_skill("zhenshan-mianzhang", 1) < 250 )
                return notify_fail("������ƻ�������죬����ʹ������֮������\n");
        if (me->query_skill_prepared("strike") != "zhenshan-mianzhang"
           || me->query_skill_mapped("strike") != "zhenshan-mianzhang")
                return notify_fail("�㲻ʹ�����ƣ�������ʹ������֮��������\n");   
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("��������Ϊ̫ǳ���޷��˾��˵У�\n");                
        if( (int)me->query("neili") < 1500 )
                return notify_fail("�������������������ܷ�������֮������\n");
       
        if( userp(me) && (int)me->query_skill("yinyun-ziqi", 1) < 250 )
                return notify_fail("����������ȼ�����������Ӧ������֮������\n");
        if(userp(me) && (int)me->query_skill("taoism", 1) < 150 )
                return notify_fail("��ȭ�����ģ���Ե�ѧ�ķ������򲻹����ǲ�����������֮�����ġ�\n");
        if(userp(me) && me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("����ڹ��ķ����ԣ����Ӳ������ƾ���֮����\n");                                                                                     
        if (userp(me) && me->query_skill_mapped("parry") != "zhenshan-mianzhang")
                return notify_fail("������ڼ�������Ϊ�мܵ�����²���ʹ������֮������\n");
        
        i=me->query_skill("strike",1)+me->query_skill("zhenshan-mianzhang",1)+me->query_skill("force",1);
        j=target->query_skill("parry",1)+target->query_skill("dodge",1)+target->query_skill("force",1);
        p =(me->query("combat_exp")-target->query("combat_exp"))/200000;		 
        if (!userp(target))
      		z = i/5 - j/10 + p;
		else z=i/8 - j/10 + p;
        
		if ( z < 3 ) z = 3;
        if ( z > 12 ) z = 12;
        k = random(z) + 1;
        
		me->set_temp("mz_mian", 1);
		me->add_temp("apply/attack",i/6);
		me->add_temp("apply/damage",i/8);
       
		message_vision(HIY"$N˫���ɸձ��ᣬ��Ȼ����������������Ӱ���Ʈ�ݲ����������䵱��ʮ��·�����еĹ���\n"+
		  HIC"$N�����ޱȵ���ͼ��$n����ʽ������ֱ�������\n"NOR,me, target);
        me->add("neili", -600);
        // �������Ʊ���
		if (me->query_skill("zhenshan-mianzhang",1)<350)
		{
			damage=i*6;
		} else damage=i*4;
		
		if (objectp(target) 
			&& me->is_fighting(target) 
			&& random(me->query("neili"))>target->query("neili")/3)
		{	
			message_vision(HIY"\n$N˫�������ߣ�ʩչ�ྡྷ�е�"MAG"[ �� ]"HIY"�־���ֱ��$n�ĵ��ﲿλ��\n"NOR,me, target);
			
			damage+=random(damage);
			
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/4,me);
		    target->apply_condition("no_exert",1);
		}	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	    
		if ( me->is_fighting(target) && me->query_skill("zhenshan-mianzhang", 1) > 250 && k > 3 )
		{
		   message_vision(MAG"\n$N����Ĭ����в��ܣ�˳�ƶ��¡������ƽ���$n�ؽڣ�������"HIG"[ �� ]"MAG"�Է����ţ�"+
			"$n��ʱ���Ƶ���æ���ҡ�\n"NOR,me, target);
	       target->add_busy(k);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
         }
	    if ( me->is_fighting(target) 
			//&& !me->query_temp("mz_jin") 
			&& me->query_skill("zhenshan-mianzhang", 1) > 250
			&& k > 4 ){
	       message_vision(HIG"\n$N�������ĵĶ���һȭ������һ�ƣ�$nһ����Ӱ���������������ޣ����黹ʵ��������Ӱ��"WHT"[ �� ]"HIG"ס��"+
			   "����һ����Ҳ�޷�ʩչ��\n"NOR,me, target);
		   
		   target->apply_condition("no_perform", 1);

           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	       
		   //target->set_temp("mz_jin",1);
           //target->start_call_out((: call_other, __FILE__, "remove_effect", target :),(int)i/6);
           //check_fight(me);
         }
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

	    if ( me->is_fighting(target) && me->query_skill("zhenshan-mianzhang", 1) > 300 && k > 5 )
		{
	       message_vision(WHT"\n$N��$n��־��ʧ���Ż��󿪣������ٲ���ԥ��˫��һ�ϣ��ھ����£�"HIR"[ �� ]"WHT"�־����֣�"+
		      "������ʮ��·�ྡྷ�������д��꣬��������վ��������\n"NOR,me, target);        
           
	       damage += damage;	
		   damage = damage + random(damage);
		   if (damage>4000) damage=4000+(damage-4000)/100;
		   
		   target->receive_damage("qi", damage,me);
		   target->receive_wound("qi", damage/4,me);
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		   me->add("neili", -i);
		}
     
		me->start_perform(4, "����");
		me->add_temp("apply/attack",-i/6);
		me->add_temp("apply/damage",-i/8);
		me->delete_temp("mz_mian");
        return 1;
}
/*
int check_fight(object me)
{
        if(!me->is_fighting(target)){
                target->clear_condition("no_perform");
		        me->delete_temp("mz_jin");
         }
        return 1;
}       
*/

void remove_effect(object target)
{
      if(!target) return;      
      target->clear_condition("no_perform");
      target->delete_temp("mz_jin");
      return 0;
}
string perform_name(){ return HIR"���ƾ���"NOR; }
int help(object me)
{
         write(HIC"\n��ɽ����"+HIR"�����ƾ�����"NOR"\n");
         write(@HELP
	��ɽ���������䵱���ŵĳ����书������
	���͵�һ�棬Ҳ�������������ʽ������
	���ڹ����������޼�һս��ƾ�軨������
	һ�е�ʩչ��ʹ����ɽ����������������
	�����¶��������������������һ��
	���ƽ��ε�ͷ�����ѡ�����û�˺���������
	�ɼ�����ʽ�����ᡣ���ƾ����ɴ˶�����
	�������У�������ǣ��ס�������ɱһ��
	������
	
	perform strike.mianzhang

Ҫ��
	��ǰ����Ҫ�� 1500 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ɽ���Ƶȼ� 250 ���ϣ�
	�������ȼ� 250 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	��ѧ�ķ��ȼ� 150 ����
	�����Ʒ�Ϊ��ɽ���ƣ�
	�����м�Ϊ��ɽ���ƣ�
	�����ڹ�Ϊ��������

HELP
        );
        return 1;
}
