// feiying.c
// YUJ@SJ 2002-07-12

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int lvl, qi2,i;

        lvl = me->query_skill("yuxiao-jian", 1);
        lvl += me->query_skill("tanzhi-shentong", 1);
        lvl += me->query_skill("luoying-zhang", 1);
        lvl += me->query_skill("lanhua-shou", 1);
        lvl += me->query_skill("xuanfeng-tui", 1);
        lvl += me->query_skill("suibo-zhuliu", 1);
        lvl /= 6;
        if (!target) target = offensive_target(me);

        if (!objectp(target)
        || !me->is_fighting(target)
		||!living(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�÷�Ӱ��\n");

        weapon = me->query_temp("weapon");

        if (!weapon || !(weapon->id("xiao")))
                return notify_fail("������û������޷�ʩչ����Ӱ��\n");

        if (me->query_skill("yuxiao-jian", 1) < 500)
                return notify_fail("������｣��������죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("qimen-bagua", 1) < 200)
                return notify_fail("������Ű��Բ�����죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("tanzhi-shentong", 1) < 500)
                return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("lanhua-shou", 1) < 500)
                return notify_fail("���������Ѩ�ֲ�����죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("luoying-zhang", 1) < 500)
                return notify_fail("�����Ӣ���Ʋ�����죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("xuanfeng-tui", 1) < 500)
                return notify_fail("�������ɨҶ�Ȳ�����죬�޷�ʩչ����Ӱ��\n");

        if (me->query_skill("bihai-chaosheng", 1) < 500)
                return notify_fail("��ı̺���������򲻹����޷�ʩչ����Ӱ��\n");

        if (me->query_skill("suibo-zhuliu", 1) < 500)
                return notify_fail("����沨������򲻹����޷�ʩչ����Ӱ��\n");

        if ( me->query_skill_mapped("sword") != "yuxiao-jian"
        || (me->query_skill_mapped("parry") != "yuxiao-jian"&& me->query_skill_mapped("parry") != "tanzhi-shentong")
        || me->query_temp("thd/feiying"))
                return notify_fail("����ʱ�޷�ʹ�÷�Ӱ������\n");

        if (me->query("max_neili") < 7500)
                return notify_fail("��������������޷�ʩչ����Ӱ��\n");

        if (me->query("neili") < 4000)
                return notify_fail("��������������޷�ʩչ����Ӱ��\n");

        if (me->query("jingli") < 2500)
                return notify_fail("��ľ����������޷�ʩչ����Ӱ��\n");

        me->set_temp("thd/feiying", 1);
      //  message_vision(HIW"\n$N����һ������ʹ���һ���������Ӱ������$n��\n\n"NOR,me, target);
        
        if (me->query("thdjj/ronghe")=="pass")
			message_vision(HBRED+HIW"\n$N����һ������ʹ���һ������｣������Ӱ����������$n��\n\n"
		                              +"$N�ѵ��һ����������裬��Ӱ����������һ��¥��\n"NOR,me, target);
		else message_vision(HIW"\n$N����һ������ʹ���һ���������Ӱ������$n��\n\n"NOR,me, target);

		lvl = to_int( lvl/3.0 * lvl/275.0);//4 -> 3,350->250 
		if (me->query("thdjj/ronghe")=="pass") 
	    {
			//lvl=1.5*lvl;
			lvl=2*lvl;
			i=3;

		}else i=1;
        

        me->add_temp("apply/attack", lvl);

		me->add_temp("apply/damage", lvl/2);

        message_vision(HIG"$N���е�"+weapon->query("name")+HIG"��������ˮһ�㣬��$n�����ع�ȥ��"NOR,me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); //����һ�У�͹�����｣����Ѹ��
        message_vision(HIG"$nֻ��������˷�������Ӱ����ʱ��֪���룡\n"NOR,me, target);
        weapon->unequip();
        me->prepare_skill("hand");
        me->prepare_skill("strike");
       // me->prepare_skill("cuff");
        me->prepare_skill("finger");
        me->prepare_skill("leg");
        me->prepare_skill("claw");
        if (me->is_fighting(target)) {
                me->prepare_skill("hand", "lanhua-shou");
                qi2 = target->query("qi");
                me->add_temp("apply/hand", lvl*2);
				message_vision(HIC"\n$N��"+weapon->query("name")+HIC"������䣬˫��������������$n��ȥ��"NOR,me, target);
                COMBAT_D->do_attack(me, target, 0, i);
				me->add_temp("apply/hand", -lvl*2);
                if (target->query("qi") < qi2)
                        message_vision(HIC"$N���÷�����$n��С����ԪѨ��$n���������޷��������ۣ�\n"NOR,me, target);
        }
        if ( me->is_fighting(target)) {
                me->prepare_skill("hand");
                me->prepare_skill("strike","luoying-zhang");
                qi2 = target->query("qi");
                me->add_temp("apply/strike", lvl*2);
                message_vision(HIM"\n$Nٿ��ת��Ϊ�ƣ�$n���õ�������Ӱ������ʵʵ�޷�׽����"NOR,me, target);
				COMBAT_D->do_attack(me, target, 0, i);

				me->add_temp("apply/strike", -lvl*2);
                if (target->query("qi") < qi2)
                message_vision(HIM"$NͻȻ����$n��������Ѩ�ϣ�$n���ɵ����˿���Ѫ��\n"NOR,me, target);
        }
        if ( me->is_fighting(target)) {
                me->prepare_skill("strike");
                me->prepare_skill("leg","xuanfeng-tui");
                qi2 = target->query("qi");
                me->add_temp("apply/leg", lvl*2);
                message_vision(HIR"\n$N��δ���ƣ�����ɨҶ���Ѿ�����$n��ǰ��"NOR, me, target);
				COMBAT_D->do_attack(me, target, 0, i);

				me->add_temp("apply/leg", -lvl*2);
                if (target->query("qi") < qi2)
                message_vision(HIR"$N�����ü��ȣ�$n�������ˣ���Ͼ������\n"NOR,me, target);
        }
        if (me->is_fighting(target)) {
                me->prepare_skill("leg");
                me->add_temp("apply/finger", lvl*2);
                me->prepare_skill("finger","tanzhi-shentong");
			    message_vision(HIY"\n$N����֮�ʣ�ͻȻʹ����ָ��ͨ�Ĺ���һָ��$n̫��Ѩ��ȥ�����Ƴ�ָ������$n��ǰ��Ѩ��"NOR,me, target);
				COMBAT_D->do_attack(me, target, 0, 3);
                me->add_temp("apply/finger", -lvl*2);
                qi2 = target->query("qi");
                if (target->query("qi") < qi2)					
                message_vision(HIY"$N$nҡҡ�λΣ��ٲ�ά�衣\n"NOR,me, target);
        }  
	
		if (objectp(target)
			&&me->is_fighting(target)
			&&me->query("thdjj/ronghe")=="pass" 
			&&me->query("quest/jiuyin2/pass"))
		{
          switch(random(3)){
              case 0:
                if (me->query_skill("cuixin-zhang",1)>449 && me->is_fighting(target)) {
                    me->prepare_skill("finger");
				    me->prepare_skill("strike","cuixin-zhang");                                      
			    	//me->prepare_skill("strike");
				    me->add_temp("apply/strike", lvl*2);
			    	message_vision(RED"\n$NͻȻʹ�������澭�С������ơ��Ĺ���,��ָ��������$n���ؿ����д�Ѩ��"NOR,me, target);
			    	message_vision(HBRED"\n$n������������ʱΪ$N���У�һ��˺���ѷεľ�ʹ������"NOR,me, target);
					target->add_condition("no_exert",1+random(1));
					target->receive_damage("qi",lvl*2,me);
					target->receive_wound("qi",lvl,me);
					me->add_temp("apply/damage",(int)lvl/4);
					COMBAT_D->do_attack(me, target, 0, 3);
                    me->add_temp("apply/damage",-(int)lvl/4);
                   
					me->add_temp("apply/strike", -lvl*2);
                    qi2 = target->query("qi");              
                    if (target->query("qi") < qi2)					
                    message_vision(HIY"$Nһ������$n�����ѣ�$n�۵��³�һ����Ѫ��\n"NOR,me, target);
					break;
			     }
				 break;
			  case 1:
			  case 2:
                 if (me->query_skill("jiuyin-baiguzhua",1)>449) {
                    me->prepare_skill("finger");
                    me->prepare_skill("claw","jiuyin-baiguzhua");
					me->add_temp("apply/claw", lvl*2);
			    	message_vision(HBBLU"\n$Nָ��һ���צ��ͻȻʹ�������澭�ϵĹ���"+HIW"�������׹�צ��!\n"NOR,me, target);
					if (random(me->query_dex(1))>target->query_dex(1)/3)
					{
			    	  message_vision(MAG"\n$nֻ��$N��ָ��Ϭ�����ƺ����о綾�������㱼�'����'һ����ץ��ͷ�ǹǣ���\n"NOR,me, target);
					  target->apply_wound("qi",lvl*3,me);
                      target->apply_condition("no_perform",2+random(1));
					}
			    	me->add_temp("apply/damage",lvl/4);
					COMBAT_D->do_attack(me, target, 0, 3);
                    me->add_temp("apply/damage",-lvl/4);
					me->add_temp("apply/claw", -lvl*2);
                   // qi2 = target->query("qi");          
                    if (objectp(target)&&!random(5)){
						target->receive_damage("qi",random(3000),me);
						target->receive_wound("qi",random(1000),me);
                        message_vision(HIY"$NצӰ��˸�����в���$n��ͷ����$nһ��С�ģ���˺ȥһ��ͷƤ��\n"NOR,me, target);                    
					}				
				   
                }
				break;
				
				  //case 2:  Ԥ���ӿڣ������ĺݶ���ʽ��
		   }
	   }

	
	
	    message_vision(HIW"\n$N��Ӱʹ�꣬��һ�ν�"+weapon->query("name")+HIW"�û����С�\n"NOR,me);
        weapon->wield();
		me->start_busy(2+random(2));
        me->add_temp("apply/attack", -lvl);
	    target->set_temp("faint_by",me);//����һ����ǣ�����Ī���������� by renlai

		me->add_temp("apply/damage", -lvl/2);
        me->add("neili", -450);
        me->add("jingli", -180);
        me->start_perform(5, "����Ӱ��");
        me->delete_temp("thd/feiying");
        return 1;
}

string perform_name(){ return HIW"��Ӱ����"NOR; }

int help(object me)
{
        write(HIW"\n���｣��֮����Ӱ��������"NOR"\n\n");
        write(@HELP
	���｣���������֮��а��ҩʦ�Ķ��ž�����
	��ʽ���ã��ͷײ��ã����Ǽ��һ��������似
	�Ĵ�ˣ������⿪�һ���һϵ��С����󣬷�
	Ӱ�Ĺ������������ϵķ�Խ����Ȼ���⿪�һ�
	���������⣬��ᷢ�����ʵĲ�ͬ��
	
	ָ�perform sword.feiying

Ҫ��
	��ǰ�������� 4000 ���ϣ�
	����������� 7500 ���ϣ�
	��ǰ�������� 2500 ���ϣ�
	���｣���ȼ� 500 ���ϣ�
	���Ű��Եȼ� 200 ���ϣ�
	��ָ��ͨ�ȼ� 500 ���ϣ�
	������Ѩ�ֵȼ� 500 ���ϣ�
	��Ӣ���Ƶȼ� 500 ���ϣ�
	����ɨҶ�ȵȼ� 500 ���ϣ�
	�̺��������ȼ� 500 ���ϣ�
	�沨�����ȼ� 500 ���ϣ�
	�ֳ�����������

HELP
        );
        return 1;
}


