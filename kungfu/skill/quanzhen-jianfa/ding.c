// ding. ������
// Modified by action@SJ
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string perform_name() {return HIB"������"NOR;}

int perform(object me, object target)
{        
        object weapon;
        int damage,p,force;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�������롹ֻ����ս���жԶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");    

        if( (int)me->query_skill("xiantian-gong",1) < 100 )
                return notify_fail("������칦�ȼ�����������ʩչ�������롹��\n");

        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʩչ�������롹��\n");
                
        if ((int)me->query_skill("quanzhen-jianfa", 1) < 100)
                return notify_fail("���ȫ�潣��������죬����ʹ�á������롹��\n");
                
        if (me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("��û�м���ȫ�潣��������ʹ�á������롹��\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("����������㣬����ʩչ�������롹��\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("����������㣬����ʩչ�������롹��\n");

        if( (int)me->query("jingli") < 600 )
                return notify_fail("��ľ������㣬����ʩչ�������롹��\n");

        //if( target->is_busy()) 
                 //return notify_fail("�Է����Թ˲�Ͼ�أ��㲻æʩչ�������롹��\n");

        me->start_perform(3, "�������롹");

        force = me->query_skill("force",1) + me->query_skill("xiantian-gong", 1);
        
		message_vision(HIW"$N�������Ž���������̤��һ�С�"HIR"������"HIW"������б�̣�"+weapon->query("name")+""HIW"��ȻԾ����ٿ�Ļ��������ǹ⣬����$n��\n"NOR,me,target);
		message_vision(HIC"��һ���������㣬��������ʽ�������޲�ǡ���ô�������ƽƽ���棬��ȴû���覴ã���������ȫ�潣����\n"NOR,me,target);
		message_vision(HIY"\n�⼸���ǹ����缸ö����һ������$n�������Ѩ��\n"NOR,me,target);
		if(random(force) > target->query_skill("force",1)
		 ||random(me->query_skill("sword",1))>target->query_skill("dodge",1)/3)
		{
           damage = force+me->query_skill("sword",1)+me->query_skill("quanzhen-jianfa",1);
           damage =2*damage;
		   damage += random(damage);
           if(target->query_skill("force",1) - 50 > force)
             damage = damage/2;
           if(target->query_skill("force",1) > (force)*2)
              damage = random(1000);
           //if((force) > target->query_skill("force",1)*2)
              damage = damage+random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

		   if(damage > 2000)
              message_vision(HIR"\nͻȻ֮�䣬$n�ؿ�һʹ���ƺ���һö��ϸ�ļ������һ�¡���һ�´�ʹ\n"+
                                     "ͻ�������������Σ�ʵ���ʣ�һ�ɽ���ͻ����Ļ����񹦣�ֱ�����ķΣ�\n"NOR,me,target);            
           
		   target->receive_damage("qi", damage, me);
		   //target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/5, me);
          // target->set_temp("last_damage_from", "���������")
		   
		   me->add("neili", -damage/10);
           if (me->query("neili")<0) me->set("neili",0);
          
		   limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"����ȫ���������һ����һ��һ����飡\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
           
if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
           me->start_busy(1);
           me->add("jingli", -20);
           target->add_busy(1);
		   if (!userp(target) && me->query_temp("xtg/wuqi"))
				target->add_busy(2+random(4));		   
           
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -5);
           tell_object(me, HIY"����"+target->query("name")+"�����������ͼ��бԾ�ܿ��˹�����\n"NOR);

		   me->start_busy(2);         
        }
        return 1;
}

int help(object me)
{
        write(HIG"\nȫ�潣��֮"+HIW"�������롹��"NOR"\n\n");
        write(@HELP
	��������ȫ�潣��������ǣ�����似��������������
	���۳ɵ㣬Ȼ��ͨ�����ⷢ�������жԷ�Ѩλ�����ɶ�
	�Է����һ�������ˣ�Ҳ����������Ѩ�����ƶԷ�����
	��������ַ���ʤ��,����Ҫ��ʹ���칦��������Ԫ
	
	ָ�perform sword.ding

Ҫ��
	��ǰ�������� 300 ���ϣ�
	����������� 1000 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	ȫ�潣���ȼ� 100 ���ϣ�
	���칦���ȼ� 100 ���ϣ�
	�����Ṧ�ȼ� 100 ���ϣ�
	��������Ϊȫ�潣����
	�����м�Ϊȫ�潣�������ȭ��
	�����ڹ�Ϊ���칦��
	��ȫ������������칦����������������
HELP
        );
        return 1;
}
