// By kingso

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

string exert_name() { return HBMAG HIY"�޺���ħ"NOR; }

int exert(object me,object target)
{
     //  string msg;
       int i;
       if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
               return notify_fail("���޺���ħ��ֻ����ս����ʹ�á�\n");

       
       if( (int)me->query_skill("luohan-fumogong",1) < 350 )
                return notify_fail("����޺���ħ�����������ʹ�����޺���ħ��\n");  
       if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("��Ļ����ڹ����������ʹ�����޺���ħ��\n");  
       
       if( (int)me->query("jingli", 1) < 1500 )
                return notify_fail("�����ھ���������\n");
       if( (int)me->query("neili", 1) < 2000 )
                return notify_fail("����������������\n");
       if (me->query_temp("luohan/sp_fast"))
                return notify_fail("������ʹ���޺���ħ��\n");

       //msg = 
           message_vision( HBMAG HIY "ֻ��$N����ͻȻ��â�������ǣ���ȣ���"HIG"�޺���ħ��"HIY"��Χ��ʱ�о������˵ľ���ӭ��������$n�ٸ��Լ���ѹ����һ�����ε�����֮�У������������ѣ�\n"NOR, me, target);


       me->add("neili", -(700+random(300)));
       me->add("jingli", -(100+random(50)));
       me->add("max_neili", - random(30));
    //   message_vision(msg, me);
       i = me->query_skill("force", 1)/10 + me->query_skill("luohan-fumogong",1)/20 + me->query_skill("dodge")/10;
       me->add_temp("apply/dexerity", -i/2);
       me->add_temp("apply/parry", -i/2);
    //   me->add_temp("apply/strength", i/2);
       me->add_temp("apply/damage", i);
       me->set_temp("luohan/sp_fast", i);
       me->set_temp("double_attack", 1);
        if( me->is_fighting(target) && (int)me->query_skill("luohan-fumogong",1) > 199 ) {
        me->add_temp("apply/attack", i*20);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       if( me->query("env/�޺���ħ") == "��ħ" ){ 
       target->add_condition("luohan_hurt", random(i/2)); }
        me->add_temp("apply/attack", -i*20);
        }  
       if (me->query_skill("luohan-fumogong",1) < 300) me->start_exert(1, "�޺���ħ");
       call_out("remove_effect", 1, me, i, i);
       return 1;
}
void remove_effect(object me, int count, int dex)
{
        if (!me) return;
        if( me->query_skill_mapped("force") != "luohan-fumogong" 
         || (!me->is_fighting() )
         || me->query("neili") < 100
         || count < 1){
                me->add("neili", - (25 + random(25)));
                me->add_temp("apply/dexerity", dex/2);
                me->add_temp("apply/parry", dex/2);
                me->add_temp("apply/damage", - dex);
              //  me->add_temp("apply/strength", -dex/2);
                me->delete_temp("luohan/sp_fast");
                me->delete_temp("double_attack");
                message_vision(HBMAG HIW"$N�������ã���Ԫ��ģ��޺���ħ�������չ���\n"NOR, me);
                return;
        }
        call_out("remove_effect", 1 , me, count -1, dex);
}

int help(object me)
{
        write(HIG"\n���޺���ħ����"NOR"\n");
        write(@HELP

        �޺���ħ��֮�޺���ħ�������ڴ�����������
        �ܹ���ս�����������ҵ�ս����ͬʱ��Ѹ��֮��
        �����Է���������ʹ��ʱҲ������һ������Ԫ��        

        Ҫ��  �޺���ħ���ȼ� 350 ���ϣ�
                �����ڹ��ȼ� 350 ���ϣ�
                set �޺���ħ ��ħ
                ���ڹ������书�����ӷ�ħ����Ч����
                ÿ��ʹ����������������30�㣻
                
                
HELP
        );
        return 1;
}

