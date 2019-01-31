// jianqin.c һ��ִ�٣�һ��ִ��
// cre by sohu@xojh 2014
// ������ʥ һ��ִ�٣�һ��ִ��������ǿ��������ʵʩһ�Ķ���֮��

#include <ansi.h>

#include <combat.h>

inherit F_SSERVER;

int exert(object me,object target)
{
	int i;
    string msg;
    object weapon,jwq;
	
	jwq=present("qin",me);
	
	i=me->query_skill("xuantian-wuji",1);

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("���ٽ�˫����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
			return notify_fail("�����޽�,����ôʹ�ó����ٽ�˫������\n");
   
    if(!jwq || !jwq->query("qinjian") )
			return notify_fail("������û�д��٣�����ʹ�á��ٽ�˫������\n");
	if( me->query_temp("lyj/liangyi") )
			return notify_fail("������ʹ�����Ǿ�������ʹ�á��ٽ�˫������\n");
	if( me->query_temp("xtwj/qinjian") )
			return notify_fail("������ʹ�á��ٽ�˫������\n");
    if( (int)me->query_skill("liangyi-jian", 1) < 350 )
			return notify_fail("������ǽ�����δ���ɣ�����ʹ�ã�\n");
	if ( me->query_skill_mapped("sword")!="liangyi-jian")
            return notify_fail("��Ľ����������ǽ����޷�ʹ���ٽ�˫����\n"); 
    if ((int)me->query_skill("xuantian-wuji", 1) < 350)
            return notify_fail("��������޼������̫ǳ��\n"); 
	if( (int)me->query("max_neili", 1) < 5000 )
			return notify_fail("����������������㣬����ʹ���ٽ�˫����\n");
    if( (int)me->query("neili", 1) < 1000 )
			return notify_fail("�������������㣬����ʹ���ٽ�˫����\n");
	
	 if(!me->query("quest/kl/xtwj/qinjian/pass"))
			return notify_fail("����δ�����ٽ�˫����\n");
		
		
				
    me->start_exert(1+random(3),"���ٽ�˫����");     	
    
    msg = HBGRN+HIY "\n$N�������֣�������糵���������������������̣���ʽ���Ӷ�䣬˿�������κ�Ӱ�졣\n"NOR;    	
	msg += BLU "\n���$N���ִ��ݵشӱ������ͳ�һ��"+jwq->query("name")+BLU"������£����Ĩ���������������죡\n"NOR;    	

	message_vision(msg, me, target);	
	me->set_temp("xtwj/qinjian",1);
	call_out("remove_effect",1,me,i/5);
	return 1;
}

void remove_effect(object me, int count)
{
	
	int i;
	object jwq;
	if (!me) return;
	
	i=me->query_skill("xuantian-wuji",1);
	
	jwq=present("qin",me);
	
	if (objectp(me))
	{
        if  ( !me->is_fighting() || count < 0 )
		{	
        
			me->delete_temp("xtwj/qinjian");			
			if (i<450)
			{
				message_vision(WHT"\n$N�������޼����վ�������һ��С�Ľ����Ұ���������\n"NOR, me);
				jwq->add_temp("duan",1);
				//����������ʹ����κ��ٶϵ���450������
				if (jwq->query_temp("duan")>10)
				{
					message_vision(HIY"\n$N�������޼����վ����������һ�����ұ��㰴�ϣ����ٳ��׷�ȥ��\n"NOR, me);
					jwq->broken("���ϵ�");
				}

			}
			else message_vision(CYN"\n$N�������޼�����Ȼ�ڻ��ͨ��������£���ٷŻ����С�\n"NOR, me);
			return;
		}
		call_out("remove_effect", 2, me, count -1);
        return;

	}
}

string exert_name() {return CYN"����˫��"NOR;}

int help(object me)
{
        write(CYN"\n�����޼���������˫������"NOR"\n");
        write(@HELP
	�����Ϊ����֮�˳�Ϊ�����彣�����־������ų�������ʥ
	���ݺ�����Լ����ԣ���Ϊ��һ����Ϊ��֮������Ϊ��ĩ��
	�������������˴��ԣ�����һ·��������ɽ�����£���
	һ��������ս����ǰ���У�����������������׼ҵ���ʱ
	��ƾ�������ڹ���һ��ִ����һ�ֲ��٣��𾪵�����
	
	ע�⣬���似��Ϊ��һ�Ķ���֮Ч�������Բ��ܺ����ǽ�
	�������Ǿ����á�����ʹ��ģʽ��������Լ�������
	
	ָ�exert qinjian

Ҫ��:
	�����޼��� 350 �����ϣ�
	������� 5000 �㣻
	��ǰ���� 1000 �㣻
	���ǽ��ȼ� 350 �����ϣ�
	�����ڹ�Ϊ�����޼�����
	��������Ϊ���ǽ�����
	��Ҫ��ִ���������
              
HELP
        );
        return 1;
}


/*
  if( random( attp ) > random( defp )/2 || target->is_busy()){
        
                message_vision( RED "$n�����������Ѿ�����ɢ����Ƭ���У�ȫ��Ѫ��ģ����\n\n"NOR, me, target );
        
                damage = me->query_skill("liangyi-jian",1) + (int)me->query_skill("xuantian-wuji", 1)*2;
                damage = damage - random( target->query_skill("dodge")/3 );
                damage *= 2;
                if (damage>2500) damage = 2500;
                
                target->receive_wound("jing", random( damage/2 ));
                target->receive_damage("qi", 20 + random(damage));
                target->receive_wound("qi", 20 + damage);
                target->start_busy(3 + random(4));
                
                
                //׷�ӹ���
                if( random( attp ) > random( defp ) || target->is_busy()) {
 
          message_vision( BBLU+HIW "$N�������޼����ӵ�������"HIG"��������"BBLU+HIW"�����������������ʱ�����޽����н���\n\n"
         + NOR + RED"$n�ҽ�һ���������Ѿ������ν�����͸��\n"NOR, me, target );
 
                        damage *= 2;
                        target->receive_wound("jing", random( damage/2 ));
                        target->receive_damage("qi", 20 + random(damage));
                        target->receive_wound("qi", 20 + damage);
                        target->start_busy(2 + random(8));
                        }
            

        }


		
        msg = HIC "$N" HIC "���г�����âԾ�������Ⱪ������������ƺ������Ҵ���$n"
              HIC "��\n$n" HIC "��������ƫ�󣬼�������ת����ֻ��һɲ������ɲʱϮ"
              "�����ף�\n";
        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 || !living(target))
        {
                me->start_busy(2);
                target->start_busy(random(3));
                damage = (int)me->query_skill("sword");
                damage = damage / 2 + random(damage / 2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIC "$n" HIC "��æ��ת��ȴ����$N"
                                           HIC "�Ľ�����û����ƫ��" + weapon->name() +
                                           HIC "��ʱ��$n" HIC "����������һ��Ѫ����"
                                           "ѪӿȪ�����\n" NOR);
                me->add("neili", -180);
        } else
        {
                me->start_busy(2);
                msg += HIY "����$p" HIY "����һЦ��������ת����Ȼ$P"
                       HIY "�Ľ�ʽͻȻ��չ����$p" HIY "��ǰ\n������"
                       "�����硣ȴ��һ����ë��û�˵���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
*/