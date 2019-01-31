// jianjue.c ȫ�潣�� ����
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
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( me->query("family/family_name") !="ȫ���" || !me->query("quest/qzjf/jianjue") )
                return notify_fail("��û�еõ�ȫ���洫���޷�ʹ��ȫ�潣�������Ρ���������\n");
        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽�������ܹ�ʹ��������������\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 350 )
                return notify_fail("���ȫ�潣��������죬�޷�ʹ������������\n");
                
        if( me->query_temp("qzjf/jianqi"))
                return notify_fail("������ʹ�á���������\n");

        if( (int)me->query_skill("xiantian-gong", 1) < 350 )
            return notify_fail("��������ڹ���򲻹����޷�ʹ������������\n");

        if( me->query_skill_mapped("force") != "xiantian-gong")
            return notify_fail("�������ʹ�õ��ڹ����ԣ��޷�ʹ������������\n");    

        if (me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan" ))
                return notify_fail("�������޷�ʹ�á����������й�����\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ����������\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("�����������������������ʩչ����������\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ������ޣ�������ʩչ����������\n");

        message_vision(HBCYN+HIC"$N�������£�������һ����������������" +NOR+weapon->name() +HBCYN+HIC"�����ۺ�����칦��ע�뽣�У�\n"+
		        "$N�Ľ�������˸һ���������޵�����"+NOR+HIR+"��������"HBCYN+HIC"!\n"NOR, me);
        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("xiantian-gong",1)/2+me->query_skill("quanzhen-jianfa",1);
      	improve = skill/5 + random(skill/5);//ԭ����5
      	if ( improve > 150 ) improve = 150 + random(improve-150) / 5;

        me->set_temp("qzjf/jianqi", improve);
        me->add_temp("apply/damage", improve/2);
        me->add_temp("apply/sword", improve);
        me->add_temp("apply/strength", improve/5);
        call_out("remove_effect", 1,  me, weapon, improve);
        if (me->query_skill("quanzhen-jianfa",1)<450) me->start_perform(5, "��������");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan")
         || count < 1 ){
          i = me->query_temp("qzjf/jianqi");
          me->add_temp("apply/sword", -i);
          me->add_temp("apply/damage", -i/2);
          me->add_temp("apply/strength", -i/5);
          me->delete_temp("qzjf/jianqi");
	    if (weapon)
                message_vision(HIW"$Nʹ��"NOR"��"HIR"����"NOR+HIW"����"NOR+weapon->name()+HIW"�Ľ�������ʧ�����������\n"NOR, me);
		
          return;
        }
        else {
          //me->start_perform(1,"��������");//���ﲻ��set�������޷�halt
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}              
string perform_name(){ return HIC"����"NOR; }

int help(object me)
{
        write(HIG"\nȫ�潣��֮"+HIC"����������"NOR"\n\n");
        write(@HELP
	ȫ�潣��������������ȫ��̵����Ž������������ͨ���ϣ�
	����ԭ��β��Ѩ���ȴ�ӿȪ�ŵ׳壬ӿȪ������ϥ����ϥ
	������β�̣����趥�ϻ������������ش���ȵ�ţ���¥ʮ��
	�����ҡ��仯��΢����ȫ��̵�ȫ���ķ�������á�
	ȫ��������ڼҹ���Ϊ����ȫƾһ��������ת�����Ե����
	�����������ʹ���칦���������������֮�У��γɽ���
	
	ָ�perform sword.jianqi
	
Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 3500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	ȫ�潣���ȼ� 350 ���ϣ�
	���칦�ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������Ϊȫ�潣����
	�����м�Ϊȫ�潣�������ȭ��
	�����ڹ�Ϊ���칦��450���ɡ�
HELP
        );
        return 1;
}
