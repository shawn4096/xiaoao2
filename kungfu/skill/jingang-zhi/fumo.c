// by sohu@xojh 2014.1
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp,skill;
        int damage;
        skill=me->query_skill("jingang-zhi",1);
     //   if (userp(me) && ! me->query("sl/jgz/pass"))
             //   return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ����շ�ħ������\n");
                        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����շ�ħ����ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("�������ֲ���ʹ�á���շ�ħ������\n");
        if (me->query_skill("force",1) < 400)
                return notify_fail("��Ļ����ڹ�����Ϊ����������ʹ����һ������\n");
		if (me->query_temp("jgz/fumo"))
                return notify_fail("������ʹ�ý�շ�ħ��ʹ����һ������\n");
		if (me->query_skill("finger",1) < 400)
                return notify_fail("��Ļ���ָ����Ϊ����������ʹ����һ������\n");
        if (me->query_skill("force",1) < 400)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");
        if (me->query("max_neili") < 8000)
                return notify_fail("��������������Ϊ����������ʹ����һ������\n");
		if (me->query("neili") < 2000)
                return notify_fail("��ĵ�ǰ��������Ϊ����������ʹ����һ������\n");
        if (me->query_skill("jingang-zhi", 1) < 400)
                return notify_fail("��Ĵ������ָ��Ϊ������Ŀǰ����ʹ�á���շ�ħ������\n");

        if (me->query("neili") < 3000)
                return notify_fail("��������������޷�ʹ�á���շ�ħ������\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi"||me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("��û�м����������ָ������ʹ�á���շ�ħ������\n");

        msg = HIR "$N" HIR "������Ϣ����˫Ŀ��ס��$n"+HIR"���ϣ���Ϣ����ת������������������ģ�����������΢�ı���֮����\n"+
              HIY "$n" + HIY "һ㵣�֪�����Ƿ������ڵ������书��������ڣ��������а�������ǽ�շ�ħ��ͨ��\n" NOR;
		message_vision(msg,me,target);
        me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/strength",skill/10);
        me->add_temp("apply/damage",skill/5);
		me->add_temp("apply/finger",skill/8);
        me->set_temp("jgz/fumo",skill);
		call_out("remove_effect",1,me,target,(int)skill);
       
        return 1;
}

void remove_effect(object me,object target,int count)
{
        int skill;
		object weapon=me->query_temp("weapon");
        if(!me||!living(me)) return;
        
		if(!me->is_fighting()
         || weapon
         || me->query_skill_mapped("finger") != "jingang-zhi"
         || me->query_skill_prepared("finger") != "jingang-zhi" 
         || count < 1 )
		{
          skill = me->query_temp("jgz/fumo");
         me->add_temp("apply/attack",-skill/3);
		 me->add_temp("apply/strength",-skill/10);
         me->add_temp("apply/damage",-skill/5);
		 me->add_temp("apply/finger",skill/8);
         me->delete_temp("jgz/fumo");
	     message_vision(HIY"$Nʹ�꡸��շ�ħ����,��ָ�Ͼ�������ʧ�����������\n"NOR, me);
          return;
        }
        else {
          //me->start_perform(1,"����շ�ħ����");
          call_out("remove_effect", 1, me,target, count-1);
        }

}              
string perform_name(){ return HIC"��շ�ħ��"NOR; }

int help(object me)
{
        write(HIG"\n�������ָ֮"+HIC"����շ�ħ������"NOR"\n\n");
        write(@HELP
	�������ָ�������־���������ŵ���ʦ�����������������һ��������
	�ջ�Ļ�ͷ�ӣ����ƹ����������ɮ�������Ǳ��꣬�ʳ�����Ź����
	��䱻���������������Ѫ�������ѧ�䱨���������й���֮�ǣ�������
	��ʮ�����͵ѧ�ɼ��ϳ˵��书���������Լ����书��ʤ������ɮ�ڣ���
	��һ��һ�ȵ������Ħ�ô�У�з��ѡ����ڴ�У�Ͻ����ش���Ħ�þŴ��
	�ӣ��������Ħ������������ʦ����ʱ�û���������������ڵ���Ǳ����
	�н�������к��Լ��й����ڵ���λɮ��һһʹ���ִ����������������
	���������һ�ɡ��������ָ��Ϊ����������似��
	��������ͷ�ӵ������䵱ɽ���Դ˾�����ս���޼ɣ�ͬʱ��֪��λ����
	�����ô˾����Ϳ��Դ�ʦ��ץ���Կ��ƿ죬���˿��Դ�ʦ����ץ�ֲ�ɱ��
	���Դ�ʦ���ɼ����书������֮����
	
	ָ�perform finger.fumo

Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 3500 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	���ָ�ȼ� 400 ���ϣ�
	�׽�ȼ� 400 ���ϣ�
	����ָ���ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	����ָ���ұ�Ϊ���ָ��
	�����ڹ������ơ�450���ɡ�
HELP
        );
        return 1;
}