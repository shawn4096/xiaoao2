// chan 
// 99.3.17  by emnil

#include <ansi.h>

inherit F_SSERVER;

void do_chan(object me, object target, object weapon, int times);

int perform(object me, object target)
{
	string *mapped,msg;
	mapping map;
	object weapon;
	int skill, time,exp,cs;

       if( !target ) target = offensive_target(me);


      weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "lingshe-bianfa")
          return notify_fail("������û�бޣ��޷�ʹ�á����߲�����\n");             
 	if( !target || !target->is_character()|| !me->is_fighting(target) )
		return notify_fail("�����߲���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if( (int)me->query_skill("lingshe-bianfa", 1) < 200 )
		return notify_fail("������߱޷�������죬����ʹ�á����߲���������\n");

	 if( (int)me->query_skill("whip", 1) < 200 )
		return notify_fail("������߱޷�������񣬲���ʹ�á����߲�����\n");
	 if( (int)me->query_skill("qusheshu", 1) < 100 )
		return notify_fail("����������ȼ�����������ʹ�á����߲�����\n");
	 if( (int)me->query_skill("force", 1) < 200 )
		return notify_fail("����ڹ�������񣬲���ʹ�á����߲�����\n");
	 if( me->query_skill_mapped("force")!="dulong-dafa" )
		return notify_fail("�㼤�����ڹ��Ƕ����󷨣�����ʹ�á����߲�����\n");

	 if( (int)me->query_skill("dodge", 1) < 200 )
		return notify_fail("��Ļ�����������񣬲���ʹ�á����߲�����\n");

	if( (int)me->query("neili")<800)
		return notify_fail("����������̫��������ʹ�ù��߲���\n");
	if( (int)me->query("jingli")<500)
		return notify_fail("�����ھ���̫��������ʹ�ù��߲���\n");
    if(me->query_temp("lingshe/chan"))
            return notify_fail("����������ʹ�á����߲�����\n");
    if(me->query("gender")!="Ů��")
            return notify_fail("���Ů�ԣ��޷�ʹ�á����߲�����\n");
	me->add("neili", -150);
	
	msg = HIY+"\n$N"+HIY+"ͻȻ�Ի�����˦�����е�"+weapon->query("name")+HIY+"����ͼ��ס$n�Ĳ��ӣ�\n"NOR;
	
	exp=random(me->query("combat_exp"));
	cs=me->query_temp("chanfail",1);
	
	if ( exp > target->query("combat_exp")/2
		|| random(me->query_skill("whip",1))>target->query_skill("dodge",1)/3)
	{
		me->delete_temp("chanfail");
		msg +=HIR+"$nһ��û���񣬱�"+weapon->query("name")+HIR+"�������ţ����е��ٶ�����������\n"NOR;
		//me->start_busy(1);
		target->add_busy(3+random(2));
        
		me->set_temp("lingshe/chan",1);

		//weapon->unequip();
	/*	if(!objectp(find_object("/d/sld/md1")))
    		{
        		load_object("/d/sld/md1");   
    		}
		//weapon->move(__DIR__"emptyroom");
		weapon->move("/d/sld/npc/xjjl");
	*/
		time = me->query_skill("whip",1)/40 +1;	
		me->start_call_out( (: call_other, __FILE__, "do_chan", me, target , weapon, time:), 1);
	}
	else {
		msg += CYN+"����$n"+CYN+"������$N"+CYN+"����ͼ�����˹�ȥ��\n"NOR;
		me->start_busy(1);
		cs++;
		me->set_temp("chanfail",cs);
	}

	message_vision(msg,me,target);

	return 1;
}

