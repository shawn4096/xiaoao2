// xu.c Ǭ����Ų�ơ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int check_fight(object me);
string perform_name(){ return HIY"���־�"NOR; }

int perform(object me, string arg)
{
	object ob;
	string msg;
	int i, jiali, p, damage;
        
	if(!me->is_fighting())
		return notify_fail("��û��ս�����أ�\n");

	if(me->query_temp("weapon"))
		return notify_fail("����־��˿��־������������������ʹ�ó���\n");

	if ( me->query_temp("qkdny/xu") == 1)
		return notify_fail("���Ѿ�ʹ���ˡ���־��ˡ�\n");

	if (!me->query("mjqkdny/pass"))
	{
        if ( me->query_temp("qkdny/yi") )
		   return notify_fail("������ʩչ���ơ��־��أ�\n");

	    if ( me->query_temp("qkdny/yin") )
		   return notify_fail("������ʩչ�������־��أ�\n");

	    if ( me->query_temp("qkdny/hua") ) 
		   return notify_fail("������ʩչ�������־��أ�\n");
	}
	
	if(me->query_temp("qkdny/xu") > 1) {
		if(arg && !objectp(ob = present(arg, environment(me))))
			return notify_fail("��û��ս�����أ�\n");
		else    ob = offensive_target(me);

		if(!ob 
		 || !ob->is_character() 
		 || !me->is_fighting(ob) 
		 || environment(ob) != environment(me) 
		 || !living(ob))
			return notify_fail("����־������������ֻ�ܶ�ս���ж���ʹ�á�\n");
         	
		i = me->query_temp("qkdny/xu");
         	
		if(me->query("neili") < i)
			i = me->query("neili");
         		
		jiali = me->query("jiali");
         	
		if(jiali > i)
			i = jiali;
         		
		if(i < 10)
			return notify_fail("�㡸��־������������̫�٣�ֻ��û��ʲô���ã�\n");
         	
		me->set("jiali", i+jiali);

		if(wizardp(me))
			tell_object(me, "����־����� = "+i+"\n");

		msg = HIY"\n$NͻȻ����һ�������������ʮ���Ƶ������鲢��Ϊһ��Ѹ������$n��\n"+
			"����һ�������ɽ�鱬��ʱ�����˺�ˮ���͵�����̱�������ˮ���������"NOR;
	

		damage = me->query_temp("qkdny/xu") * (4+random(2));
		ob->receive_damage("qi", damage, me);
		ob->receive_wound("qi", damage/3*2 + random(damage/3), me);
		if (random(2)) {
			p = (ob->query("eff_qi")+ob->query_temp("apply/qi"))*100/(ob->query("max_qi")+ob->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = ob->query("qi")*100/(ob->query("max_qi")+ob->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	//	msg+="����ԭ����˴�����$p������ʵ�ˣ�������ʱ��ǡ��۹ǡ���ǡ��߹�һ���۶ϣ���\n"+
			//"ѪҲ�粻������������Ϊһ��Ѫ��ģ�����Ҳ����ԣ�\n"NOR;
		message_vision(msg, me, ob);

		me->set("jiali", jiali);
		me->delete_temp("qkdny/xu");
		me->reset_action();
		me->start_busy(2);
		ob->add_busy(2);
  	 if (!me->query("mjqkdny/pass"))
	  {
		  me->start_perform(2, "����־�");

	   }
	   return 1;
	}
	if(me->query_skill("qiankun-danuoyi", 1) < 400 )
		return notify_fail("���Ǭ����Ų�ƻ�δ�������߲㣬����ʹ�á���־���\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("��û��ʹ��Ǭ����Ų����Ϊ�н����޷�ʹ�á���־���\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 400 )
		return notify_fail("���ʥ���񹦵ȼ�������\n");
                 
	if((int)me->query("neili") < 4000 )
		return notify_fail("��Ŀǰ������������\n");
	if((int)me->query_skill("force") < 400 )
		return notify_fail("����־���Ҫ�����ڹ�����������������󻹲�����\n");
        
	if((int)me->query_temp("qkdny/yi") )
		return notify_fail("������ʩչ���ơ��־��أ�\n");
                
	me->add("neili", -200);
	tell_object(me, HIC"\n�㰵������Ǭ����Ų���ķ��о�������ʩչ����־������Է���������������������\n\n"NOR); 
	me->set_temp("qkdny/xu", 1);
	check_fight(me);
	return 1;
}

int check_fight(object me)
{

	if (!me || !me->query_temp("qkdny/xu")) return 0;

	else if(me->is_ghost() || !living(me))
		me->delete_temp("qkdny/xu");
        
	else if(!me->is_fighting()){
		tell_object(me, BLU"\n���˳���ս�����㽫�������������ɢ�˳�ȥ��\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else if(me->query("neili") <= 1000){
		tell_object(me, BLU"\n��ͻȻ���ֱ����������Ѿ�Ҫ�ݽ�����æ�ѻ��������ɢ�˳�ȥ��\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else if (me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 || (me->query_temp("weapon")&&!me->query("mj/qkdny/ronghe"))){
		tell_object(me, BLU"\n������һת���ı���ս�����ѻ��������ɢ�˳�ȥ��\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else call_out("check_fight", 1, me);
	return 1;
}

int help(object me)
{
        write(HIC"\nǬ����Ų�ơ����־�����"NOR"\n");
        write(@HELP

	�����������ǡ������޼ɵ������书������ԭ���̵Ľ�����
	ϰ�á�����Դ�Բ�˹�ݻ�̣������֮������ѧ������Ԫ��
	��仯���棬�������������۷���书���˹����߲㾳��
	���Ը�����ϰ����һ�������꣬�ڶ���ӱ��������������
	�������߱���ֻ���������㣬ϰ�����߲���ʵ�ǹ���������
	һ�ˡ���Ҫ�оŴ��ܣ������������Ǳ�������书������
	�ɣ���������������������ճס������ǣ��Ų�Ƶо���
	�������֣�ת���������������������ȡ�
	�ر�ע�⣺���⿪Ǭ����Ų�Ƶĵ��߲���ʱ��Ǭ����Ų��
	��������ʹ�ø������������־����ǿ����似��
	
	ʹ��ָ�perform parry.xu
	
Ҫ��
	��ǰ���������� 4000 ���ϣ�
	Ǭ����Ų�Ƶȼ� 400 ���ϣ�
	�����ڹ��ĵȼ� 400 ���ϣ�
	ʥ���񹦵ĵȼ� 400 ���ϣ�
	�����м�ΪǬ����Ų�ơ�
	�����ںϺ�������Ծ��
        
HELP
        );
        return 1;
}