//zhijian.c ָ��
//cre by sohu@xojh 2014
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve,i;
        i=10-(int)me->query("yyz/degree");
        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ָ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( me->query("family/family_name") !="������" )
                return notify_fail("��û�еõ�����һ��ָ�洫���޷�ʹ��һ��ָ�����Ρ�ָ������\n");
        if( objectp(weapon = me->query_temp("weapon")))       
                return notify_fail("������������������ܹ�ʹ����ָ��������\n");
		if (!me->query("quest/tls/zhijian/pass"))
		        return notify_fail("����Ȼ��˵������һ��ָ��ָ������������ȴ����ʹ�á�\n");

        if( (int)me->query_skill("yiyang-zhi", 1) < 350 )
                return notify_fail("���һ��ָ������죬�޷�ʹ����ָ������\n");
                
        if( me->query_temp("yyz/zhijian"))
                return notify_fail("������ʹ�á�ָ������\n");
		if( (int)me->query_skill("kurong-changong", 1) < 350 )
			if( (int)me->query_skill("qiantian-yiyang", 1) < 350 )
				return notify_fail("��������ڹ���򲻹����޷�ʹ����ָ������\n");
		if( me->query_skill_mapped("force") != "kurong-changong")
			if( me->query_skill_mapped("force") != "qiantian-yiyang")
				return notify_fail("�������ʹ�õ��ڹ����ԣ��޷�ʹ����ָ������\n");    

        if (me->query_skill_mapped("finger") != "yiyang-zhi"
         || me->query_skill_mapped("parry") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á�ָ�������й�����\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ��ָ������\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("�����������������������ʩչ��ָ������\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ������ޣ�������ʩչ��ָ������\n");

        message_vision(HBYEL+HIW"$N����һ��ָ�������������ʳָ����ָ�ɻ��ɿ죬��ʱ����Ʈ�ݣ����������磬����ָ֮�����ֺ����\n"+
		        "ֻ��$N��ָ����������˸�ų�Լ"+chinese_number(i)+HBYEL+HIW"������Ρ�ָ������!\n"NOR, me);
        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        if (me->query_skill_mapped("force")=="kurong-changong")
		   skill =me->query_skill("kurong-changong",1)/4+me->query_skill("yiyang-zhi",1);
      	else if (me->query_skill_mapped("force")=="qiantian-yiyang")
		   skill =me->query_skill("qiantian-yiyang",1)/6+me->query_skill("yiyang-zhi",1);
		
	

		improve = skill/5;//ԭ����5
      	
		if ( improve > 180 ) improve = 180 + (int)random(improve-180) / 100;

        me->set_temp("yyz/zhijian", improve);

        me->add_temp("apply/damage", improve/2);
        me->add_temp("apply/finger", improve);
		me->add_temp("apply/attack", improve);
        me->add_temp("apply/strength", improve/5);

        call_out("remove_effect", 1,  me,improve);
        if (me->query_skill("yiyang-zhi",1)< 500) 
			me->start_perform(1, "��ָ����");
        return 1;
}

void remove_effect(object me,int count)
{
        int i;
		object weapon;
        if(!me) return;
		weapon=me->query_temp("weapon");
        if(!me->is_fighting()
         || weapon
         || me->query_skill_mapped("finger") != "yiyang-zhi"
         || me->query_skill_mapped("parry") != "yiyang-zhi"
         || count < 0 )
		{
          i = me->query_temp("yyz/zhijian");
          me->add_temp("apply/damage", -i/2);
		  me->add_temp("apply/finger", -i);
		  me->add_temp("apply/attack", -i);
          me->add_temp("apply/strength", -i/5);
          me->delete_temp("yyz/zhijian");
          message_vision(HBYEL+HIW"$N"HBYEL+HIW"ʹ��һ��ָָ��������������ָ�ϵľ�������ʧ�����������\n"NOR, me);
		
  return;
        }
      
          //me->start_perform(1,"��ָ����");
		/*
		  if (!random(3)&&objectp(target))
		  {
			  switch (random(3))
			  {
				case 0:
					message_vision(HIW"$N������ָ��һʽ��"HIR"��ɷ"HIW"��������������͵�һ�����죬һ�ɴ���������ֱϮ$n���ؿڣ�\n"NOR,me,target);
					target->add_busy(1);
					break;
				case 1:
					message_vision(HIR"$Nһ��ָ�������"HIW"����"HIR"���Դ���������ͬʱ͸��$n���������Ϲ�Ѩ����ά�����Ѩ����������Ѩ����������Ѩ������������Ѩ��\n"NOR,me,target);
					target->add_condition("yyz_hurt",1);
					break;
				case 2:
					message_vision(HIC"$N̤ǰһ������ָ��"HIY"����"HIC"��������ӿ�����յ���$n��ǰ������Ѩ������Ѩ�������֮���\n"NOR,me,target);
					target->receive_damage("jingli",200+random(500),me);
					break;

			  }
			 
		  }*/
          call_out("remove_effect", 2, me, count -1);
       
}              
string perform_name(){ return HBYEL+HIW"ָ��"NOR; }

int help(object me)
{
        write(HIY"\nһ��ָ֮"+HIW"��ָ������"NOR"\n\n");
        write(@HELP
	���������һ��ָ�������£���һ��ָ�����˹���������ʳָ��Ѩ��
	��ָ�ɻ��ɿ죬��ʱ����Ʈ�ݣ����������磬����ָ֮�����ֺ�
	����������������֮�ʣ��ô�ָ���ȿ������������Ѩ����Ҳ
	�ɴ�Զ���۽���ȥ��һ�м��룬һ�����ˣ�ʵΪ�˵б����������
	����500���ɣ���������𷨾�տ����˼���������׼��������ơ�
	
	ָ�perform finger.zhijian
	
Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 3500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	һ��ָ�ȼ�   350 ���ϣ�
	Ǭ��һ���ȼ� 350 ���ϣ�
	����ָ���ȼ� 350 ���ϣ�
	����ָ��Ϊһ��ָ��
	�����м�Ϊһ��ָ��
	�����ڹ�Ϊ����������Ǭ��һ����
HELP
        );
        return 1;
}
