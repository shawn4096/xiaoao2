
// pfm luda
// �ϱ��˱��� & ��ѧЧ��
// create by olives@SJ
// ���� �ټ�һhit������ȡ���Ա�����--by daidai
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HIG"³�����"NOR; }

int perform2(object me,object target);
int perform(object me, object target)
{
        int skill,ap,pp,damage,effect,p;
        object weapon = me->query_temp("weapon");
		object vweapon;
        string dodge_skill;
        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		vweapon = target->query_temp("weapon");

        if(userp(me) && me->query("family/master_id")!="hong antong")
                return notify_fail("��³�������ֻ�а��˽���������ã�\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 250 )
                return notify_fail("��Ĳ��˹���������죬����ʹ��³�������\n");
		if( (int)me->query_skill("hook", 1) < 250 )
                return notify_fail("��Ļ�������������죬����ʹ��³�������\n");
		if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("��Ķ����󷨲�����죬����ʹ��³�������\n");
    	if( (int)me->query("neili", 1) < 3000 )
       			return notify_fail("�������������㣡\n");
       	if( (int)me->query("jingli", 1) < 500 )
       			return notify_fail("�����ھ������㣡\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       			return notify_fail("��������Ϊ���㣡\n");
        if( (int)me->query_str() < 30  )
                return notify_fail("�������̫�ͣ�����ʹ��³�������\n");

        if(!weapon || weapon->query("skill_type")!="hook" )
                return notify_fail("�������޷�ʹ��³�������\n");
        if(weapon->query("sharpness")<3)
        		return notify_fail("�����й��Ӳ����������޷�ʹ��³�������\n");
		
		if (me->query_skill_mapped("hook") != "canglang-goufa"
		  ||me->query_skill_mapped("parry") != "canglang-goufa")
                return notify_fail("����ʹ�õ��似���ԣ������޷�ʹ�õ��ཱུ����\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("�㼤���ڹ����ԣ������޷�ʹ�õ��ཱུ����\n");

		skill = (int)me->query_skill("canglang-goufa", 1);
	    ap = me->query("combat_exp")/1000*me->query_str();
        pp = target->query("combat_exp")/1000*target->query_dex();
        
		if(me->query("gender")!="����")
				return notify_fail("�㲻�����ӣ����ʹ��³�������\n");

			
		skill+= (int)me->query_skill("dulong-dafa", 1);  

	
        me->add("neili", -350);
        me->add("jingli", -200);
        if(objectp(vweapon))       
        {
		    ap *= weapon->query("sharpness");
	        pp *= vweapon->query("rigidity");

 		    message_vision(HIY"\n$N˫��һ����������ݣ��ұ�ȴ���Ӷ�����"+weapon->query("name")+HIY"������$n����"+vweapon->query("name")+HIY"��"NOR,me,target);
  			if(random(ap+pp)>pp  )
  			{

  				message_vision(WHT"\n���$n����"+vweapon->query("name")+WHT"Ӧ�ֶ��ϣ�\n"NOR,me,target);
				vweapon->unequip();
				vweapon->move(environment(target));
				vweapon->set("name", "�ϵ���" + vweapon->query("name"));
				vweapon->set("value", 49);
				vweapon->set("weapon_prop", 0);
				target->reset_action();
			}
			else message_vision(CYN"\n���$n���һ���������$N��һ����\n"NOR,me,target);
 	   } else if((int)me->query_skill("canglang-goufa", 1)>350) 
	   { 
		    message_vision(HIY"\n$N˫��һ����������ݣ��ұ�ȴ���Ӷ���������"+weapon->query("name")+HIY"������$n��"NOR,me,target);
            me->add_temp("apply/attack", me->query_skill("canglang-goufa", 1)/2); 
			me->add_temp("apply/damage", me->query_skill("canglang-goufa", 1)/5); 
            COMBAT_D->do_attack(me,target,weapon,3);
            me->add_temp("apply/attack", -me->query_skill("canglang-goufa", 1)/2); 
			me->add_temp("apply/damage", -me->query_skill("canglang-goufa", 1)/5); 
        }	
		message_vision( HIY"\n$NͻȻһ��ǰ������������$n�����������ֻһ���ƣ�����ץ��$n�ҽ����ף�����"+weapon->query("name")+HIY"����$nС����\n"NOR, me, target);
	    ap = (int)me->query_skill("dulong-dafa",1) * (int)me->query("neili") * (int)me->query_str()/1000;
        pp = (int)target->query_skill("force", 1) * (int)target->query("neili") * (int)target->query_dex()/1000;
        ap *= (int)me->query("combat_exp")/1000;
        pp *= (int)target->query("combat_exp")/1000;
        ap /= 1000;
        pp /= 1000;
	    if(!living(target)) pp = 1;
		if (me->query("gender")=="����")
		   ap=ap*2;
       if(random(ap+pp) > pp/2){
                me->start_perform(4, "��³�������");
                if (!userp(target))
                   target->add_busy(2);
                damage =  me->query_skill("force",1)*2;
                damage += me->query("jiali") * 10;
                damage -= target->query_temp("apply/armor") * 2;
                effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
                damage *= (5-effect);
                if (damage < 0) damage = 0;
                damage = damage + random(damage);
                //if (!userp(me)&&damage > 5000) damage = 5000 + (damage-5000)/100;
				if (userp(target)&&damage > 5000) damage = 5000 + (damage-5000)/100;

              //  if(me->query("gender")!="����")
                //   damage = damage/3; 
 // ����������С   
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/4, me);
                target->add("neili",-random(2000));
                me->add("neili", -random(1000));
                if(damage >= 5000)
                        message_vision(HBYEL"��һ������ʹ����ȫ����˿��������أ�$n����������������������֮�䣡\n"NOR, me, target);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                //message_vision( damage_msg(damage, "����"), me, target);
                message_vision("���ֻ����$nһ���Һ���"+weapon->name()+"����$p��С���Դ���������Ѫ�������أ���\n"NOR, me, target);
                message_vision( "( $n"+eff_status_msg(p)+" )\n", me, target);
             //   msg= replace_string( msg, "$l", "С��");
                // msg= replace_string( msg, "$w", weapon->name());
                if(me->query_skill("canglang-goufa", 1)>450 && objectp(target) && me->is_fighting())
				{ 
					message_vision( HIY"\n$Nһ�����У�"+weapon->query("name")+HIY"һ�ճ��ƶ�ǰ������$n�������У�"NOR, me, target); 
					perform2(me, target);  
				}
        }
       else {
               // me->start_perform(2, "��³�������");
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                message_vision( SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
                message_vision( HIY"\n$Nһ�����У�"+weapon->name()+HIY"һ�չ��ض�ǰ����$n�������У�"NOR, me, target); 
                perform2(me, target); 
          }         
		       me->add("neili", -400);
               me->add("jingli", -100);
			   me->start_perform(3,"��³�������");
        return 1; 
}

int perform2(object me, object target)
{
	int lvl;
    object weapon = me->query_temp("weapon");
    if( !target
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target))
            	return notify_fail("ֻ����ս����ʹ�á�\n");
    lvl = (int)me->query_skill("canglang-goufa", 1)  /4; 
	me->add_temp("apply/attack", lvl); 
    me->add_temp("apply/damage", lvl/2); 
    weapon->unequip(); 
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    weapon->wield();
    if ( me->is_fighting(target) 
		&& random(me->query_skill("canglang-goufa", 1)) > 250)
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    me->add_temp("apply/attack", -lvl); 
	me->add_temp("apply/damage", -lvl/2); 
    me->add("neili", -400);
    me->start_busy(1);
    me->add("jingli", -200);
	me->start_perform(4,"��³�������");
}

int help(object me)
{
   write(WHT"\n���˹�����"HIG"³�����"WHT"����"NOR"\n");
   write(@HELP
	���˹�������������������������Լ�����ѧ�似
	��������������һ�׹����似��ȥ���ͼ򣬹���Ϭ
	��������ʤ����������ڱ����ϴ��е��Ӷ��ԣ���
	�Ƿǳ�ʵս�Ĺ�������³��������ǵ��͵�ǿ��
	�似�������Լ��ߵı����ͷ��������������ζԷ�
	�ı������Ҹ������ش���
	ע�⣺����Խ�����ȣ�Ч��Խ�ѣ��۱��������á�

	perform hook.luda

Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	���˹����ȼ� 250 ���ϣ�
	�����󷨵ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�����ұ��Ʒ�Ϊ�������ƣ�
	�����ڹ�Ϊ�����󷨣�
	�ֳֹ����������ҷ����Ȳ�����3
	�Ա����� ���ԡ�
HELP
   );
   return 1;
}
