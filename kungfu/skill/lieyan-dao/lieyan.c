// guangming.c  ʥ������
// By River@SJ

#include <ansi.h>
inherit F_SSERVER;
//#include <combat.h>

//#include "/kungfu/skill/eff_msg.h";
string perform_name(){ return HIC"ʥ������"NOR; }

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
}); 

string *limb=({
"����","����","����","ͷ��","С��","�ؿ�","����","�ɲ�","�Ҽ�","�ұ�","�ҽ�",
});

int perform(object me, object target)
{
	object weapon;
	int damage, p, ap, dp,lvl,lvl1;
	string msg,name,dodge_skill,limbs;
    weapon=me->query_temp("weapon");
	if(!target) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("��ʥ�����桹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
                
	if((int)me->query_skill("lieyan-dao", 1) < 100 )
		return notify_fail("������浶��������죬����ʹ�á�ʥ�����桹��\n");

	if ( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 100 )
		return notify_fail("���ʥ���񹦲����ߣ�����ʹ�á�ʥ�����桹��\n");
                        
	if((int)me->query_skill("piaoyi-shenfa", 1) < 100 )
		return notify_fail("���Ʈ���������ߣ�����ʹ�á�ʥ�����桹��\n");

	if( me->query_skill("hand",1)<100 )
		return notify_fail("��Ļ����ַ������ߣ�����ʹ�á�ʥ�����桹��\n");

	if( me->query_skill("yingzhua-shou",1)<100 )
		return notify_fail("��ӥצ�����ֲ����ߣ�����ʹ�á�ʥ�����桹��\n");

	if((int)me->query("jingli", 1) < 300 )
		return notify_fail("��ľ�����Ϊ����������ʹ�á�ʥ�����桹��\n");

	if( me->query_skill_mapped("blade") != "lieyan-dao")
		return notify_fail("�����ڵ�״̬�޷�ʹ�á�ʥ�����桹��\n");
    if( me->query_temp("mj/lieyan"))
		return notify_fail("����������ʹ�á�ʥ�����桹������\n");

	if ((int)me->query("max_neili",1) < 1400)
		return notify_fail("�����������������޷�ʹ�á�ʥ�����桹��\n");

	msg = HIC"\n$N���һ����"HIR"Ϊ�Ƴ���Ω�����ʣ�ϲ�ֱ���Թ鳾��"HIC"��"+weapon->query("name")+HIC"���˺϶�Ϊһ����������ɱ������$n��\n"NOR;
    me->set_temp("mj/lieyan",1);
	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("blade");
	dp = target->query("combat_exp", 1) / 1000 * target->query_skill("parry");
	me->add_temp("apply/damage",me->query_skill("lieyan-dao",1)/6);
	if( random(ap + dp) > dp || random(me->query_str())>target->query_con()/2) {
		limbs= limb[random(sizeof(limb))];
		msg +=WHT"$nֻ����������·��������˵�ɱ�����֣����޿ɱܣ����ɴ�ʧɫ����ʱ��ǰһ����"+weapon->name()+CYN"�Ѵ���"+limbs+"����������\n"NOR;
		//����,��������
		/*if (!userp(target))
		    target->start_busy(1+random(2));*/
		damage = me->query_skill("blade",1);
		damage += me->query_skill("lieyan-dao",1);
		damage += me->query_skill("shenghuo-shengong",1);
		damage += me->query_skill("yingzhua-shou",1);
		damage *= 4;
		damage += random(damage/2);
		if (!userp(me)&& damage>3000) damage=3000; 
		
		if(damage > 4000) damage = 4000 + (damage-4000)/10;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add_temp("apply/attack",damage/7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query_temp("mj/shenghuo")?3:1);
		me->add_temp("apply/attack",-damage/7);
		me->add("neili", - 150);
		me->add("jingli", - 70);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", limbs);
		
		if( me->query_skill("yingzhua-shou",1 ) > 150
	 	 && me->query_skill_mapped("hand") == "yingzhua-shou"
		 && me->query_skill_prepared("hand") == "yingzhua-shou"
		 && me->query("mjyzs/pass")
	     && objectp(target)
		 //&& !target->is_busy()
			 ){
			name = xue_name[random(sizeof(xue_name))];
			msg += HIC"\n$N��������ǰһ�����˶Է�����֮�ʣ����ֱ���Ϊӥצ֮�ƣ���������ץ��$n��"+name+"��\n"NOR;
            if (me->query_skill("lieyan-dao",1)<350) ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("hand")*2; //֧������350
            else ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("hand");
			dp = target->query("combat_exp", 1) / 1000 * target->query_skill("dodge");
			
			if( random(ap + dp) > dp || living(target)) {
				me->add("neili", -100);
				if (!userp(target))
				   target->add_busy( random(me->query_skill("yingzhua-shou", 1)/50)+1 );
				else target->add_busy(1+random(2));
				msg += HIW"���$n��"+name+HIW"��ץ�����ţ�ȫ����������һ������ʱ���ɶ�����$N��׼ʱ���ֳ�һ�С�\n"NOR;
				lvl1=me->query_skill("yingzhua-shou", 1);
				weapon->unequip();
                me->add_temp("apply/hand",lvl1/5);

				target->receive_damage("qi",random(1000),me);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                me->add_temp("apply/hand",-lvl1/5);
				weapon->wield();
			 }  
		 }
		//message_vision(msg,me,target);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	//	message_vision(msg, me, target);
		me->add("neili", -100);
		me->start_busy(1);
	}
	//message_vision(msg, me, target);
	message_vision(msg,me,target);
	me->add_temp("apply/damage",-me->query_skill("lieyan-dao",1)/6);
	me->start_perform(4,"��ʥ�����桹");
	me->delete_temp("mj/lieyan");
	return 1;
}

int help(object me)
{
        write(HIC"\n���浶��"+HIR"��ʥ�����桹"NOR"\n");
        write(@HELP
	���浶�����������ż����书��Դ����ң�����з����Ĵ���
	����ʹ�书��Ϊ���ӣ��������ݶ���������ڲ�����Ϊ����
	�ݺ����̵Ķ�ͷ�����ư�ͷ�ӵ�����ʾ�����⣬ʵ�����̵�
	�󹦳���ʥ�������ǽ��������ڵ��ڣ�ȫ��һ�������Է���
	�У�ͬʱ����һ��ӥ������ʽ����Ϊ������
	
	ָ�perform blade.lieyan

Ҫ��
	�������Ҫ�� 1400 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�����ַ�Ҫ�� 100 ���ϣ�
	ӥצ����Ҫ�� 100 ���ϣ�
	���浶���ȼ� 100 ���ϣ�
	Ʈ�����ȼ� 100 ���ϣ�
	ʥ���񹦵ȼ� 100 ���ϣ�
	��������Ϊ���浶����
	�����ַ�Ϊӥצ�����֡�
���⣺
	ʥ���񹦶����浶�и������á�

HELP
        );
        return 1;
}
