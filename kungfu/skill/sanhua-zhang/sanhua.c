// sanhua-zhang perform �ļ�ɢ��(�����ﶬ)
// by beyon
// rewrite by snowman@SJ 05/12/1999

#include <ansi.h>

inherit F_SSERVER;
#include <combat_msg.h>

int hehe(object me, object target, int i)
{
	string dodge_skill, msg;
	string weapon;
	int j,atk,damage;
	//�˺��������й�ϵ
	
	damage = (random(me->query("int")/6)+1) * me->query_skill("sanhua-zhang",1);
	atk=me->query_skill("sanhua-zhang",1)+me->query_skill("yijin-jing",1);
        if (!userp(target)&&damage>5000) damage=5000+random((damage-1000)/100);
	    if (userp(target)&&damage>3000) damage=3000+random((damage-1000)/100);
        if(!target || ! me->is_fighting(target)) return 1;
	
	if (i >= 180 ) msg = HIW"\nͻȻ$N���һ������ʱ��$n����һ�����飬ֻ��$N��ü��֮�䲼����һ�㱡˪��˫Ŀ����ĵ���$n������ɮ��һ����һ���������"MAG"����÷��"HIW"��$n����������\n"NOR;          
	else if( i >= 140) msg = HIY"\nͻȻ$N˫��Ĭ��ģ�$n��Ȼ������ǰ��Ӱ��ɽ��������ɽ����������������ɽ��ˮ������һ�ж�����$nԶȥ������һ�����˵�"GRN"����ա�"HIY"�����˱Ƕ���������\n"NOR;           
    else if( i >= 120) msg = HIR"\nֻ��$N����ѽ��һ����������ǰ��ȥ��ͻȻһ���������֣��ƿ�֮���м���"WHT"��������"HIR"��$n����ǰ��ȥ��\n"NOR;             
    else msg = HIG"\n$NͻȻ���΢Ц������΢�ţ�����ӿ��һ�ɾ��磬�к���һƬƬ���̵�"CYN"�����ݡ�"HIG"��ֱ��$n����շ�ȥ��\n"NOR;
        
         
    if (random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/3||random(me->query_str())>target->query_con()/2)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -damage/3);
                me->add("jingli", -50);
                i = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(damage, "����") + "( $n"+eff_status_msg(i)+" )\n";
		        message_vision(msg, me, target);
				me->add_temp("apply/attack",atk/2);
                me->add_temp("apply/damage",me->query_skill("sanhua-zhang",1)/3);
				if (target->is_busy()||target->query_temp("nhz/fuxue")||!userp(target)) j=3;
				else j=1;
				//�������˷�Ѩ����˺�
		      	if (!userp(target)||target->query_temp("nhz/fuxue"))
				{ 
					me->add_temp("apply/damage",atk/4);
					me->add_temp("apply/strike",me->query_skill("sanhua-zhang",1)/3);
				}			
			       COMBAT_D->do_attack(me, target, weapon, j);
				if (me->is_fighting()&& me->query_skill("sanhua-zhang",1)>120)
                   COMBAT_D->do_attack(me, target, weapon, j);
                if (me->is_fighting()&& me->query_skill("sanhua-zhang",1)>140)
                   COMBAT_D->do_attack(me, target, weapon, j);
				if (me->is_fighting()&& me->query_skill("sanhua-zhang",1)>180)
                   COMBAT_D->do_attack(me, target, weapon,j);
				me->add_temp("apply/attack",-atk/2);
                me->add_temp("apply/damage",-me->query_skill("sanhua-zhang",1)/3);
				if (!userp(target)||target->query_temp("nhz/fuxue"))
				{ 
					me->add_temp("apply/damage",-atk/4);
					me->add_temp("apply/strike",-me->query_skill("sanhua-zhang",1)/3);
				}		
				if( !me->is_killing(target->query("id"))
		            && !target->is_killing(me->query("id"))
		            && !me->query("have_master")   // added by snowman
		            && target->query("qi")*2 <= target->query("max_qi"))
			        COMBAT_D->end_fight(me, target);
		        return 1;
        } 
        else {       
                me->start_busy(2);
                me->add("neili", -100); 
                me->add("jingli", -25);
                dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                message_vision(msg, me, target);

                return 0;
        }    
}

