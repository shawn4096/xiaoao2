// Modified by action@SJ 2008/09/15

#include <ansi.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

string perform_name() {return HIR"ӥ"HIC"��"HIW"��"HIM"��"NOR;}
int perform(object me, object target)
{
        string msg;
        int i;
        
        if (!me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á�ӥ�����衹��\n");
        
	//	if( !target ) target = offensive_target(me);
	//	if (target!=me)
	//	{
		//	return notify_fail("��ֻ����ս�����Լ�ʹ�á�ӥ�����衹��\n");
	//	}
        if ((int)me->query_skill("xiantian-gong", 1) < 300)
                return notify_fail("������칦���������ʹ������ӥ�����衹��\n");  

        if ((int)me->query_skill("jinyan-gong", 1) < 300)
                return notify_fail("��Ľ��㹦���������ʹ������ӥ�����衹��\n");  

        if ((int)me->query_skill("dodge", 1) < 300)
                return notify_fail("��Ļ����Ṧ���������ʹ������ӥ�����衹��\n");  

        if ((int)me->query("jing", 1) < 500)
                return notify_fail("�����ھ�������\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("����������������\n");

        if (me->query_temp("jyg/yanwu"))
                return notify_fail("������ʹ�á�ӥ�����衹��\n");

        msg = HIW "�㳤Хһ��������Ȼ�ӿ죬����ӥ�����ա�����Ⱥ����裬�����ۻ����ң�ɷ�Ǻÿ���\n\n" NOR; 

        me->add("neili", -200 + random(100));
        me->recieve_damage("jingli", 50);
        
        
        i = me->query_skill("xiantian-gong", 1) / 5;

        me->add_temp("apply/dodge", i);
        if (me->query("quest/qz/jyg/shangtianti/pass"))
        {
			me->add_temp("apply/parry", i);
			me->add_temp("apply/dexerity", i/10);
			msg += HIY "�㽫������"HIR"�������ݡ�"HIY"�Ĺ���ʩչ���������������������Ĺ�����ʱ���ֳ�����������������ࡣ\n\n" NOR; 

        }
		
        me->set_temp("jyg/yanwu", i);
        
		tell_object(me,msg);
  
      //  remove_call_out("remove_effect");
        call_out("remove_effect", 1, me, (int)me->query_skill("dodge",1) / 10);
        return 1;
}

void remove_effect(object me,object target, int count)
{
	   int i;
	   if(!me || !me->query_temp("jyg/yanwu")) return;
	   i=me->query_temp("jyg/yanwu");
	   
	   if (!me->is_fighting()
		   ||count<0
		   ||me->query_skill_mapped("dodge")!="jinyan-gong")
	   {
         me->add_temp("apply/dodge", - i);
		 if (me->query("quest/qz/jyg/shangtianti/pass"))
         {
			 me->add_temp("apply/parry", - i);
			 me->add_temp("apply/dexerity", - i/10);
		 }
		 me->delete_temp("jyg/yanwu");
         tell_object(me, HIW "�����ν�ͣ������һ�������ջ��ˡ�ӥ�����衹�Ṧ������\n" NOR);
         return;
	   }
	   //�����ݾ���
	   
	   if (me->is_busy()
		   && me->query("neili")>1500
		   && me->query("env/���㹦")=="������"
		   && random(me->query_skill("jinyan-gong",1))>(me->query_skill("jinyan-gong",1)/2)
		   && me->query("quest/qz/jyg/shangtianti/pass"))
	   {
			if (!me->query("quest/qz/xtg/daojue/pass"))
				me->add("max_neili",-1-random(2));	
			tell_object(me, HIR "���ۼ�����Σ�������·���ȫ��������һ�ݣ�ʩչ���������ݡ��ľ�����\n" NOR);
			tell_object(me, HIY "˲��������Լ�æµ��״̬��\n" NOR);
			me->start_busy(-1);
			
			//me->clear_codition("no_perform");
			me->add("neili",-1000-random(500));
	   }
	   else if (me->query_condition("no_perform")
		   && me->query("neili")>1500
		   && me->query("env/���㹦")=="������"
		   && random(me->query_skill("jinyan-gong",1)>me->query_skill("force",1)/2)
		   && me->query("quest/qz/jyg/shangtianti/pass"))
	   {
			if (!me->query("quest/qz/xtg/daojue/pass"))
				me->add("max_neili",-1-random(2));	
			tell_object(me, HIM "���ۼ�����Σ�������·���ȫ��������һ�ݣ�ʩչ���������ݡ��ľ�����\n" NOR);
			tell_object(me, HIY "˲��������Լ��޷����еľ�����\n" NOR);
			//me->start_busy(-1);
			
			me->clear_codition("no_perform");
			me->add("neili",-1000-random(500));
	   }
       call_out("remove_effect", 2, me,count--);
       return;
                                     
}

int help(object me)
{
        write("\n���㹦֮"+HIC"��ӥ�����衹��"NOR"\n\n");
        write(@HELP
	���㹦��ȫ�����Ҫ���Ṧ���������������
	�������಻˵�������ڹ��������������棬��һ��
	���͵�������޵Ĺ�����
	���㹦Խ�����ڹ���Խ����������ֳ�����Ч��
	Խ�����ԣ�������������Ҫ���Ṧ�����������ݡ�
	���õ����������򣬿���Σ��֮�ʣ�����Է���Ϯ
	�ţ��ɹ�����һ����
	���ã�set ���㹦 ������(��Ҫ����)

	ָ�perform dodge.yanwu

Ҫ��
	��ǰ�������� 500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	���㹦���ȼ� 300 ���ϣ�
	���칦���ȼ� 300 ���ϣ�
	�����Ṧ�ȼ� 300 ���ϣ�
	�����ṦΪ���㹦��

HELP
        );
        return 1;
}


