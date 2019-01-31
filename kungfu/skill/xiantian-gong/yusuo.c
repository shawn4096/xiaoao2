// yusuo.c
// 
//���������
//by sohu
#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return MAG"���������ʮ�ľ�"NOR; }


int exert(object me, object target)
{
	int skill,i,j;
	i=(int)me->query("yusuo/degree");
	skill = me->query_skill("jinguan-yusuojue",1);
	if (i>9) i=9;
	
	if( me->query("neili") < 100 )
		return notify_fail("�������������\n");

	if( me->query_skill("xiantian-gong", 1) < 350 )
		return notify_fail("������칦�ȼ�������\n");
	if( me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ�������\n");
	if( me->query_skill("jinguan-yusuojue", 1) < 350 )
		return notify_fail("��Ľ���������ȼ�������\n");
	
	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("����ڹ����ԡ�\n");
	
	if( me->query("jingli") <2000)
		return notify_fail("��ľ������㣬�޷�ʩչ��������������ˡ�\n");
	if( me->query("neili") <2500)
		return notify_fail("����������㣬�޷�ʩչ��������������ˡ�\n");
	if (skill<i*100)
	{
		return notify_fail("��Ľ�����������й����㣬�޷�ʩչ��������������ˡ�\n");
	}
	if( me->query_temp("xtg/yusuo") )
		return notify_fail("���Ѿ����ˡ�������������ˡ�\n");
	
	if((int)me->query("yusuo/degree")<3 )
		return notify_fail("����δ�������������ľ�������޷�ʩչ�����������\n");
	
	
	me->receive_damage("neili", -300);	
	j=12-i;	
	
	if (CHAR_D->addbuff(me,"damage",to_int(skill/j),to_int(skill/30),"xtg/yusuo",HIR"$N���칦��ת����["+HIW+"���������ʮ�ľ�"+HIR+"]�����չ���"))
	{
		me->add("neili",-200*i);
	    me->add("jingli",-150*i);
		if (i<6)
		message_vision(HIR"$N"HIR"����"HIC"���������ʮ�ľ�"HIR"����"HIY+chinese_number(i)+HIR"�ؾ���Ĺ���ʩչ��������������֮��������Ͷ�������������Хһ�㡣\n" NOR, me);
	else message_vision(HBWHT+HIR"$N"HBWHT+HIR"����"NOR+HIC"���������ʮ�ľ�"HBWHT+HIR"����"HIY+chinese_number(i)+HIR"�ؾ���Ĺ���ʩչ��������������֮��������Ͷ�������������Хһ�㡣\n" NOR, me);
		
	}
	
	
	//me->add_temp("apply/damage", skill/j);

	
	//me->set_temp("xtg/yusuo", j ); 
	//me->add("neili",-200*i);
	//me->add("jingli",-150*i);
		
	//call_out("remove_effect",1, me, (int)skill/30);
	

	return 1;
}

void remove_effect(object me,int count)
{
        int skill,j;
        if(!me)  return;
		skill = me->query_skill("jinguan-yusuojue",1);

		j= me->query_temp("xtg/yusuo"); 

		if (!me->is_fighting()
			&&count--<0)
        {
		//	me->add_temp("apply/attack", -skill/8);
			me->add_temp("apply/damage", -skill/j);
			me->delete_temp("xtg/yusuo");

			message_vision(HIR"$N���칦��ת����["+HIW+"���������ʮ�ľ�"+HIR+"]�����չ���\n" NOR, me);

			return;
        }
		call_out("remove_effect",1,me,count--);
		return;
}

int help(object me)
{
	write(HIC"\n���칦֮"MAG"�����������ʮ�ľ�����"NOR"\n\n");
        write(@HELP
	���칦��ȫ�����������Ϊ��Ҫ���ڹ��ķ����޵�
	����磬�ɷɻ�ժҶ���������Ρ����ڵ����ؾ�
	�磬�޷�ʩչ�����������

	���������ʮ�ľ���ȫ�����Ҫ���ķ��������칦
	����Ҫ�ķ��������˾������к��˺�����������
	�������ںͽ����߹�һ���ս÷�����ʱ�����
	˵�伸�仰���̺���ʮ�ľ��Ĺ�������÷���硣
		
	����������ܹ��о��ؾ��磬���ʦ��ָ�����
	��һ�㾳�磬Ȼ�����������бչ�������ֱ�����
	���磬����Խ�ߣ���������Խ�󡣽������������
	�칦����������أ��Ǽ�Ϊ��Ҫ�ĸ���ѡ��м�
	����������ͽ�������������

	ָ�exert yusuo

Ҫ��
	��ǰ��������  300  ���ϣ�
	��ǰ��������  500  ���ϣ�
	�����ڹ��ȼ�  350  ����,
	���칦���ȼ�  350  ����,
	���������    350  ����
	�����ڹ����칦;
HELP
        );
        return 1;
}
