// pixie.c Ⱥа���� Created by action 2007/7/25

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIB"Ⱥа����"NOR;}

int perform(object me, object target)
{
        object weapon;
        int i,a,j;

        weapon = me->query_temp("weapon");
       
        if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�Ⱥа���ס�������\n");
 
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("�����޽�,����ôʹ�ó���Ⱥа���ס�������\n");

        if( (int)me->query_skill("pixie-jian", 1) < 500 )
                return notify_fail("��ı�а��������̫ǳ���޷�ʹ����а����֮��Ⱥа���ס�������\n");

        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("��Ļ�������̫��,�޷�ʹ����Ⱥа���ס�������\n");

        if( (int)me->query_skill("kuihua-shengong", 1) < 500)
                return notify_fail("��������ڹ�̫��,�޷�ʹ����Ⱥа���ס�������\n");

        if(me->query_skill_mapped("force") != "kuihua-shengong" )
            return notify_fail("��������ڹ����ԣ��޷�ʹ�á�Ⱥа���ס���\n");

        if( (int)me->query("max_neili") < 15000 )
               return notify_fail("���������Ϊ̫ǳ���޷�ʹ����Ⱥа���ס���\n");

        if( (int)me->query("neili") < 2000 )
                return notify_fail("��ĵ�ǰ�����������޷�ʹ����Ⱥа���ס�����\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("��ĵ�ǰ�����������޷�ʹ����Ⱥа���ס�����\n");

        if (   me->query_skill_mapped("sword") != "pixie-jian"
	          || me->query_skill_mapped("parry") != "pixie-jian"
	          || me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("�㲻ʹ�ñ�а����,���ʹ���ˡ�Ⱥа���ס���\n");                         
                     
        message_vision(HIM"\n$N���е�"+weapon->query("name")+HIM"ͻȻһ�Σ��������ߣ�һ������������һƬ��Ӱ��һ�С�"+GRN+"Ⱥ"+
           "а����"+HIM+"��ֱ��$n��\n"NOR,me,target);  
        i = ((int)me->query_skill("pixie-jian",1)+(int)me->query_skill("kuihua-shengong",1))/2;
        j = i /3;

	    if ( i > 200 )
		j = to_int(i/100.0 * i/3.0);
        
        if ( me->query("quest/pixie/super") ) {
        	message_vision(HBMAG"\n������Ⱥָ��֮�������С�"+GRN+"Ⱥа����"+HBMAG+"��������ʹ��������������ʤ��ǰ���Ѵ������\n"NOR,me,target);
        	me->add_temp("apply/sword",j/2);
        	me->add_temp("apply/damage",j);
          }
        else if(QUEST_D->queryquest(me,"kuihua/book")) {
        	message_vision(HIW "\n$N���С�"+GRN+"Ⱥа����"+HIW+"���ѵÿ������侫Ҫ,��ʱʹ������,�����˽������!\n"NOR,me,target);
          } 
            me->add("jingli",-300); 
            me->add("neilili",-500); 
            me->add_temp("apply/attack", j*4/5);
	        me->add_temp("apply/sword", j*2/5);
	        me->add_temp("apply/damage", j/2);
		    me->set_temp("pixie",4);
        
		for(a=0;a<7;a++)
         {
		     if(random(2)) me->set_temp("pxj/pixie",1);

		     if (me->query_temp("pxj/pixie")&& me->query("quest/pixie/super")&& QUEST_D->queryquest(me,"kuihua/book"))
		     {
		         if(me->is_fighting(target))
		            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
              } else {
                       if(me->is_fighting(target))
                       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
              }
             me->delete_temp("pxj/pixie");
            }
		   me->delete_temp("pixie");
		   me->delete_temp("pxj/pixie");
           me->add_temp("apply/attack", -j*4/5);
           me->add_temp("apply/sword", -j*2/5);
           me->add_temp("apply/damage",-j/2);
           me->start_perform(5+ random(1), "��Ⱥа���ס�");
           if ( me->query("quest/pixie/super") ) {
        	me->add_temp("apply/sword",-j/2);
        	me->add_temp("apply/damage",-j);
          }
}


int help(object me)
{
   write(WHT"\n��а������"HIG"Ⱥа����"WHT"����"NOR"\n");
   write(@HELP
	��������˽�������Ҫ��һ��а����֯������ȫƾ���˺ö�
	���г����似�������������а�����������ν�����������
	�ľ��������������������ְ汾�������ڱ�а���������ɡ�
	���������ơ�
	��Ⱥа���ס����ǽ����������ܵĵ������������ƽƽ����
	�޻��Σ�����������������������⣬����Ͽ����񹦣�ʵ
	�˽��������Ĺ����������Ȼ��������Ե�ɺ��ܵõ�����Ⱥ
	��ָ�㣬��а��������Ҳ����Ϊ��һ�ȴ�ɱ�У�
    
	ָ�perform sword.pixie

Ҫ��
	��ǰ���� 2000 ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��а���� 500 ���ϣ�
	�������� 500 ���ϣ�
	������ 500 ���ϡ�
	�����ڹ�������
	����������а����
	�����мܱ�а����
	�����Ṧ��а����
	���ֳֽ���������

HELP
   );
   return 1;
}
