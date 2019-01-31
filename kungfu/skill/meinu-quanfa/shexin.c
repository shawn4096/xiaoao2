// shexin.c ����
// edit by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

void affectob(object ,object ,int ,int ,int);
void dohit(object,object);
string perform_name(){ return HIW"����"NOR; }
int perform(object me, object target)
{
	int affect,skill,hits;
	string msg;
	
	if(!me->is_fighting())
		return notify_fail("��û��ս�����أ�\n");

	if(!target) target = offensive_target(me);

	if( (skill=(int)me->query_skill("meinu-quanfa", 1)) < 200 )
		return notify_fail("�����Ůȭ�����������죬�޷�ʩչ�����ġ�������\n");
	if( me->query_skill("cuff", 1) < 200 )
		return notify_fail("��Ļ���ȭ�����������죬�޷�ʩչ�����ġ�������\n");
	if( me->query_skill("force", 1) < 200 )
		return notify_fail("��Ļ����ڹ����������죬�޷�ʩչ�����ġ�������\n");
	if( me->query_skill("yunu-xinjing", 1) < 200 )
		return notify_fail("�����Ů�ľ����������죬�޷�ʩչ�����ġ�������\n");

	if( me->query_skill_mapped("cuff") != "meinu-quanfa"
		||me->query_skill_prepared("cuff") != "meinu-quanfa"
		||me->query_skill_mapped("parry") != "meinu-quanfa")
		return notify_fail("��û�м�����Ůȭ������õ������ľ�����\n");
	
	if ( me->query_temp("weapon"))
		return notify_fail("���ֳ����������ʹ�á����ġ�������\n");

	if(me->query("gender")=="����")
		return notify_fail("�����������������ʩչ�����ġ�������\n");
	if(target->query("gender")=="����")
		return notify_fail("�Է������������������������ʩչ�����ġ�������\n");
	if(me->query_temp("mnq/shexin"))
		return notify_fail("�Է��Ѿ����ˡ����ġ�����\n");

    if(target->query("gender")==me->query("gender"))
		if (me->query_per(1)<target->query_per(1))
			return notify_fail("���ͬ�Զ��֣������ò����Է������ʩչ�����ġ�������\n");
	if(me->query("max_neili")<2500)
		return notify_fail("����������������޷�ʹ�á����ġ�������\n");
	if(me->query("neili")< 800 )
		return notify_fail("�㵱ǰ�����������޷�ʹ�á����ġ�������\n");
	if(me->query("jingli")< 500)
		return notify_fail("�㵱ǰ�����������޷�ʹ�á����ġ�������\n");
	affect=me->query_per()+random(me->query("per")/2);
    
	if (me->query("gender")=="����") affect=affect / 2;
	me->set_temp("mnq/shexin",1);
	if (   target->query_skill("buddhism") > (skill+random(affect))  
	    || target->query_skill("dacheng-fofa") > (skill+random(affect))
		|| target->query_skill("mizong-fofa") > (skill+random(affect))
	    || target->query_skill("taoism") > (skill+random(affect)) )
	{
		msg = HIY"\n$N��$n����һЦ���۹�֮����¶������֮�⣬��ʩչ�����ġ�������\n"+
			HIY"����$nƽ�����Ĺ����˵ã����˶���ͻȻ���һ������ʱ��$N����һ���亹��\n"NOR;
		message_vision(msg,me,target);
		me->start_busy(1);
	}
	else if (target->query_per()>=me->query_per())
	{
		msg = HIY"\n$N��Ȼ��$n����һЦ���۹��Ĵ�������������֮���ƺ����������ġ�\n"NOR; 
		message_vision(msg, me, target);
		message_vision(HIW"����$N��ɥ�ط�����$n���Լ�Ư���������ġ������޷�ʩչ��\n"NOR,me,target);
		me->start_busy(2);
	}
   else if (random(10)>5)
	{
		msg = HIM"\n$N��Ȼ��$n����һЦ���۹��Ĵ�������������֮���ƺ����������ģ�$n���ɵ�һ����\n"NOR; 
      
		message_vision(msg, me, target);

		if ( random(skill) > target->query_skill("force",1)/2 )
		{
			target->add_temp("apply/dexerity", -affect);
			hits = skill / 10;
			me->start_perform(4,"����");
			target->apply_condition("no_perform", 3);
			target->set_temp("shexin", 1);
            target->add_busy(3);
			me->add("jingli",-100);
			me->add("neili",-300);
			dohit(me,target);
			dohit(me,target);
			call_out("affectob",2, me, target, affect, hits,3);
		}
		else 
		{
			message_vision(CYN"\n����$n������ʶ��Σ�գ����һ���������ۻ����������$N���������ĵ����գ�\n"+
					"���$nֻ�����������У����޷�����$N���ĵ��۹��ˡ�\n"NOR, me, target);

            target->add_busy(2);

			me->add("neili",-100);
			target->add_temp("apply/dexerity", -affect);
			dohit(me,target);
			dohit(me,target);
			if (skill >= 250) dohit(me,target); //200�����Ծ
			target->add_temp("apply/dexerity", affect);
			
		//	me->delete_temp("muq/shexin");

			me->start_perform(4,"����");
		}
	}
	else
	{
		msg = HIY"\n$N��Ȼ��$n����һЦ����ʩչ�����ġ�������\n"+
			HIM"˭֪$n������û���ϵ���\n"NOR; 
		message_vision(msg, me, target);
		//me->delete_temp("muq/shexin");
		me->start_perform(5,"����");
	}
	me->delete_temp("mnq/shexin");

	return 1;
}

