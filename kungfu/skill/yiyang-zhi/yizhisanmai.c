// Modified by snowman@SJ 05/12/2000
// Update By lsxk@hsbbs 2007/6/14

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

string perform_name() {return HIR"һָ������"NOR;}

int perform(object me, object target)
{
        int lev,lvl;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("��һָ��������ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�һָ����������\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 500 )
                return notify_fail("���һ��ָ��������죬ʹ������һָ��������������\n");

        if((int)me->query_skill("force",1) < 500 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ������һָ��������������\n");

        
        if(me->query_skill("kurong-changong", 1)<500)
          if(me->query_skill("qiantian-yiyang", 1) < 500)
                return notify_fail("�������ڼ������ڹ���Ϊ��ʹ������һָ����������\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á�һָ����������\n"); 

        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");                

        if( (int)me->query("max_neili") < ((int)me->query_skill("force",1)+1000) )
                return notify_fail("����������̫����ʹ������һָ����������\n");      

        if( (int)me->query("neili") < ((int)me->query_skill("force",1)+1100) )
                return notify_fail("����������̫����ʹ������һָ����������\n");

        if( (int)me->query("jingli") < ((int)me->query_skill("force",1)+ 800) )
                return notify_fail("�����ھ���̫�٣�ʹ������һָ����������\n");
        if (me->query_temp("yyz/yizhisanmai"))
                return notify_fail("����������ʹ�á�һָ����������\n");
        
		lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        if(!userp(me)) lev = lev*2/3 ;
        else lev = lev *3/2  ; //3/8������
		lvl=lev;

	    
		message_vision(BRED+HIY"\n$N��ת������������ָ�滺���磬�ձ�����Ʈ�ݣ��ֱ۲������������ѵ�ˮ��һָ���������Ϯ����������������ף�\n"NOR,me,target);
        me->add_temp("apply/strength", lev /5);
        me->add_temp("apply/attack", lev);
        me->add_temp("apply/damage", lev);
        me->add_temp("apply/finger", lev);
        me->set_temp("yyz/yzsm",lev);
		//�趨��ʱ����

		if (me->query("yideng/ronghe")=="pass")
           me->set_temp("yyz/yz3m",4);
		else me->set_temp("yyz/yz3m",3);
        //��һָ
        if (objectp(target)&&me->is_fighting())
        {
		  if (me->query("yideng/ronghe")=="pass")
		  {
            me->set_temp("yyz/yz3m",4);
		    lev=lev+me->query_skill("xiantian-gong",1);
		    message_vision(HIR"$N����ʳָ�ζ�����������˫�ֲ�ɢ����ָ֮���ֺ����һ�м��룬һ�����ˣ�����$n���ؿڴ�Ѩ��\n"NOR,me,target);
		    target->receive_damage("qi",lev*4,me);
		    target->receive_damage("jing",lev,me);
			if(userp(me) && me->query("env/damage")&&objectp(target))
        		tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ lev+ WHT"�㹥���˺���\n"NOR);

		  }
			COMBAT_D->do_attack(me, target, 0, 3);

        }
         //me->add_temp("yyz/yz3m",-1);
		//�ڶ�ָ
        if( me->is_fighting(target)) {
            COMBAT_D->do_attack(me, target, 0, 3);
           // me->add_temp("yyz/yz3m",-1);
        }
		//����ָ
        if( me->is_fighting(target) && (int)me->query_skill("yiyang-zhi",1) > 199 ) {
      	 COMBAT_D->do_attack(me, target, 0, 3);
	     //me->add_temp("yyz/yz3m",-1);
        }
        //׷��һ�����⹥��
		
		if(objectp(target)&& me->is_fighting() &&me->query("yideng/ronghe")=="pass") {
		 message_vision(HIM"$Nһ��ָ������Ȼ��ˣ���ת���⣬����ָ̧�侢����ӿ���ں������칦��һ��ָ����������\n"NOR,me);
         switch(random(3)){
           case 0:
            if(objectp(target)&& me->is_fighting(target)) {      
		         message_vision(BLU"$N����������칦�ľ�Ҫʩչ������������������ʱָ�����������硰���͡����죡\n"NOR,me);
                // me->add_temp("apply/attack",lvl/2); 
				 target->add_busy(2+random(2));
                 COMBAT_D->do_attack(me, target, 0, 3);
				 //me->add_temp("apply/attack",-lvl/2);				 
				 //me->add_temp("yyz/yz3m",-1);
				 me->add("neili",-lvl/4);
				 }
		   break;
		   case 1:
            if( objectp(target)&&me->is_fighting(target)) {          
		         message_vision(HIC"$Nֱ����ά����ʮ��Ѩ����һ����ң�㣬������Զ��$nһ�ɿ��⣬ٿ��֮�䣬�۽���ȥ���������еķ��Ѩ��һ�м��룬������ף�\n"NOR,me,target);
                 if (objectp(target))
				    target->set_temp("must_be_hit",1);
				 target->apply_condition("no_exert",1+random(1));
                 COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
				 COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
				 COMBAT_D->do_attack(me, target, 0,  3);
				 if (objectp(target))
				    target->delete_temp("must_be_hit");
                 target->receive_wound("qi",-(int)lvl/2,me);
                 me->add("neili",-lvl/4);
                 //me->add_temp("yyz/yz3m",-1);
		   }
		   break;
		   case 2:
			  if(objectp(target)&& me->is_fighting(target)) {  
		         message_vision(HBMAG"$N����$n�����˶��У����ֳ�ָ��������������Ѩ����������а�Ѩ�����ּ��������к�������,����֧�ֲ�ס̬֮��\n"NOR,me,target);
                 target->apply_condition("no_perform",1+random(2));
				 target->add("jingli",-lvl/2);
				 me->add_temp("apply/damage",lvl/6);                 
				 COMBAT_D->do_attack(me, target, 0, 3);
				 me->add_temp("apply/damage",-lvl/6);
                 //me->add_temp("yyz/yz3m",-1);				 
				 me->add("neili",-lvl/4);
		        }
		   break;		   
		   }
		}
        //me->start_busy(1);
        me->delete_temp("yyz/yz3m");

        me->add_temp("apply/strength", -lev /5);
        me->add_temp("apply/attack", -lev);
        me->add_temp("apply/damage", -lev);
        me->add_temp("apply/finger", -lev);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(4,"��һָ��������");
        return 1;
}


int yzsm_attack(object me, int flag)
{
        object target;
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("��һָ��������ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�һָ����������\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 500 )
                return notify_fail("���һ��ָ��������죬ʹ������һָ��������������\n");

        if((int)me->query_skill("force",1) < 500 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ������һָ��������������\n");

        if( me->query_temp("pf_rong"))
                return notify_fail("���������á��١��ִ󷨣�\n"); 

        if(me->query_skill("kurong-changong", 1)<500)
          if(me->query_skill("qiantian-yiyang", 1) < 500)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������һָ����������\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á�һָ����������\n"); 

        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");                

        if( (int)me->query("max_neili") < ((int)me->query_skill("force",1)+1000) )
                return notify_fail("����������̫����ʹ������һָ����������\n");      

        if( (int)me->query("neili") < ((int)me->query_skill("force",1)+1100) )
                return notify_fail("����������̫����ʹ������һָ����������\n");

        if( (int)me->query("jingli") < ((int)me->query_skill("force",1)+ 800) )
                return notify_fail("�����ھ���̫�٣�ʹ������һָ����������\n");

        lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        if(userp(me))  lev = lev * flag;


        message_vision(HIR"\n$N��ָ�滺���磬�ձ�����Ʈ�ݣ��ֱ۲������������ѵ�ˮ��һָ���������Ϯ����������������ף�\n"NOR,me,target);

        me->add_temp("apply/strength", lev /10);
        me->add_temp("apply/attack", lev/ 2);
        me->add_temp("apply/damage", lev);
        me->add_temp("apply/finger", lev);


        me->set_temp("yyz/yz3m",3);
        
         COMBAT_D->do_attack(me, target, 0, 3);
        me->add_temp("yyz/yz3m",-1);
 
        if( me->is_fighting(target)) {
          COMBAT_D->do_attack(me, target, 0, 3);
          me->add_temp("yyz/yz3m",-1);
        }

        if( me->is_fighting(target) && (int)me->query_skill("yiyang-zhi",1) > 450 ) {
      	 COMBAT_D->do_attack(me, target, 0, 3);
	     me->add_temp("yyz/yz3m",-1);
        }
        me->start_busy(1);
        me->delete_temp("yyz/yz3m");

        me->add_temp("apply/strength", -lev /10);
        me->add_temp("apply/attack", -lev/ 2);
        me->add_temp("apply/damage", -lev);
        me->add_temp("apply/finger", -lev);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(5,"��һָ��������");
        return 1;
}


int help(object me)
{
   write(HIY"\nһ��ָ֮��"HIR"һָ������"WHT"����"NOR"\n\n");
   write(@HELP
	���������һ��ָ�������£���һ��ָ�����˹���������ʳָ��Ѩ��
	��ָ�ɻ��ɿ죬��ʱ����Ʈ�ݣ����������磬����ָ֮�����ֺ�
	����������������֮�ʣ��ô�ָ���ȿ������������Ѩ����Ҳ
	�ɴ�Զ���۽���ȥ��һ�м��룬һ�����ˣ�ʵΪ�˵б����������
	����
	һָ�����������Ǵ�������Ͼ�����һָ����֮�£���������������
	�˵��������ޱȣ����ܽ⿪һ�ƴ�ʦ�����칦�ں��ؼ���һָ����
	�����������ͷš�

Ҫ��: 
	����������ڻ����ڹ�1000�����ϣ�
	��ǰ�������ڻ����ڹ�1100�����ϣ�
	��ǰ�������ڻ����ڹ�800�����ϣ�
	һ��ָ�ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	����ָ��Ϊһ��ָ��
	���֣���һ��ָ��
	������ set һ��ָ��Ѩ ������������

HELP
   );
   return 1;
}
