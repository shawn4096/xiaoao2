// cangsong.c ����ӭ�� Created by LSXK@hsbbs 2007/7/25
// �ڡ�Ц�������������Ϊ��������������趨Quest,��Ҫ���������̺�����������
// ���ͽ�questǰ�������ʣ�����quest�󣬲Żָ��̺õ����С�  By lsxk@hsbbs 2007/7/31
/* ����ͷ�ٿ��ڶ���ͼ��ʱ����ʹ������ʹ�Ǳ���һ�С�����ӭ
   �͡�����ʱ����һ����һ�����������㻨��һ����ʱ�����
   �ô��죬�ѳ�Ϊ���ٵ�ʱ�ľ���֮һ��
*/

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name() {return HIG"����ӭ��"NOR;}
int perform(object me, object target)
{
        object weapon;
        int damage,p,i;
        string msg,dodge_skill;
        if ( me->query("quest/hsjf/cangsong")=="pass")
        {
			i=3;
        }
		else i=1;
		weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("������ӭ�͡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("huashan-jianfa", 1) < 250 )
                return notify_fail("��Ļ�ɽ��������̫ǳ��ʹ������ɽ����֮������ӭ�͡��Ĺ���!\n");

        if( (int)me->query_skill("sword", 1) < 250 )
                return notify_fail("��Ļ�������̫��,ʹ����������ӭ�͡��Ĺ���!\n");

        if( (int)me->query_skill("huashan-qigong", 1) < 250
	       &&(int)me->query_skill("zixia-gong", 1) < 250)
                return notify_fail("��������ڹ�̫��,ʹ����������ӭ�͡��Ĺ���!\n");

        if(me->query_skill_mapped("force") != "huashan-qigong"
         &&me->query_skill_mapped("force") != "zixia-gong" )
            return notify_fail("��������ڹ����ԣ��޷�ʹ�á�����ӭ�͡���\n");

        if( (int)me->query("max_neili") <2500 )
               return notify_fail("���������Ϊ̫ǳ��ʹ����������ӭ�͡���\n");

        if( (int)me->query("neili") <1000 )
                return notify_fail("�������������ʹ����������ӭ�͡�����\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "huashan-jianfa"
	    || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("�㲻ʹ�û�ɽ����,���ʹ���ˡ�����ӭ�͡�?\n");
                 
        me->set_temp("hsjf/cangsong", 1); 
//���ܲ�����ʽ
       if(target->query("cs_upgrade") && target->query("cs_kill_id") == me->query("id") && me->query("quest/hsjf/cangsong")!="pass")
	   {
          if(random(me->query("kar"))>26)
		  {
			me->delete_temp("sj_credit/quest/hs/cangsong");
			message_vision(HIG"\n$NͻȻ����ˡ�����ӭ�͡��ľ�Ҫ��������ӯ���ɣ�������׾�����������ǳ���\n\n"NOR,me);
			log_file("quest/cangsong", sprintf(HIG"����ӭ��Quest��¼��%s(%s)�ɹ���ᡸ����ӭ�͡�������%d��"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
			me->set("quest/hsjf/cangsong","pass");
		  } else{
			message_vision(BLINK HIR"\n$N��˼�����֮�ԣ���������⡸����ӭ�͡��ľ�Ҫ֮����\n"NOR,me);
			log_file("quest/cangsong", sprintf(HIR"����ӭ��Quest��¼��%s(%s)ʵսδ��ᡸ����ӭ�͡�������%d��"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
		  }
		}

        message_vision(HIG"\n$N���е�"+weapon->query("name")+HIG"ͻȻһ�Σ��������ߣ�һ������������һƬ��Ӱ��һ�С�"+GRN+"��"+
           "��ӭ��"+HIG+"��ֱ��$n��\n"NOR,me,target);
	   message_vision(HIM"\nֻ��$N������"+weapon->query("name")+HIM+"�����̳�,����˿�����ζ�,�����ж����������������뻯��!\n"NOR,me);

      if( random(me->query_skill("sword",1))>target->query_skill("parry",1)/3 
           || random(me->query("combat_exp")) > target->query("combat_exp")/2
           || target->is_busy() )
	  {
           damage = (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("sword",1);
		   //�����˺������ڹ�
		   if ( me->query("huashan/quest") == "����")
		        damage=damage+(int)me->query_skill("force",1);

				damage = damage*2 + random(damage);
           if ( me->query("quest/hsjf/cangsong")=="pass") {
               damage = damage*2;
               message_vision(HIW "$N���С�"+GRN+"����ӭ��"+HIW+"���ѵþ�Ҫ,��ʱʹ������,�����˽������!\n"NOR,me,target);
           }

           if (wizardp(me))
               write(HIR"damage is; "+damage+" !\n"NOR);
           
		   me->add("neili", -100);
           me->add("jingli",-100);
		   if (damage>3000) damage=damage+(damage-3000)/100;
		 
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage /3,me);

           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           //target->set_temp("last_damage_from", me);
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", random(2)?"�ؿ�":"����" );
           msg = replace_string( msg, "$w", weapon->query("name"));
	       message_vision(msg, me, target);
		   //�⿪����������
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		   if (objectp(target)&&me->query("quest/hsjf/cangsong")=="pass"&&me->is_fighting())
		   {
			   message_vision(HBBLU+HIW"$N������Ĳ���ӭ�;���ʩչ������˲�佫ƽʱ�����������ʽϤ���ڻ��ͨ����$n�������С�\n"NOR,me,target);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);

		   }
		   if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR); 
		   
if(userp(target)&& target->query("env/damage"))
			   tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
		   } else {
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      message_vision(msg, me, target);
              me->add("neili", -100);
              me->start_busy(1); 
              target->add_busy(random(2)+1); 
        }
         //�������ɴ򶷡�
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
         message_vision(HIB"\n$N������$n��˿����Ϣ����,������"+weapon->query("name")+HIB"��һ�λӳ�,�������ᡱ��һ��,"+
           "��Я���ޱ������Ľ�������$n!\n"NOR,me,target);

        if( random( me->query_dex(1)) >target->query_dex(1)/2
           || random(me->query("combat_exp")) > target->query("combat_exp")/3
           || target->is_busy() )
		{
           damage =  (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("force",1);
		   
           damage = damage + random(damage*3/2);
           if ( me->query("quest/hsjf/cangsong")=="pass") {
               damage = damage*2;
		       target->add_busy(2+random(2));
               message_vision(HIR "$N���ѽ��������ô������,����һ��,�������������Ʊ�����ǧ�������,ֱϮ$n����֮��!\n"NOR,me,target);
           }
           if (wizardp(me))
               write(HIR"damage is; "+damage+" !\n"NOR);
           me->add("neili", -200);
           me->add("jingli",-100);
		   if (damage>5000) damage=damage+(damage-5000)/100;
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/3,me);

           p = (int)target->query("qi")*100/(int)target->query("max_qi");
          // target->set_temp("last_damage_from", me);
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", random(2)?"ͷ��":"����" );
           msg = replace_string( msg, "$w", weapon->name());
	       message_vision(msg, me, target);
		   if (me->is_fighting(target))
		 		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
		   if (me->is_fighting(target))
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        } 
        else {
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      message_vision(msg, me, target);
              me->add("neili", -100);
              me->start_busy(1); 
              target->add_busy(random(2)+1); 
        }
        me->delete_temp("hsjf/cangsong"); 

        me->start_perform(4, "������ӭ�͡�");
        return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"HIG"����ӭ��"WHT"����"NOR"\n");
   write(@HELP
	���������˸�����������ɽ�����������ɡ����������ơ�����
	������ӭ�͡����ǻ�ɽ��ͽ�����ĵ������,����ƽƽ�����޻���,
	�����������������������,�������ϼ��,ʵ�˻�ɽ����һ��ɱ��!
    
	ָ�perform sword.cangsong

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 2500 ���ϣ� 
	��ɽ���� 250 ���ϣ�
	�������� 250 ���ϣ�
	��ɽ����/��ϼ�� 250 ���ϡ�
˵����
	���ܵõ������ָ�㣬����������⣬����������

HELP
   );
   return 1;
}
