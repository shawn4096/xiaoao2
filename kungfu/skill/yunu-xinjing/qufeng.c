// qufengshu.c  ������
// cre by sohu@xojh 2014/9
// ģ��С��Ů����ʹ��壬��job�й�

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
	object weapon;
	object ob,yfj;
	string msg;
	weapon=me->query_temp("weapon");
	
	if( !target ) target = offensive_target(me);

	if( !target
	|| !objectp(target)
	|| !living(target)
	||	!me->is_fighting(target)
	||	!target->is_character())
		return notify_fail("��Ҫ��ʹ��乥��˭��\n");
	
	if((int)me->query_skill("yunu-xinjing",1) < 200)
		return notify_fail("����Ů�ľ��Ĺ���������������ʹ���!\n");
	if(!me->query("quest/gm/ynxj/qufeng/pass") )
		return notify_fail("��ֻ����˵��ѵ������������,��ȴû��˿�����鲻����ʹ���!\n");
	if((int)me->query_skill("force",1) < 200)
		return notify_fail("��Ļ����ڹ���Ϊ����,������ʹ���!\n");

	if((int)me->query("neili") < 2000)
		return notify_fail("���������ڲ���, ������ʹ���! \n");
	if((int)me->query("neili") < 800)
		return notify_fail("�㾫�����ڲ���, ������ʹ���! \n");
	if(me->query_skill_mapped("force")!="yunu-xinjing")
		return notify_fail("�㼤�����ڹ�����,������ʹ���!\n");

	if(!present("yufeng jiang",me) && !me->query("quest/gumu/ynxj/pass"))
		return notify_fail("������û�д������,������ʹ���!\n");
	
	if (me->query_skill("qufengshu",1)<50)
		return notify_fail("�����������δ�������죬����ȥ��С��Ů��̰ɣ�\n");


	if( target->query_temp("ynxj/fengmi") )
		return notify_fail(target->name() + "�����Ѿ������˷��ۣ�\n");

	message_vision(HBYEL+HIW"$N��ת��Ů�ľ����������߷��£���彬����һ�������㣬������Ƣ��������ɢ����ȥ��\n"NOR,me);	
	
	
	if (random(me->query_dex(1))>target->query_dex(1)/2)
	{
		message_vision(HIG"$N���ᵯ��һ����ۣ���������ס������$n���ϡ�\n"NOR,me,target);
		target->set_temp("ynxj/fengmi",1);
		call_out("yufeng_come",1,me,target,environment(target));
	}
	else {
		message_vision(HIC"$n��Ц�������ڹ�����һ������Щ���۵�����\n"NOR,me,target);
		me->add_busy(1);
	}
	me->add("neili",600);
	me->add("jingli",200);
	//if (me->query_skill("yunu-xinjing",1)<450) 
	me->start_exert(4,"Ԧ����");
	
	return 1;
}

int yufeng_come(object me,object target,object env)
{
	int i,j;
	object yufeng,room;
	if (!me||!target) return 0;
	i=(int)me->query_skill("qufengshu",1)/50;
	
	//����Ӹ��жϣ��������ս���У�������Ŀ��ͷ���
if (!me->is_fighting() || !living(target) || environment(me) != env || environment(target) != env) 
{
	message_vision(HBYEL"����ʧȥ��Ŀ�꣬���׷�ɢȥ��\n"NOR,me);
	return 0;
}

  if(present( "yu feng", environment(me)))
	  
  return 0;
	
	message_vision(HBYEL"��Ȼ��Զ������һƬ�ܼ�������֮������Ȼ���˴��������,˲�佫$nΧ��������\n"NOR,me,target);
	
	target->apply_condition("bee_poison",1);	
	for (j=0;j<i;j++ )
	{
		room=environment(me);
		if (environment(me) == env && living(target))
		{
		   if (present("yufeng jiang",me) || me->query("quest/gumu/ynxj/pass")) 
		   {			   
		   yufeng=new("d/gumu/npc/bee3");			
		   yufeng->move(room);
		   yufeng->set_temp("ynxj/attackname",target->query("id"));
		   yufeng->set("owner",me->query("id"));
		   }
		   else return notify_fail("��ķ��������ˡ�\n");
			   
		}
		else
		{
			return notify_fail("ս���Ѿ�����,��ȺҲɢ�ˡ�\n");
		}
	}
	return 1;
}

string exert_name(){ return HIY"������"NOR; }

int help(object me)
{
   write(WHT"\n��Ů�ľ�֮��"HIY"������"WHT"����"NOR"\n");
   write(@HELP
	������ǹ�Ĺһ����С��Ů������һ�����ط���
	����������о綾�����Ҿ�С��Ůѵ���󣬸���
	�����Ұ�����ǰ���Χ�Ⱦ������ƣ���֮���м�
	Ϊ��Ч�����ֹ�ʦ֮ͽ����Ϊ������ɽ��С��Ů
	���ף��������ڶ�����֮ͽǰ����Ĺ��С��Ů��
	��������������ˡ�������Ů�ľ���һ�κ󣬿�
	��ƾ�軨���ǿ����ڹ���ʹ����䡣450����ȡ
	��busy
	
ָ�exert qufeng
  
Ҫ��
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 2000 ���ϣ�
	��ǰ����Ҫ�� 2000 ���ϣ�
	��Ů�ľ��ȼ� 200 ���ϣ�
	�������ȼ��� 200 ���ϣ�
	�����ڹ�Ϊ��Ů�ľ�,
	��������ۻ��ʽ�;	

HELP
   );
   return 1;
}
