//cangzhuo.c ��׾�� Write By sohu@xoja 2014/5/31
//��Ի�ɽ������׾�⣬����ԭ����������6-7�����ж�����
//���ƻ�ɽ����
//

inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>
#include <combat_msg.h>

string perform_name() {return HIM"��׾��"NOR;}

string *xue_name = ({
"����Ѩ","���Ѩ","����Ѩ","����Ѩ","����Ѩ","�Ϲ�Ѩ","���Ѩ","�ٻ�Ѩ","̫��Ѩ","��ǿѨ","��̨Ѩ"
});

int perform(object me, object target)
{       
        object weapon = me->query_temp("weapon");
        object weapon1=target->query_temp("weapon");
      
	  if (!me->query("quest/hmy/tmgcz/pass"))
		return notify_fail("��ֻ����˵����׾�⣬��û������ָ�㣬������ս����ʹ�á�\n");
        if( !target ) target = offensive_target(me);
 
        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("����׾�⡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!weapon
         || weapon->query("skill_type") != "club"
         || me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("�������޷�ʹ����ħ������׾�⡹�������ˡ�\n");
        if (me->query("quest/hmy/tmgf/jueji")!="pass")
	            return notify_fail("����δ�ڻ��ͨ������ʹ�ò�׾�⾳��\n");
        
        if((int)me->query_skill("tianmo-gun", 1) < 500
         ||(int)me->query_skill("club", 1) < 500
         ||(int)me->query_str() < 65   
         ||(int)me->query_dex() < 40)  
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á���׾�⡹��\n");

        if((int)me->query_skill("tianmo-gong", 1) < 500 
			&&(int)me->query_skill("xixing-dafa", 1) < 500)
                return notify_fail("��������ڹ���Ϊ�������޷����򡸲�׾�⡹�ľ��衣\n");

        if(me->query_skill_mapped("force") != "tianmo-gong"
         &&me->query_skill_mapped("force") != "xixing-dafa" )
            return notify_fail("��������ڹ����ԣ��޷�ʹ�á���׾�⡹��\n");

        if( (int)me->query("max_neili") < 12000 )
                return notify_fail("�������̫�����޷�ʹ�ó�����׾�⡹��\n");
        
        if( (int)me->query("neili") < 1500 )
                return notify_fail("�������������\n");

	   if( me->query_temp("tmgf/cangzhuo"))
                return notify_fail("������ʹ�á���׾�⡹��\n");

        me->start_perform(3, "����׾�⡹");
		if (weapon1)
		{
	      message_vision(HIC"\n����$Nʹ����ħ�����ġ���׾�⡹������"+weapon->query("name")+HIC+"֮��ֱָ�Է����е�"+weapon1->query("name")+HIC+"!��ʽ�Ե��쳣��׾��\n"NOR, me, target);
		}
        else message_vision(HIW"\n����$Nʹ����ħ�����ġ���׾�⡹������"+weapon->query("name")+HIW+"֮��ֱָ�Է�!��ʽ�Ե��쳣��׾��\n"NOR, me, target);
		message_vision(HIG"���С���׾�⡹������ħ�����ľ�����������׾֮��ȴ�������಻���������޾�֮�⡣һ�м��������������߸����У�\n"NOR, me);
        me->set_temp("tmgf/cangzhuo/wait",1);
		/*if (target->query_skill_mapped("sword")=="huashan-jianfa")
		{

		}*/
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		//me->add_temp("apply/attack",me->query_skill("tianmo-gun",1)/4);
       // if (me->is_fighting(target)) //ֱ�ӵ��ã�ȥ����������
           call_out("cangzhuo1", 0, me , target, weapon);
		   
		//me->delete_temp("tmgf/cangzhuo");
        return 1;
}
//�ڶ������У�����Ѩ��
int cangzhuo1(object me, object target, object weapon)
{
	string xue,msg;
	int t_exp,m_exp,t_dodge,m_skill,damage;
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 500
	    ||(int)me->query("jingli")< 150){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "����׾�⡹");
        return notify_fail(HIR"�������ʽ�޷����ᣬ����͸֧���ȣ��޷�����ʹ�á���׾�⡹��\n"NOR);
	}


    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "����׾�⡹");
		return notify_fail(HIR"���������������֣�ȴ�����Ѿ�û�������Ҫ�ˣ�\n"NOR);
	}
	if (!me->is_fighting(target)){
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "����׾�⡹");
		return 1;
	}
    
    t_exp = (int)target->query("combat_exp");
    m_exp = (int)me->query("combat_exp");
    t_dodge = (int)target->query_skill("dodge",1);
    m_skill = (int)me->query_skill("tianmo-gun",1);
    damage = 0;
	
    xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIR"\n$N��$n�������ƽ⣬�����ϵ�������"+weapon->query("name")+HIR"˳����һ�֣���Ȼ��ת"+
                  "������$n�ġ�"HIY+xue+HIR"��!\n"NOR, me, target);
    if ( random(m_exp) > t_exp/3
	|| random(m_skill) > t_dodge/3){
           damage = m_skill*(int)me->query("int")/2;
           if (userp(target)&&damage > m_skill*8) damage = m_skill*8;
           if (wizardp(me) && me->query("env/fengyi")) write("damage is "+damage+"!\n");
		me->receive_damage("neili",150);
		me->receive_damage("jingli",50);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		target->add_busy(1+random(2));
           msg = HIB"$n�����ϵõ�$N��������˱��У�����֮�࣬��"HIY+xue+HIB"����Ȼ�����У����ζ�ʱһ��!\n"NOR;
		   msg += COMBAT_D->damage_msg(damage,"����");
           msg = replace_string( msg, "$l", "��"+HIY+xue+NOR"��" );
           msg = replace_string( msg, "$w", weapon->name());
		   message_vision(msg,me,target);
       if(userp(me) && me->query("env/damage")) 
		  tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
	   
if(userp(target)&& target->query("env/damage")) 
		  tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR);
	 	
		//COMBAT_D->report_status(target, 1);
		me->set_temp("tmgf/cangzhuo/first","����");
		//����2
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
        call_out("cangzhuo2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	else{
		message_vision(HIY"$n��ʹ�Ṧ��˫������һ�㣬ʮ�����ɵ����˿�ȥ��\n"NOR,me,target);
		me->set_temp("tmgf/cangzhuo/first","δ��");
		//me->receive_damage("neili",200);
		//me->receive_damage("jingli",100);
		call_out("cangzhuo2", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}

    return 1;
}
//���������У��������󣬵�����������
int cangzhuo2(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg;
	int busy,damage;
	object tweapon=target->query_temp("weapon");
	
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 500
	    ||(int)me->query("jingli")< 150){
		if (userp(me))
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(3, "����׾�⡹");
        return notify_fail(HIR"�������ʽ�޷����ᣬ����͸֧���ȣ��޷�����ʹ�á���׾�⡹��\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
     if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return notify_fail(HIR"���������������֣�ȴ�����Ѿ�û�������Ҫ�ˣ�\n"NOR);
	}
	
	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return 1;
	}

	if(m_skill >= 350){
		if(me->query_temp("tmgf/cangzhuo/first")=="����"){
			message_vision(HIW"\n$Nһ�����У���$n�����ͻ�������˳�Ʊ仯������"+weapon->query("name")+HIW"������ޱȵ�����$n��"HIR"����"HIW"����\n"NOR, me, target);
			if ( random(m_skill) > t_dodge/4){
                    busy = m_skill/100;
                    if (busy > 2) busy = 2+random(3);
					    target->add_busy(busy);
                    if (wizardp(me)&&me->query("env/fengyi")) write("busy is "+busy+"!\n");
					    me->receive_damage("neili",100);
					    me->receive_damage("jingli",60);
					    target->add("qi",-m_skill*6);
					
					//msg = HIC"$N����ʹ��¯���࣬$n���ﻹ�мܵ�ס��ֱ��"HIR"����"HIC"һ�飬������ʧ���࣡\n"NOR;
					if (tweapon)
					{
						message_vision(HIC"$n����һ���ʹ����һ�ɣ�"+tweapon->query("name")+"������ϣ�\n"NOR,me,target);
						tweapon->move(environment(me));
					}
					//message_vision(msg,me,target);
					me->delete_temp("tmgf/cangzhuo/first");
					me->set_temp("tmgf/cangzhuo/second","����");
					//����3
					if (me->is_fighting(target))
						COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
						
                    call_out("cangzhuo3", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			   }
			   else{
				    message_vision(HIC"$n��������׺��ޱȣ���æ�͵�һ�����Ǳ������˿�ȥ��\n"NOR,me,target);
				    me->set_temp("tmgf/cangzhuo/second","δ��");
				    me->delete_temp("tmgf/cangzhuo/first");
					
				    call_out("cangzhuo3", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
			        }
		}
		else{
			message_vision(HIB"\n$N�����϶�$n��Ȼ����һ���������˿�ȥ������"+weapon->query("name")+
			HIW"��Ȼ��Ȼ����Բ�˳�$n��ͷ������ȥ��\n"NOR, me, target);
			    if ( random(m_skill) > t_dodge/4){
                    damage = m_skill*(int)me->query("str")/3;
                    if (damage > m_skill*10) damage = m_skill*10;
					damage = damage*2+random(damage);
                    if (wizardp(me)&&me->query("env/fengyi")) write("damage is "+damage+"!\n");
					me->receive_damage("neili",150);
					me->receive_damage("jingli",50);
					target->receive_damage("qi",damage,me);
					target->receive_wound("qi",damage*7/10,me);
					msg = HIR"$n���ܲ������������ţ���ʱ��Ѫ�������ѱ��������ˡ�\n"NOR;
					msg += COMBAT_D->damage_msg(damage,"����");
					
					message_vision(msg,me,target);
                    if(userp(me) && me->query("env/damage"))
			           tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
		            
if(userp(target)&& target->query("env/damage"))
			           tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR);
		            //COMBAT_D->report_status(target, 1);
			         me->set_temp("tmgf/cangzhuo/second","����");
			  //����4
					if (me->is_fighting(target))
			            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                     call_out("cangzhuo3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
				else{
					message_vision(CYN"$n���һ���������ھ��������м�ס��������һ����\n"NOR,me,target);
					me->set_temp("tmgf/cangzhuo/second","δ��");
					//me->receive_damage("neili",80);
					//me->receive_damage("jingli",40);
					call_out("cangzhuo3", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
				}
		}
	}
	else{
		if (userp(me))
		   me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
        return 1;
	}
    //me->add_temp("apply/attack",-me->query_skill("tianmo-gun",1)/4);
	return 1;
}
//�����к��У�
int cangzhuo3(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        //||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(1, "����׾�⡹");
            return notify_fail(HIR"�������ʽ�޷����ᣬ����͸֧���ȣ��޷�����ʹ�á���׾�⡹��\n"NOR);
	}
    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "����׾�⡹");
		return notify_fail(HIR"���������������֣�ȴ�����Ѿ�û�������Ҫ�ˣ�\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(1, "����׾�⡹");
		return 1;
	}

	if(m_skill< 450){
		if (userp(me))
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(1, "����׾�⡹");
        return 1;
	}
	if(me->is_fighting(target)){
		message_vision(HIY"\n$NĬ�����죬ȴ����������ֻ�����ৡ�������Х��˲��㹥������,�����Կ��ƿ�Ĺ���!\n"NOR, me, target);
		me->add("neili",-300);
		me->add("jingli",-150);
		me->add_temp("apply/attack",m_skill/10);
		me->add_temp("apply/dodge",m_skill/10);
		if (me->query_temp("xxdf/xixing")){
			message_vision(HIM"$N����"+chinese_number(me->query_skill("xixing-dafa",1)/100)+HIM"�����Ǵ󷨾�������ħ��������ʱ����!\n"NOR, me);
			me->add_temp("apply/damage",m_skill/10);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			
			me->add_temp("apply/damage",-m_skill/10);
		}
		else{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			
		}
		me->add_temp("apply/attack",-m_skill/20);
		me->add_temp("apply/dodge",-m_skill/20);
	}
	else{
		message_vision(HIC"\n$N���뷢�У�ȴ�����Լ��������ƣ�ֻ�ó��з���!\n"NOR, me, target);
	}
	me->start_perform(1, "����׾�⡹");
    call_out("cangzhuo4", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);

    return 1;
}
//���ĸ�����
int cangzhuo4(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{
	string msg,xue;
	int damage;

	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
	    me->delete_temp("tmgf/cangzhuo");
	    me->start_perform(3, "����׾�⡹");
            return notify_fail(HIR"�������ʽ�޷����ᣬ����͸֧���ȣ��޷�����ʹ�á���׾�⡹��\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
   	 if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return notify_fail(HIR"���������������֣�ȴ�����Ѿ�û�������Ҫ�ˣ�\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return 1;
	}

    if(m_skill<450
		//||me->query("quest/tmgf/cangzhuo4")!="pass"
	){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
                return 1;
	}
	
	xue = xue_name[random(sizeof(xue_name))];
    message_vision(HIR"\n����$N�ٴ�Ծ������"+weapon->query("name")+HIR"��������λ��ǡ�÷�����$n�ĺ��б仯��\n"NOR, me, target);
    if ( random(m_exp) > t_exp/2
	    || random(m_skill) > t_dodge*2/5){
            damage = m_skill*(int)me->query_str()/3;
            damage = damage*2 + random(damage);
        if (wizardp(me)&&me->query("env/cangzhuo")) write("damage is "+damage+"!\n");
	        me->receive_damage("neili",400);
	        me->receive_damage("jingli",200);
	        target->receive_damage("qi",damage,me);
	        target->receive_wound("qi",damage*7/10,me);
            msg = RED"$n��ʱ���ָ��ţ�������޿��������!\n"NOR;
	        msg += COMBAT_D->damage_msg(damage,"����");
            if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR); 
			
if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR);
			msg = replace_string( msg, "$l", "��"+HIY+xue+NOR"��" );
            msg = replace_string( msg, "$w", weapon->name());
	        message_vision(msg,me,target);
	        //COMBAT_D->report_status(target, 1);
	        target->add_busy(3+random(3));
	        target->apply_condition("no_perform",1+random(1));
	        //target->apply_condition("no_exert",1);
	        me->set_temp("tmgf/cangzhuo/forth","����");
			//me->delete_temp("tmgf/cangzhuo/");
	        me->start_perform(3, "����׾�⡹");
	        call_out("cangzhuo5", 1, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	else{
           message_vision(MAG"$n����������Ϭ����������ʽ��һ�����⣬�㴦�����ƣ�\n"NOR,me,target);
		   me->set_temp("tmgf/cangzhuo/forth","δ��");
	
		   target->apply_condition("no_exert",1);
		   me->start_perform(3, "����׾�⡹");
		   call_out("cangzhuo5", 0, me, target, weapon, t_exp, m_exp, t_dodge, m_skill);
	}
	return 1;
}
//���������
int cangzhuo5(object me, object target, object weapon, int t_exp, int m_exp, int t_dodge, int m_skill)
{

	if (!objectp(weapon)
        ||weapon->query("skill_type") != "club"
        ||me->query_skill_mapped("club") != "tianmo-gun"
        ||me->is_busy()
	    ||(int)me->query("neili")< 700
	    ||(int)me->query("jingli")< 350){
		
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
                return notify_fail(HIR"�������ʽ�޷����ᣬ����͸֧���ȣ��޷�����ʹ�á���׾�⡹��\n"NOR);
	}

    if(!objectp(target)||!living(target)||environment(target)!=environment(me)){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return notify_fail(HIR"���������������֣�ȴ�����Ѿ�û�������Ҫ�ˣ�\n"NOR);
	}

	if (!me->is_fighting(target)){
		if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
		return 1;
	}
 
    if(m_skill<300
		//||me->query("quest/tmgf/cangzhuo5")!="pass"
	){
    	if (userp(me))
		me->delete_temp("tmgf/cangzhuo");
		me->start_perform(3, "����׾�⡹");
                return 1;
	}
    message_vision(HIR"\n����$N"HIR"����һ�ţ���ʽ�����Źۣ�һ���м��޷��İ�����̬������"+weapon->query("name")+HIR"�����Ļ���������������ϵ���ƣ�\n"+
		               "$n"HIR"������Ц��ͻȻ֮�䣬����Ц�ݽ�Ӳ������������һ���������ëֱ������Ŀ��ת˲������$N"HIR"��������"+weapon->query("name")+"\n"
	  	               HIR"Խ��Խ���������������λʵ������˼�����$n"HIR"֪���Լ���ʽ�Ʊض����������֮�ϣ�\n"+
                       "������迴֮�����Ǽ�׾��ȴ�˼��ɣ�����������ʵ����ǿ�����浽�ˡ��Ծ��ƶ�����׾���ɡ��ļ��裡\n"NOR, me, target);
   me->add_temp("apply/attack",m_skill);
           if(me->query_temp("xxdf/xixing")&&me->query("xixing",1)>1){
			message_vision(MAG"$N���Ǵ���Ȼ��ת"+chinese_number(m_skill/100)+MAG"�����Ǵ��ھ�����!\n"NOR, me);
			me->add_temp("apply/damage",m_skill/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			me->add_temp("apply/damage",-m_skill/3);
		   }
		   else{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		   }
	me->add_temp("apply/attack",-m_skill);
	me->add("neili",-400);
	me->add("jingli",-200);
 
	me->delete_temp("tmgf/cangzhuo");
	me->start_perform(4, "����׾�⡹");

	return 1;
}

int help(object me)
{
    write(WHT"\n��ħ��֮��"HIM"��׾��"WHT"����"NOR"\n");
    write(@HELP
    ��ħ�������������ʮ����ħ֮����Գ��ħ���ų˷�͡��׺���ħ���ų���
	�ֵܶ����������������𽭺�������ʮ����Χ����ɽ�����䲻����ʹ��
	���ž����Ӵ�ʧ��������������˵�ڻ�ɽ��ɽʯ�����ֹ���ħ����ʽ��
	��������д�������Լ�̽����
    ����׾�⡹������ħ���������ڣ����Ʊ�׾�ޱȣ�ʵ������ף�һ��
	����ȴ�����������У�������̵�������Ҫ���ϼ����²�֪���б仯��
	����������ʵս��������õģ����輸�ؿ������ɾ�����һʽ����䣬
	һ��ǿ��һ�䡣
    ָ�perform cangzhuo
	ע�⣺set ��׾ �����⹦Ч
    Ҫ����ħ�������Ǵ�500��
          ��ħ���� 500 ����
          �������� 500 ����
          ������40���ϣ�
          ����������65���ϣ�
          ��ǰ����1500���ϣ�
          ��ǰ����350���ϣ�
          �������12000���ϣ�
   

HELP
	);
	return 1;
}
