//cred by sohu@xojh 2013
#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
		int damage,p;
        int i = me->query_skill("huifeng-jian",1);
        weapon=me->query_temp("weapon");
        damage=i+me->query_skill("linji-zhuang",1);
		
        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("����ڹ����Ƕ����ķ����޷�ʹ�á�������������\n");
        if( me->query_skill("linji-zhuang", 1) < 250 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á�������������\n");
        if( me->query_skill("huifeng-jian", 1) < 250 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á�������������\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("������û�н����޷�ʹ�á�������������\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á�������������\n");
        if(me->query("max_neili") < 2000 )
                return notify_fail("���������Ϊ����������ʹ�á�������������\n");
        if(me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ�á�������������\n");
        if(me->query("jingli") < 750 )
                return notify_fail("�����ھ������㣬����ʹ�á�������������\n");
        if(me->query_temp("em/jue"))
                return notify_fail("������ʹ�á�������������\n");
        if(me->query_skill("sword", 1) < 250 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á�������������\n");

       

        msg = HIW "$N������Ȼ��Ĭ���ţ�ʹ������"+RED"������������"+HIW"����ʱ$N���е�"+weapon->query("name")+HIW"����һ����ɱ���⾳��\n"NOR;
        me->set_temp("em/jue", 1);
        if(random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/2
		||random(me->query_int(1))>target->query_int(1)/2
        ||random(me->query("combat_exp"))>target->query("combat_exp")/2) {
            			
            me->add_temp("apply/attack", i/2);
            me->add_temp("apply/damage",  i/4);
            me->add_temp("apply/sword",  i/2);
			if (target->query_temp("em/mie"))
            {
				msg = msg + CYN"$nֻ��$N�𽣡���������쳣�����ʽ�������ܣ�����ѹ��������\n"NOR;
				damage+=damage*4;
            }
			if (me->query_skill("jiuyin-zhengong"))
			{
				msg = msg + BLU"$N�����������������ֳֵĽ��ϣ�����������\n"NOR;
				damage += damage/2;
			}
			if (target->query("family/family_name")=="����"&&!userp(target))
			{
				damage+=damage/6;
			}
			//����npc����
			if (!userp(me)&&me->is_fighting()&&damage>4000)
               damage=4000+random(damage-4000)/10;
			msg = msg + HIR "���$nһ��С�ı�$Nһ�����У���Ѫ�ɽ���\n" NOR;	
			//����jue������bug
			//if (damage>target->query("qi")) damage=target->query("qi")-10;
			
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/4,me);
            p = (int)target->query("qi")*100/(int)target->query("max_qi");
		    msg += COMBAT_D->damage_msg(damage, "����");
		    msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";		    
			message_vision(msg, me,target);
            if (objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack", -i/2);
            me->add_temp("apply/damage", -i/4);
            me->add_temp("apply/sword",  -i/2);
			           
			//if (objectp(target)&&object->is_fighting())
			if (me->query_skill("huifeng-jian",1)>350 && me->query("em/jue/pass") && objectp(target) && me->is_fighting(target))
				call_out("next1", 0, me, target, i);			
		
        }
        else
           {
			msg = msg + MAG "����$n�侲�Ƿ�������ֵ����㿪�����ɱ��һ��,��ȴ�ŵ�һ���亹��\n" NOR;
            me->add_busy(1+random(1));	
            message_vision(msg, me,target);
		   }            
		    me->start_perform(1+random(3),"������������"); 
        me->delete_temp("em/jue");
        return 1;
}

int next1(object me, object target, int i)
{
        string msg;
        int damage;
        object weapon;
        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
               // me->add_temp("apply/attack", -i/2);
               // me->add_temp("apply/damage",  -i/4);
               // me->add_temp("apply/sword",  -i/2);
                me->delete_temp("em/jue");
                return 0;
        }

        message_vision(HBRED+YEL "$N����һ��������������ټ�ʮ��ׯ,��ϡ��𽣡��ķ�,ʹ����������������\n"NOR,me);
        me->add_temp("apply/attack", i/2);
        me->add_temp("apply/damage", i/4);
        me->add_temp("apply/sword",  i/2);
       // message_vision(msg, me, target);
        if((random(me->query("max_neili")) + me->query_int()*me->query_skill("force",1)/2) >(target->query("max_neili") + target->query_int()*target->query_skill("force",1)/2)/4 )
		{
                message_vision(HIW"$N�𽣡���������쳣����ط��������������,���������С�\n"NOR,me);
                damage = me->query_skill("huifeng-jian",1);
                damage += me->query_skill("sword",1);
                damage += random(damage);

                target->add("neili",-(500+random(150)));
				target->receive_damage("qi",damage,me);
			    target->receive_wound("qi",damage/2,me);
                target->add_condition("no_exert",1+random(2));    // �𽣡���������쳣�������ѹ������
                target->add_condition("no_perform",1+random(2)); //���˵�2�������Ż�����Ч����
               
                //COMBAT_D->report_status(target, random(2));
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                me->add("neili",-300);
                me->add("jingli",-100);
        } else {
                
                message_vision( CYN"$n��Σ���ң����²������䣬���㿪����\n"NOR,me,target);
                me->add_busy(1+random(2));
        }
        me->add_temp("apply/attack", -i/2);
        me->add_temp("apply/damage", -i/4);
        me->add_temp("apply/sword",  -i/2);
        me->delete_temp("em/jue");        
        return 1;
}
string perform_name(){ return HBRED+HIW"��������"NOR; }

int help(object me)
{
        write(WHT"\n�ط������֮��������������"NOR"\n\n");
        write(@HELP
	�ط���������Ƕ�ü����֮�أ���ɽ��ʦ����������ʱ�ھ���
	��Ϊ�ḻ�������ǳ�������һ���������ϣ���ϼҴ���ѧ��
	�书���輫Ϊ��񡣺�������������ã�������������ʮ��
	��󳹴��򣬳���Ϊ�ᣬ������ü��ѧ--�ط��������
	�������ҵ��������������ʦ̫���У������ԭ�����ʦ̫
	���ط�����������󣬸���ʦ�ֹº��ӵĲ���������ʹ����
	��ʦ̫������������Ҫ�ľ������𽣺;���������
	��������ƾ����ḻ��ս�����飬�������Լ������ƣ�����
	��Чɱ�˶��֣������ʦ̫��ϲ�����ӣ������ҳ��ڶ�ü����
	���𷨵ĵ����ж������������Ե�ɺϣ�ϰ�ö�ü��ѧ����
	�澭�ٳ�ƪ��������������һ��¥��350��С�ɣ�450�����
	�ɡ�
	
	ָ�perform sword.jue

Ҫ��
	��ǰ���������� 1000 ���ϣ�
	������������� 2000 ���ϣ�
	��ǰ���������� 750 ���ϣ�
	�ط�������ȼ� 250 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 250 ���ϣ�
	�����ڹ�Ϊ�ټ�ʮ��ׯ��
	��������Ϊ�ط��������
	�����м�Ϊ�ط��������
	�ֱֳ�����

HELP
        );
        return 1;
}


