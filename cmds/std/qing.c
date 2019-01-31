#include <ansi.h>

int main(object me, string arg)
{
	object ob;
	mapping quest;
	string msg;
	int i,j;

	if ((!mapp(quest = me->query_temp("quest")) || quest["type"] != "��") && !me->query_temp("ry/ry_job/��") )
	{		
		return notify_fail("������������Ҫ����˭�ɣ�\n");	
	}		

	if( me->is_busy())
		return notify_fail("����æ���أ���Ъ�����ɡ�\n");

	if( me->is_fighting())
		return notify_fail("�����ڴ���أ��Ȼ����˵�ɡ�\n");

	if( me->query_temp("yaoqing") )
		return notify_fail("�����ڼ��������˼��أ�\n");

	if( !arg || !objectp(ob=present(arg, environment(me))))
		return notify_fail("����û�������Ү��\n");

	if( !ob || ob == me)
		return notify_fail("��������Ķ��������\n");

	if( !living(ob) )
		return notify_fail("��Ҫ�ȵ����ѹ�����˵��\n");

	if( !wizardp(me) && wizardp(ob) )
		return notify_fail("��������ʦ�Է��������⣬������ chat Ч������á�\n");

	if( ob->is_fighting() || ob->is_busy())
		return notify_fail("û����"+ob->name() + "��æ����û�����㣡\n");

	if( ob->query_temp("songshan_job") == me || ob->query_temp("riyue_job") == me)
	{
		ob->set_leader(me);
		ob->reincarnate();
		message_vision("$N��������$nһ���ж���\n", ob, me);
		return notify_fail(ob->name() + "�Ѿ����������룬�㲻���ٷѾ�����\n");
	}
		

	if ((!mapp(quest = me->query_temp("quest")) || quest["id"] != ob->query("id")) && me->query_temp("ry/npc/id") != ob->query("id"))
		return notify_fail("������������Ҫ�������˰�1��\n");

	i = (int)me->query_skill("force") + (int)me->query_kar() * 5;
	j = (int)ob->query_skill("force") + (int)ob->query_kar() * 5;

	if(me->query("shen") < ob->query("shen")*2) i += 100;
	else if(ob->query("shen") < me->query("shen")*2) j += 100;
	else if(ob->query("shen") < me->query("shen")) i += 10;
	else j += 10;

	if(me->query("jing") < me->query("eff_jing")/2
	|| me->query("jingli") < me->query("eff_jingli")/2)
		return notify_fail("�㾫��������Ϣһ�°ɣ�\n");

	me->set_temp("last_damage_from", "������");
	me->receive_damage("jing", me->query("jing")/3, me);
	me->receive_damage("jingli", me->query("jingli")/3, me);
    
	if (!me->query_temp("ry/ry_job")) {
	switch(random(4)){
		case 0: msg = CYN"\n$Nһ���Ĺ�������$n��ȭ�Ϲ���������ɽ��������֮����ǰ����"+RANK_D->query_respect(ob)+"��ɽ������\n"NOR;break;
		case 1: msg = CYN"\n$N����$n����һ������"+me->name()+"��"+RANK_D->query_respect(ob)+"�밲�ˣ�����ɽ������������"+RANK_D->query_respect(ob)+"��ɽ������\n"NOR;break;
		case 2: msg = CYN"\n$N���Ц�ݣ���$n��������ɽ��������֮����ǰ������ǰ����ɽ����������"+RANK_D->query_respect(ob)+"����������������һ�ý��棬��Ȼ�����鴫��\n"NOR;break;
		case 3: msg = CYN"\n$N��$n�Ϲ�������ɽ��������ǲ"+RANK_D->query_self(me)+"ǰ������"+RANK_D->query_respect(ob)+"��ɽ������˳��һ�����֮�顣\n"NOR;break;
	 }
	}
	
	else {
		switch(random(4)){
		case 0: msg = CYN"\n$Nһ���Ĺ�������$n��ȭ�Ϲ��������·�����ʹ֮����ǰ����"+RANK_D->query_respect(ob)+"������\n"NOR;break;
		case 1: msg = CYN"\n$N����$n����һ������"+me->name()+"��"+RANK_D->query_respect(ob)+"�밲�ˣ�������ʹ֮����"+RANK_D->query_respect(ob)+"��ɽ������\n"NOR;break;
		case 2: msg = CYN"\n$N���Ц�ݣ���$n����������ʹ֮����ǰ������ǰ����ɽ����������"+RANK_D->query_respect(ob)+"����������������һ�ý��棬��Ȼ�����鴫��\n"NOR;break;
		case 3: msg = CYN"\n$N��$n�Ϲ���������ʹǲ"+RANK_D->query_self(me)+"ǰ������"+RANK_D->query_respect(ob)+"��ɽ������˳��һ�����֮�顣\n"NOR;break;		
	}
	}

	if(ob->is_killing(me->query("id"))){
		ob->remove_all_enemy();
		msg += "\n$n���´�����$Nһ�ۣ��������һԾ������սȦ�����ˡ�\n";
	}

	message_vision(msg, me, ob);
	me->set_temp("yaoqing", 1);
	//npc�����ƶ�
	ob->delete("chat_chance");
    ob->delete("chat_msg");
	me->start_busy(2);
	call_out( "compelete_yaoqing", 3, me,ob, i, j);

	return 1;
}


