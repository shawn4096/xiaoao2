// xinghe Modify By River@SJ 2001.12.13
inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>
void check_xinghe(object me, object target, int count);
void xinghe_effct(object me);

mapping valid_types = 
([
	"finger":	"ָ��",
	"hand":		"�ַ�",
	"cuff":		"ȭ��",
	"claw":		"צ��",
	"strike":	"�Ʒ�",
	"leg":		"�ȷ�",
]);

int perform(object me, object target)
{
	string *skill, basic1, msg, sk;
	int i,lvl;
	mapping smap, pmap;
    lvl=me->query_skill("tanzhi-shentong",1)+me->query_skill("bihai-chaosheng",1)/5;
	if( !target ) target = offensive_target(me);

        if( !objectp(target)
	 ||  !target->is_character()
	 ||  !me->is_fighting(target) )
		return notify_fail("���Ǻ�ǧ���衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  
	if ( me->query_skill("bihai-chaosheng", 1) < 350 )
		return notify_fail("��ı̺��������������޷�ʹ���Ǻ�ǧ���衣\n");

	if ( me->query_skill("suibo-zhuliu", 1) < 350 )
		return notify_fail("����沨������Ϊδ�����޷�ʹ���Ǻ�ǧ���衣\n");

	if ( me->query_skill("tanzhi-shentong", 1) < 350 )
		return notify_fail("��ĵ�ָ��ͨ��Ϊδ�����޷�ʹ���Ǻ�ǧ���衣\n");

	if ( me->query_skill_mapped("parry") != "tanzhi-shentong"
	 || me->query_skill_mapped("finger") != "tanzhi-shentong"
	 || me->query_skill_prepared("finger") != "tanzhi-shentong")
	 	return notify_fail("�������޷�ʹ���Ǻ�ǧ���衣\n");

	if ( me->query_temp("weapon"))
		return notify_fail("�������޷�ʹ���Ǻ�ǧ����,������֡�\n");

	if ( me->query_skill("finger",1) < 350 )
		return notify_fail("���ָ����Ϊ���㣬ʹ�����Ǻ�ǧ���衣\n");

	if( me->query("max_neili") < 3500 )
		return notify_fail("������̫�������ܳ��Ǻ�ǧ���衣\n");

	if( me->query("neili") < 1200 )
		return notify_fail("������̫�������ܳ��Ǻ�ǧ���衣\n");

	if( me->query("jingli") < 1000 )
		return notify_fail("�㾫��̫�������ܳ��Ǻ�ǧ���衣\n");
    if (me->is_busy()
	  ||me->query_temp("no_prepare")
	  ||me->is_perform()
	  ||me->query_condition("no_perform")){	  
	  return notify_fail("����Ѫ���ȣ��޷�ʹ���Ǻ�ǧ���衣\n");
    }
		
	if (me->query_temp("thd/xinghe"))
		//|| me->query_temp("xinghe")
		return notify_fail("������ʹ���Ǻ�ǧ���衣\n");

	sk = me->query("env/xinghe");

	if (!sk || sk == "tanzhi-shentong") 
		return notify_fail("�����ѡ��һ����������ϣ�\n");

	if (me->query_skill(sk,1) < 350)
		return notify_fail("�����ϼ��ɻ�û���졣\n");
	//����map���似
	smap = me->query_skill_map();
	//����prepare���似
	pmap = me->query_skill_prepare();
	//��������ǺӵĻ����似basic1
	skill = keys(valid_types);
	for (i=0; i<sizeof(skill); i++) {
		if( smap[skill[i]] == sk ) basic1 = skill[i];
	}
	if ( !basic1 )
		return notify_fail("���ּ�����δ������Ŀǰ����׼����\n");
	//��ʱ��������prepare ���ܣ�

	skill = keys(pmap);
	for (i=0; i<sizeof(skill); i++) {
		me->prepare_skill(skill[i]);
	}
	//����׼���¼���
	me->prepare_skill(basic1, sk);
	//������Ϊ
	me->reset_action();

	if (me->query_skill("tanzhi-shentong",1)<400)
	   me->start_perform(2, "�Ǻ�ǧ����");
	
	message_vision(HIW"\n$N��Хһ�������μӿ죬ʩչ���һ����������Ǻ�ǧ���衹������һ�䣬��ʱ���ʩչ��ָ��ͨ��\n"NOR,me,target);
	me->add("neili",-400);
	me->add_temp("apply/attack", lvl/4);
	me->add_temp("apply/damage", lvl/6);
	me->add("jingli", - 200);
	me->set_temp("thd/xinghe",lvl);
	//message_vision(msg, me, target);
	if ( me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, 0, 3);
  /*  if ( me->is_fighting(target) )
                 COMBAT_D->do_attack(me, target, 0, 3);*/
	//if ( me->is_fighting(target) ){
		//remove_call_out("check_xinghe");
		//��Ϊֱ�ӵ��ã��������
	call_out("check_xinghe", 1, me, target, (int)me->query_skill("tanzhi-shentong",1));
	//}
	return 1;
}

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 

void check_xinghe(object me, object target, int count)
{
	int p, lvl, dam,i, x=1;
	int ap, dp;
	string msg, *skill, dodge_skill, name, *limbs;
	mapping pmap;
    object weapon;
	
 
	if ( !me ) return; //�������˳�
	//if( !target ) target = offensive_target(me);
	weapon=me->query_temp("weapon");

    lvl=me->query_temp("thd/xinghe");

	dam = (me->query_skill("finger",1)+me->query_skill("tanzhi-shentong",1)+me->query_skill("bihai-chaosheng",1))* 2;
	dam += me->query("jiali");
	dam += random(dam);

	pmap = me->query_skill_prepare();	

	if (count < 1 || !me->is_fighting() || !objectp(target)|| objectp(weapon))
	{
		me->delete_temp("thd/xinghe");
		if (weapon)
		{
			message_vision(HIC"$N�������������ǺӶ�ʱ���᲻������\n"NOR,me);
		}
		
		skill = keys(pmap);
		for (i=0; i<sizeof(skill); i++) {
			me->prepare_skill(skill[i]);
		}
		me->prepare_skill("finger", "tanzhi-shentong");		
		//me->delete_temp("xinghe");
		me->add_temp("apply/attack", -lvl/4);
		me->add_temp("apply/damage", -lvl/6);
		if (me->query_skill("tanzhi-shentong",1)<400)
			me->start_perform(1, "�Ǻ�ǧ����");
		if (living(me) && !me->is_ghost())
			message_vision(HIW"\n$N����һ�䣬��ת���˵�ָ��ͨ��\n"NOR, me);
		return;
	}

		if (!sizeof(pmap)) msg = "unarmed";
		else msg = keys(pmap)[0];

		limbs = target->query("limbs");
		name = xue_name[random(sizeof(xue_name))];
		
		message_vision(HBGRN+HIW+"\n$N����ָ��ͨЮ������֮�У�����һ��ָ�磬ֱָ��$n�ġ�"NOR+HIR+name+HBGRN+HIW"����\n"NOR, me, target);
		message_vision(replace_string(SKILL_D("tanzhi-shentong")->query_action(me, 0)["action"],"$l", limbs[random(sizeof(limbs))]) + "��\n"NOR, me, target);
        
		
	   
		if ( me->is_fighting(target)&&objectp(target) )
                 COMBAT_D->do_attack(me, target, 0, 3);
		switch (random(3)) 
		{
			case 0:
				if (objectp(target) && me->is_fighting(target) )
				{	
					target->receive_damage("qi", dam, me);
					target->receive_wound("qi", dam/4, me);
					if (!random(3)) target->add_condition("no_exert", 2);
				//msg = COMBAT_D->damage_msg(lvl, "����");
					message_vision(HIC"$N����������ʳָ����ָ��ͨ�������ȣ��������Ī��,ָ������������������\n"NOR,me,target);
					//if(userp(me) && me->query("env/damage"))
						//tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ dam+ WHT"�㹥���˺���\n"NOR);
				
					//if(userp(target)&& target->query("env/damage"))
						//tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ dam+ WHT"���˺���\n"NOR);
					if (random(2) && target->query("qi") >=0 || target->query("eff_qi")+target->query_temp("apply/qi") < 0) 
					{
						p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100
							/(target->query("max_qi")+target->query_temp("apply/qi"));
						msg = "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
					}
					else {
						p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
						msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
					}
					msg = replace_string( msg, "$w", "��ָ����");
				//	msg = replace_string( msg, "$l", name);
					//me->delete_temp("xinghe/"+target->query("id"));
					//message_vision(msg,me,target);  //����msg�����strike����Ϣ����ʱ���� by renlai
 					message_vision(HIG"$N��$n����ʽһ����ã֮�ʣ���ָ��ͨ�������У�\n"NOR, me, target);
					COMBAT_D->do_attack(me, target, 0, 3);
					//COMBAT_D->do_attack(me, target, 0, 3);
				}
				break;
			case 1:
				if (objectp(target) && me->is_fighting(target) )
				{
 					message_vision(HIY"$N��ָ��ͨ�����Ѿ������뻯����������������$n��"+HIR+name+HIC"����\n"NOR, me, target);
					if (userp(target)) target->add_busy(2);
					else target->add_busy(4);
				}
				break;
		    case 2:
				if (objectp(target) && me->is_fighting(target) )
				{
				 message_vision(HIG"$n��΢¶��������$N����ָ��ͨ����������$n��"+HIR+name+HIG"������������\n"NOR, me, target);
                 
				 target->receive_damage("jing",random(500),me);
				 
				 me->add_temp("apply/finger",(int)me->query_skill("finger",1)/3);
				 COMBAT_D->do_attack(me, target, 0, 3);
				 COMBAT_D->do_attack(me, target, 0, 3);
				 me->add_temp("apply/finger",-(int)me->query_skill("finger",1)/3);
			    }
				break;			
			//default: call_out("xinghe_effct",2,me);
			
		}
		 //remove_call_out("check_xinghe");
		call_out("check_xinghe", 2, me, target, count -1);
	return;	

}

string perform_name(){ return HIW"�Ǻ�ǧ����"NOR; }

int help(object me)
{
        write(HIW"\n��ָ��֮ͨ���Ǻ�ǧ���衹��"NOR"\n\n");
        write(@HELP
	��а��ҩʦϲ��ʫ�ʸ踳������ϲ�������յġ���Ұ���
	��������������Ǻ���תǧ���衣�·��λ���������
	����������ҹ�δ����ҵ�·�����ĺ��ѧʫ���о���
	�������������٣�����ס�����۴�ȡ��ɽȥ��������
	ҩʦ�����⾳���뵽�Լ�ƽ���������֮�С�
	
	perform finger.xinghe
	
Ҫ��
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1200 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�̺������ȼ� 350 ���ϣ�
	�沨�����ȼ� 350 ���ϣ�
	��ָ��ͨ�ȼ� 350 ���ϣ�
	����ָ���ȼ� 350 ���ϣ�
	����ָ��Ϊ��ָ��ͨ��
	�����м�Ϊ��ָ��ͨ��
	�����ұ�ָ��Ϊ��ָ��ͨ��
	ע����400�����Ծ
ʹ��˵����
	set xinghe <���������书>
	����set xinghe luoying-zhang

HELP
        );
        return 1;
}
