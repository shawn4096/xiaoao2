//banruo-zhang's perform yipai(һ����ɢ)
//cool 981226

#include <ansi.h>

inherit F_SSERVER;
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
int next1(object me, object target, int i);
int perform(object me, object target)
{
        int damage, i,lvl;
        mapping pre;
        string *skill, a, b;
        lvl=me->query_skill("banruo-zhang",1)+me->query_skill("yijin-jing",1)/2;
        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) || !living(target) 
         || environment(target)!=environment(me))
                return notify_fail("һ����ɢ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");      

        if((int)me->query_skill("banruo-zhang", 1) < 500 )
                return notify_fail("��İ����ƻ���������������ʹ��һ����ɢ���жԵУ�\n");
		if((int)me->query_skill("yijin-jing", 1) < 500 )
			if((int)me->query_skill("hunyuan-yiqi", 1) < 500 )
                return notify_fail("����׽������������������ʹ��һ����ɢ���жԵУ�\n");
 
        if((int)me->query_skill("strike", 1) < 500 )
                return notify_fail("����Ʒ�������죬ʹ���������Ƶľ��У�\n");
                
        if(objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á�һ����ɢ����\n");
        
        if (me->query_skill_prepared("strike") != "banruo-zhang"
         || me->query_skill_mapped("strike") != "banruo-zhang"
		 || me->query_skill_mapped("parry") != "banruo-zhang")
                return notify_fail("������Ƚ��������������Ʒ����м�֮�в��С�\n");

        if(me->query_skill_mapped("parry") != "banruo-zhang")
                return notify_fail("������Ƚ��������������м�֮�в��С�\n");
        if((int)me->query("neili") < 5000 )
                return notify_fail("�㵱ǰ������Ϊ���㣬ʹ���������Ƶľ��У�\n");  
        if((int)me->query("max_neili") < 15000 )
                return notify_fail("�����������Ϊ���㣬ʹ���������Ƶľ��У�\n");     
        if((int)me->query("jingli") < 5000 )
                return notify_fail("�㵱ǰ������Ϊ���㣬ʹ���������Ƶľ��У�\n");  
        if( (int)me->query("neili") < (int)me->query("max_neili")*2/3 )
                return notify_fail("�������������㣬ʹ���������Ƶľ��У�\n");     

        if( (int)me->query("jingli") < me->query("eff_jingli")/2 )
                return notify_fail("�����ھ������㣬ʹ���������Ƶľ��У�\n");   
                
//        me->start_perform(15, "һ����ɢ");

        message_vision(HIR"\n$N���з�ţ�����ȫ��������עһ��������˫��֮�������ĳ�������������Լ�С�ž����һ�����죡\n" NOR, me,target);
 
        pre = me->query_skill_prepare();
        skill = keys(pre);     
        for (i=0; i<sizeof(skill); i++){
                if(skill[i]=="strike") continue; 
                a = skill[i];
                b = pre[skill[i]];
                me->prepare_skill(skill[i]);
        }         
        if ( (int)me->query("combat_exp",1) < (int)target->query("combat_exp",1) )
                damage = me->query("neili")/10;
        else    damage = me->query("neili")/3;
        
		me->set_temp("brz_yipai", 1);
        me->set("jiali", damage);
        
        if(wizardp(me))  tell_object(me, "Jiali = "+damage+"��");

       if(random(me->query_skill("banruo-zhang",1))>target->query_skill("parry",1)/2
		   ||random(me->query("combat_exp"))>target->query("combat_exp")/2 
		   ||(random(me->query_str())>target->query_dex()/2 && me->query_temp("yjj/powerup")))
	   {
                me->add_temp("apply/attack",lvl/2);
				me->add_temp("apply/strike",lvl/3);
				message_vision(HIW"$N��һ����ǰ�鰴����"HIR"һ��"HIW"��������$nΪ�侢����ѹ�ȣ��پ���ǰһ����Ϣ��\n"NOR,me,target);
				  //if(random(3))
			    target->add_condition("no_exert", 1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
                me->add_temp("apply/attack", -lvl/2);
				me->add_temp("apply/strike",-lvl/3);
				if (objectp(target)&&me->is_fighting())
					call_out("next1",1,me,target,i);
					//next1(me, target, i);
         }
        else {
			message_vision(HIC"$N����һ�ݣ���ʶ�����е���������ǿ���ܽ⣬����һ����¿����������������Ȼ�Ǽ�����\n"NOR,me,target);
            target->add_busy(3);

		}
        me->prepare_skill(a,b);
        if (me->query("yjj/powerup")!="pass")
        {
			message_vision(RED"$N����������һ�ƺľ����Լ�ȫ��������;��������ɵش�ڴ�ڴ�����\n"NOR,me);
       		me->set("jingli",100);
			me->set("neili", 100);
			me->delete("jiali");
		}else{
			message_vision(HBRED+HIW"$N�׽����ת��Ϣ��͸��һ�������������ָ�Щ������\n"NOR,me);
			me->add("neili",-3000-random(1000));
			me->add("jingli",-2000-random(1000));
		}
        //me->set("qi",10);
//        me->set("eff_qi";10);
//        me->set("jingli",0);
        //me->set("jingli",10);     
       // me->delete("jiali");
        //me->set("jingli", me->query("eff_jingli")/2);
        
        if(!target->is_killing(me->query("id"))) 
                target->kill_ob(me); 
        me->start_busy(3);
		me->start_perform(4,"һ����ɢ");
        if(!target->is_busy())
                target->start_busy(2); 
        return 1; 
}

int next1(object me, object target, int i)

{
      string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("brz_yipai");
                return 0;
        }
        msg = HBRED"\n������$N�����ǰ��Խ�벽���ҽ���΢���㣬˫��ͬʱ��ǰ�Ⱥ��ĳ���һ����ӿ������������$n�������ڣ�\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += YEL"$n��Ȼһ������$N��������ʽ���̺���ɽ�����㾢�������ǰ������м�Ϊ�����ġ�"HIR"һ����ɢ"YEL"��������\n"NOR;
                damage = me->query_skill("banruo-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
                damage += random(damage);
        if ( damage > 8000 )
				damage = 8000 + (damage-1000) /100;

		if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add("neili",-(800+random(400)));
                target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
        if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("banruo-zhang") /3);

		me->add_temp("apply/damage", me->query_skill("banruo-zhang") /3);

        //if(random(3))
			//target->add_condition("no_perform", 1);
        //if(random(3))
			//target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("banruo-zhang") /3);

		me->add_temp("apply/damage", -me->query_skill("banruo-zhang") /3);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "��һ����ɢ��");
        }
        else {
                msg  += CYN"\n$n��æ�˺��ӱܣ�Σ��֮�ж��������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
	    me->delete_temp("brz/yipai");
        return 1;
}



