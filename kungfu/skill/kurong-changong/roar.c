// roar.c ������
// by sohu@xojh 2014
//�����á��ػ�������һ����ȣ����˶��о�����������졣������֪�����Ƿ�����һ�ż��ϳ˵Ĺ���
//������ʨ�Ӻ𡯣�һ���Ϻ����������������������о���֮Ч��

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        string force;
        mapping msg;
        object *ob;
        
        int i, skill, damage;

		if( (int)me->query("max_neili") < 5000 )
                return notify_fail("����������������\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("��ĵ�ǰ����������\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("�����󳪼�Ϊ���ľ�������ĵ�ǰ����������\n");
        
		if (me->query_skill_mapped("force") != "kurong-changong" )
                return notify_fail("�����ڵ��ڹ�û������ܡ�\n");     

        if( environment(me)->query("no_fight") )
             return notify_fail("���ﲻ��ս����\n");
        if( (int)me->query_skill("force",1) < 250 )
                return notify_fail("��Ļ����ڹ��ȼ���Ϊ������\n");
		if( (int)me->query_skill("kurong-changong",1) < 250 )
                return notify_fail("��Ŀ��������ȼ���Ϊ������\n");
                
        if( (int)me->query_skill("buddhism",1) < 150 )
                return notify_fail("��ķ��������򲻹���\n");
        
        if( (int)me->query("jingli") < 150 )
                return notify_fail("��̫���ˣ�������Ϣһ�°ɡ�\n");      
        skill =me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1);
		//skill =skill+random(skill);
        me->add("neili", -random(2000));
        me->receive_damage("jingli", random(1000));

        

        message_vision(HBRED+HIY "������$N���ػ�--��һ����ȣ����˶��о�����������졣$Nʹ��������һ�ż��ϳ˵Ĺ���\n"
								+"����������������һ���Ϻ����������������������о���֮Ч��\n\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( wizardp(ob[i])||!living(ob[i]) || ob[i]==me ) continue;
                if( random(skill) < (int)ob[i]->query_skill("force",1)) continue;
                
                damage = skill;
                damage += damage;
                tell_object(ob[i], "�㱻��޺������ǰ���Σ�����һƬ�հף�����һ���㱡�\n");
                //���ܾ���ս����
				if (ob[i]->is_fighting()) 
                {
					ob[i]->remove_all_enemy();
					message_vision("\n$N����һ����ֹͣ��ս����\n", ob[i]); 
                }
                else if ((int)ob[i]->query_temp("pending/exercise")) 
                {
					force = ob[i]->query_skill_mapped("force");
					if (force) msg = SKILL_D(force)->exercise_msg(ob[i]);
					if (!msg || undefinedp(msg["halt_msg"]))
						message_vision("$N��ֻ����Ϣ��˳��վ��������\n", ob[i]);
					else
						message_vision("$Nֻ����Ϣ��˳,"+msg["halt_msg"], ob[i]);
                }
                else if ((int)me->query_temp("pending/respirate") != 0) 
                message_vision("$Nֻ����Ϣ��˳���������ڴ�����վ��������\n", me);
                
				ob[i]->interrupt_me();
                        
                if( damage > 0 ) {
                        if (ob[i]->query("jing")>=damage)
							ob[i]->receive_damage("jing", damage, me);
                        else ob[i]->unconcious();
                        
                }
                if(living(ob[i]) && (random(me->query("combat_exp",1)) > ob[i]->query("combat_exp") / 2)){
					message_vision(HIY"$Nһ���㱺��ƺ���ӳ��Щ�ٶۡ�\n"NOR,ob[i]);
					ob[i]->add_busy(random(skill/100) +1);
				}
        }
		me->start_busy(2);
		//if (me->query_skill("kurong-changong",1)<450)
		//{
		me->start_exert(4,"������");
		//}
        return 1;
}

string exert_name() {return HIY"������"NOR;}


int help(object me)
{
        write(WHT"\n��������������������"NOR"\n");
        write(@HELP
	�����������Ǵ����������Ժ--���������ֿ��ٳ��ϵ��ڹ��ķ�
	�ഫ�����������ڰ˿���֮�䡣��˿����ֶ����ϱ��������÷�
	�У����Ƿֱ���һ��һ�٣������ϱ��ֱ��ǣ������޳���������
	�֣��������ң������޾��� ���������޿����ٷ��Ǵ�ɡ�����
	�������������������һ����ֻ�εð�ݰ��١�
	
	����������ʹ���ƾ���ۺ��ڹ��Է���ʨ�Ӻ𷢳����ػ�������
	������һ����ȣ����˶��о�����������졣������һ����һ��
	�Ϻ����������������������о���֮��Ч��

Ҫ��:
	�������� 200 �����ϣ�
	������� 2000 �㣻
	��ǰ���� 1500 �㣻
	�輤���ڹ�Ϊ����������

HELP
        );
        return 1;
}


