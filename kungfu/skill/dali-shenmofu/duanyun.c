//�������  
//duanyun.c ѡ�Դ�����ħ���ɾ���
//cre by sohu@xojh 

#include <ansi.h>
#include <combat.h>
inherit F_DBASE;
inherit F_SSERVER;
string *bodys=({"�ؿ�","�ϱ�","С��","��","����","����","�β�"});
int perform(object me, object target)
{
        object weapon;
        int damage, axe, i,ap,pp,j;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
		||!living(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��������ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "axe" )
                return notify_fail("�������޸����������á�������ơ�����\n");


       // if( me->query_temp("sl_chaodu") )
              // return notify_fail("��������ơ��������ܼ���̫��������Υ��ͣ����ɶ��ã�\n");

        

        if(me->query_temp("dlf/duanyun"))
               return notify_fail("������ʹ�ô�����ħ���ġ�������ơ���ȫ�������Ѿ���ע�����б����У���Ͼ�����ˡ�\n");

        if((int)me->query_skill("dali-shenmofu", 1) < 300 )
               return notify_fail("�㡸������ħ������Ϊ����������δ�����򡸲�����ơ���\n");

        if((int)me->query("str")<15)
               return notify_fail("������������������޷��ó���������ơ�\n");

        if((int)me->query_con(1)<10)
               return notify_fail("��ĸ��ǲ������޷����ܡ�������ơ��ľ����ŷ���\n");

      

        if((int)me->query_skill("axe",1) < 300)
               return notify_fail("��������ơ����Ը�ͷ�����������޼᲻�ݣ���Ļ���������Ϊ��ǳ��?\n");

        if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 

        if(me->query_skill("xixing-dafa", 1)<350)
          if(me->query_skill("tianmo-gong", 1) < 350)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������������ơ���\n");  

        if (me->query_skill_mapped("axe") != "dali-shenmofu"
         || me->query_skill_mapped("parry") != "dali-shenmofu")
                return notify_fail("�������޷�ʹ�á�������ơ����й�����\n");

        if( me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ���㣬����������ʩչ��������ơ���\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("�����������������������ʩչ��������ơ���\n");

        if( me->query("jingli") <= 1500 )
                return notify_fail("��ľ������ޣ�������ʩչ��������ơ���\n");

        message_vision(HIR"\n$N���һ���������������������ζ�ʱ���ǣ���ͬ��ħ����һ�㣬����"+weapon->name()+HIR"�����ܷ��ؿ�ȥ��\n"+
			"$N����������"+weapon->name()+HIR"����һƬ��Ӱ����$n������!\n" NOR, me,target);       

        damage = (int)me->query_skill("axe",1) + (int)me->query_skill("tianmo-jue",1);
        axe = me->query_skill("axe",1);        
		i = 10+random(me->query_skill("tianmo-jue",1)/20);
        damage = damage*i;
        
		if(userp(target))
                damage = damage *2/3;
        else
                damage = damage *3/2;
        if (wizardp(me))
                write(sprintf("damage = %d\n",damage));
        ap = COMBAT_D->skill_power(me,"axe",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
        
		if(target->is_busy())
                pp /= 2;
        //���Ǵ󷨼ӳ�
		j=1;
		if (me->query_skill_mapped("force")=="xixing-dafa" && me->query("xixing",1)==1)
		{
			j=2;
		}
		if(me->query_skill("xixing-dafa",1)>550 && me->query("xixing",1)>1){
                damage *=2;
                ap *= 2;
                pp /= 2;
				j=3;
        }
		
        me->set_temp("dlf/duanyun",1);
        if(random(ap+pp)>pp)
        {
                me->add("neili", -1000);
                me->add("jingli", -800);
                if (damage>10000) damage=damage+(damage-10000)/100;
                
				target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/3,me);
                message_vision(HIY"\n$nһʱΪ$N�Ե����͵���������,�ۼ�$N��ʽѸ���ޱȣ�һʱ���мܲ�������"+weapon->name()+HIY"����"NOR+HIR+bodys[random(sizeof(bodys))]+HIY"����ʱ��Ѫ�ɽ���\n" NOR, me,target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR); 
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR); ;
               // COMBAT_D->report_status(target);
                target->start_busy(j+random(2));
				target->apply_condition("no_exert",1+random(1));
                
       }
       else {
                message_vision(HIC"\n$n�ۼ�$N�����׺ݣ������������һ�����������Ի������ɣ������������һ����\n" NOR, me,target);
				target->start_busy(1+random(1));
                me->add("neili", -1500);
                me->add("jingli", -800);
                
       }
       // if (objectp(target)&&me->is_fighting(target))
        //{
		//	message_vision(YEL"\n$N�漴���ϣ�������"+weapon->query("name")+YEL"����������\n" NOR, me,target);
        //}
        if(!userp(me)) axe = axe / 2;
        
		me->add_temp("apply/attack", axe/4);
        me->add_temp("apply/damage", axe/5);

        if(me->is_fighting(target)){
              message_vision(HIG"\n$N�Ϻ�һ����������ʽ��������ʽ��������������Ҫ�����һ��ͷ�����Ƶã�"+weapon->query("name")+HIG"����������\n" NOR, me,target);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		}
        if(me->is_fighting(target)){
			  message_vision(HIR"\n$N��ǰһ�ݣ����ֽ�ס"+weapon->query("name")+HIR"�ֺ����������ʽ����������͸��"+weapon->query("name")+HIR"�������У�\n" NOR, me,target);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		      if(me->is_fighting(target))
			     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			  if(me->is_fighting(target))
			     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
        me->add_temp("apply/attack", -axe/4);
        me->add_temp("apply/damage", -axe/5);
        me->delete_temp("dlf/duanyun");
		me->start_perform(4+random(2),"��������ơ�");

       return 1;
}


string perform_name(){ return HIW"�������"NOR; }
int help(object me)
{
        write(HIW"\n������ħ��֮��������ơ���"NOR"\n\n");
		write(
@HELP�������:
	������ħ�������еĴ�����ħ���˵�����������ϧ��
	ʮ����Χ��ɽ�󣬷����ϵ�ʧ�ٶ���ʧ����˵����
	���ڻ�ɽ��ɽɽ���з��ַ����ϵľ�������
	��������ơ������⹥���������б�������������֡�
	���ǡ�������ħ�����ķ����ռ���ʽ��
	Ҫ��
		��Ҫ������ħ��500��
		�����ڹ�Ҫ��  500��
		���������С��35��
		������ǲ�С��20��
HELP
        );
        return 1;
}

