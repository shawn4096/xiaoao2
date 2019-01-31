///kungfu/skill/quanzhen-jianfa/qixing.c ���Ǿ�����
// Modified by sohu@xojh
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIR"���Ǿ�����"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv, i, atk, hit,def;
        string htz_msg;
        object weapon = me->query_temp("weapon");
        int damage, p;     
		def=1;
        if( !target ) return notify_fail("��Ҫ��˭ʹ�á����Ǿ���������������\n");
			
		//target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
		 || !living(target)
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á����Ǿ���������������\n");
        //������ʩչ��������Ч���ε��⴫��ʽ
		if(!me->query("quest/qz/qzjf/qixing/pass"))
                return notify_fail("����Ȼ��˵�����Ǿ�����������һֱû���������о��ϣ����������ã�\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 500 )
                return notify_fail("���ȫ�潣������������ʹ���������Ǿ�������������\n");

        if ( !weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa")
               return notify_fail("�������޷�ʹ�����Ǿ�������\n");
        if(me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�����Ǿ�������\n");

        if((int)me->query_skill("sword", 1) < 500 )
               return notify_fail("��Ļ�������������죬ʹ���������Ǿ�������������\n");
        if((int)me->query_str(1) < 60)
               return notify_fail("�����Ǿ���������Ҫ�ߵı������㻹ʹ���������Ǿ�������������\n");
        if((int)me->query_dex(1) < 60)
               return notify_fail("�����Ǿ���������Ҫ�ߵ������㻹ʹ���������Ǿ�������������\n");

        if((int)me->query_skill("force", 1) < 500)
               return notify_fail("����ڹ���Ϊ�������޷�ʹ�á����Ǿ�������������\n");  
        if((int)me->query_skill("xiantian-gong", 1) < 500)
               return notify_fail("������칦��Ϊ�������޷�ʹ�á����Ǿ�������������\n");  

        if((int)me->query_temp("qzjf/qixing"))
               return notify_fail("������ʹ�á����Ǿ�������������\n"); 

        if((int)me->query("max_neili") < 5500)
               return notify_fail("��������������޷�ʹ�á����Ǿ�������������\n");
        if((int)me->query("neili") < 1500)
               return notify_fail("��������������޷�ʹ�á����Ǿ�������������\n");
        if((int)me->query("max_jingli")< 3000)
               return notify_fail("��ľ����������޷�ʹ�á����Ǿ�������������\n");


        
        me->set_temp("qzjf/qixing",1);     
        lv = me->query_skill("quanzhen-jianfa",1);
		atk= me->query_skill("quanzhen-jianfa",1)+me->query_skill("xiantian-gong",1)/2;

        //if(!userp(target)) atk = atk*3/2; //��ҹ���npc��Ч������

        hit = (lv/75); //560����
        if(hit >7) hit = 7;
        if(hit <2) hit = 2;       

        
        message_vision(HBMAG"\n$Nһ����Х��һ�����н�����Ļ�зɳ�"+chinese_number(hit)+"�亮�ǣ������籩���������ǰ���$n���˹�ȥ��\n"NOR,me,target);
        me->add_temp("apply/attack", atk/2);
		me->add_temp("apply/damage", atk/4);
       	
		htz_msg = HIC"\n$N���Լ���������������İ��غͽ������������Ĭ�����칦���������\n";
        if(hit >= 1)htz_msg += "��"HIR"�����"HIC"��";
        if(hit >= 2)htz_msg += "����"HIG"������"HIC"��";
        if(hit >= 3)htz_msg += "����"HIY"������"HIC"��";
        if(hit >= 4)htz_msg += "����"HIB"��Ȩ��"HIC"��";
        if(hit >= 5)htz_msg += "����"HIM"�����"HIC"��";
        if(hit >= 6)htz_msg += "����"HIC"������"HIC"��";
        if(hit >= 7)htz_msg += "����"HIW"ҡ����"HIC"��";

        htz_msg += "�ǹ���й��"+chinese_number(hit)+"��½��΢΢һ����\n"NOR+HIY"�����Ǿ��������ƺ��������������������������ޱȣ�\n"NOR;

        message_vision(htz_msg, me, target);
        me->set_temp("htz_times",hit);
        me->set_temp("htz_effect",1);
        me->add_temp("htz/lianhuan", 3);
        me->set_temp("action_flag", member_array("sword", keys(me->query_skill_map())));

//���Ǿ�������Ծ        
        if( objectp(target)&&me->query("str")>=45 
			&&me->query("quanzhen/force")=="pass")
		{
		         me->set_temp("htzup",1);
	           	 target->set_temp("must_be_hit",1);
		         target->add_temp("apply/defense",-2000);
				 target->add_temp("apply/armor",-lv/2);
				 target->add_temp("apply/parry",-lv/2);

				 def=3; //�����˺����Ծ
				 call_out("target_remove",lv/50,target,lv);
	             message_vision(HBBLU"\nֻ��$N�������������������Ƕ��⻪������Ͷ��֮�侹��˿���ǹ��˸���������Ǵ�����\n"NOR, me, target);
		}
		me->add_temp("apply/attack",lv/6);
		me->add_temp("apply/armor",lv/6);
		me->add_temp("apply/sword",lv/6);
        for( i=0; i < hit; i++ )
        {
              me->add_temp("htz/lianhuan", 1);            
			  if (!(objectp(target) && me->is_fighting(target)))
			  {
				 message_vision(HBRED"\n$N��Ȼ������ʽ�����񶨾����ơ�\n"NOR, me, target);
				 break;
				  
			  }
			     COMBAT_D->do_attack(me, target, weapon, 3);
              continue;
        }
		me->add_temp("apply/attack",-lv/6);
		me->add_temp("apply/armor",-lv/6);
		me->add_temp("apply/sword",-lv/6);

        //ȡ������
		me->delete_temp("htz/lianhuan");
        
		if(me->query_temp("htzup")) {
	     if(objectp(target)&& me->is_fighting(target)) {
           message_vision(HBRED"\nֻ��$N������������������ҫ�������ǲ��ơ�֮���������ռ������λ��������˸������$n��ǰ�ء�\n"NOR, me, target);
           target->add_busy(2);  
           if( random(me->query("str",1)) > target->query("str",1)/2 
              || random(me->query("combat_exp",1)/10000) > target->query("combat_exp",1)/20000 
              || random(me->query("neili",1)/100 )> target->query("neili",1) /200)
{

              message_vision(HBMAG"�Ǿ�Ө������ǹ����һ��ը�ѿ�������Ȼȫ�Ǿ����������������۶��ɣ������������޼᲻�ݣ�\n$n⧲����������±����ض������ۿ��ǻ���ˣ�\n"NOR, me, target);
              target->receive_damage("qi",2000+random(5000),me);
			  target->receive_wound("qi",2000+random(2000),me);
			  me->add_temp("apply/damage",atk/4);

              COMBAT_D->do_attack(me, target, weapon, 3);//ȡ��call die,����һ���
              me->add_temp("apply/damage",-atk/4);
           }
            else  message_vision(HBMAG"�Ǿ�Ө������ǹ����һ��ը�ѿ�������Ȼȫ�Ǿ����������������۶��ɣ������罣���޼᲻�ݣ�\n"
			                   +GRN+"$n֪���ǹ���죬��������׼���������ˣ����������ȴ�����Ǳ�������\n"NOR, me, target);
             target->receive_damage("jingli", atk,me);
		     target->delete_temp("must_be_hit");
		     target->add_temp("apply/defense",2000);  
	          	                      
		    } 			 
		}
        message_vision(HIC"\n��"+chinese_number(hit)+"�����Ǿ����������������Ƕ���ת�켣���仯��������Ѳ⣡\n"NOR, me);
		     
        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(6,"�����Ǿ�������");
		me->start_busy(1+random(2));
        me->delete_temp("htz/lianhuan");
        me->delete_temp("htz_times");
        me->delete_temp("qzjf/qixing");
        me->delete_temp("htzup");
        
        me->add_temp("apply/attack",   - atk/2);
		me->add_temp("apply/damage", -atk /4);
        return 1;
}

int target_remove(object target,int lv)
{
	if (!target) return 0;
	
	target->delete_temp("must_be_hit");
	target->add_temp("apply/defense",2000);
	target->add_temp("apply/armor",lv/2);
	target->add_temp("apply/parry",lv/2);
	return 1;
}
int help(object me)
{
        write(HIR"\nȫ�潣��֮�����Ǿ���������"NOR"\n");
        write(@HELP
	ȫ�潣��Ϊȫ������������������Ǵӵ��غͱ���������ת�Ĺ�����
	��������������������ľ��������������Ǿ���������ʽ���ǰ�
	��������й�����ȫ��̺�����ʽ������ʽ�����ޱȣ������Ƕ���
	�������°�����ȫ������������칦��ȫ�潣���ﵽ350���������
	����������ָ��ȥ��Ӧ�ص���ܶ��á�

	ָ�perform sword.qixing

Ҫ��  
	��Ч���ͱ���Ҫ������60��
	��ǰ�������� 1500 ���ϣ�
	����������� 5500 ���ϣ�
	��������� 3000 ���ϣ�
	ȫ�潣���ȼ� 500 ���ϣ�
	���칦���ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	��������Ϊȫ�潣����
	�����м�Ϊȫ�潣�������ȭ��
	�����ڹ�Ϊ���칦��
	�������>=45���ж��⹥���ӳɣ�550���������״�ɡ�
                
HELP
        );
        return 1;
}


