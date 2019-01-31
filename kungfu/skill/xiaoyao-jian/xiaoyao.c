// xiaoyao.c ��ң����֮ ��ң����
// By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j,damage,count,skill;
		object weapon,weapon2,tweapon,*inv;
		weapon=me->query_temp("weapon");
		//weapon2=present("sword",me);
        inv = all_inventory(me);
		skill=me->query_skill("xiaoyao-jian",1);
        
		for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "dagger") 
		   {
			   weapon2 = inv[i];
			   break;
		   }
        }
		
        if(!objectp(weapon) || !objectp(weapon2)||weapon2->query("skill_type")!="dagger" ||weapon->query("skill_type")!="sword")
		    return notify_fail("����һ��ִ����һ��ذ�ף�����ʩչ���е���ң����������\n");
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("����ң������ֻ����ս����ʹ�á�\n");       
        if( !objectp(me->query_temp("weapon")) )
               return notify_fail("�����������������ʩչ����ң��������\n");
        if( me->query_temp("xyjf/xiaoyao"))        
                return notify_fail("������ʹ�á���ң����������\n");
		if( me->query("xyjf/jueji")!="pass")        
                return notify_fail("����Ȼ��˵����ң����������δ��Ⲣ����ʹ�á���ң����������\n");
        if((int)me->query_skill("sword", 1) < 350 )
                return notify_fail("��Ļ�������̫�ͣ��޷�ʹ�á���ң��������\n");  
        if((int)me->query_skill("xiaoyao-jian", 1) < 350 )
                return notify_fail("�����ң����������죬����ʹ������ң��������\n");
        if (me->query_skill_mapped("parry") != "xiaoyao-jian"
           && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("����мܲ��ԣ�������ʹ�á���ң����������\n");   
        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("��Ľ������ԣ�������ʹ�á���ң����������\n");   
	    if ( me->query("max_neili") < 3500 )
                return notify_fail("��������Ϊ̫ǳ���޷�ʹ�á���ң��������\n");                
        if( (int)me->query("neili") < 1000 )
                return notify_fail("�������������������ܷ�������ң��������\n");       
         if((int)me->query_skill("shenghuo-shengong", 1) < 350 )
                return notify_fail("���ʥ���񹦵ȼ�����������Ӧ�á���ң��������\n");       
    
        i=me->query_skill("sword",1)+me->query_skill("xiaoyao-jian",1)+me->query_skill("force",1);
        j=target->query_skill("parry",1)+target->query_skill("dodge",1)+target->query_skill("force",1);         
       
	    me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/5);
		me->add_temp("apply/sword",skill/5);

        message_vision(HIR"ֻ��$N����̧�ȣ�ͻȻ֮�䵹�����࣬һת����������֮�⣬�漴��ٿȻ�����������ϳ��һ��"+weapon2->query("name")+HIR"\n"+
		  HIC"$N�����е����ѱ����䶯��������ʽȴ�Ǻ�����գ��仯�޷�,ɷ�Ǻÿ���\n"NOR,me, target);
         me->add("neili", -600);
        // me->start_busy(2);
	 	if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
		{	
			message_vision(HIY"$N�������������˴�ײ����������ϵ�������$nһ���䲻������Ϊ���������š�\n"NOR,me, target);
			target->receive_damage("jing",i/2,me);
			target->receive_wound("jing",i/6,me);
		    target->add_busy(2+random(1));
		}	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	   //����
	   if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 300 ){
	      message_vision(MAG"ֻ�����������죬$N��������Сʯ����$n�佫�����������ƿ�֮����ֱ��$n������Ѩ����\n"+
			  HIY"ȴ��$N�ԡ���ָ��ͨ�����ˡ���ʯ��Ѩ���Ĺ���$nһ��С�ı�ʯ�ӵ��С�"HIR"����Ѩ"HIY"����\n"NOR,me, target);
	     target->apply_condition("no_exert",2); 
		 weapon->unequip();
		 me->add_temp("apply/attack",i/6);
         me->add_temp("apply/damage",i/8);
		 target->add_busy(2);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		 me->add_temp("apply/attack",-i/6);
         me->add_temp("apply/damage",-i/8);
		 weapon->wield(); 
       }
	   //dagger
	   if ( me->is_fighting(target)&& me->query_skill("xiaoyao-jian", 1) > 350 ){
	 message_vision(HIG+"$N�����������������и����Ȳ��񽣣��ֲ���ذ�ף�ȴ������$N��˫�ּ��������裬�����ɽ���\n"+
		 "������Ϊ��ü�̡������������䲻�ݷ�����������½������$n������\n"NOR,me, target);
        target->receive_damage("qi",i*3,me);
        target->receive_wound("qi", i/8,me);
		weapon->unequip();
		weapon2->wield();
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		weapon2->unequip();
		weapon->wield();
        }
	//���
	  if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 350 ){
	     message_vision(HIW+"$N������ϣ�˫�ֻ��裬�������ֽ�����ǹ�̡��򡢲����ģ��ͷ�Ѥ�ã�Ŀ��Ͼ�ӡ�\n"+
		 HIC+"$N����"+weapon2->query("name")+HIC"�������йٱʵ㡢�����ࡢ��������ʱ����ذ�ף�����ˮ�̡�\n"NOR,me, target);        
         target->add_busy(1+random(2));
		 target->receive_damage("qi",i*2,me);
         target->receive_wound("qi", i/4,me);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		}
     if ( me->is_fighting(target) && me->query_skill("xiaoyao-jian", 1) > 400  ){
	   message_vision(HIB"$N���쳤Хһ������Ȼ�������˶�ʮ���������ʽ��ÿ����о���������ʽ��һ����ʮ������ʽ½��ʩչ��\n"NOR,me,target);
	   message_vision(HIY"������ʽ�����ͷף����䲵�ӣ���$Nʩչ������������˵��������������Ŀ��\n"NOR,me,target);

	     me->add_temp("apply/attack",i/5);
         me->add_temp("apply/damage",i/6);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
         me->add_temp("apply/attack",-i/5);
         me->add_temp("apply/damage",-i/6);
	  }
		me->add("neili", -(200+random(100)));
		 me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/5);
		me->add_temp("apply/sword",-skill/5);
        me->start_perform(5, "����ң������");   
		
        return 1;

}

string perform_name(){ return HIC"��ң����"NOR; }
int help(object me)
{
        write(HIG"\n��ң����֮"+HIC"����ң������"NOR"\n");
        write(@HELP
	�����������̹�����ʹ���뷶ң�ϳơ���ң���ɡ���һ���书���䲵�ӣ�
	��ߴ����Եļ�Ϊ����ң����������������һս�������������书��
	��������һ����ս�����书֮�����������ֵ����쾡�£���ƽ��һ
	��������ķ�ң����Ϊ̾����
	��ң����������ң�������еľ�����һ����ȫ�����ӡ������ֳֽ�
	ذ����ʩչ���С�
	
	ָ��;perform sword.xiaoyao

Ҫ��  
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 600 ���ϣ�
	��ң�����ȼ� 350 ���ϣ�
	ʥ���񹦵ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������Ϊ��ң������
	�����м�Ϊ��ң������Ǭ����Ų�ƣ�
	�����ڹ����ޡ�
HELP
        );
        return 1;
}