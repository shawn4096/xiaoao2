//updata by Jpei 2010 
//������Ч��������death_times��������

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIB"�����޹�"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i,j;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("�����޹�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!me->query("quest/gb/dgb/wugou/pass"))
		return notify_fail("��û�н���ʽ�Ͱ����ںϹ�ͨ���޷�ʹ�������޹���\n");
    if(me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("����ڹ����ǻ����������޷�ʹ�������޹���\n");
    if( (int)me->query_skill("huntian-qigong", 1) < 500 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�������޹���\n");
    if( (int)me->query_skill("dagou-bang", 1) < 500 ) 
                return notify_fail("��Ĵ򹷰�����δ���ɣ�����ʹ�������޹���\n");
    if((int)me->query_skill("stick", 1) < 500 )
                return notify_fail("��Ļ�������������죬������ʹ�������޹���\n");
    if((int)me->query_skill("bangjue", 1) < 200 )
                return notify_fail("��Ĵ򹷰���������죬������ʹ�������޹���\n");
    if((int)me->query_con(1) < 70 )
                return notify_fail("������岻��ǿ׳������ʹ�������޹���\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang"
        || me->query_skill_mapped("parry") != "dagou-bang")
                return notify_fail("������ʹ���������޹�ô��\n");
                
    if((int)me->query("max_neili") < 15000 )
                return notify_fail("���������Ϊ����������ʹ�������޹���\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("�������������㣬����ʹ�������޹���\n");

        message_vision(HIW"\n$N�����������һ·���򹷰�����ʹ�ñ仯�򷽣�������ȥ������ز�ã����������������裬������ʽ,����������\n",me);
        message_vision(HIG"�����Ǵ򹷰����ľ��С������޹���,��˵�����ֱ仯��һ��ʹ��,��������,����˷�ȫ�ǰ�Ӱ��\n",me);
        message_vision(HIG"��ʱ�����м�ʮ����ȮҲ��һ�������ˣ���ν�������޹������Ǵ��⣬����֮������ף�������ѧ�еľ���!\n"NOR,me);
        message_vision(HBRED"$N�ѵá������޹�������֮��Ҫ������������ˮ��ɲ�Ǽ�����İ�Ӱ����$n!\n"NOR,me,target);

    me->start_perform(2+random(2),"�������޹���");
    i = (int)me->query_skill("dagou-bang",1);
    j= me->query_skill("bangjue",1);
    // if(j>500) j = 500;

    me->add("neili", -500);
	me->add("jingli", -500);
        me->add_temp("apply/attack",  i/2);
        me->add_temp("apply/damage",  i/4);
	
	if (weapon->query("material")=="bamboo"
		||weapon->query("material")=="wood"
		|| weapon->query("id") == "yuzhu bang"
		|| weapon->query("material") == "paper" 
		|| weapon->query("weapon_prop/damage") < 20 )
	{
		if (!me->query_temp("dgb/zhubang")) 
		{
			message_vision(HBYEL+HIW"\n\n$N�Ѿ���ô򹷰����������ɡ��ľ�ּ�����е�"+weapon->query("name")+HBYEL+HIW"��$N������ע�£���������䣡\n"NOR,me);
			me->add_temp("apply/stick",  i/2);
			me->add_temp("apply/strength",  i /10);
			me->add_temp("apply/attack",  i/2);
			me->add_temp("apply/damage",  i/4);
			me->set_temp("dgb/zhubang",i);
		}
		
	}
		me->set_temp("dgb/wugou",6);


        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        

    if( j>200 && me->is_fighting(target)&& userp(target) ) 
	   target->add_busy(j/50);
   
        
 
      if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
	   	me->add_temp("apply/attack",  -i/2);
        me->add_temp("apply/damage",  -i/4);
	if (me->query_temp("dgb/zhubang"))
	{
        me->add_temp("apply/stick", - i/2 );
        me->add_temp("apply/strength",  - i /10 );
        me->add_temp("apply/attack",  -i/2 );
        me->add_temp("apply/damage",  -i/4);
		me->delete_temp("dgb/zhubang");
	}
    
	if (me->query("gender")=="Ů��") me->start_perform(5,"�������޹���");
	else me->start_perform(6,"�������޹���");
	
	me->delete_temp("dgb/wugou");
    me->start_busy(2);
    return 1;
}

int help(object me)
{
   write(HIB"\n�򹷰��������޹�����"NOR"\n");
   write(@HELP
	���й������䣬Ϊ�򹷰����ռ��ľ��У��佭����ʢ��ؤ��
	�����У�������Ϊ�ߣ���Ȼѧ��þ�������ֻ��������ʽ��
	�ѣ��������ҵ�ؤ���������ү���׿ڴ��ڸþ���������
	�������޹���֮�����ʹ��������������������޹���
	�Ǵ򹷰������ռ��似����һ��ʹ������������˷��ǰ���
	�������������м�ʮ����ȮҲһ������ˣ���ν�������޹���
	���Ǵ��壬����֮���������ѧ���衣
	
	ָ�perform stick.wugou

Ҫ��
	����������� 15000 ���ϣ�
	��ǰ�������� 2000 ���ϣ�
	�򹷰����ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	���������Ҫ 70  ���ϣ�
	�򹷰����ȼ� 200 ���ϣ�
	�����м�Ϊ�򹷰���
HELP
   );
   return 1;
}
