// sanwu.c ����������
// By River@SJ 02/16/2001

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
string perform_name(){ return HIW"����������"NOR; }
int perform3(object me,object target);
int perform2(object me,object target);

int perform(object me, object target)
{       
        string msg, dodge_skill;
        int i,damage, ap, dp,skill;
        object weapon;
        skill=me->query_skill("yinsuo-jinling",1)+me->query_per(1);
     //   if( !me->query("gmsanwu")) return notify_fail("�㻹���ᡸ���������֡����������\n");
		if( !me->query("quest/gumu/sanwu/pass")) 
			return notify_fail("�㻹���ᡸ���������֡����������\n");

        if( !target ) target = offensive_target(me);
 
         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target))
                return notify_fail("�����������֡�ֻ����ս����ʹ�á�\n");
		
        if( !living(target))
                return notify_fail("�Է��Ѿ��ι�ȥ�ˡ�\n");
                
        if( !objectp( weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "whip" )
                return notify_fail("��װ�����������ԣ��޷�ʩչ�����������֡���\n");

        if( (int)me->query_skill("yinsuo-jinling", 1) < 400 
         || (int)me->query_skill("meinu-quanfa", 1) < 400 
         || (int)me->query_dex() < 28)
                return notify_fail("�����Ůȭ�����򻹲�����죬����ʹ�á����������֡���\n");

        if(me->query_skill("yunu-xinjing", 1) < 400)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ���������������֡���\n");        
         
        if(me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if (me->query_skill_prepared("cuff") != "meinu-quanfa" 
         || me->query_skill_mapped("cuff") != "meinu-quanfa"
         || me->query_skill_mapped("whip") != "yinsuo-jinling" )
                return notify_fail("�������޷�ʹ�á����������֡����й�����\n");

        if (me->query_skill_mapped("parry") != "yinsuo-jinling")
                return notify_fail("����ʹ�õ��мܲ��ԡ�\n");
	//	if (me->query_temp("ysjl/sanwu"))
              //  return notify_fail("������ʹ�����������֡�\n");

        if((int)me->query("max_neili") < 6000 )
                return notify_fail("���������Ϊ̫��������ʹ�á����������֡���\n");

        if((int)me->query("neili") < 2500 )
                return notify_fail("�������������\n");
        if((int)me->query("jingli") < 1000 )
                return notify_fail("��ĵ�ǰ����������\n");
       
		me->start_perform(4, "����������");
		me->set_temp("ysjl/sanwu",3);
        //�޿ײ���
		msg = HIM"ͻȻ��ֻ����Ӱ�϶�����ǰ�����"+weapon->query("name")+HIM"��Ӱ�ӡ�$N��һ�С��޿ײ��롹��������$n����\n"+
                 "�ٺ�����������һ�У���ʵǧͷ������һ��֮�а�������ʮ�У�����ͬʱ��$nȫ�������Ѩ��\n"NOR;

        ap = (int)me->query("combat_exp") * me->query_per(1)/100000;
        dp = (int)target->query("combat_exp")* target->query_per(1)/100000;

        if( random(ap) > dp /2 ){
                damage = (int)me->query_skill("yinsuo-jinling", 1);
                damage *= me->query_per(1);
				damage /=2;
		//npc������ң�����		
        if (!userp(me) && userp(target))
        {
			if( damage > 4000 ) damage = 4000;
		}
			 
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                //�����޿ײ���
				target->set_temp("sanwu/wukong", 1);
                me->add("neili", - 200);
               // msg += damage_msg(damage, "����")+
               // "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
             
				
				i = me->query_skill("yinsuo-jinling", 1) / 20;
                //��һ�еĶ��⽱��
				if (me->is_fighting()&&objectp(target))
             		call_out("perform_bonus", 0, me, target, i);
        }
        else {
                me->add("neili", -100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                               
        }        
        message_vision(msg, me, target);
		////if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR); 				
		//if(userp(target)&& target->query("env/damage")) 
			//tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
 
		skill=skill+me->query_skill("jiuyin-zhengong",1)/4;
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/6);
		COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
		if (me->query("quest/jiuyingm/pass")&&me->query_skill("jiuyin-zhengong"))
		{
			message_vision(HIB"$N���г��޻Ӷ������������������漴����һ�еݳ���\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);

		}
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
        //�ڶ���
		if( me->query_skill("meinu-quanfa", 1) >= 140 
         && me->query_skill("yinsuo-jinling", 1) >= 140
		 && objectp(target)
         && me->query("neili") > 800 )
         perform2(me, target);
        return 1;
}

int perform2(object me, object target)
{
        int i,ap,dp;
        string msg,dodge_skill;
        int skill;
        skill=me->query_skill("yinsuo-jinling",1)+me->query_per(1);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me, "����Ҫ�ٷ�һ�У�ȴ���ֶ����Ѿ����ô��ˡ�\n");
               return 1;
        }

        ap = (int)me->query_dex(1)* me->query_per();
        dp = (int)target->query_dex(1)* target->query_per();             
        
		i = skill+me->query_skill("meinu-quanfa", 1);
		i +=me->query_skill("yunu-xinjing", 1)/5;
		
		if (me->query_skill("jiuyin-zhengong",1)>=200) 
			i=i+me->query_skill("jiuyin-zhengong",1);
		i=i/3;
		//��������
        msg = HIC"\n$N����һ�С����������������ֻӱޣ�����ʩչ����Ůȭ��������βֱָ$n�������ƫ��Ѩ����\n"NOR;
        
		if( random(ap) > dp/3 ){
                msg += HIR"$n�����������������ƫ��Ѩ�����������У�ȫ��Ȼ�᲻��һ˿������\n"NOR;
                target->add_temp("apply/attack", -i/5);
                target->add_temp("apply/damage", -i/5);
                target->add_temp("apply/defense", -i/5);
                
				if( !random(3))
                   target->apply_condition("no_exert", 2);
                else  
                   target->apply_condition("no_perform", 2);
                
				target->set_temp("sanwu/wusuo", i/5);
                
				call_out("check_fight", 1, me, target, i/20);
                me->add("neili", -200);
        }
        else{
                me->add("neili", - 100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		//2��
		COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);

		if (me->query_skill("jiuyin-zhengong",1)>200 && objectp(target)) {
			message_vision(HIB"$N����Ĺ�����湦���ھ�������������ʽ����������\n"NOR,me,target);
			me->add_temp("apply/attack",skill/3);
			me->add_temp("apply/damage",skill/6);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/damage",-skill/6);
		}
        //������
		if( me->query_skill("meinu-quanfa", 1) >= 160
         && me->query_skill("yinsuo-jinling", 1) >=160
		 && objectp(target)
         && me->query("neili") > 800 )
         perform3(me, target);
        return 1;
}

int perform3(object me, object target)
{
        object weapon;
        int i;
		
        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me,"����Ҫ�ٷ�һ�У�ȴ���ֶ����Ѿ����ô��ˡ�\n");
               return 0;
        }

        weapon = me->query_temp("weapon");

        i = me->query_skill("meinu-quanfa",1);
        i += me->query_skill("yinsuo-jinling", 1);
		i += me->query_skill("yunu-xinjing", 1)/5;
		if (me->query("quest/jiuyingm/pass"))
			i += me->query_skill("jiuyin-zhengong", 1)/2;
        i /= 3;
        
        if(!userp(me)) i = i / 4;


        message_vision(HIW"\n$N�ĵ����֡�������Ϊ������ʹ������һ�в��ٵ�Ѩ��ר���۾����ʺ�С�����������������\n"+
                          "����֮�������Խ�����������Ϊ�������ݶ�����\n"NOR, me);
		//���Է����ڶ��д�������
        if( target->query_temp("sanwu/wusuo")&&!me->query_temp("sanwu/buwei"))
		{
                
				me->add_temp("apply/attack", i);
                me->add_temp("apply/whip", i);
                me->add_temp("apply/damage", i);
                me->set_temp("sanwu/buwei", 1);
        }

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//����������������
		if (me->query("quest/jiuyingm/pass") && me->query_temp("weapon"))
		{
			weapon = me->query_temp("weapon");
			me->add_temp("apply/attack",i/2);
			me->add_temp("apply/damage",i/4);
			message_vision(HBMAG"$N�������澭�Ĺ������õ����������似֮�У��޷��鶯�쳣����ʱ����������\n"
			+HIY"$nһ��С��Ϊ"+weapon->name()+HIY"�����С�\n"NOR,me,target);
			target->add_busy(3);
			if (present(target,environment(me)) && me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack",-i/2);
			me->add_temp("apply/damage",-i/4);
		}
		if(objectp( weapon = me->query_temp("weapon"))) weapon->unequip(); 
		//�����κα��Ŀ����似
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, 0, 3);
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, 0, 3);
		if (weapon) weapon->wield();
		//�����޷�����
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		//
        if( me->query_temp("sanwu/buwei")){
                me->add_temp("apply/attack", -i);
                me->add_temp("apply/whip", -i);
                me->add_temp("apply/damage", -i);
                me->delete_temp("sanwu/buwei");
        }
        me->add("neili", -200);
        me->add("jingli", -100);
        me->start_perform(4, "����������");
        return 1;
}

