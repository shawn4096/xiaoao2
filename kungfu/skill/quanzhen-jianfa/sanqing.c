// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIW"һ��������"NOR; }
int perform(object me, object target)
{
        int skill = me->query_skill("quanzhen-jianfa", 1);
        object weapon = me->query_temp("weapon");  
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("һ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill("force", 1) < 300 )
                return notify_fail("����ڹ����δ�����޷�ʩչһ�������壡\n");
        if ( !weapon
			 || weapon->query("skill_type") != "sword"
			 || me->query_skill_mapped("sword") != "quanzhen-jianfa")
               return notify_fail("�������޷�ʹ��һ�������塣\n");
        if( me->query_skill("dodge") < 300 )
                return notify_fail("һ�����������Ṧ��ϣ�����ʩչ��\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("�㽣�����δ�㣬�޷�ʹ��һ�������壡\n");

        if( me->query("neili") < 500 )
                return notify_fail("�����������ʹ��һ�������壡\n");
		if( me->query("max_neili") < 1500 )
                return notify_fail("��������������ʹ��һ�������壡\n");
        if( me->query("jingli") < 500 )
                return notify_fail("��ľ�������ʹ��һ�������壡\n");
        if (me->query_temp("sanqing"))
        		return notify_fail("������ʹ��һ�������壡\n");
        if (me->query_temp("qzjf/sanqing"))
        		return notify_fail("������ʹ��һ�������壡\n");

       // if((int)me->query_temp("hebi"))
             //  return notify_fail("������ʩչ˫���ϱڣ��޷�ʹ�á�һ�������塹������\n"); 

        if(!me->query_skill("xiantian-gong"))
          if(me->query_skill("yunu-xinjing", 1) < 200)
                return notify_fail("����ڹ���򲻹����޷�ʹ��һ�������塣\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
		 || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan" ))
                return notify_fail("�������޽�����ʹ��һ�������壿��\n");

        msg = HIC"\n$N���н����Ȼ���߲��������һ����Х��ʹ��ȫ�潣���еľ���һ�������壬����ֳ����㣬����$n������һ�У�\n" NOR;
       
		if (me->query("family/family_name")=="ȫ���")
    	{
			 
			skill=skill+me->query_skill("xiantian-gong",1)/5;
			
	    }		
		
		if (me->query("family/family_name")=="��Ĺ��"
			&& me->query_skill("quanzhen-jianfa",1)<350
			&& me->query("gender")=="����")
		{
			 msg += HIM"\n$N����Ů�ľ������Ṧ��������ȫ�潣���У���һ��������ʹ��ȴҲ����ģ������\n" NOR;
			 //target->start_busy(1+random(1));
			 skill=skill+me->query_skill("yunu-xinjing",1)/5;
		}
		message_vision(msg , me, target);
        
		me->set_temp("qzjf/sanqing",skill);
		me->add_temp("apply/attack", skill/3 );
        me->add_temp("apply/damage", skill/5 );
        me->add("neili", -300);
        me->add("jingli", -100);
        me->set_temp("sanqing1", 1);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        me->start_perform(3,"һ��������");
        me->delete_temp("sanqing1");
        
		me->add_temp("apply/attack", -skill/3 );
		me->add_temp("apply/damage", -skill/5 );

		//if (objectp(target)&&me->is_fighting())
       	call_out("check_fight", 1, me,(int)skill/30);

	//	else call_out("sanqing_finish",1,me);
        return 1; 
}
void check_fight(object me,int count)
{
    int skill;
	object target,weapon;

	if(!me) return;
	skill=me->query_temp("qzjf/sanqing");
	
	weapon=me->query_temp("weapon");
	
	target=offensive_target(me);

	if(!target
		|| !me->is_fighting()
        || !weapon
        || me->query_skill_mapped("sword") != "quanzhen-jianfa"
		|| me->query_skill_mapped("parry") != "quanzhen-jianfa"
        || count < 0 )
	{
                message_vision(HIW"\n�⼸��һ���ǳɣ��������������Ƴ��ȣ�һ�������建���չ���\n\n"NOR, me);
                me->delete_temp("sanqing");
				me->delete_temp("qzjf/sanqing");
                me->add_temp("apply/attack", -skill/3);
                me->add_temp("apply/damage", -skill/5);
                return;
     }
     else {
              me->set_temp("sanqing", 1);
              me->add_temp("apply/sword", skill/5);
              message_vision(HIC"\n$N����һ������Ѹ�ݴ̳����У��⼸��һ���ǳɣ��������������Ƴ��ȣ�ȡ�����һ��������֮�⣬����ȫ�潣���еľ������ڡ�\n\n"NOR, me);

			  if (me->query_skill("xiantian-gong", 1) > 350) 
				 {
				   if (me->is_fighting(target))
             	      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

			     }
             if (me->query_skill("xiantian-gong", 1) > 450) 
				 {
                   if (me->is_fighting(target))
             	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 	     }
		     if (me->query_skill("xiantian-gong", 1) > 550) 
				 {
                   if (me->is_fighting(target)){
				     me->add_temp("apply/attack",me->query_skill("xiantian-gong",1)/10);
             	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
					 me->add_temp("apply/attack",-me->query_skill("xiantian-gong",1)/10);
					 }
				}
			 me->add_temp("apply/sword", -skill/5);

             me->delete_temp("sanqing");
             me->start_perform(3,"һ��������");
       }  
       call_out("check_fight", 2, me, count - 3);  
}

//��������
int sanqing_finish(object me)
{
	int skill;
	if (!me) return 0;

	skill=me->query_temp("qzjf/sanqing");
	
	me->add_temp("apply/attack", -skill/3 );
    me->add_temp("apply/damage", -skill/5 );
	me->delete_temp("sanqing");
	me->delete_temp("qzjf/sanqing",skill);
    message_vision(HIW"\n�⼸��һ���ǳɣ��������������Ƴ��ȣ�ȡ��������壬����ȫ�潣���еľ������ڡ�\n\n"NOR, me);
	return 1;


}
int help(object me)
{
        write(HIG"\nȫ�潣��֮"+HIW"��һ�������塹��"NOR"\n\n");
        write(@HELP
	ȫ�潣��������������ȫ��̵����Ž������������ͨ���ϣ�
	����ԭ��β��Ѩ���ȴ�ӿȪ�ŵ׳壬ӿȪ������ϥ����ϥ
	������β�̣����趥�ϻ������������ش���ȵ�ţ���¥ʮ��
	�����ҡ��仯��΢����ȫ��̵�ȫ���ķ�������á�
	һ�������壬�������У�ÿ�ζ�����������������Ϊȫ�潣
	������ɱ�С�
	
	ָ�perform sword.sanqing

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	ȫ�潣���ȼ� 300 ���ϣ�
	���칦���ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	�����Ṧ�ȼ� 300 ���ϣ�
	��������Ϊȫ�潣����
	�����м�Ϊȫ�潣�������ȭ��
	�����ڹ�Ϊ���칦��
	�ֳֽ�������
	��ȫ������������칦����������������
HELP
        );
        return 1;
}