void affectob(object me,object target,int affect,int hits,int now)
{
	if( !me 
		|| !target 
		|| ( now > hits) 
		|| objectp(me->query_temp("weapon")) 
		|| target->is_ghost() 
		|| me->is_ghost()  
		|| !me->is_fighting(target) 
		|| me->query("neili") < 800 
		|| me->query_skill_prepared("cuff")!="meinu-quanfa"
		|| me->query_skill_prepared("parry")!="meinu-quanfa")
	{
		if( me ) message_vision(HIC"\n$N����ͻȻһ�٣��۹��ָֻ�ƽ����\n"NOR, me);
		me->delete_temp("muq/shexin");
		if( target && target->query_temp("shexin"))
			target->delete_temp("shexin");
		if ( target )  target->add_temp("apply/dexerity", affect);
			return;
	}

	if( now > (hits/2) && target->query_temp("shexin"))
		target->delete_temp("bujue_busy");

	dohit(me,target);
	dohit(me,target);
	me->start_perform(1,"����");
	call_out("affectob",2,me,target,affect,hits,now+1);
}

void dohit(object me,object target) 
{
	int neili,jiali;
	neili = me->query("neili");
	jiali = me->query("jiali");
	if (!userp(target))
	{  
	    message_vision(HIY"\n$N��üǳЦ���������ӣ���ǧ����������һ��,��$n���鷢��֮���������У�\n"NOR, me, target);
		me->add_temp("apply/attack",me->query_skill("meinu-quanfa",1)/2);
	    me->add_temp("apply/damage",me->query_skill("meinu-quanfa",1)/4);
		if (target->query("class")=="huanxi")
			   me->add_temp("apply/damage",me->query_skill("meinu-quanfa",1)/4);

		COMBAT_D->do_attack(me, target,0, 3);
		//me->set_temp("mnq",1);
		COMBAT_D->do_attack(me, target,0, 3);
		//me->delete_temp("mnq");
		COMBAT_D->do_attack(me, target,0, 3);
		me->add_temp("apply/attack",-me->query_skill("meinu-quanfa",1)/2);
	    me->add_temp("apply/damage",-me->query_skill("meinu-quanfa",1)/4);
		if (target->query("class")=="huanxi")
			   me->add_temp("apply/damage",-me->query_skill("meinu-quanfa",1)/4);
	}
	else COMBAT_D->do_attack(me, target,0, 3);
	if (me->query("neili")<neili && jiali>0) me->set("neili",neili-jiali/3);
}
int help(object me)
{
   write(WHT"\n��Ůȭ����"HBMAG"����"WHT"����"NOR"\n");
   write(@HELP
	��Ůȭ��֮���ľ���������������Ĺ�����澭����
	��Ůȭ���ص��������һ�����С��ڸճ���ʱ��ɢ��֮
	ս��������֮���ʤ���ڷ������˴���ͣ���Ϊ��ʱ��
	���档��Ҫ˼·����Դ�Ծ����澭���ƻ�󷨣��ô�
	������Ůȭ�󣬽����Ů���������Σ��������ж����
	ɱ�������ջ�����250��С�ɡ�
	ע�⣺ͬ�Լ���������ò����Է����ʧЧ�������޷�
	ʩչ���С�������������������ʿ����˷𷨡�ɮ
	��Ч����Щ�������޻�ϲ����Ч�������ӱ���

	perform cuff.shexin
	
Ҫ��
	������� 2500 ���ϣ�
	��ǰ���� 800 ���ϣ�
	��ǰ���� 500 ���ϣ�
	��Ůȭ���ȼ� 200 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	��Ů�ľ��ȼ� 200 ���ϣ�
	�����ұ�ȭ��Ϊ��Ůȭ����
	�����м�Ϊ��Ůȭ����
	Ů�������ƣ�����ƫ����
	
HELP
   );
   return 1;
}