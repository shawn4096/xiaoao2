//tangshi.c  ������ʫ����
//by sohu@xojh�������Ǿ���д


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon, weapon2;
	int i,j,l, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
    lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1)/2;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("����ʫ������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    if(me->query("tangshi/ts")!="pass") 
                return notify_fail("�����ʫ�����İ���һ�ϲ�ͨ����ʹ�ò�����ʫ������\n");
	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 350 ) 
                return notify_fail("�����ʫ������δ���ɣ��޷�ʹ�á�ȥ�硹�־���\n");

    if((int)me->query_skill("sword", 1) < 350 )
                return notify_fail("��Ļ�������������죬����ʹ�á�ȥ�硹�־���\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("�����ʹ�ý���������ʹ������ʫ������!\n");
  
   if(me->query_skill_mapped("parry") != "tangshi-jianfa")
           return notify_fail("����ʫ��������Ҫʹ����ʫ�����м�һ�ез�������\n"); 

   if((int)me->query("max_neili") < 5000 )
           return notify_fail("��������Ϊ��ǳ��ʹ��������ʫ�������־���\n");  

   if( (int)me->query("neili") < 1500 )
           return notify_fail("����������̫����ʹ��������ʫ�������־���\n");

       l=(int)me->query("int")/10+(int)me->query_skill("literate",1)/60;
	   
	   if (l>6) l=6;
	
	   j = lvl/2;
	   me->set_temp("tangshi/shiyin",1);
       message_vision(HIC"$N�Ľ��ƺ�Ȼһ�䣬�Ƶ�Ʈ�죬���ⰻȻ���󿪴�ϣ��������Ǿ������ڵġ���ʫ����������!\n"NOR,me,target);
	   me->add_temp("apply/sword", j);
       me->add_temp("apply/attack", j);
       me->add_temp("apply/damage", j/2);
	
	for( i = 0; i <=l; i ++ ) 
	  {
       
            // me->add_temp("apply/damage",(int)me->query_skill("tangshi-jianfa",1)/4);
			 if (objectp(target)&& me->is_fighting(target))
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            // me->add_temp("apply/damage",-(int)me->query_skill("tangshi-jianfa",1)/4);
      }
    
	me->add_temp("apply/sword", -j);
    me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j/2);
    //call_out("check",1,me);
	me->delete_temp("tangshi/shiyin");

	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(5, "����ʫ������");
	return 1;
}

string perform_name(){ return HIG"��ʫ����"NOR; }

int help(object me)
{
        write(HIC"\n��ʬ����֮����ʫ��������"NOR"\n\n");
        write(@HELP
	 ����ʬ���������ǽ�ӹʮ�Ĳ����������С����Ǿ����������书
	��Ҫ���ɷ����ɫ�������Ὥ���ݳ������е�һ�ֽ�������Ϊ��
	���˶�Ŀ���ѡ���ʫ����������ﴫΪ����ʬ�����������е���
	����������Ҳ�ĳ�г���ֻ�ͬ�������֣������Ѹý�������С
	˵�����˹����ơ��ɴˣ��Զﴫ��,ʵ�˻�����֮�����
	��ʫ���������ǻ�ԭ��ʵ����ʫ������ʽ�������������󿪴�
	�ϣ����Ǽ�Ϊ������һ���似��
	
	ָ�perform sword.tangshi
			
Ҫ�󣺡�
	��ǰ���� 5000 ���ϣ�
	������� 1500 ���ϣ�
	��ʬ�����ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����м�Ϊ��ʫ������

HELP
        );
        return 1;
}
