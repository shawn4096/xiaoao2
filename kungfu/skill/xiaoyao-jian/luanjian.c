// luanjian.c ��ң����֮ �����磬Դ�Կ�ͷ��
// By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j,damage,count,skill;
		object weapon,tweapon;
		weapon=me->query_temp("weapon");
		//weapon2=present("sword",me);
		skill=me->query_skill("xiaoyao-jian",1);
        
	
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("���ҽ�����ֻ����ս����ʹ�á�\n");       
        if( !objectp(me->query_temp("weapon")) )
               return notify_fail("�����������������ʩչ���ҽ�������\n");
        if (!me->query("quest/mj/xyj/luanjian/pass"))
                return notify_fail("������˵�����ҽ���������δ�õ������Ĵ��ڣ�\n");
		if (!weapon||weapon->query("skill_type")!="sword")
				return notify_fail("����������ԣ�\n");
        if((int)me->query_skill("sword", 1) < 400 )
                return notify_fail("��Ļ�������̫�ͣ��޷�ʹ�á��ҽ�������\n");  
        if((int)me->query_skill("xiaoyao-jian", 1) < 400 )
                return notify_fail("�����ң����������죬����ʹ�����ҽ�������\n");
        if (me->query_skill_mapped("parry") != "xiaoyao-jian"
           && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("����мܲ��ԣ�������ʹ�á��ҽ���������\n");   
        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("��Ľ������ԣ�������ʹ�á��ҽ���������\n");   
	    if ( me->query("max_neili") < 3500 )
                return notify_fail("��������Ϊ̫ǳ���޷�ʹ�á��ҽ�������\n");                
        if( (int)me->query("neili") < 1000 )
                return notify_fail("�������������������ܷ������ҽ�������\n");   
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ������������ܷ������ҽ�������\n");       
        if( (int)me->query_con() < 65 )
                return notify_fail("�����ں�����ǲ��������ܷ������ҽ�������\n");       

        if((int)me->query_skill("force", 1) < 400 )
                return notify_fail("��Ļ����ڹ��ȼ�����������Ӧ�á��ҽ�������\n");       
    
        if (me->query_temp("xyj/luanjian"))
                return notify_fail("������ʩչ���ҽ�������\n");       


        message_vision(WHT"$Nˢ��һ����б�̶��������к���������������ػ��档$nһ�Ӳ�⣬$N�������أ���ʹ���У�����ûһ����ʹ�õ����˵ġ�\n"NOR,me, target);
        message_vision(WHT"$N����"+weapon->query("name")+WHT"���裬ʹ����"HIR"�ҽ���"WHT"���еġ������硱����������ӳ�գ�����������������Ҵܣ�\n"NOR,me,target);
		me->add("neili", -600);
	 	
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/10);
		me->add_temp("apply/sword",skill/6);
		me->set_temp("xyj/luanjian",skill);
		call_out("remove_effect",1,me,(int)skill/50);
		
		
        return 1;

}
void remove_effect(object me,int count)
{
	int skill;
	object weapon;
	if (!me) return;
	skill=me->query_temp("xyj/luanjian");
	weapon=me->query_temp("weapon");
	if (!me->is_fighting()
		||count<0
		||!weapon
		|| weapon->query("skill_style")!="sword"
		||me->query_skill_mapped("sword")!="xiaoyao-jian")
	{
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/10);
		me->add_temp("apply/sword",-skill/6);
		me->delete_temp("xyj/luanjian");
		//me->start_perform(5, "���ҽ�����");  
		message_vision(WHT"$N����ﵹ�����ʣ�ˢ��һ���������������˽��У�˫�ֻ���һ�\n"NOR,me);
		return;
	}
	call_out("remove_effect",1,me,count--);

}

string perform_name(){ return HIY"��"+HIC+"��"+WHT+"��"NOR; }
int help(object me)
{
        write(HIG"\n��ң����֮"+HIC"���ҽ�����"NOR"\n");
        write(@HELP
	�����������̹�����ʹ���뷶ң�ϳơ���ң���ɡ���һ���书���䲵�ӣ�
	��ߴ����Եļ�Ϊ����ң����������������һս�������������书��
	��������һ����ս�����书֮�����������ֵ����쾡�£���ƽ��һ
	��������ķ�ң����Ϊ̾����
	������ʹ���������Կ�ͷ�ӵ�����Ե��ɹţ������ں����޼�һս��
	���������Ӳ���������ʹ�����ҽ����������޼ɶ���Ϊ�����Ľ���
	�����˱���ħ�����׵Ľ�����
	���ҽ�����������ң���ɷ����ľ�����һ����ȫ�����ӡ������ֳֽ���
	������ʩչ���У�ƾ�����Ӳ���������
	
	ָ��;perform sword.luanjian

Ҫ��  
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ҫ�� 3500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ң�����ȼ� 400 ���ϣ�
	ʥ���񹦵ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	����������� 65  ����;
	��������Ϊ��ң������
	�����м�Ϊ��ң������Ǭ����Ų�ƣ�
	�����ڹ����ޡ�
HELP
        );
        return 1;
}