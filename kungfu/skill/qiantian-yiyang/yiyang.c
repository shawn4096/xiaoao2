// yiyang.c һ����
// by sohu@xojh  2014

#include <ansi.h>

int exert(object me)
{
	int i;
	
	i = me->query_skill("qiantian-yiyang",1);

	/*
    if(me->query("class") == "bonze" )
	      return notify_fail("���Ѿ����ң����׼��书�Ѿ����ʺ����㣡\n");
	if ( me->query("family/master_name") != "һ�ƴ�ʦ" )
		return notify_fail("���һ�Ƶ��ӣ��޷��˽���Ǭ��һ����\n");
*/
	if (me->query_skill("qiantian-yiyang",1) < 300 )
		return notify_fail("���Ǭ��һ����������죬�޷���ʹ��һ��������\n");

	if( me->query_skill_mapped("force") != "qiantian-yiyang" )
		return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
/*
	if ( me->query_skill("yiyang-zhi", 1) < 300 )
		return notify_fail("���һ��ָ�ȼ��������޷���һ��������\n");

	if ( me->query_skill_mapped("finger") != "yiyang-zhi"
	|| me->query_skill_prepared("finger") != "yiyang-zhi") 
		return notify_fail("�������һ��ָʹ�á�һ��������\n");
*/
	if (me->query("max_neili") < 5000  )
		return notify_fail("����ھ���Ϊ������\n");

	if (me->query("neili") < 1000  )
		return notify_fail("�������������\n");
	
	if (me->query("jingli") < i  )
		return notify_fail("��ľ���������\n");

	if (me->query("max_jing") < 2000  )
		return notify_fail("������Ѫ���㡣\n");

	if (me->query("jing") < 1000  )
		return notify_fail("��ľ�Ѫ���㡣\n");

	if (me->query_temp("qtyy/yiyang"))
		return notify_fail("���Ѿ�ʹ�á�һ�������ˡ�\n");

	message_vision(HIY"\n$N�����������ɫ���䣬��ɫ���������,����������������ָ�����ƴ�����\n"NOR, me);

	

	me->add("neili", -i);
	me->add("jingli",-i);
	if (me->query("class") == "bonze")
		i=i/2;
	
    me->add_temp("apply/attack",i/8);
	me->add_temp("apply/damage",i/10);
	me->add_temp("apply/finger",i/10);
	
	if (me->query_skill("qiantian-yiyang",1)>450)
	{     
       me->add_temp("apply/attack",i/6);	  
	  if (me->query("yideng/ronghe")=="pass")
	  {
		  message_vision(HIC"\n$N�����򵽡����칦���İ�����Ǭ��һ�����˴��ںϣ�����������\n"NOR, me);
	      me->add_temp("apply/damage",i/5);
		  
	  } else 
		  me->add_temp("apply/damage",i/10);	
	}
   
	me->set_temp("qtyy/yiyang", i);
	
	if (me->query_skill("qiantian-yiyang",1)<450)
	{
	   if( me->is_fighting() ) 
		   me->start_busy(random(2));
	   me->start_exert(2, "һ����");
	}	
	call_out("remove_effect", 1, me, 3+me->query_skill("qiantian-yiyang", 1)/50);
	return 1;
}

void remove_effect(object me, int tick)
{
	int i;
	if(!me) return;
	i=me->query_temp("qtyy/yiyang");

	if( me->query_skill_mapped("force")!="qiantian-yiyang" 
		|| tick<0 ) 
	{
		tell_object(me, HIY"\n�㹦����ת��ֹ����һ��ָ��������������ڸо�֧�ֲ�ס���������³�һ��������\n" NOR);
		me->add_temp("apply/attack",-i/8);
	    me->add_temp("apply/damage",-i/10);
	    me->add_temp("apply/finger",-i/10);
        if (me->query_skill("qiantian-yiyang",1)>450)
	    {
		   me->add_temp("apply/attack",-i/6);
	       if (me->query("yideng/ronghe")=="pass")
		      me->add_temp("apply/damage",-i/5);
	       else
	          me->add_temp("apply/damage",-i/10);
		 }

		me->delete_temp("qtyy/yiyang");
		return;
	}
	call_out("remove_effect", 1, me, tick-1);
}

string exert_name(){ return HIY"һ����"NOR; }

int help(object me)
{
	write(HIY"\nǬ��һ����֮��һ��������"NOR"\n\n");
        write(@HELP
	һ�����Ǵ���Ǭ��һ���ش��������Ǻ��ĵ��Ӳ���
	���ʺϺ�һ��ָ��ʹ������Ϊ�ϵ�һ�ƴ�ʦ������
	����ͨ����������֮���칦�ľ�Ҫ������һ�ƴ�ʦ
	����һ��������ʹ����һ��¥�����һ�ƴ�ʦָ��
	�������칦������һ������������Ծ�����Ტ��
	ע�⣺���ҵ���ʹ�����������׼ҵ��ӵ�һ�롣	
    
ָ�exert yiyang
	
Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	������� 5000 ���ϣ�
	����� 2000 ���ϣ�
	Ǭ��һ���� 300 ���ϣ�
		
		
HELP
        );
        return 1;
}
