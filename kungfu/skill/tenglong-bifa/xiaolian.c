// guifei С�����
// created by olives@SJ
// Update By lsxk@hsbbs 2007/6/6
/*
     ��������Դ��������Լ��ؿ����䣬���˼ܾ��е�һ����Ȼ��գ���˳����
����һ����ڽ����������������ذ�׵����ֳ�ȭ������һȭ���ڽ������ģ�
ֻ�ǽ������ϡ���������ԵУ���һ����Ȼ�����˵��˱��ġ�ΤС���ִ��һ��
�����ã���

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name() {return HIR"С�����"NOR;}

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl,i,skill;
		skill=me->query_skill("tenglong-bifa",1);
        if(!target) target = offensive_target(me);

         if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��С����¡�ֻ����ս��ʱʹ�ã�\n");
/*
        if(me->query("family/generation")>2)
                return notify_fail("��С����¡�ֻ�а�������������ã�\n");
*/
        if(!objectp(weapon=me->query_temp("weapon"))
			|| weapon->query("skill_type") != "dagger")
             return notify_fail("������û��ذ�ף����ʹ�á�С����¡���\n");
        
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 70 )
                return notify_fail("����������ʹ�á�С����¡������»��˵��Լ���\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 400 )
                return notify_fail("�������ذ������������������ʹ�á�С����¡���\n");

        if((int)me->query_skill("dagger",1) < 400)
                return notify_fail("��Ļ���ذ����������������ʹ�á�С����¡���\n");

        if(me->query_skill_mapped("hand") != "chansi-shou"
        || me->query_skill_prepared("hand") != "chansi-shou")
                return notify_fail("������û������׼����˿�֣��޷�ʹ�á�С����¡���\n");

        
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�С����¡���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 400 )
                return notify_fail("��Ķ����󷨹������㣬�����á�С����¡���\n");

        if( (int)me->query_skill("force", 1) < 400 )
                return notify_fail("��Ļ����ڹ��������㣬�����á�С����¡���\n");

        if((int)me->query("max_neili", 1) < 4000)
                return notify_fail("���ֵ�������Ϊ���㣬����ʹ�á�С����¡���\n");

        if((int)me->query("eff_jingli", 1) < 2500)
                return notify_fail("���ֵľ�����Ϊ���㣬����ʹ�á�С����¡���\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�С����¡���\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("�������������㣬����ʹ�á�С����¡���\n");
        
		if(me->query("gender") == "����" )
                return notify_fail("����Ů����ô��ʹ�á�С����¡��أ�\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�������໥�ִ�������ʹ�á�С����¡���\n");

        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ���շ��˲���֮����������С����¡�"NOR;
        msg +=MAG "\n$Nʹ��һ�С�С����¡����Դ�������Լ��ؿ����䣬˳���ڵ���һ��������\n��$n������������ű��������ֳ�ȭ��$n�����������¡�\n"NOR;
        lvl = ((int)me->query_skill("tenglong-bifa",1)+(int)me->query_skill("chansi-shou",1)+(int)me->query_skill("dagger",1))/3;
        if (userp(target))
        {
			lvl+=(int)me->query_skill("dulong-dafa",1)/5;
        }
		message_vision(msg,me,target);
        
		me->add("jingli",-100);
        me->add("neili",-300);

        me->add_temp("apply/attack",lvl/2);
        me->add_temp("apply/damage",lvl/5);
		me->add_temp("apply/dagger",lvl/4);
        me->set_temp("sld/pfm/xiaolian",1);
             
        if (me->query("gender")=="Ů��"&& me->query("per")>28)
		{
             i=3;
			 me->add_temp("apply/damage",lvl/5);
		}
		else 
	    {
			i=1;
			me->add_temp("apply/damage",lvl/8);
		 }
		me->set_temp("sld/xiaolian",1);
        COMBAT_D->do_attack(me,target,weapon,i);
		me->delete_temp("sld/xiaolian");
		//��һ��
        if(objectp(target) && me->is_fighting(target))
        {
                //weapon->unequip();
                COMBAT_D->do_attack(me,target,weapon,i);//�ڶ���
                //weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me,target,weapon,1); //������
        if(objectp(target) && me->is_fighting(target))   //������
        {
                message_vision(HIR"$N�����������Ȼ�������б�����������У��������Զ������ڹ�����������ʱ����������\n"NOR,me,target);
				
				if (userp(target)) target->add_busy(1);
				else target->add_busy(3);
				
				weapon->unequip();
				me->add_temp("apply/hand",lvl/4);
				if(random(me->query("combat_exp"))>target->query("combat_exp")/i)
                        COMBAT_D->do_attack(me,target,weapon,i);
                else
                        COMBAT_D->do_attack(me,target,weapon,1);
				me->add_temp("apply/hand",-lvl/4);
				weapon->wield();
        }
        me->delete_temp("sld/pfm/xiaolian");
        me->add_temp("apply/attack",-lvl/2);
        me->add_temp("apply/damage",-lvl/5);
		me->add_temp("apply/dagger",-lvl/4);
        if (me->query("gender")=="Ů��"&& me->query("per")>28)
		{
             me->add_temp("apply/damage",-lvl/5);
		}
		else 
	    {
			me->add_temp("apply/damage",-lvl/8);
		 }
        me->start_busy(1+random(2));
        me->start_perform(4+random(2),"��С����¡�");
        return 1;
}

int help(object me)
{
   write(WHT"\n����ذ����"HIR"С�����"WHT"����"NOR"\n");
   write(@HELP
	����ذ�����������������������Ĳ���֮��
	�仯��ˣ�����ʤ������ν��Ů�˵����Ʒ�
	�ӵ����쾡�¡�
	С����£�������һ���⾳���ջ�Ů�˵�
	���Ʒ��ӵ����쾡�£������������ջ���
	���а���ɱ����������ذ������֮һ��
	  
	perform dagger.xiaolian

Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	����ذ���ȼ� 400 ���ϣ�
	����ذ���ȼ� 400 ���ϣ�
	�����󷨵ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	������Ҫ�� 70 ���ϣ�
	�����ұ��ַ�Ϊ��˿�֣�
	����ذ��Ϊ����ذ����
	�����н�Ϊ����ذ����	
	�Ա�����Ů����Ư��Ů���ж������ơ�
HELP
   );
   return 1;
}
