//wanshe.c ��������             
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HIB"��������"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i,damage;
	i=me->query_skill("lingshe-zhangfa",1)+me->query_skill("hamagong",1);

    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    if((int)me->query_skill("staff", 1) < 450 )
                return notify_fail("��Ļ����ȷ�������죬����ʹ���������塣\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("���������ȣ����ʹ���������壿\n");
    if (me->query_skill("lingshe-zhangfa", 1) < 450 )
		            return notify_fail("��������ȷ���������죬ʹ�����������������\n");
	if (me->query_skill("hamagong", 1) < 450 )
		            return notify_fail("��ĸ�󡹦�ȼ����㣬�޷�ʹ���������塣\n");
	if (me->query_skill("force") < 450 )
		            return notify_fail("����ڹ��ȼ�������ʹ�����������������\n");
	if (me->query_str(1) < 70)
		            return notify_fail("�������������ǿ����ʹ�����������������\n");
	if (me->query_skill_mapped("force") != "hamagong")
		            return notify_fail("���������塹��Ҫ�ø�󡹦Ϊ������\n");
    if (me->query("oyf/hamagong") < 3 )         
                return notify_fail("���������塹��Ҫ�ڻ�ɽ֮�۵õ�ŷ����ָ��ſ�ѧϰʹ�á�\n");
	  if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
		  return notify_fail("�����ڵ�״̬���޷�ʹ�����������塹������\n");                
      if((int)me->query("max_neili") < 15000 )
                return notify_fail("���������Ϊ����������ʹ���������壡\n");
      if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ���������壡\n");
                
        message_vision(HIR"\n$N����󡹦��������Ѩ�����з�����������������������������������������\n"+
        ""HIB"ͻȻֻ��$Nʹ�������ȷ����һ�С�"HIM"��������"NOR"��"HIB"������"+weapon->name()+HIB"����ֶ�ȥ��\n"+
        ""HIG"������ŷ�����ڻ�ɽ֮��Ϊ�˴򹷰���������֮�����޹����龫���ǣ��ľ���Ѫ����������һ�������Ǻ��߹�������Ҳ�øʰ��·磡\n"NOR,me,target);
    
    me->set_temp("lszf/wanshe",1);
    me->add("neili", -500-random(500));
    me->add_temp("apply/attack",  i/2);
    me->add_temp("apply/damage", i/3);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
	         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
	{
         if (weapon->query("id")=="guaishe zhang")
         {
			 message_vision(HIB"$N��Ȼ�����й�����һ�������������߹ֽ���˲�����һ�ɷۺ�ɫ����������$n\n"NOR,me,target);
			 target->receive_wound("jing", 10,me);
             target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +
                target->query_condition("bt_poison")); 
         }
		 message_vision(BLU"$N�û������е�"+weapon->query("name")+BLU"�ϵļ�̴���$n������������������״��"NOR,me,target);
		 if (random(me->query_str(1))>target->query_dex(1)/3)
		 {
			 message_vision(YEL"һ��С�ģ�Ϊ$N���еı�������Ѩ������ʱ��Ѫ���ɵ�һ�͡�\n"NOR,me,target);
			 target->add_busy(1+random(2));
			 target->apply_condition("no_exert",1);
		 }
		 else message_vision(CYN"$n��������ʩչ���Ϸɾ�������Ȼ��Щ�Ǳ��������Ƕ��˿�ȥ��\n"NOR,me,target);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	}
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

    
    damage=me->query_str(1)*damage/20+random(damage);
    if (me->is_fighting(target)
     	&& random(me->query_str(1)) > target->query_con()/2) 
	{
     	message_vision(HBRED"\nͻ��"+weapon->query("name")+HBRED"���ٵ���ת�������������߽������з��ٲ�ס��$n���壡��������Ѹ���ϴ���\n"NOR,me,target);
     	target->add_busy(4+random(2));
     	message_vision(HBRED"���������߷�����$n�ʺ�ҧȥ�����ȵ�����ҧס����$nҪ����$n���������߶��ˣ�\n"NOR,me,target);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
        target->receive_damage("jing",damage/10,me);
     	target->add_condition("snake_poison",5+random(5));
     	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    }
    if (me->is_fighting(target)) {
     	message_vision(HIY"\n$N������"+weapon->name()+HIY"ֱͦ�����۹�����"+weapon->name()+HIY"�ϣ��������Ʈ�ڣ����ȼ�������籩��Ҳ���ƶ���\n"+
	    HIY"����ֱָ$n�Ŀڣ����ǵ�����ɽ֮��ŷ����Ż����Ѫ���һ���ƽ⡸"HIG"�����޹�"NOR"��"HIY"����ʽ��\n"NOR, me, target);	   
		//target->receive_damage("qi",damage);
		target->receive_wound("qi",damage/6);
		target->apply_condition("no_perform",1+random(2));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		}			                      
	if ( me->is_fighting(target)&&me->query_temp("hmg_nizhuan")){
		message_vision(HBBLU+HIW"\n������ת֮���ڻ�ɽ֮���ٵ�ŷ����ָ��֮������֮����ʤ��ǰ��$N���������������"NOR+weapon->name()+HBBLU+HIW"\n$N�����۸��֮���ھ���������ʹ��ʹ����������ǧ���������̾۳�һ����$n�ؿ��ػ���ȥ��\n"NOR,me,target);
		me->set_temp("must_be_hit",1);
		me->add_temp("apply/damage",me->query_skill("hamagong",1)/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	    me->delete_temp("must_be_hit");
		me->add_temp("apply/damage",-me->query_skill("hamagong",1)/4);

      }
	me->delete_temp("lszf/wanshe");					
    me->add_temp("apply/attack",  -i/2);
    me->add_temp("apply/damage",  -i/3); 	
    me->start_perform(5,"���������塹");
	me->start(2+random(2));
    return 1;
}

int help(object me)
{
        write(HIC"\n�����ȷ�֮"+HIB"���������塹"NOR"\n\n");
        write(@HELP
	�����ȷ����ǰ���ɽ��ѧ�������ڣ�ŷ����һ�������ߺ͸�󡹦���ｭ����ƾ�����
	���񼼵���������ƺ�������������ɽһ����ѧ������ɽ��ѧ�Ժ��������ա��綾
	����Ϊ��ɫ��������������ŷ������������߹��ڻ�ɽ֮��һս��Ϊ���ƽ������޹�
	����ʽ�������������ں��߹�����󶼲�����Ϊ�����
	����ʽΪ�����书,���ھ������
	Ҫ�󣺵�ǰ���� 1000  ���ϣ�
		��ǰ���� 1000  ���ϣ�
		������� 15000 ���ϣ�
		�����ȷ��ȼ� 450 ���ϣ�\
		��󡹦�ĵȼ� 450 ���ϣ�
		��������ȼ� 70 ���ϣ�
		����ȭ��Ϊ����ȭ����
		�����м�Ϊ�����ȷ���

HELP
        );
        return 1;
}

