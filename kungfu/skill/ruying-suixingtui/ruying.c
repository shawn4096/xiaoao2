// ruying ��Ӱ����
// by snowman@SJ 
// Modify by snowman@SJ 22/02/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	mapping pre;
	string *skill, a, b;
	int i;

	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("����Ӱ���Ρ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á���Ӱ���Ρ�ʱ˫�ֱ�����ţ�\n");
	if( me->query_temp("fumo"))
		 return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");
	if( (int)me->query_skill("ruying-suixingtui", 1) < 350 )
		return notify_fail("�����Ӱ�����Ȳ�����죬����ʹ�á���Ӱ���Ρ���\n");

	if( (int)me->query_skill("yijin-jing", 1) < 350 )
		return notify_fail("����׽�ȼ�����������ʹ�á���Ӱ���Ρ���\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á���Ӱ���Ρ����й�����\n");  
			
	if( (int)me->query_dex() < 60 )
		return notify_fail("���������ǿ������ʹ�á���Ӱ���Ρ���\n");

	if (me->query_skill_prepared("leg") != "ruying-suixingtui"
	|| me->query_skill_mapped("leg") != "ruying-suixingtui")
		return notify_fail("�������޷�ʹ�á���Ӱ���Ρ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("������������Ϊ̫��������ʹ�á���Ӱ���Ρ���\n");
	if( (int)me->query("neili") < 1500 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á���Ӱ���Ρ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á���Ӱ���Ρ���\n");


	message_vision(YEL"\n$N����һ�����������ھ���˲ʱ�������������˫�Ż���һƬ��Ӱ���������ף���$n��ȥ��\n" NOR,me, target);
	
	pre = me->query_skill_prepare();
	skill = keys(pre);     
	
	for (i=0; i<sizeof(skill); i++){
		if(skill[i]=="leg") continue; 
		a = skill[i];
		b = pre[skill[i]];
		me->prepare_skill(a);
	}

	i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/2;
 
        me->add_temp("apply/attack", i);
        me->add_temp("apply/strength", i/15);
        me->add_temp("apply/leg",i/3);
        me->add_temp("apply/damage", i/4);
        me->add_temp("apply/dodge", i);


	me->set_temp("sl_rysxt", 5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
	me->add("neili", -80);
	if(me->is_fighting(target)){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
		me->add("neili", -80);
	}
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 250){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
		me->add("neili", -80);
	}
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 350){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add("neili", -100);
	}
	
	me->add_temp("apply/attack",- i);
    me->add_temp("apply/strength",- i/15);
    me->add_temp("apply/leg",- i/3);
    me->add_temp("apply/damage",- i/4);
    me->add_temp("apply/dodge", - i);
	
	// 5th kick is type_super. cannot be done in normal fight.
	//if(me->is_fighting(target) && me->is_killing(target->query("id"))
	  // && random(me->query_skill("ruying-suixingtui", 1)) >= 400) {
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 500)
	{
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add("neili", -150);
	}
	if (me->query("quest/sl/rysxt/pass")
		&&objectp(target)
		&&me->is_fighting()
		&&me->query_skill("ruying-suixingtui",1)>550)
	{
		message_vision(HBRED+HIY"$N˫�������߳����ó�һƬ��Ӱ����ǰ��������Ĺ���˲���ͷţ���������!\n���������һƬ��Ӱ�������Σ�������Ӱ�������ռ�����---"NOR+HIC"����Ӱ�š���"NOR,me,target);
		me->add_temp("apply/leg",i/4);
		me->add_temp("apply/damage",i/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add_temp("apply/leg",- i/4);
		me->add_temp("apply/damage",- i/4);
	}
	message_vision(YEL "\n$N��������ʹ�꣬ȫ��һת���������ڵ��ϣ��������С�\n" NOR,me);
	me->prepare_skill(a,b);
	me->reset_action();

   

	me->delete_temp("sl_rysxt");

	me->start_busy(2);           

    me->start_perform(4,"����Ӱ�����ȡ�");

	return 1;
}


string perform_name(){ return HIY"��Ӱ����"NOR; }
int help(object me)
{
        write(HIB"\n��Ӱ������֮����Ӱ���Ρ���"NOR"\n");
        write(@HELP
	��Ӱ����Ϊ������ʮ������֮һ���������־������ȷ��ļ��¡�
	���ü�ʵ���ȹ���ǿ�������������������У�˫�Ȳ�������
	�߳�������ַ���ʤ�������޿ɶ㣬�˵��������ǳ���������
	�����Ħ��һ��ʥɮ����͵ѧ������Ӱ����������С���๦ʩ
	չ��������Ȼ�����������׽������Ч���ã�������ʽ֮��
	���Լ�����֮�ۻ룬ȴ��ģ�µ����켫��,550�����ܺ�����
	��һ����Ӱ�š�
		
	ע�⣺����Ӱ�����ȡ��������Ĺ�Ч������������һ�б�һ
		�кݣ�����������ʽ�������������У�������硣���һ
		����Ҫ���ܻ�á�

Ҫ��  
	������� 5000 ���ϣ�      
	��ǰ���� 1500  ���ϣ�  
	��Ӱ�����ȵȼ� 350 ���ϣ�
	�׽�ȼ� 350 ���ϣ�
	�����ȷ�Ϊ��Ӱ�����ȣ�
	�����м�Ϊ��Ӱ�����ȣ�
	�����ޱ�����
	��Ч������С��60��
	�������ǧҶ�ֻ��������⹦Ч��
                
HELP
        );
        return 1;
}
