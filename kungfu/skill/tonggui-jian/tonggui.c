// jianjue.c ͬ�齣�� ͬ�齣��
// modified by xjqx@SJ 2009/01/01
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ͬ�齣����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽�������ܹ�ʹ����ͬ�齣��������\n");

        if( (int)me->query_skill("tonggui-jian", 1) < 250 )
                return notify_fail("���ͬ�齣��������죬�޷�ʹ����ͬ�齣������\n");
                
        if( me->query_temp("tgj/tonggui"))
                return notify_fail("������ʹ�á�ͬ�齣������\n");
        
		if( !me->query("quest/qz/tgj/tonggui/pass"))
                return notify_fail("��ֻ��˵�����У�������ʹ�á�ͬ�齣������\n");
			

        if( (int)me->query_skill("xiantian-gong", 1) < 250 )
         return notify_fail("��������ڹ���򲻹����޷�ʹ����ͬ�齣������\n");

        if( me->query_skill_mapped("force") != "xiantian-gong")
        return notify_fail("�������ʹ�õ��ڹ����ԣ��޷�ʹ����ͬ�齣������\n");    

        if (me->query_skill_mapped("sword") != "tonggui-jian"
         || me->query_skill_mapped("parry") != "tonggui-jian")
                return notify_fail("�������޷�ʹ�á�ͬ�齣�������й�����\n");

        if( me->query("max_neili") <= 2500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ��ͬ�齣������\n");

        if( me->query("neili") <= 500 )
                return notify_fail("�����������������������ʩչ��ͬ�齣������\n");

        if( me->query("jingli") <= 500 )
                return notify_fail("��ľ������ޣ�������ʩչ��ͬ�齣������\n");

        message_vision(HIW"$N���ƶ��䣬�����Ա������ǵķ�λ����ʩչ�����н�������������ʽ���ң�ֻ�����أ������͹�$nҪ��!\n"
			+"$N���з��ݣ������͹���������$nͬ���ھ������ǡ�"HIR"ͬ�齣��"NOR"������ʽ��\n"NOR, me,target);
		
		if (me->query("neili")<500)
			me->set("neili",0);
        me->add("neili", -500);
        me->add("jingli", -300);
        
        skill = me->query_skill("tonggui-jian",1);
      	
		improve = skill/5 ;//ԭ����5
      	

        me->set_temp("tgj/tonggui", improve);
        
        me->add_temp("apply/sword", improve);
		me->add_temp("apply/attack", improve);
        me->add_temp("apply/damage", improve/2);

		me->add_temp("apply/dodge", -improve);
		me->add_temp("apply/parry", -improve);
		me->add_temp("apply/dexerity", -improve);
		me->add_temp("apply/armor", -improve);
        call_out("remove_effect", 1,  me, weapon, 7);
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int improve;
        if(!me||!me->query_temp("tgj/tonggui")) return;
		improve = me->query_temp("tgj/tonggui");
        
		if(!me->is_fighting()
         || !weapon
         || me->query_skill_mapped("sword") != "tonggui-jian"
         || me->query_skill_mapped("parry") != "tonggui-jian"
         || count < 1 )
		{
          
			me->add_temp("apply/sword", -improve);
			me->add_temp("apply/attack", -improve);
			me->add_temp("apply/damage", -improve/2);

			me->add_temp("apply/dodge", improve);
			me->add_temp("apply/parry", improve);
			me->add_temp("apply/dexerity", improve);
			me->add_temp("apply/armor", improve);
			me->delete_temp("tgj/tonggui");
			if (weapon)
				message_vision(HIW"$Nʹ��"NOR"��"HIR"ͬ�齣��"NOR+HIW"����"NOR+weapon->name()+HIW"��ͬ�齣�����������\n"NOR, me);

			return;
        }
        call_out("remove_effect", 1, me, weapon, count -1);
        
}               
string perform_name(){ return HIC"ͬ�齣��"NOR; }


int help(object me)
{
        write(HIG"\nͬ�齣��֮"+RED"��ͬ�齣������"NOR"\n\n");
        write(@HELP
	ͬ�齣��Ϊȫ������������ȫ�׽���ֻ�����أ������͹�����Ҫ����
	�������ͬ���ھ����ʵô�����ȫ�����Ӽɵ�ŷ�����书��ǿ����
	ŷ�����ػ���ԭʱȫ����и���֮�ݣ�Ϊ���������䵥ʱ��������
	������������������һ�˶���ȫͬ�š��𴦻��뽭���߹ּ���ľ��
	ʦ����ʱ�״�ʹ����
	ע�⣬����ֻ�����أ�ʹ�ô��л�����������������ȡ��ʱ���
	�����������á�
	
	ָ�perform sword.tonggui

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 2500 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	ͬ�齣���ȼ� 300 ���ϣ�
	���칦�ĵȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	������� 200 ���ϣ�
	��������Ϊͬ�齣����
	�����м�Ϊͬ�齣�������ȭ��
	�����ڹ�Ϊ���칦��
	�ֳֽ���������
HELP
        );
        return 1;
}
