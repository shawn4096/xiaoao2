// write by snowman@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
int check_pfm(object me, object target,object ob);
int remove_effect(object me);

int perform(object me, object target)
{
      	object ob;
		int skill;
        if( !target ) target = offensive_target(me);
		skill=me->query_skill("chousui-zhang",1);
        if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target)
        || !necessary(target) )
                return notify_fail("�����򡹹���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
      
      	if( (int)me->query("max_neili") < 2500 ) 
                return notify_fail("�㷢���Լ�����̫�����޷����������򡹽��й�����\n");
		if( (int)me->query("neili") < 1200 ) 
                return notify_fail("�㷢���Լ��������������������򡹽��й�����\n");
        if( (int)me->query_skill("huagong-dafa",1) < 250 )
                return notify_fail("�㷢���Լ��Ļ�������Ϊ�������޷�ʹ�á����򡹽��й�����\n");
        if( (int)me->query_skill("poison",1) < 150 )
                return notify_fail("�㷢���Լ����ھ۶��������޷�ʹ�á����򡹽��й�����\n");
        if( (int)me->query_skill("chousui-zhang", 1) < 250 )
                return notify_fail("�㷢���Լ������޶��ƻ�������죬�޷�ʹ�á����򡹽��й�����\n");
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á����򡹣�\n");        
        if( !objectp(ob = present("huo yan", environment(me))) )
                return notify_fail("û�л����ô���������򡹽��й�����\n");
        if( me->query_temp("csz/huoqiu") )
                return notify_fail("������������ѽ��й�����\n");
		if(me->query_temp("csz/yinhuo"))
                return notify_fail("���������������𡹽��й�����\n");
		if(me->query_temp("csz/huoqiang"))
                return notify_fail("��������������ǽ�����й�����\n");

       message_vision(CYN"\n$N������ȣ�������ʢ��������ͻȻ����һ�������"HIR"����"CYN"���ڿ��й�µµ��Ѹ��ת����\n\n"NOR,me);
      
        me->start_busy(2);
       me->set_temp("csz/huoqiu", 1);
	   me->add("neili",-200);
	   if (objectp(target)&&me->is_fighting()) {
		    message_vision(CYN"\n$N������ӿ����������ʹ���"HIR"����"CYN"��$n���ٹ�ȥ��\n\n"NOR,me,target);		    
	       call_out("check_pfm", 2, me, target, ob);
	   }
       else remove_effect(me);
	   return 1;
}
int remove_effect(object me)
{
           	message_vision(HIY"$N�����ٷ����������"RED"����"HIY"ѹ�ػ���֮�С�\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;

}

int check_pfm(object me, object target,object ob)
{
        string msg, *limbs;
        int i, neili, ap, dp, damage, p;
        object *inv;
        

        //me->delete_temp("pfm_chousui");
        if (!living(me) )
        {
           	message_vision(HIY"$Nһ�ӵ��������Բ��ѣ��������"RED"����"HIY"ѹ�����¡�\n"NOR,me);
			me->delete_temp("csz/huoqiu");
			return 1;
        }
        if( me->is_ghost()||!me ) return 0;
        
        if(!target 
        //|| !living(target) 
        || !me->is_fighting()
        || environment(me)!=environment(target)){
           	message_vision(HIY"$N�����ٷ����������"RED"����"HIY"ѹ�ػ���֮�С�\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;
        }  
        
        i = (int)me->query_skill("chousui-zhang", 1);
        neili = (int)me->query("neili");
        //me->start_busy(2+random(2));
        
        if(!objectp(present(ob, environment(me)))){
           	message_vision(HIY"$N�ۿ����Ϩ��ɢ����Ϣ�����¾����˫�֡�\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;
        }
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang"){
                tell_object(me,"������ó����Ʋ���ʹ�á����򡹽��й�����\n"); 
				me->delete_temp("csz/huoqiu");
                return 1;
        }                                                                                
        if( me->query_skill_mapped("force") != "huagong-dafa"){
                tell_object(me,"�㷢���Լ����õ��ڹ��޷����С����򡹹�����\n");
				me->delete_temp("csz/huoqiu");
                return 1;
        }
        if(neili < 1000){
                tell_object(me,"�㷢���Լ���������̫����ʹ���������򡹽��й�����\n");
				me->delete_temp("csz/huoqiu");
                return 1;
        }           
              
       
		ap = me->query_skill("chousui-zhang",1);
		dp = me->query_skill("parry",1);
        
		if(objectp(target)&&!userp(target))
        	dp /= 3;
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -600);
        me->add("jingli", -100);
		damage = ( i + me->query("jiali") ) * 15;
		if(userp(target)) damage = damage*2/3;
		if( ap < dp ) damage -= random(damage/3);
		if( ap > dp ) damage += random(damage/3);
	
        msg = WHT"\n��ʱ$N�������ް��Ѫɫ��һ�ڿ���Ѫ��ס��"RED"����"WHT"����ȥ!\n"HIR"ɲ�Ǽ�,����һʢ�������������죬"
"��������𻨣�"RED"����"WHT"��Ȼ�����$n���������\n"NOR;

       
        if(random(ap+dp) > dp*4/5
			||random(me->query_str())>target->query_str()/2)
		{
       		target->add_condition("xx_poison", 3);
			if (userp(me) && userp(target) && me->query_condition("killer") < 15)
				me->apply_condition("killer", 15);
			if(!target->is_busy())
                target->add_busy(1);
          	//inv = check_armor(all_inventory(target));
          	inv = filter_array(all_inventory(target),(:$1->query("equipped")=="worn":));
			inv -= ({0});
          	//�Ƽ�
			if( sizeof(inv) >= 1 ){     
            		if( neili > random(target->query("neili"))*2){
               			if( me->query_str()/3*2 > random(target->query_str()) ){
                  			msg += HIY"���Ҽ�����¶�������𻨱��䣬ը����$p�Ļ��ߣ�\n" NOR;
                  			damage += random(damage)*2;
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->unequip();
                         			inv[i]->move(environment(target));
                         			inv[i]->set("name", "�����" + inv[i]->query("name"));
                         			inv[i]->delete("value");
                         			inv[i]->set("armor_prop", 0);
                         		}     
                  		}                   
            			else {
                  			msg += HIY"ֻ��������Ȼ���£����Ľ�������ֱ͸$p�Ļ��ߣ�\n" NOR;
                  			damage += random(damage);
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->set("name", "���ѵ�" + inv[i]->query("name"));
                        			inv[i]->set("value", 49);
                         			if(inv[i]->query("armor_prop/armor"))
                             				inv[i]->set("armor_prop/armor", inv[i]->query("armor_prop/armor")/2);
                        		}
                  		}
                  		target->reset_action();     
               		}
          			else {
                  		msg += HIY"�����ٹ���������Ľ��������������ײ��$p���\n" NOR;
                  	}
				//�Ƽ׺�˳������
                  	target->receive_damage("qi", damage, me);   
                  	target->receive_wound("qi", damage/3, me);  
				if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
			
	if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); 
			}            	
        	else{
                //target has no armor, so, hehe...
                	if( neili > target->query("neili")/2*3 )
                		damage += random(damage);
                	else if( neili < target->query("neili")/3*2 )
                		damage -= random(damage/2);
                	else if( neili > target->query("neili")*2 ) 
                		damage *= 3;
                	damage += random(damage);
                	target->receive_damage("qi", damage, me);   
                	target->receive_wound("qi", damage/3, me);
                    if(userp(me) && me->query("env/damage"))
						tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
					
if(userp(target)&& target->query("env/damage"))
						tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR);           }
                p = (int)target->query("qi")*100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
               	msg += "( $n"+eff_status_msg(p)+" )\n";
               	limbs = target->query("limbs");
       		    msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
       		    msg = replace_string(msg, "$w", RED"����"NOR);   
        }        
    	else{
    		if(!target->is_busy())
        		target->start_busy(1);
        	msg += HIY"\n$p�ۿ���Ҫ�����У�ð��һ���������š���ȫ����ϥ�Ǵ����ȥ�������ܹ�����"HIY"��\n" NOR;
        }
            
       	message_vision(msg, me, target);
       	if( userp(target)&&!target->is_killing(me->query("id")) ) target->kill_ob(me);
		me->delete_temp("csz/huoqiu");
		me->start_perform(3,"����");
       	return 1;
} 


string perform_name(){ return HIR"����"NOR; }
int help(object me)
{
        write(HBBLU"\n������֮�����򡹣�"NOR"\n\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	������������ս���У�ƾ������ڹ������ڴ涾�Ƴ������˵е�
	һ�Ź��򡣡����򡹾���ר�ƶԷ����ߣ�˳�����������ѷ�����
	
	ָ�perform strike.huoqiu

Ҫ��  
	��ǰ�������� 1000 ����;
	����������� 2500 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	�����󷨵ȼ� 250 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ����;
	�������ޱ�����        
HELP
        );
        return 1;
}