string perform_name(){ return HBRED+HIW"һ����ɢ"NOR; }

int help(object me)
{
        write(HIB"\n������֮��һ����ɢ����"NOR"\n");
        write(@HELP
	��������������ʮ�������и����似���Ʒ��еļ���
	��һ����ɢ����ʵ�Ǳ�������֮���ۣ���ν�� ��ɢ ��
	��ָ����ʯ�ϣ�ʯм�ġ�ɢ����������������ǡ�ɢ��
	��·�Ʒ���ֻ��ôһ�У�ֻ������̫���ۻ룬�ٵ�ʱ
	�ò���ʹ�ڶ��У����˱��ѱ���������һ���������
	ɽ�����������Ϊ������Ҫ����л�ʽ���������֮
	���ܡ�
		
	��λ�����־�ɱ����֮һ������Ϊ��Ҫǿ��������
	������Խ������Խ��ͬʱ��Ϊ�ľ����������Է���
	��̫��������ɶԷ��ķ�������С�����á����кͱ�
	���뾭��ֵ��ء�

	˵�����þ������⿪�׽��������������ɢ����
	���;�����������ס�
	
	ָ�perform strike.yipai

Ҫ��  
	����������� 15000 ���ϣ�      
	��ǰ�������� 5000  ���ϣ�  
	�����Ʒ��ȼ� 500 ���ϣ�
	�׽�ĵȼ� 500 ���ϣ�
	�����Ʒ��ȼ� 500 ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƣ�
	�����ޱ�����
	ע�⣺�����������õõ��������Ļ�����һ���ķ�����Ч��
                
HELP
        );
        return 1;
}
