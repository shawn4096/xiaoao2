// wudi.c 
// by fengyue

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HBRED+HIW"�޵д�"NOR;}

void remove_effect(object me, int amount);
void remove_effect2(object me, int amount);

int exert(object me)
{
        int i,j;
        string s;

        if((int)me->query_skill("dulong-dafa",1) < 350  )
                return notify_fail("��Ķ����󷨹����������޷�ʩ�á��޵С��󷨡�\n");
         if((int)me->query_skill("force",1) < 350  )
                return notify_fail("��Ļ����ڹ������������޷�ʩ�á��޵С��󷨡�\n");
		  if((int)me->query_skill("shenlong-yaoli",1) < 150  )
                return notify_fail("�������ҩ�����������޷�ʩ�á��޵С��󷨡�\n");
        if((int)me->query("max_neili") < 3500 )
                return notify_fail("�����������������޷�ʹ�á��޵С��󷨡�\n");
		if((int)me->query("neili") < 1000 )
                return notify_fail("��ĵ�ǰ�����������޷�ʹ�á��޵С��󷨡�\n");
        if((int)me->query("eff_qi") < me->query("max_qi")/10 )
            return notify_fail("���������˹��أ�����ʹ�á��޵С��󷨡�\n");

        if( me->query_temp("sld/wudi") && environment(me)->query("no_death"))
               return notify_fail("û��Ҫ�����ಫ�ɡ�\n");

        if( (int)me->query_temp("sld/wudi2") )
                return notify_fail("�㲻Ҫ���������Ѿ��������Ǳ����\n");

        if((int)me->query("neili") < 1000  )

			return notify_fail("��������������޷�ʹ�á��޵С��󷨡�\n");

        i = me->query_skill("dulong-dafa", 1);
      
 //�ж��޵�2    
	    if( me->query_temp("sld/wudi") 
			 && me->query("eff_qi") < me->query("max_qi")			 
			 && !me->query_temp("sld/wudi2") )
         {
			if( me->is_fighting() )
			{   
                s=RED"\n$N�����Ľе������������ͨ���ӣ��ڵ��������ٱ�����һ���٣��԰ٵ���\n"+
                "�������Ŀ��磬�����ķ����ҵ���ɱ�л��̣�������׼���Σ�����ʥְ��\n"+ 
                "�ҽ̵��ӻ��̶�����ͬ�����ã�����ͻȻ���һ����Ѫ���ƺ��Ѿ���������ʹ��\n\n"NOR;

           
                if (!me->query("quest/sld/dldf/pass") && !random(3))
                {
					me->add("max_neili", -1); // 1��max neili��Ϊ���۵õ��߹�����
                }
                          
                me->set("neili", me->query("max_neili")*2);
                me->set("jingli", me->query("eff_jingli")*2);
                me->set_temp("double_attack",1);
                me->add_temp("apply/attack", i/3);
                me->set_temp("sld/wudi2", i);
				me->reincarnate();

				//remove_call_out("remove_effect");
                //call_out("remove_effect",20, me);

                me->start_exert(1,"���޵С�");
                message_vision(s, me);
                return 1;
          }
		  else return notify_fail("����û��ս�����õ�����ôƴ��ô��\n");

        }
		//�޵�1
		else if (!me->query_temp("sld/wudi"))
		{
			  me->set_temp("sld/wudi", i); 
			  me->add("neili", - 200);
                s=HIR"\n$N�����е������������ͨ����ҽ�ս�޲�ʤ�����޲��ˣ��޼᲻�ݣ��޵в��ƣ�\n"+
                "�����������ң���֮زز������˫��ͻȻð��һ˿��⣬�ƺ�ͻȻ�����˹�����\n\n"NOR;
                 if (me->query("quest/sld/dldf/pass"))
                 {
					s+=HBRED+HIY"$Nҧ���Լ�����⣬��Ѫ�ɽ�������������һ�����򣬰�����$N��Χ�������󷨵Ĵ��������˷��ԡ�\n"NOR;
					me->add_temp("apply/damage",i/8);
					me->add_temp("apply/defense",i/6);					
					me->add_temp("apply/armor",i/6);
					me->set_temp("sld/wudi3",1);
                 }
				 //��ֹ��������
				if (j=me->add_temp("apply/attack"))
				{
					me->delete_temp("apply/attack");
                    me->delete_temp("apply/strength");		
				}
                 me->add_temp("apply/attack", i/3);
                 me->add_temp("apply/strength", i/15);				 
                                
				call_out("remove_effect",30, me);
                me->start_exert(1,"���޵С�");
                message_vision(s, me);
                return 1;			
		}               
       
		return notify_fail("�����ڲ���Ҫʹ�á��޵С��󷨡�\n");
}

void remove_effect(object me)
{
        int i,j;
        if(objectp(me) && me->query_temp("sld/wudi")) 
        {           
           i = me->query_temp("sld/wudi");
           me->add_temp("apply/strength", -i/15);
           me->add_temp("apply/attack", -i/3);		   
		   if (me->query("quest/sld/dldf/pass"))
           {
					me->add_temp("apply/damage",-i/8);
					me->add_temp("apply/defense",-i/6);					
					me->add_temp("apply/armor",-i/6);
            }
           me->delete_temp("sld/wudi");           
           message_vision(HIR"\n$N����������һ����ͻȻ����������\n"NOR,me);
		   
		   if (me->query_temp("sld/wudi2"))
		   {
			    j = me->query_temp("sld/wudi2");                  
                me->add_temp("apply/attack", -j/3);
                me->delete_temp("double_attack");
				me->delete_temp("sld/wudi");
                me->delete_temp("sld/wudi2");
				me->delete_temp("sld/wudi3");
                message_vision(RED"����$N������һ�ɣ���Ҳ֧�ֲ�ס�������ʱ����ή��̬֮��\n"NOR,me);
		   }
		   
        }
}


int help(object me)
{
        write(WHT"\n������֮"+HIR"���޵д󷨡�"WHT"��\n\n"NOR);
        write(@HELP
	�����������������ڹ����������ǿ�ɽ��ʦ
	������������ɶ����ķ����������������߶�
	�����ԣ�������ǿ����һ�档
	���޵д󷨡������������������ڹ��ķ���
	���ص�����ҩ��֪ʶ���ϣ��ڶ�ʱ���ڴ��
	�����Լ��Ĺ�������ԽսԽǿ��

	ʹ��ָ�yun wudi
		
Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ҫ�� 3500 ���ϣ�
	�����ڹ��ȼ� 350  ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	����ҩ��ȼ� 150 ���ϣ�
	�����ڹ�Ϊ�����󷨣�
ע�⣺
	1����û�н⿪�����󷨵����⣬���������
	ʹ���ߵ�����������⿪����󣬶����󷨽�
	�����޴�ķ�Ծ��
	2����Ч�����û������벻����Ч����������
	���г����ߣ������ͨ����ͬ���趨�ﵽ��ͬ
	��Ч��������ָ�����£�
	set ���� <����> 
	Ч���������߻��Զ��������ˣ��������ж�
	set ���� <����>
	Ч���������߻����Լ��ֵ����ֽ���������
	�����п�������ֵ�����һ���������߻����
	��������Ҫ����������	
HELP
        );
        return 1;
}

