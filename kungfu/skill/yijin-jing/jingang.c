// snowman 04/01/99
// Modified by snowman@SJ 28/09/2000
// Modified by olives@SJ 5/2/2001
// for exert jingang �İٶ����ֵ�bug
// By Spiderii��ǿЧ�����Ͼ������NB��force
// By Server Fix ���� Exert bug
#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      int skill;
	  skill=me->query_skill("yijin-jing",1);
	  if ( !me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á���ղ������񹦡���\n");
	
      if( (int)me->query_skill("yijin-jing", 1) < 199 )
                return notify_fail("����׽�ڹ���Ϊ�������޷�ʹ�á���ղ������񹦡���\n");

      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("�����ڹ��С���ղ������񹦡���\n");

      if( (int)me->query_con() < 40 )
                return notify_fail("��ĸ���̫�ͣ������޷�ʹ�á���ղ������񹦡���\n");
 
      if( (int)me->query("neili") < 1000 )
                return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á���ղ������񹦡���\n");   
    
      if( (int)me->query("max_neili") < 3800 )
                return notify_fail("���������Ϊ��ô�����ʹ�á���ղ������񹦡���\n");   
       if( me->query_temp("jingang/fanzhen"))
                return notify_fail("���������á���ղ������񹦡���\n");
                                                                                 
      if( me->query_temp("fanzhen"))
                return notify_fail("���������á���ղ������񹦡���\n");
       
      message_vision(HIY"\n$NͻȻ����һ������Ŀ¶�ȹ⣬���΢Ц��������ת����ʹȫ�����±����������ǡ���ղ������񹦡���\n\n" NOR, me);
      if (me->query_skill("yijin-jing",1)<450)
      {
		  me->start_busy(random(1));//ԭ����1
      }
      me->set_temp("fanzhen", me->query_skill("yijin-jing", 1)/2); 
      me->set_temp("no_skill_hit_ob", 1);
	 // me->set_temp("jingang/fanzhen");
	  me->set_temp("jingang/fanzhen",1);
      me->set_temp("yjj/jingang",skill);
	  
	  me->add_temp("apply/armor", skill/3);		
      me->add_temp("apply/parry", skill/2);
	  me->add_temp("apply/dodge", skill/2);
      me->add_temp("apply/attack", skill/5);
	  
	  if (me->query("yjj/powerup")=="pass"&& me->query_temp("yjj/powerup"))
	  {
		  message_vision(HBYEL+HIW"$N�׽��Ȼ��ɣ��ڻ��ͨ����ղ������񹦵Ĵ�������ʱ�ŵ������ֳ�����\n"NOR,me);
		  me->add_temp("apply/defense",me->query_skill("yijin-jing", 1)/2);
		  me->add_temp("apply/armor", me->query_skill("yijin-jing", 1)/3); 
		  me->add_temp("apply/dodge",me->query_skill("yijin-jing", 1)/2);
		  me->add_temp("apply/parry",me->query_skill("yijin-jing", 1)/2);
		  me->set_temp("yjj/poweruptemp",1);
	  }
      me->add("neili", -500);    
      call_out("remove_effect", 1, me, (int)me->query_skill("yijin-jing", 1)/20);
      if (me->query_skill("yijin-jing",1)<450)
      {
		  me->start_exert(2,"����ղ������񹦡�");
      }
      return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		if( !me) return;
		skill=me->query_temp("yjj/jingang");
        if( count < 1 )
	   {
				me->delete_temp("fanzhen");
                me->delete_temp("no_skill_hit_ob");
				me->delete_temp("jingang/fanzhen");
			  
			  me->add_temp("apply/armor", -skill/3);		
			  me->add_temp("apply/parry", -skill/2);
			  me->add_temp("apply/dodge", -skill/2);
			  me->add_temp("apply/attack", -skill/5);
			  
			  if (me->query_temp("yjj/poweruptemp"))
				{
				  me->add_temp("apply/defense",-me->query_skill("yijin-jing", 1)/2);
				  me->add_temp("apply/armor", -me->query_skill("yijin-jing", 1)/3); 

				  me->add_temp("apply/dodge",-me->query_skill("yijin-jing", 1)/2);
				  me->add_temp("apply/parry",-me->query_skill("yijin-jing", 1)/2);
				  me->delete_temp("yjj/poweruptemp");
		 		}
				message_vision(HIR"\n$N˫�ֺ�ʮ��ɢȥ��������ȫ�����µġ���ղ������񹦡���\n"NOR, me);    
				return;
		}
     
            call_out("remove_effect", 1, me,count -1);
			return;
}
string exert_name(){ return HIY"��ղ�����"NOR; }

int help(object me)
{
        write(HIY"\n�׽��֮����ղ����塹��"NOR"\n");
        write(@HELP
	��գ�����֮�⣬���ٽ�ǧ������ת�����������Բ��������Խ��֮�ᣬ��
	�����壻�Խ��֮�����������á���ղ�������Ϊ���ֵ�һ�����������
	�Ϊ����ʹ���塢���������ڣ�ѭ�򽥽�����֮�Ժ㣬���ܵ�����ħ��
	�������������⿪�׽���������ܣ����ղ������񹦽����״�ˡ�
    
	ָ�exert jingang

Ҫ��  
	�׽�ȼ� 200 ���ϣ�
	���� 40 ���ϣ�
	������� 3800 ���ϣ�
	���� 1000 ���ϡ�
HELP
        );
        return 1;
}