void do_chan(object me, object target, object weapon, int times)
{
	int force;

	if(!objectp(me))
	{
		if(objectp(target) && !target->is_ghost())
		{
			if(objectp(weapon))
			{
				weapon-> move(environment(target));
				message("vision",HIY+weapon->quest("name")+HIY"��ž����һ�������˵��ϡ�\n"NOR,environment(weapon));
			}
		}
		else if(objectp(weapon))
			destruct(weapon);
		
		return;
	}
	if( !living( me ) || me->is_ghost() ) 	{
        me->delete_temp("lingshe/chan");
		if(objectp(target) && !target->is_ghost())
		{
			if(objectp(weapon))
			{
				weapon-> move(environment(target));
				message("vision",HIY+weapon->quest("name")+HIY+"��ž����һ�������˵��ϡ�\n"NOR,environment(weapon));
			}
		}
		else if(objectp(weapon))
			destruct(weapon);
		return;
	}
	if(!objectp(target) || target->is_ghost())
	{
		me->delete_temp("lingshe/chan");
		if(objectp(weapon))
		{
			weapon->move(me);
			weapon->wield(me);
			tell_room(environment(weapon),HIY+weapon->query("name")+HIY+"�ص�"+me->query("name")+HIY+"�����С�\n"NOR);
		}
		return;
	}
	if(!objectp(weapon))
	{
		me->delete_temp("lingshe/chan");
		return;
	}
	if(!me->is_fighting(target)) {
		message_vision(HIY+weapon->query("name")+HIY+"�ص�"+"$N"+HIY+"�����С�\n"NOR,me,target);
		weapon->move(me);
		weapon->wield(me);
                me->delete_temp("lingshe/chan");
		return ;
	}

	if(times<=0) {
		message_vision(HIY+"\n$n"+HIY+"����һ�����������"+weapon->query("name")+HIY+"�ľ�����"
			+weapon->query("name")+HIY+"�ص�"+"$N"+HIY+"�����С�\n"NOR,me,target);
                me->delete_temp("lingshe/chan");
		weapon->move(me);
		weapon->wield(me);
		return ;
	}

	if (me->query_temp("weapon")) {
		message_vision(HIY+"\n$N"+HIY+"���ű������޷��ټ��о���"
			+weapon->query("name")+HIY+"�ص�"+"$N"+HIY+"�����С�\n"NOR,me,target);
		//weapon->move(me);
                me->delete_temp("lingshe/chan");
		return ;
	}
	
	target->add("jingli",- (me->query_skill("whip")/4));
	if ( target->query("jingli")<1 ) target->set("jingli",1);

	force=random(me->query_skill("force")*13/10);
	if(force  > random(target->query_skill("force",1)) ) {
		target->add_busy(2+random(2));
		message_vision( HIR"$n"+HIR+"���������������ϵ�"+weapon->query("name")
			+HIR+"Ū����æ���ң�û��ʱ������ˣ�\n"NOR,me,target);
		call_out("do_chan",3,me,target,weapon,times-1);
	}
	else
		call_out("do_chan",2,me,target,weapon,times-1);

}
string perform_name(){ return HIM"���߲�"NOR; }

int help(object me)
{
        write(HIC"\n���߱޷�"+HIM"�����߲���"NOR"\n");
        write(@HELP
	���߱޷����������������鰲ͨ����������������ϰ������
	һ������Ϊ���������ۣ�����һ����Ҳƾ����ʹ����ǰ�ж�
	����ѧ�����鶯Ϭ�������ն������Ҵ������趯֮�ʣ�����
	�������������߳����������ǳ�����������Ů���ӵ�������
	�������߲������Խ���֮�⾳���ƶԷ���ʹ֮�޷�������
	
	ָ�perform whip.chan

Ҫ��
	��ǰ����Ҫ�� 800 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�����޷�Ҫ�� 200 ���ϣ�
	���߱޷�Ҫ�� 200 ���ϣ�
	�����Ṧ�ȼ� 200 ���ϣ�
	�����󷨵ȼ� 200 ���ϣ�
	�������ȼ��� 100 ���ϣ�	
	�����޷�Ϊ���߱޷���
	�����м�Ϊ���߱޷���
	�����ڹ�������
	�ֱֳ�������
HELP
        );
        return 1;
}
