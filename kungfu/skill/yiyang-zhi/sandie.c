// /kungfu/skill/yiyang-zhi/sandie.c
// COOL@SJ
// Modified by snowman@SJ 05/12/2000

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
#include <combat.h>
 
string perform_name() {return YEL"��������"NOR;}
int perform2(object me, object target);
int perform3(object me, object target);

int perform(object me, object target)
{       
        string msg;
        int damage;
        
        if( !target ) target = offensive_target(me);
 
        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target))
                return notify_fail("������������ֻ����ս����ʹ�á�\n");
        if( !living(target) )
        	return notify_fail("�Է��Ѿ��ι�ȥ�ˡ�\n");
        	
        if( objectp( me->query_temp("weapon")) )
                return notify_fail("ֻ�п��ֲ���ʩչ��������������\n");

        if((int)me->query_skill("yiyang-zhi", 1) < 450 
         ||(int)me->query_skill("finger", 1) < 450 
         ||(int)me->query_str() < 60)
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á�������������\n");

        if(me->query_skill("kurong-changong", 1)<450)
          if(me->query_skill("qiantian-yiyang", 1) <450)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������������������\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
        if (me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á��������������й�����\n");
 
        if(me->query_temp("start_6mai"))
                return notify_fail("���Ѿ������������񽣵����ν����ˣ�\n");

        if (me->query_skill_mapped("parry") != "kurong-changong" )
           if (me->query_skill_mapped("parry") != "yiyang-zhi")
                return notify_fail("����ʹ�õ��мܲ��ԡ�\n");

        if((int)me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ̫��������ʹ�á�������������\n");

        if((int)me->query("neili") < 1500 )
                return notify_fail("�������������\n");
			
		if( me->query_temp("sandie/js") || me->query_temp("sandie/jt") )
		return notify_fail("�������������\n");

	    if( me->query("env/һ��ָ") == "����" ) {
		if ( target->query_temp("sandie/jingshen")) 
			return notify_fail("�����������ʹ���š���������֮���񡹾��У�\n");
		else {
			if( me->query_temp("sandie/js") ) 
				return notify_fail("������ʹ���š���������֮���񡹾��У�\n");
			else
			me->set_temp("sandie/js",1);
			perform2(me, target); 
//			call_out("perform2", 0, me, target); 
			return 1;
		}
	}
	else if( me->query("env/һ��ָ")=="����" ) {
		if( target->is_busy() ) 
			return notify_fail("�Է���æ���أ�\n");         
		else {
			if( me->query_temp("sandie/jt") ) 
				return notify_fail("������ʹ���š���������֮���졹���У�\n");
			me->set_temp("sandie/jt",1); 
			perform3(me, target); 
//			call_out("perform3",0,me, target); 
			return 1;
		}
	}
		
               
    
        if((string)me->query("class")=="bonze")
           	msg = WHT "\n$N˫�ƺ�ʲ�����е��з�ţ�������ָ��һʽ����ɷ��������������͵�һ�����죬һ�ɴ���������ֱϮ$n�ؿڣ�\n" NOR;
        else if ((string)me->query("class")=="officer")
           	msg = HIY "\n$Nʹ�����������������У��뷢����, ����֮�������һ������ɷ��,һָ���������������������һ�ɴ���������ֱϮ$n�ؿڣ�\n" NOR; 


        else msg = YEL "\n$Nʹ�����������������У����һ������ɷ��,һָ���������������������һ�ɴ���������ֱϮ$n�ؿڣ�\n" NOR; 

        
        if( random( me->query("combat_exp") ) > target->query("combat_exp")/3  
        || target->is_busy() 
		|| (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass"))
        || me->query("env/һ��ָ") == "��ɷ" )
         {

             	target->add_busy(1);
             	damage =(int)me->query_skill("kurong-changong", 1) * 3 + (int)me->query_skill("finger") * 3 + (int)me->query_skill("qiantian-yiyang", 1) * 3;
             	damage += (int)me->query_skill("yiyang-zhi", 1)*3;
        	    damage = random(damage)+damage;

             	if( me->query("neili") > target->query("neili") )
                     	damage += random(me->query("jiali"))*2;
                if (me->query("neili") > target->query("neili")*2 ) 
                       	damage *= 2;
                       	

                if(!userp(me)) damage = damage / 2;
               
            	target->receive_damage("qi", damage, me);
            	target->receive_wound("qi", damage/3, me);
				target->receive_damage("jingli",damage/4,me);
				
            	me->add("neili", -(damage/5));
            	msg += damage_msg(damage, "����")+"( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
            	
               if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR); 
			   
if(userp(target)&& target->query("env/damage"))
				   tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
			   if(me->query_skill("yiyang-zhi", 1) >=350)
            	{      	
				   me->start_perform(4, "����");
                  // call_out("perform2",1,me, target);       
                }
                else me->start_perform(5, "��ɷ");
	            }
        else {
		   if (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass"))
		   {
                me->start_busy(2);
                me->add("neili", -70);                
                msg += HIY"$p����ָ��Ϯ����֪���޷�Ӳ����һ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n"NOR;
                me->start_perform(4, "����");
                call_out("perform2", 1, me, target);
		   }        	    
	    }        
        message_vision(msg, me, target);
		if (objectp(target)&&objectp(me)&&me->is_fighting()&&(me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass")))
		{		
			call_out("perform2", 1, me, target);
		}
		
		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//��һ�У�������ѧ�˺�
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);
        return 1;
}

int perform2(object me, object target)
{
        int f,i,damage;
        string msg;
        
		if (!me ) return 0;        
        
        if( !living(me) ) return 0;
        
		me->delete_temp("sandie/js");   
        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
               return notify_fail("����Ҫ��һ�У�ȴ�������Ѿ����ô��ˡ�\n");;

        if((int)me->query("neili", 1) < 400 )
               return notify_fail("���Ҫ����һָ��ȴ�����Լ������������ˣ�\n");;    

        if( (int)me->query_skill("yiyang-zhi", 1) < 140)               
               return notify_fail("���һ��ָ��Ϊ�������޷�ʹ������������ ��֮ ����\n");;
     
        damage =(int)me->query_skill("kurong-changong", 1)  + (int)me->query_skill("finger") + (int)me->query_skill("qiantian-yiyang", 1);
        damage += (int)me->query_skill("yiyang-zhi", 1)*3;
        damage = random(damage)+damage*2;
 
        f = (int)me->query_skill("yiyang-zhi",1);

        me->start_perform(4, "����");             
        
        if( target->is_busy() ){
          	msg = YEL "\n������$Nһ��ָ�ڶ��ε��������һָ��һʽ�����񡹵�����������͵�һ�����죬һ�ɴ�����ָ��͸��$n���������Ϲ�Ѩ��\n" NOR;
          	i = 2+random(2);
        }
        else {
          	msg = YEL "\n������$Nһ��ָ�ڶ��ε�����Դ���������ͬʱ͸��$n���������Ϲ�Ѩ����ά�����Ѩ����������Ѩ����������Ѩ������������Ѩ��\n"NOR;        
          	i = 2;
        }


		if( random(me->query_skill("force",1)) > target->query_skill("force",1)/i
			|| (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass"))
			|| me->query("env/һ��ָ") =="����" )
         {
        	
                me->add("neili", -f*2);
                msg += HIR "$nֻ��һ������֮�����������澭����,ȫ������ů����ģ���Ϊ��������Ȼ�᲻��һ˿������\n" NOR;
                target->add_temp("apply/attack", -f/4);
                target->add_temp("apply/dodge", -f/4);
                target->add_temp("apply/parry", -f/4); 
                target->add_temp("apply/strength", -f/4); 
                
				
				target->receive_damage("qi", damage, me);
            	target->receive_wound("qi", damage/3, me);
				target->receive_damage("jingli",damage/4,me);

               
			    if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR); 
			   
				if(userp(target)&& target->query("env/damage"))
				   tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);


				if( random(2) ) 
                 	target->apply_condition("no_exert", 2);
                else  
                 	target->apply_condition("no_perform", 2);
                 	
                target->set_temp("sandie/jingshen",f/4);

                call_out("sandie_back", 5+random(20), target, f/4);

                if((int)me->query_skill("yiyang-zhi", 1) >= 180 && (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass")))
                {
                 	remove_call_out("perform3");
                 	call_out("perform3", 1, me, target);
                }
           }
        else{
   
               me->add("neili", - 100);
                msg += HIY"\n��������һ��˲��ֿ�,ȴ��$p��������ڹ�����ȥ�˹������ڵ�һ��ָ����\n" NOR;
                if((int)me->query_skill("yiyang-zhi", 1) >= 180 && (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass")))
                {
                  	call_out("perform3", 1, me, target);
                 }
        }
        message_vision(msg, me, target);
		if (objectp(target)&&objectp(me)&&me->is_fighting() && (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass")))
		{		
			call_out("perform3", 1, me, target);
		}
		
		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//�ڶ��У������Ʒ�Ч��
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);
		
        return 1;
}

int perform3(object me, object target)
{
       
    int i;
 	string msg;
	if( !me ) return 0;

	if( !living(me) ) return 0;
	me->delete_temp("sandie/jt");
	me->delete_temp("yyz/sd");
	if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
               return notify_fail("����Ҫ��һ�У�ȴ�������Ѿ����ô��ˡ�\n");

        if((int)me->query("neili", 1) < 300 )
				return notify_fail("���Ҫ����һָ��ȴ�����Լ������������ˣ�\n");
		
		if( (int)me->query_skill("yiyang-zhi", 1) < 180)			
               return notify_fail("���һ��ָ��Ϊ�������޷�ʹ������������ ֮ ���񡹡�\n");

        if (target->is_busy()) return notify_fail("�Է����Թ˲�Ͼ���ŵ������ɣ�\n");
        
        i = me->query_skill("yiyang-zhi") /35;
     
        if(i>10) i=10; 
   
	     me->start_perform(4, "����");

         msg = YEL"\n����$N̤ǰһ����������ָ�����졹���յ���$n��ǰ������Ѩ������Ѩ�������֮�\n"NOR;

        if( random(me->query_skill("finger",1)) > target->query_skill("parry",1)/3 
			 || (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass"))
             || me->query("env/һ��ָ") =="����" ){
              msg += HIR "���һָ���У�$nֻ��������ͨ���������������ܸ��ӣ����ζ�ʱ��óٻ�������\n"NOR;
                target->add_busy( i );
                target->add("neili", -me->query_skill("force",1)*4);
                me->add("neili", -(me->query_skill("force",1)/3));
				if (me->query("yideng/ronghe")=="pass" && (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass")))
				{
					msg += HIY"\n$N�����칦��Ǭ��һ���ںϺ��ھ���һ��ָʩչ������һ��ָ����������\n"NOR;
					me->start_call_out( (: call_other, __DIR__"yizhisanmai", "yzsm_attack", me, 2 :), 1 );
				}
				else if( (i =10  && userp(me) && (me->query("env/һ��ָ") == "����" && me->query("quest/tls/yyz/sandie/pass"))) || ( random(10)> 4 && me->query("env/һ��ָ") =="����"))
                {
          	        msg += HIM"\n$NǱ����������ɫ��������������ָ�ϵľ���ȴ��Խ��Խǿ��\n"NOR;
                    me->start_call_out( (: call_other, __DIR__"yizhisanmai", "yzsm_attack", me, 1 :), 1 );
                }

           }
      
         else {
               	me->start_busy(1+random(2));
                me->add("neili", -200);
                target->add("neili", -random(100));
                msg += HIY"\n$p����ָ��Ϯ����֪���޷�Ӳ������Ҳ����һ������������������$p˳�����˿�ȥ��\n" NOR;
               }

        message_vision(msg, me, target);

		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//�����У�����busyЧ��
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);


        return 1;
}
void sandie_back(object target, int i)
{        
        if( !target ) return;
        target->add_temp("apply/attack", i);
        target->add_temp("apply/dodge", i);
        target->add_temp("apply/parry", i); 
        target->add_temp("apply/strength", i); 
        target->delete_temp("sandie/jingshen");
}



int help(object me)
{
   write(HIY"\nһ��ָ֮��������������"NOR"\n\n");
   write(@HELP
	μ�ǳ��꣬һ�����᳾��
	������������࣬Ū������ǧ����ɫ�¡� 
	������������࣬ǧ����ɫ�¡�
	�ݷ��գ�Ȱ������һ���ƣ�
	�������٣��ԹŸ������ж��֣�Īǲ��������
	�ݷ��գ�Ȱ������һ���ƣ�
	ֻ�����������أ��������Σ���ǰ�޹���

	ȡ������������ӽ֮̾��˼��������ָ������ɷ
	�˵���Ѫ���Ծ���һ��ָָ�����룬��������
	������˲����б������������˷������мܣ���
	�͵������С�����Խ���ָ����Ѩʹ֮æ�ҡ���
	����Ȼ����������һ��ָ������˫�������ޱȡ�
	
	perform finger.sandie
	
����Ҫ��
	һ��ָ�ĵȼ� 450  �����ϣ�
	����ָ���ȼ� 450  �����ϡ�
	Ǭ��һ���ȼ� 450  �����ϣ���(��������)
	�������Ҫ�� 60   ���ϣ�
	�������Ҫ�� 5000 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϡ�
	��ָ�����м�Ϊһ��ָ��
	
�������ݣ� 
	set    һ��ָ   xxxx 
	��ɷ   Ч��Ϊ�����ɷ���У���ɷ��ЧΪ����
	����   Ч��Ϊ��߾������У�����ЧΪ���б���
	����   Ч��Ϊ��߽������У����칦ЧΪ���������öԷ�busy
	����   Ч��Ϊ��ߺ���һָ�����ļ��ʣ��൱�����������ں�
	

HELP
   );
   return 1;
}




