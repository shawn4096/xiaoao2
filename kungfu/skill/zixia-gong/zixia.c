// zixia.c yun zixia ������ս���м���ʱ����
// Update By lsxk@hsbbs ����set������double neiliЧ��,���ӹ�Ч��
/* update by lsxk@hsbbs ����Ϊ�����������������Ҫset, ս���������ǰ��������
   ս��ǰ��������ֱ�ӵ�����ս��ǰ���������ѷ�ֹ����zixia��add max_neili
*/

#include <ansi.h>

//inherit F_CLEAN_UP;
inherit F_SSERVER;

string exert_name() {return HBMAG"��ϼ��"NOR;}

void remove_effect(object me);

int exert(object me, object target)
{
    if( !target ) target = offensive_target(me);

        if (!me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ������ϼ����\n");
        if(userp(me) && !me->query("quest/huashan/zixia/pass"))
           if(userp(me) && me->query("quest/huashan")!="����")
                return notify_fail("��ϼ���˻�ɽ���ھ�ѧ����ǻ�ɽ���ڵ��ӣ�����͵ѧ������ϼ�񹦣�\n");

        if( (int)me->query("neili") < 1000  )
                return notify_fail("�������������\n");
        if( (int)me->query_temp("zxg/zixia") ) 
                return notify_fail("���Ѿ���������ϼ���ˡ�\n");

        me->set_temp("zxg/zixia", me->query("neili"));
        me->add("neili", -500);
        if(me->query("neili")>me->query("max_neili")*2){
                 me->set("neili",me->query("max_neili")*2);
        }
       
        message_vision(MAG "$N���˻�ɽ���ھ�����ϼ�񹦣���������ʱ��ʱ�֡�\n" NOR, me);
      	me->add_temp("apply/attack",(int)me->query_skill("zixia-gong",1)/5);
        me->add_temp("apply/armor",(int)me->query_skill("zixia-gong",1)/7);
		me->add_temp("apply/damage",(int)me->query_skill("zixia-gong",1)/7);
       	
        call_out("remove_effect", 1, me,me->query_skill("zixia-gong",1)/5);
        call_out("zixia_temp",1,me,target);
        if (me->query_skill("zixia-gong",1)<450) me->start_exert(2+random(2), "��ϼ��");
        else if (me->query_skill("zixia-gong",1)<550)  me->start_exert(1, "��ϼ��");

        return 1;
}

void remove_effect(object me)
{
        if (objectp(me)) {
                if (me->is_fighting() && (int)me->query("neili")>800) {
                        call_out("remove_effect", 1, me);
                        return;
                }
               // if((int)me->query("neili")>(int)me->query_temp("zxg/zixia"))
                
				me->add_temp("apply/attack",-(int)me->query_skill("zixia-gong",1)/5);
                me->add_temp("apply/armor",-(int)me->query_skill("zixia-gong",1)/7);
		        me->add_temp("apply/damage",-(int)me->query_skill("zixia-gong",1)/7);
				me->set("neili",(int)me->query_temp("zxg/zixia"));
                me->delete_temp("zxg/zixia");
                tell_object(me, MAG"�����ϼ��������ϣ����������������ˡ�\n"NOR);
        }
}

void zixia_temp(object me,object target)
{
    int lvl;
    if(!me) return;
    if(!target) return;

    lvl = (int)me->query_skill("zixia-gong",1)*2/3 + (int)me->query_skill("force",1)/3;
    if (me->query_temp("zxg/zixia") && me->is_fighting(target) )
     {
          if (random(lvl) > ( (int)target->query_skill("parry") )*3/4 ){
              message_vision(HIM "$NǱ����ϼ�񹦣���$n��������ʱ�������У�\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
          }
          else if (random(lvl) > ( (int)target->query_skill("parry") )/2 ){
              message_vision(MAG "$NǱ����ϼ�񹦣���$n��������ʱ�ݹ�һ�У�\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
          }
          call_out("zixia_temp",1,me,target);
      }
}

int help(object me)
{
   write(YEL"\n��ϼ�񹦡�"MAG"��ϼ��"YEL"����"NOR"\n");
	write(@HELP
	����ɽ�Ź����׹���ϼ��������ϼ�񹦲���Ϊ�����湦������������
	�����Լ������ľ������ò��������������˾���ȴ�����Լ��ڶ���ʱ
	�ۼ���������������������ʱ��Ѱ�һ�����з�����ʹ�ö���ɱ����
	�練�ơ�����ϼ�񹦴���ߣ����л�����Ч��
	450����С�ɣ�550�����ɣ�ȡ��busy��
	ָ�exert zixia
	Ҫ�󣺵�ǰ���� 1000 ���ϡ�	
	˵����
		����ϼ�񹦴���300��ʱ������ͨ����set ��ϼ�� ���塿
		��ʹ����ϼ�񹦵��������Ч����ÿ����һ�λ���Ч������
		�����Ĳ��ֵ�ǰ�����������ʹ�ã�
HELP
	);
	return 1;
}
