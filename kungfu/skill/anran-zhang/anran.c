// cre by sohu@xojh 2014
// anran.c ��Ȼ������
// ��λ����Ҫ�ĸ�������

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string *pictures=({
"�ľ�����","�������","��������","�����ˮ","�ǻ��չ�","��������","��ʬ����", "ӹ������"
});
void check_fight(object me,object target,int time);

int perform(object me,object target)
{

		string picture;
        int i,j;       
        i = me->query_skill("anran-zhang", 1);
        if( me->query("eff_qi") > 0)
			j = me->query("max_qi") / me->query("eff_qi");
        else j = 0;
        picture = pictures[random(sizeof(pictures))];

        if( !target ) target = offensive_target(me);
        if( !target
         || !me->is_fighting(target) )
               return notify_fail("����Ȼ�����⡹ֻ����ս���жԶ���ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á���Ȼ�����⡹������\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
        )
               return notify_fail("����������ʹ�á���Ȼ�����⡹������\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 450 )
               return notify_fail("�����Ȼ��Ȼ�������Ʒ���򲻹���ʹ��������Ȼ�����⡹������\n");

        if((int)me->query_skill("strike", 1) < 450 )
               return notify_fail("��Ļ�������������죬ʹ��������Ȼ�����⡹������\n");

        if((int)me->query_skill("force",1) < 450 )
               return notify_fail("����ڹ��ȼ�������ʹ��������Ȼ�����⡹������\n");
        if (me->query("gender")=="����")
                    return notify_fail("��������ȫ��ʹ��������Ȼ�����⡹������\n");
 
       if (me->query("gender")!="����")
                    return notify_fail("���������㣬ʹ��������Ȼ�����⡹������\n");
        if((int)me->query_str() < 70)
               return notify_fail("�������������ǿ����ʹ��������Ȼ�����⡹������\n");

        if((int)me->query_dex() < 30)
                return notify_fail("�����������Ѹ�ͣ�ʹ��������Ȼ�����⡹������\n");

   
        if((int)me->query_temp("arz/anran")) 
                return notify_fail("����������ʹ�á���Ȼ�����⡹������\n"); 

        if((int)me->query("max_qi") <= (int)me->query("eff_qi"))
                return notify_fail("�������ڵ��ľ�����ʹ�÷��ӳ���Ȼ�����������\n"); 
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����������\n"); 
		
		if((int)me->query("neili") < 2000 )
                return notify_fail("�������������\n");

        if((int)me->query("jingli") < 1000)
                return notify_fail("��ľ���������\n");

        message_vision(HBRED+HIY"\n$N����������ݾ��������������ң���Ȼ֮�����Ķ�����û����ɵ��ĳ�һ��"HIG"��"+picture+"����\n"+
                          HBRED+HIY"�����Ʒ缤�����л��㱣�����ԼԼ��ɲʱ��Ȼ��Ȼ�������������������Ʋ��ɵ���\n"NOR,me,target);

        if (me->query("gender")=="����")
			i=i/2;
		else i=i/6;

		if (me->is_busy())
		{
			message_vision(HIG"$N����һ������$n��ͷ,���ƺ�$nֻ������ؿھ�ʹ������һ�Σ���ŭ�����o�����������ϡ�\n"NOR,me,target);
			me->start_busy(-1);
			target->receive_damage("qi",1000+random(3000),me);
		}
        me->add("neili", -random(1500));
        me->add("jingli", -random(600));
		
		me->set_temp("arz/anran", i);

        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i/4);
		me->add_temp("apply/strike", i/4);
		if (me->query("marry"))
		{
			message_vision(HIM"$N�����Լ��Ͱ���"+me->query("name")+"��ı�����ϣ�������Ȼ�������а�������Ȼ������⾳������������\n"NOR,me);
			me->add_temp("apply/strength",i/8);
			me->add_temp("apply/damage", i/4);
			me->add_temp("apply/strike", i/4);

		}

		if (me->query_skill("anran-zhang",1)<550)
			me->start_perform(1,"��Ȼ������");
		else if (me->query_skill("anran-zhang",1)<500)
			me->start_perform(2,"��Ȼ������");
		
        call_out("check_fight", 1 , me,target,(int)i/5);
        return 1;
}

void check_fight(object me,object target,int time)
{
        int i;
		if (!me) return;
        time = me->query_skill("anran-zhang",1)/5; 
        i=me->query_temp("arz/anran");
		if (me->query_temp("weapon")
			|| me->query_temp("secondary_weapon")
			|| me->query_skill_mapped("strike") != "anran-zhang"
			|| me->query_skill_prepared("strike") != "anran-zhang" ){
					me->add_temp("apply/attack", -i);
					me->add_temp("apply/damage", -i/4);
					me->add_temp("apply/strike", -i/4); 
					if (me->query("marry"))
					{						
						me->add_temp("apply/strength",-i/8);
						me->add_temp("apply/damage", -i/4);
						me->add_temp("apply/strike", -i/4); 
					}
					me->delete_temp("arz/anran");
					tell_object(me, HIR"\n��ʹ�ù��򲻶ԣ�����Ȼ�����⡹����������ϣ����ص���.\n" NOR);
					return;
        }
        if ( !target
         || time < 1
         || !me->is_fighting())
		{
					me->add_temp("apply/attack", -i);
					me->add_temp("apply/damage", -i/4);
					me->add_temp("apply/strike", -i/4); 
					if (me->query("marry"))
					{						
						me->add_temp("apply/strength",-i/8);
						me->add_temp("apply/damage", -i/4);
						me->add_temp("apply/strike", -i/4); 
					}            
					me->delete_temp("arz/anran");
					tell_object(me, HIR"\n�㡸��Ȼ�����⡹����������ϣ������չ������ص���.\n" NOR);
					return;
        }
        call_out("check_fight", 1, me, target,time -1);
}
string perform_name(){ return HBBLU+HIW"��Ȼ������"NOR; }
int help(object me)
{
        write(HIB"\n��Ȼ��Ȼ�������ơ�"WHT"��Ȼ������"NOR"����\n");
        write(@HELP
	
	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	
	��Ȼ�����⣬���������˼��õ��ľ��£��Ļ�����
	��Ȼ���������ڹ��������������ܷ��ӳ�������Ȼ
	����ʵ����Ȼ�����Ƶ���߾�����
	
	ע�⣺���˺���ʹ�á��������޷�ʹ�á����˺�Խ��
	��Ȼ����������Խ��550�����ɡ�Ů��������������
	�����ɡ�

	perform strike.anran

Ҫ��
	�����Ʒ�Ҫ�� 450 ������
	��Ȼ�Ʒ�Ҫ�� 450 ������
	�����ڹ�Ҫ�� 450 ������
	��ǰ����Ҫ�� 2000 ����
	��ǰ����Ҫ�� 1000 ����
	��ǰ����Ҫ�� 70  ����
	��ǰ��Ҫ�� 30  ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
