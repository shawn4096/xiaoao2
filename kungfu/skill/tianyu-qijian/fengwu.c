//Modified by zhuifeng@SJFY
//Update by Jpei 2010

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIC"��"HIG"��"HIY"��"HIB"��"NOR; }

int perform(object me, object target)
{
        int skill,lvl;
        object weapon;

    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (me->query_skill_mapped("force") != "beiming-shengong")
    if (me->query_skill_mapped("force") != "bahuang-gong" )                
                return notify_fail("����ڹ������޷�ʹ�á�������졹��\n");

    if(!wizardp(me) && (int)me->query_skill("beiming-shengong", 1) < 450 )
		if(!wizardp(me) && (int)me->query_skill("bahuang-gong", 1) < 450 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á�������졹��\n");

    if((int)me->query_skill("force", 1) < 450 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡�������졹��\n");

    if( (int)me->query_skill("tianyu-qijian", 1) < 450 ) 
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á�������졹��\n");

    if((int)me->query_skill("sword", 1) < 450 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á�������졹��\n");

    if((int)me->query_skill("dodge", 1) < 450 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á�������졹��\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tianyu-qijian"
        || me->query_skill_mapped("parry") != "tianyu-qijian")
                return notify_fail("�������޽������ʹ�á�������졹��\n");
                
    if((int)me->query("max_neili") < 12000 )
                return notify_fail("�������������㣬����ʹ�á�������졹��\n");

    if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ�á�������졹��\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("������̫���ˣ�����ʹ�á�������졹��\n");
   
    me->add("neili",-350);
	 me->add("jingli",-250);
    lvl = me->query_skill("tianyu-qijian",1);
    skill = me->query_skill("tianyu-qijian",1)+ me->query_skill("bahuang-gong", 1) /2 ;
    skill = skill /4;
    if (me->query("family/family_name") == "���չ�") skill=skill*3/2;
//����npcЧ��
    if(!userp(me)) 
		skill = skill / 3;
     me->add_temp("apply/attack", skill/2 );	
     me->add_temp("apply/damage", skill/4);
     me->add_temp("apply/sword", skill/4);
	

    message_vision(HIW"\n$N�����ת���飬���е�"+weapon->name()+""HIW"�����������Ľ��⣬��������Ʈ�ݣ����������潣֮��"HIC"��"HIG"��"HIY"��"HIB"��"HIW"����\n" NOR,me,target);       
	if (me->query("quest/ljg/tyqj/pass1"))
	{
		message_vision(HIC"\n$N��������赵Ľ����ڻ��ͨ����������졹������ʱ������\n" NOR,me,target);       
		me->add_temp("apply/damage", skill/5);
		me->add_temp("apply/sword", skill/5);
	 }
//180��֮ǰֻ�ܳ�����Ŷ��

    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
    if(me->is_fighting(target))
    {    
		message_vision(HIR"    ��һ����\n" NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    }
    if(me->is_fighting(target) && target->query("qi")> 0 )
    {   
		message_vision(HIR"    �ڶ�����\n" NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    }
    if(me->is_fighting(target) && target->query("qi")> 0 )
    {    
		 message_vision(HIC"    ��������\n" NOR,me,target);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

	}
    if(me->is_fighting(target) && lvl >= 250 && target->query("qi")> 0 )
    {
        me->add_temp("apply/damage", skill);
        message_vision(HIY"    ���Ľ���\n" NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
        
        if(me->is_fighting(target))
        {      
			message_vision(HIG"    ���彣��\n" NOR,me,target);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
        me->add_temp("apply/damage", -skill);
      }


      if(me->is_fighting(target) && lvl >= 350 && target->query("qi")> 0 )
       {        
		  message_vision(HIM"    ��������\n" NOR,me,target);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
 
	   }
//���ø�С�ɰ� �����߽�
      if(me->is_fighting(target) && lvl >= 350 && target->query("qi")> 0 ) 
      { 
        me->add_temp("apply/damage", lvl);
        target->set_temp("must_be_hit",1);
        message_vision(HBGRN+HIW" �����һ��Яǰ������֮�������������������ǵ��޿ɵ���\n" NOR,me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        target->delete_temp("must_be_hit") ;
        me->add_temp("apply/damage", -lvl);
        message_vision(WHT"$N����ʹ�ϣ�����"+weapon->name()+""WHT"���ֻӳ���\n" NOR,me,target);
//�ٴη�Ծ����������

        if(me->is_fighting(target))
		{
           if (random(me->query("combat_exp")/10000)> target->query("combat_exp")/20000 )
             {                
               message_vision(HIC "$nֻ�����˿�һ�䣬ԭ���Ѿ���������Ϣ�б�������һ����������\n" NOR,me,target);
               target->apply_condition("shengsi_poison",3);
              }
           else   
             message_vision(HIC "$nֻ���ö���һ�䣬��æ���ã�ԭ��ȴ��$N������Ϣ�з�����һ�������������ɵþ�����һ���亹��\n" NOR,me,target);

        }
	  }
	      me->add_temp("apply/attack", -skill/2);
	      me->add_temp("apply/sword",  -skill/4);
	      me->add_temp("apply/damage", -skill/4);
		if (me->query("quest/ljg/tyqj/pass1"))
		{
			me->add_temp("apply/damage",-skill/5);
			me->add_temp("apply/sword", -skill/5);
		}
          me->start_busy(2);
          me->start_perform(5,"��������졹");
          return 1;
}

int help(object me)
{
    write(WHT"\n�����潣֮��"MAG"�������"WHT"����"NOR"\n");
         write(@HELP
	�����潣֮����������죬�������飬�������У�
	���е�����֮�������������߽����������ҡ�
	���ҿ������мд������������˷���ʤ����
	����Ե�ɺϣ��ÿ��������֮���ܣ�����н���
	�η�Ծ����������һ��¥��
  
	perform sword.fengwu
	
Ҫ��
	�˻Ĺ��ĵȼ� 450 ����;
	�����潣�ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�����Ṧ�ȼ� 450 ���ϣ�
	����������� 12000 ����
	��ǰ�������� 1000  ����
	��ǰ�������� 1000  ����
	��������Ϊ�����潣��
	�����м�Ϊ�����潣��
	�ֳֽ���������
	��
HELP
    );
        return 1;
}
