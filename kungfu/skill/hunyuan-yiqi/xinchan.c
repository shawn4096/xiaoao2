// sohu@xojh
//xinchan.c
//����

#include <ansi.h>
void remove_effect(object me,int count);
string pic;
string *pictures=({
  HIY"������������������������۶�ʱ���ռ����̽Կգ���һ�п��"NOR,
  HIC"�����ӣ�ɫ����գ��ղ���ɫ��ɫ���ǿգ��ռ���ɫ��������ʶ�ิ����"NOR,
  HIR"�����ӣ�������࣬�������𣬲�����������������"NOR,
  HIB"��˵���������۶��䣬��˵��Ի�����н��С����޽��С�����ɮ���С���������ڭ"NOR,
  MAG"�ǹʿ�����ɫ����������ʶ�����۶��������⣬��ɫ����ζ���������۽���������ʶ��\n�������������������������������������������޿༯������������޵á�"NOR,
  HIW"�������ùʣ��������ʡ������������۶�ʣ����޹Ұ����޹Ұ��ʣ����пֲ���Զ��ߵ����룬��������"NOR,
  HIG"��֪���������۶࣬�Ǵ����䣬�Ǵ����䣬�������䣬���޵ȵ��䣬�ܳ�һ�п࣬��ʵ����"NOR
});

int exert(object me)
{    
      int skill;
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á�����������\n");
	
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 250 )
                return notify_fail("����׽�ڹ���Ϊ�������޷�ʹ�á�����������\n");
      if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("��Ļ����ڹ���Ϊ�������޷�ʹ�á�����������\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("�����ڹ��С�����������\n");

      if( (int)me->query_con() < 40 )
                return notify_fail("��ĺ������̫�ͣ������޷�ʹ�á�����������\n");
 
      if( (int)me->query("neili") < 600 )
                return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á�����������\n");   
    
      if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ�������������ʹ�á�����������\n");   
      if( me->query_temp("hyyq/xinchan"))
                return notify_fail("���������á�����������\n");
                                                                                 
      message_vision(HIR"\n$N���з�ţ������ӷ��������գ�������ϲ���ǣ�һ�ɾ����鲼�������ܿ����"HIG"����"HIR"���磡\n" NOR, me);
	  pic=pictures[random(sizeof(pictures))];
	  message_vision(pic+"\n",me);

    
      me->set_temp("hyyq/xinchan",skill);
	  
	  me->add_temp("apply/attack", skill/4);		
      me->add_temp("apply/damage", skill/6);
	  if (me->query("quest/sl/hyyq/xinchan/pass"))
	  {
		message_vision(HIC"�������е������������֣�����𴫣�ֱָ���ģ����Գɷ𣡡����գ����գ�����$N�����У��ɶ��������ɾ����ۣ�\n"NOR,me);
		me->add_temp("apply/intelligence", (int)me->query_skill("buddhism",1)/10);
	  }
      me->add("neili", -300);  
	  me->add("jingli", -200);  

      call_out("remove_effect", 1, me, (int)me->query_skill("hunyuan-yiqi", 1)/40);

      return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		if( !me||!me->query_temp("hyyq/xinchan")) return;
		skill=me->query_temp("hyyq/xinchan");
        if( count < 1
			||!me->is_fighting())
	   {
		  me->add_temp("apply/attack", -skill/4);		
		  me->add_temp("apply/damage", -skill/6);
		  if (me->query("quest/sl/hyyq/xinchan/pass"))
		  {
			me->add_temp("apply/intelligence", -(int)me->query_skill("buddhism",1)/10);
		  }

		  me->delete_temp("hyyq/xinchan");
		  message_vision(HIR"\n$NĬ���ţ������ͷ�����Ļ�Ԫһ����,����״̬�����\n"NOR, me);    
		  return;
		}     
        call_out("remove_effect", 1, me,count -1);
		return;
}
string exert_name(){ return HBGRN+HIW"����"NOR; }

int help(object me)
{
        write(HIY"\n��Ԫһ����֮����������"NOR"\n");
        write(@HELP
	���ֻ�Ԫһ�����������»����ķ������ۻ�Ԫһ����
	�ȿ���������������Ҳ����������ͷ�Ϲ���������
	�����Ȼ���籾�ŵ�һ���׽��������������
	��̥���׽�ķ���Ҳ�ǲ��׵��ڹ��ķ���
	������������ͥ���Զ��������������ǽ������뵽
	�似�У��������֣�����𴫣�ֱָ���ģ����Գɷ�
	�������������к��˺����ڹ��ķ������ܺ��������
	�������ԣ��ͷ���Ϊ�йء�

	ָ�exert xinchan

Ҫ��  
	��Ԫһ�����ȼ� 250  ���ϣ�
	�����ڹ��ĵȼ� 250  ���ϣ�
	������ǵ����� 40   ���ϣ�
	��ǰ���������� 600 ���ϣ�
	��ǰ�ľ������� 500  ���ϡ�

HELP
        );
        return 1;
}