void check_fight(object me,object target,int amount)
{        
        int j;
        if( !objectp(target) ) return;
        if( !me
         || !me->is_fighting(target)
         || amount < 1){
              j = target->query_temp("sanwu/wusuo");
              target->add_temp("apply/attack", j);
              target->add_temp("apply/damage", j);
              target->add_temp("apply/defense", j); 
              target->delete_temp("sanwu/wusuo");
              message_vision(HIW"\n$NΪ���������������е�Ѩ���ѽ⣬������Ϊ֮һ��\n"NOR, target);
              return;
        }
        call_out("check_fight", 1, me, target, amount -1);
}

void perform_bonus(object me,object target,int amount)
{
        int j;
        object weapon;
        if (!me||!target) return;
		
		j = me->query_skill("yinsuo-jinling", 1);
        j += me->query_skill("yunu-xinjing", 1);
		j= j*me->query_per()/20;
        
		weapon = me->query_temp("weapon");

        if( me->is_fighting(target)
         && me->query_skill_mapped("whip") =="yinsuo-jinling"
         && me->query_skill_mapped("cuff") =="meinu-quanfa"
         && me->query_skill_prepared("cuff") == "meinu-quanfa"
         && environment(me) == environment(target)
         && amount > 0){
               

                switch(random(4)){
                        case 0:
                              message_vision(HIR"\n$Nֻ����ӡ�ú�̫��Ѩ������̰��ʹ,������,�ƺ��о���Ѫ�ڲ�����ʧ��\n"NOR,target);
                              target->receive_damage("jing", j,me);
                              target->receive_wound("jing", j/10,me); //edit by sohu..��������Ϊ�˺�̫�󣬵�������
                              break;
                        case 1:
                              message_vision(HIY"\n$nֻ����$N�ı�β��Ȼ��ֱ�����ؿ�̴��Ѩ���������������й��ͬʱ�ھ��޷����ơ�\n"NOR,me,target);
                              target->add("neili", -j*3);
                              if(target->query("neili") < 0) target->set("neili", 0);
							  target->apply_condition("no_exert",1);
                              target->add("jingli", -j);
                              break;                          
                        case 2:
                              message_vision(HIG"\n$Nֻ����ȫ������Ѩ�����裬���β���һ�ͣ��ж�����,�����޷����С�\n"NOR,target);
                              target->add_condition("no_perform",6);
                              target->add_busy(2+random(3));
                              break;
                        case 3:
                              message_vision(HIC"\n$nֻ����$N�ı�Ӱ��һ�ŷ������裬���Լ���������$N��$n���ƣ��ֻӳ�һƬ��Ӱ��\n"NOR,me,target);
                              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);							  
                             if (me->query_temp("weapon")) 
							 {
							 weapon = me->query_temp("weapon"); 
							 weapon->unequip(); 
                              COMBAT_D->do_attack(me, target, 0, me->query("gender")=="Ů��"?3:1);
							  COMBAT_D->do_attack(me, target, 0, me->query("gender")=="Ů��"?3:1);
                              weapon->wield();
							 }
                              break;
                }
     //           me->start_perform(3, "����������");
				if (me->is_fighting()&&objectp(target))
					call_out("perform_bonus", 3, me, target, amount - 3);
        }
        else {
                target->delete_temp("sanwu/wukong");
                return;
        }
}
int help(object me)
{
        write(WHT"\n��������֮"+HIR+"�����������֡���"NOR"\n");
        write(@HELP
	�����������ǹ�Ĺ�����似��Դ��С��Ů
	��ս���ַ�����������λӢ�ۺ���ʱ����
	�����������ǲ�����ɽ���˿���죬��Ϊ
	���ͣ��������ޱȣ�ǰ��Ϊһ��ɫ��������
	�и��ŶԷ�ʩչ�����似�Ĺ��ܡ�
	�������������ǹ�Ĺ����֮һ����Ϊ���޿�
	���롱������������������������Ϊ�����С���
	һ���޿ײ��뿴��ֻ��һ��,ʵ��ǧͷ������
	һ��֮�а�������ʮ��,��������������
	���������������ȫ�������Ѩ���ڶ���
	��������������ǵ��������ƫ��Ѩ����
	�����С�������Ϊ�����ٵ�Ѩ,����ר���۾���
	�ʺ�С���������������������֮��,��
	ʽ�������ն�����
	
	perform whip.sanwu

Ҫ��
	�������Ҫ�� 6000 ���ϣ�      
	��ǰ����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��Ů�ľ��ȼ� 400  ���ϣ�
	��Ůȭ���ȼ� 400  ���ϣ�
	��������ȼ� 400  ���ϣ�
	�����޷��ȼ� 400  ���ϣ�
	����ȭ���ұ�ȭ��Ϊ��Ůȭ����
	���������޷����м�Ϊ�������壻
	�����ڹ�Ϊ��Ů�ľ���
	�ֱֳ�����������                
                
HELP
        );
        return 1;
}