private void compelete_yaoqing(object me, object ob, int i, int j)
{
	object where;

	if (!me) return;
	where = environment(me);
	me->delete_temp("yaoqing");

	if (!living(me))
		return;
	if( !ob || environment(ob) != where ) {
		tell_object(me, "̫��ϧ�ˣ���Ҫ��������Ѿ����ˡ�\n");
		return;
	}

	if(ob->is_killing(me->query("id"))) ob->remove_killer(me);

	if( living(ob) && (random(i+j) > j) ) {
		if (ob->query_temp("last_lost_to") == me && ob->query_temp("yaoqing") == me){
			if (!me->query_temp("ry/ry_job")) {
			message_vision(
				CYN"\n$N����һЦ����"
				+RANK_D->query_respect(me)
				+"�Ĺ����Ȼ�������������ſ�������͸��Ҵ�·�ɣ���\n"NOR, ob
			);
			ob->set_temp("songshan_job", me);
			ob->delete_temp("yaoqing");
			ob->set("chat_c", ob->query("chat_chance"));
			if (ob->query("location"))
				ob->set_temp("location", 1);
			ob->set("location", 1);
			ob->delete("chat_chance");
			ob->apply_condition("songshan_busy", 20+random(30));
			ob->set_leader(me);
			ob->reincarnate();
			message_vision("$N��������$nһ���ж���\n", ob, me);
			return;
			}
			else
			{
				message_vision(
				CYN"\n$N����һЦ����"
				+RANK_D->query_respect(me)
				+"�Ĺ����Ȼ������������ʹ����������ȥ�������͵�����\n"NOR, ob
			);
			ob->set_temp("riyue_job", me);				
			ob->delete_temp("yaoqing");
			ob->delete("chat_chance");
            ob->delete("chat_msg");
			message_vision("$N����һ�����Ѿ���ʧ������\n", ob, me);
			ob->move("/d/hmy/liangting");
			
			return;
			}			
			
		}
		//��Ϊǣ����job�Ѷȣ�������ʱ�������ˡ��ж����
		
		if( (ob->query("jing") * 100 / ob->query("max_jing")) < 90
		|| (ob->query("qi") * 100 / ob->query("max_qi")) < 90
		|| (ob->query("jingli") * 100 / ob->query("eff_jingli")) < 90
		|| (ob->query("neili") * 100 / ob->query("max_neili")) < 70 ) {
			message_vision("$N��ɫ�԰ף�ֻ����$nһ�ۡ����������岻�ʡ�\n", ob, me);
			
			ob->set("eff_jing",ob->query("max_jing"));
		    ob->set("jing",ob->query("max_jing"));
		    ob->set("eff_qi",ob->query("max_qi"));
		    ob->set("qi",ob->query("max_qi"));
			ob->set("neili",ob->query("max_neili"));
			message_vision("$N������һ��������������ɫ���󣬾������������\n", ob, me);
			//return;
		}
		
		
		message_vision(
			HIY"\n$Nɨ��$nһ�۵�����"+RANK_D->query_rude(me)
			+"����Ȼ������������м������ʵѧ������"
			+RANK_D->query_self_rude(ob)+"������������ɣ���\n"NOR, ob, me
		);
		ob->delete_temp("last_lost_to");
		ob->set_temp("yaoqing", me);
		ob->fight_ob(me);
		me->fight_ob(ob);
		return;
	}
	switch(random(4)){
		case 0:
			message_vision("$Nת��ͷ�����������¿���$nһ�飬��ת��ͷȥ�ˡ�\n", ob, me);
			break;
		case 1:
			message_vision("$N�����ɨ��$nһ�ۣ�����¶����м�ı��顣\n", ob, me);
			break;
		case 2:
			message_vision(
				"$N�ٺ�һ����"+RANK_D->query_rude(me)+"�����붯"
				+RANK_D->query_self_rude(ob)+"���ɵû����ٹ��򰡡�\n", ob, me
			);
			break;
		case 3:
			message_vision(
				"$Nһ�����ͷ��ı��飺ȥ��ȥ��ȥ����������"
				+RANK_D->query_self_rude(ob)+"��\n", ob
			);
			break;
	}
	me->add_temp("ry/qing",1);//�������˴������Ա㽱��
	me->start_busy(3);
}

int help(object me)
{
write(@HELP
����ĳ�ˡ�

ָ���ʽ : qing <ĳ��>

HELP
    );
    return 1;
}
