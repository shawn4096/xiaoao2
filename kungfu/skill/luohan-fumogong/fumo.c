#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int skill);

int exert(object me, object target)
{
        int skill;
        string fam;
        fam = me->query("family/family_name");

        // ������������������
        if (userp(me)
         //  && fam != "������"
         //  && fam != "������"
         //  && fam != "������"
           && ! me->query("quest/Ħ����/luohan")
            )
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if (target != me)
                return notify_fail("��ֻ�����޺���ħ���������Լ���ս������\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        
         //�޸�Ϊ�������Ӻ�����õ��������Ч��һ��
        if ((int)me->query_skill("dacheng-fofa", 1) > 100
           ||(int)me->query_skill("buddhism", 1) > 100
           || (int)me->query_skill("huanxi-chan", 1) > 100)
	        message_vision(HBMAG HIY "$N" HIY "�ߺ�һ����ţ������޺���ħ��"
                                "����ȫ��Ƥ��һ�����" NOR + HBMAG HIY"�Ͻ�" HIY
                                "ɫ��һ���ֳ��ֳ�һ����" HIY "���" HIY "��\n"
                                NOR, me); 
           
                             
  /*      else

        if (fam == "������")
	        message_vision(HIY "$N" HIY "�ߺ�һ����ţ������޺���ħ��"
                                "����ȫ���������ȣ�������֮���͡�\n"
                                NOR, me);
*/
        else 
	        message_vision(HIY "$N" HIY "΢һ���������޺���ħ�񹦣�"
                                "ȫ������������ֳ�" NOR + HIB "����" HIY
                                "��" HIR "Ѫ��" HIY "��ɫ��\n" NOR, me);

 
        me->add_temp("apply/attack", me->query_skill("luohan-fumogong", 1)/2);
        me->add_temp("apply/damage", me->query_skill("luohan-fumogong", 1)/3);
        me->add_temp("apply/parry", - me->query_skill("luohan-fumogong", 1)/3);
        me->set_temp("luohan_power",1);
        me->set_temp("powerup", 1);
       

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill);

        if (me->is_fighting())
                me->start_busy(0);
        return 1;
}
void remove_effect(object me, int skill)
{
	
	 if (objectp(me)) {
                if (me->is_fighting()) {
                        call_out("remove_effect", 1, me, skill);
                        return;
                }

           me->delete_temp("powerup");
	    
           me->add_temp("apply/attack", -me->query_skill("luohan-fumogong", 1)/2);
           me->add_temp("apply/damage", -me->query_skill("luohan-fumogong", 1)/3);
           me->add_temp("apply/parry", me->query_skill("luohan-fumogong", 1)/3);

	    message_vision(HIR"\n$N���޺���ħ��������ϣ��������ջص��\n"NOR, me);
	    return;

	}
}

string exert_name() { return HIY"��ħ��"NOR; }
int help(object me)
{
        write(HIY"\n���޺���ħ����"NOR"\n");
        write(@HELP

        �޺���ħ��֮��ħ����������������ͬС�ɡ�
        �������޺���ʱ�����������ҵĹ����������С�
        ���ǽ����мܡ�����Ƿ��ŵ���ʹ��Ч�����á�

        Ҫ��  �޺���ħ���ȼ� 100 ���ϣ�
                �����ڹ��ȼ� 100 ���ϣ�
                set �޺���ħ ��ħ
                ���ڹ������书�����ӷ�ħ����Ч����
                              
                
HELP
        );
        return 1;
}


