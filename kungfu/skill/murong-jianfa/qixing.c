// qixing.c for murong-jianfa
// by sohu

#include <ansi.h>
//int check_xu(object me);
void remove_effect(object me);
inherit F_SSERVER;
int perform(object me,object target)
{
   object weapon;
    int i=me->query_skill("murong-jianfa",1);
    //int d=me->query_skill("shenyuan-gong",1);
	int dz=me->query_skill("douzhuan-xingyi",1);
   
    if( !target ) target = offensive_target(me);
     
    if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��ת����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ�ý�ת���ǣ�\n");
    if( (int)me->query_skill("shenyuan-gong", 1) < 300 )
                return notify_fail("�����Ԫ����򲻵�������ʹ�ý�ת���ǣ�\n");
    if( (int)me->query_skill("murong-jianfa", 1) < 300 )
                return notify_fail("���Ľ�ݽ�����û�о���������ʹ�ý�ת���ǣ�\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("������û�н����޷�ʹ�ý�ת���ǣ�\n");
                
    if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("��ת���Ǳ��뼤����ת���ƣ������޷�ʹ�ý�ת���ǣ�\n");
    if((int)me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ����������ʹ�ý�ת���ǣ�\n");
    if((int)me->query("neili") < 1500 )
                return notify_fail("�������������㣬����ʹ�ý�ת���ǣ�\n");
    if((int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ������㣬����ʹ�ý�ת���ǣ�\n");
    if((int)me->query_temp("qixing"))
                return notify_fail("������ʹ�ý�ת���ǣ�\n");
    if((int)me->query_skill("sword", 1) < 300 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�ý�ת���ǡ�\n");
                
    message_vision(HIB"\n$N"HIB"Ĭ��"HIY"��ת����"HIB"ʹ��Ľ�ݽ���֮����"HIY"����ת���ǡ�"HIB"����������"+weapon->query("name")+HIB"�����������ǣ����Ž����Ѿ���$n"HIB"����ס��\n"NOR, me,target);
    message_vision(HIB"\n$N"HIB"˳�ű������ǵķ�λ��������������"+weapon->query("name")+HIB"����Խ��Խ�죬����������\n"NOR, me,target);
	if (me->query("mrqixing/super","pass"))
    {
	    message_vision(HIC"\n$N�Զ�ת�����Ѿ��ڻ��ͨ����Ȼ������ת��ֻ���߶�Ѥ�õ�"+HIG+"����"+HIB+"������$n��ǰ�������ֱ�Ϯ��$n���ߴ�ҪѨ��\n"NOR,me,target);
        me->receive_damage("neili", 1500);
        me->receive_damage("jingli", 350);
    
		me->add_temp("apply/attack", i/4);
        me->add_temp("apply/damage", i/4);    
        me->add_temp("apply/sword", i/4);
    //��һ��
	    me->add_temp("qixing1",1);
		if (me->is_fighting()&&objectp(target))
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
        me->delete_temp("qixing1");
        me->add_temp("qixing2",1);
	//�ڶ���
		if (me->is_fighting()&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3); 
        me->delete_temp("qixing2");
        me->add_temp("qixing3",1);
	//������
		if (me->is_fighting()&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
        me->delete_temp("qixing3");
        me->add_temp("qixing4",1);
	//���Ľ�
		if (me->is_fighting()&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        me->delete_temp("qixing4");
        me->add_temp("qixing5",1); 
	//���彣
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->delete_temp("qixing5");
        me->add_temp("qixing6",1); 
	//������
		if (me->is_fighting()&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
        me->delete_temp("qixing6");
	//���߽�
        me->add_temp("qixing7",1);    
		if (me->is_fighting()&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("apply/attack", -i/4);
        me->add_temp("apply/damage", -i/4);        
        me->add_temp("apply/sword", -i/4);  

        me->delete_temp("qixing7"); 
		me->delete_temp("qixing1");
        message_vision(WHT"\n$N��ת����ʩչ��ϣ������չ����ս�ͦ�����У���Ľ�ݵ�������Ȼ��\n"NOR,me); 
//        call_out("check_xu", 6, me);
		me->start_perform(6,"��ת����");
      //  me->start_busy(3);    
        return 1;

    }
	else {
		me->set_temp("qixing", 1+(int)i/50);
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
		me->add_temp("apply/attack", i/5);
		me->add_temp("apply/damage", i/5);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		me->add_temp("apply/attack", -i/5);
		me->add_temp("apply/damage", -i/5);  
		call_out("check_fight", 1, me, (int)1+i/30);
		me->start_perform(3,"��ת����");
		return 1;
	}
}

void remove_effect(object me)
{
    if(!me) return;
    me->delete_temp("qixing");
    if(!living(me)) return;
    
	if(me->query("qixingquest")) return;
    
	message_vision(RED"\n$N����û�����׶�ת���Ƶ����հ��أ���С�Ĵ�̤���ǣ���ʱѪ����ӿ��ͷ��Ŀѣ��\n"NOR, me);
    me->receive_damage("qi", 100);
    me->receive_damage("jing", 50);
    if(!me->is_busy()) me->start_busy(1+random(2));
	return;
}
//û����ǰ��������
void check_fight(object me, int i)
{
    object weapon, target;
	

    if (!me ) return;
    
    target = offensive_target(me);
     
    if( !living(me) 
        || !target 
        || !me->is_fighting(target) 
        || !living(target)
        || environment(target)!=environment(me)
        || !me->query_temp("qixing"))
                return remove_effect(me);

    else if(me->query_skill_mapped("sword") != "murong-jianfa"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á���ת���ǡ�������\n");
                return remove_effect(me);
                }
    else if(me->query_skill_mapped("force") != "shenyuan-gong"){
                tell_object(me, HIR"����ʱ�Ļ��ڹ�����������ʹ�á���ת���ǡ�������\n");
                return remove_effect(me);
                }
    else if(me->query_skill_mapped("parry") != "douzhuan-xingyi"){
                tell_object(me, HIR"����ʱ�Ļ��мܣ���������ʹ�á���ת���ǡ�������\n");
                return remove_effect(me);
                }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á���ת���ǡ�������\n");
                return remove_effect(me);
                }
    else{
          
		   me->receive_damage("neili", 200);
           me->receive_damage("jingli", 100);
           me->add_temp("apply/attack", me->query_skill("murong-jianfa",1)/3);
           me->add_temp("apply/damage", me->query_skill("shenyuan-gong",1)/5);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
           me->add_temp("apply/attack", -me->query_skill("murong-jianfa",1)/3);
           me->add_temp("apply/damage", -me->query_skill("shenyuan-gong",1)/5);  
           i--;
           call_out("check_fight", 1, me, i);
    }
}

string perform_name(){ return HIB"��ת����"NOR; }
int help(object me)
{
        write(HIG"\nĽ�ݽ���֮"+HIB"����ת���ǡ�"NOR"\n\n");
        write(@HELP
	Ľ�ݽ���������Ľ���似�еľ�����ʽ���Ǻ��ĵ��Ӳ���
	�佣���ص��Ǽ��ݲ������ں����½������������ֱ����
	�ã����ڲ�ͬ����������Ľ�ݼҴ��ڹ�֧�֣���Ϊ���ָ�
	��һ��¥�����м���ָ�������⿪��ת���ƾ����似����
	������һ��¥��

ָ�perform sword.qixing

Ҫ��
	��ǰ�������� 1500 ���ϣ�
	����������� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	Ľ�ݽ����ȼ� 300 ���ϣ�
	��Ԫ�����ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	��������ΪĽ�ݽ�����
	���뼤���м�Ϊ��ת���ƣ�
	�����ڹ�Ϊ��Ԫ����
	�ֳֽ���������
HELP
        );
        return 1;
}