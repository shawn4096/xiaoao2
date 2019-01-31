// ������ɫ,wuse.c 
// cre by sohu@xojh
// ������һ�У���ʵ�м�仯���.����ϲŭ���֣���״�ٳ�������һ������ʱ�����������ƣ���ϲ��ϲ�����ǵ��ǣ�������������
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void check_fight(object me,object target,int time);

int perform(object me, object target)
{
        int lvl;

        lvl = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("��������ɫ��ֻ����ս����ʹ�á�\n");
        if( me->query("per")< 27 )
                return notify_fail("�㳤����˼�Ʒ��ʹ�á�������ɫ��ֻ��������Ż��\n");   

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������ɫ����\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 350 )
                return notify_fail("�����Ȼ�����ƻ�������죬ʹ������������ɫ��������\n");
		if( (int)me->query_skill("strike", 1) < 350 )
                return notify_fail("��Ļ����Ʒ���������죬ʹ������������ɫ��������\n");

		if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ���������죬ʹ������������ɫ��������\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
			|| me->query_skill_mapped("parry") != "anran-zhang"
			|| me->query_skill_prepared("strike") != "anran-zhang"
)
                return notify_fail("�������޷�ʹ�á�������ɫ��������\n");

      

        if((int)me->query("max_neili") < 5000)
                return notify_fail("�������������̫����ʹ������������ɫ����\n");      

        if((int)me->query("neili") < 1000)
                return notify_fail("����������̫����ʹ������������ɫ��������\n");
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ���������ɫ��������\n"); 
   //     if((int)me->query("eff_qi") >= (int)me->query("max_qi"))
              //  return notify_fail("����������ܺã���ôʹ�ó���������ɫ��������\n");
		if ((int)me->query("divorce")>0)
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����������\n"); 
        if( me->query_temp("arz/wuse")) 
                return notify_fail("����������ʹ�á�������ɫ��������\n"); 

        message_vision(BLU"ȴ��$Nʹ��һ��"HIR"��������ɫ��"BLU"������һ�У���ʵ�м�仯���.����ϲŭ���֣���״�ٳ���\n"
						+"$nһ������ʱ�����������ƣ�$Nϲ��$nϲ��$N����$n�ǣ�������$n��ȫ������$N�� \n\n"NOR,me,target);

        me->set_temp("arz/wuse", 1);
		call_out("check_fight",1,me,target,(int)lvl/20);
   
        me->add("neili", -random(800));
        me->add("jingli", -100);
        if (me->query_skill("anran-zhang",1)<450)
			me->start_perform(2,"������ɫ");

        return 1;
}

string perform_name(){ return BLU"������ɫ"NOR; }

void check_fight(object me,object target,int time)
{
        int i;
		if (!me) return;
		if (me->query_temp("weapon")
         || me->query_temp("secondary_weapon")
		 || me->query_skill_mapped("strike") != "anran-zhang" 
         || me->query_skill_prepared("strike") != "anran-zhang" ){
			
			me->delete_temp("arz/wuse");
			me->start_perform(4,"������ɫ");
            tell_object(me, HIR"\n��ʹ�ù��򲻶ԣ���������ɫ������������ϣ����ص���.\n" NOR);
            return;
        }
        if ( !target
			|| time < 1
			|| ! me->is_fighting(target))
		{
           
            me->delete_temp("arz/wuse");
            tell_object(me, BLU"\n�㡸������ɫ������������ϣ����ص���.\n" NOR);
            return;
        }
        call_out("check_fight", 1, me, target,time -1);
}


int help(object me)
{
        write(HIB"\n��Ȼ������֮"+BLU"��������ɫ��"NOR"\n");
        write(@HELP

	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	������ɫ��������һ�У���ʵ�м�仯��ˣ�����ϲŭ
	���֣���״�ٳ�������һ������ʱ�����������ƣ���ϲ
	��ϲ�����ǵ��ǣ������������ҡ�����������Ӱ��ʤ��
	֮������֮��Х��������ָ߳�һ��������޷�ʹ��
	
	perform strike.wuse

Ҫ��
	�����Ʒ�Ҫ�� 350 ������
	��Ȼ�Ʒ�Ҫ�� 350 ������
	�����ڹ�Ҫ�� 350 ������
	��ǰ����Ҫ�� 5000 ����
	��ǰ����Ҫ�� 1000 ����
	������òҪ�� 26  ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