int perform(object me, object target)
{
      	if( !target ) target = offensive_target(me);
     
      	 if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
      		return notify_fail("���ļ�ɢ����ֻ����ս���жԶ���ʹ�á�\n");
             
      	if(me->query_temp("weapon"))
      		return notify_fail("��������ʹ�á��ļ�ɢ������\n");
      
      	if( (int)me->query_skill("sanhua-zhang",1) < 100 )
      		return notify_fail("���ɢ���Ʋ�����죬����ʹ�á��ļ�ɢ������\n");
      
      	if( (int)me->query_skill("yijin-jing",1) < 100 )
      		return notify_fail("����׽�ڹ��ȼ�����������ʹ�á��ļ�ɢ������\n");  
      
      	if( (int)me->query_str() < 30 )
      		return notify_fail("��ı�������ǿ������ʹ�á��ļ�ɢ������\n");
      
      	if( (int)me->query("max_neili") < 1200 )
      		return notify_fail("�������̫��������ʹ�á��ļ�ɢ������\n");
      
      	if( (int)me->query("neili") < 500 )
      		return notify_fail("�������̫���ˣ��޷�ʹ�ó����ļ�ɢ������\n");   
                                                                                 
        //if( me->query_temp("fumo"))
                //return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");
     
      	if (me->query_skill_prepared("strike") != "sanhua-zhang"
          || me->query_skill_mapped("strike") != "sanhua-zhang")
      		return notify_fail("�������޷�ʹ�á��ļ�ɢ�������й�����\n");     
     
     	if (me->query_skill_mapped("force") != "yijin-jing")
      		return notify_fail("��Ŀǰ���ڹ��޷�ʹ�á��ļ�ɢ�������й�����\n");  
      		  
        if (me->query_skill_mapped("finger")=="nianhua-zhi"
		&&me->query_skill_mapped("strike")=="sanhua-zhang"
		&&me->query_skill_prepared("strike")
		&&me->query_skill_prepared("finger"))
        {
			me->start_perform(2, "���ļ�ɢ����");
        }
		else me->start_perform(5, "���ļ�ɢ����");
          
    	if (!hehe(me, target, me->query_skill("sanhua-zhang", 1))){
        	if (random(me->query_int()) > target->query_int()/2) 
        		hehe(me, target, random(me->query_skill("sanhua-zhang", 1)*2));
        	else return 1;
        }
                
        else if (random(me->query_int()) > target->query_int()/2) 
        	hehe(me, target, random(me->query_skill("sanhua-zhang", 1)*2));
        return 1;
       
}
string perform_name(){ return HIW"�ļ�ɢ��"NOR; }
int help(object me)
{
        write(HIB"\nɢ����֮���ļ�ɢ������"NOR"\n");
        write(@HELP
        ɢ���������ֵ��ӵĳ������似�����ǵ���һ����ɮ����ɨԺ��ʱ�������׽�Ĺ����ƶ�����
        ���仨�����γ�һ�ŷǳ����صľ�������������������ʮ���ž���֮һ����Ϊ���Ʒ���ԱȽ�
        ��ͣ��ⷢ����Ҳ���Ե���ͬʱ����ǿ�����壬���һ�Ժ�Ĺ�Ч������Ϊ���ֵ������ű����书��
		���书�����黨ָ����ϣ�һ��������Ѩ������ôɢ���Ƶ�ɱ���������������

        Ҫ��  ������� 1200 ���ϣ�      
                ��ǰ���� 500  ���ϣ�  
                ɢ���Ƶȼ� 100 ���ϣ�
                �׽�ȼ� 100 ���ϣ�
                �����Ʒ�Ϊɢ���ƣ�
                �����ޱ�����
                
                
HELP
        );
        return 1;
}