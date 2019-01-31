//yingyang.c ӥ������
//cre by sohu@xojh 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIR"ӥ������"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv,lvf;
		object weapon=me->query_temp("weapon");

        if( !target ) target = offensive_target(me);
        
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("ӥצ�֡�ӥ��������ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�ӥ����������\n");   
        if( (int)me->query_skill("yingzhua-shou", 1) < 250 )
                return notify_fail("���ӥצ�ֻ�������죬ʹ������ӥ��������������\n");
        if (me->query_skill_prepared("hand") != "yingzhua-shou"
        || me->query_skill_mapped("hand") != "yingzhua-shou")
                return notify_fail("�������޷�ʹ�á�ӥ�����������й�����\n");  

	    if( me->query_skill_mapped("force") != "shenghuo-shengong" )
		        return notify_fail("������ʹ�õ��ڹ�������ʹ�á�ӥ����������\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 250 )
                return notify_fail("���ʥ���񹦵ȼ���������ʹ������ӥ��������������\n");
       
        if( me->query("max_neili") < 3500 )
                return notify_fail("����������̫����ʹ������ӥ����������\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("����������̫����ʹ������ӥ����������\n");
      
        
        lv = me->query_skill("yingzhua-shou",1);
		lvf=me->query_skill("shenghuo-shengong",1)/8;
     
        if (me->query("mj/quest/yzs"))
        {
			//message_vision(HIC"$N����ӥ����ָ�㣬���һ������ʥ���񹦾�������צ�У���ʽ����Ϭ����\n"NOR,me,target);
			lv += lvf;
        }
		//lv += lvf;
		
		if (target->is_busy() && me->query_skill_mapped("force")=="shenghuo-shengong")
		{
			message_vision(HIC"$N��$n������æ��֮�У��Թ˲�Ͼ��ʥ��������צ�У�ӥצ��������ʱ���Ӳ��١�\n"NOR,me,target);
			lv+=lv/8;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/hand", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        message_vision(HIR"\n$NͻȻ����һ����������ϣ������ڿ��а�����ݣ�˫�ֻ�������������ʩչ����ӥ������������˲����$n������������ɱ�С� \n"NOR,me,target);
     
   
        me->set_temp("yzs/yingyang", 3);
		
      
        COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
        COMBAT_D->do_attack(me, target, 0, 3);
		COMBAT_D->do_attack(me, target, 0, 3);
		if (me->query("mj/quest/yzs") && me->query_temp("mj/shenghuo"))
		{
			target->add_busy(1);
			message_vision(HIC"$N����ӥ����ָ�㣬���һ������ʥ���񹦾�������צ�У���ʽ����Ϭ����\n"NOR,me,target);
			COMBAT_D->do_attack(me, target,0, 3);

		}      
       
        me->add_temp("apply/attack", -lv/3);
		me->add_temp("apply/hand", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		
		me->start_perform(4,"��ӥ��������");
        me->start_busy(1+random(2));
        me->delete_temp("yzs/yingyang");
      
        return 1;
}


int help(object me)
{
        write(HIY"\nӥצ��֮��ӥ����������"NOR"\n");
        write(@HELP
	ӥצ�־����������̻��̷���üӥ���������ĳ���������
	�ǽ����ø�����������ں���һ��ľ�������˫��
	��ս�����У��ȿ���ͨ�����������������жԷ���Ѩ����
	�ֿ���ͨ����ɱ��һ���µС�
	
	ָ��:perform hand.yingyang

Ҫ��
	������� 3500 ���ϣ�      
	��ǰ���� 1500  ���ϣ�  
	ӥצ�ֵȼ� 250 ���ϣ�
	ʥ���񹦵ȼ� 250 ���ϣ�
	����צ��Ϊӥצ�֣�
	�����м�Ϊӥצ�֣�
	�����ޱ�����
                
HELP
        );
        return 1;
}


