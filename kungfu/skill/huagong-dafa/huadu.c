// huadu.c ����
// By Spiderii@ty����Ч��
#include <ansi.h>

inherit F_CLEAN_UP;
void remove_effect(object me,int count);

int exert(object me)
{      
    int skill;
    skill = me->query_skill("huagong-dafa",1);
    if( !me->is_fighting() && (int)me->query_skill("huagong-dafa",1)<350 )
       return notify_fail("��ֻ����ս����ʹ�á���������\n");

    if( (int)me->query_skill("huagong-dafa", 1) < 200 )
       return notify_fail("��Ļ�������Ϊ��������\n");

    if (me->query_skill_mapped("force") != "huagong-dafa")
       return notify_fail("�����ڹ��С���������\n");

    if( (int)me->query_skill("poison", 1) < 200 )
        return notify_fail("�����ڵĶ��ز������޷�ʹ�á���������\n"); 

    if( (int)me->query("max_neili") < 1500 )
        return notify_fail("���������Ϊ��ô�����ʹ�á���������\n");
    if( (int)me->query("neili") < 500 )
        return notify_fail("�������������\n");

    if( me->query_temp("hgdf_power"))
                return notify_fail("���Ѿ���ʹ�û��������ˡ�\n");

     message_vision(BLU"$N�����������ɶ����ڹ������󷨣��������̻��Ķ���������Ϊ��������ɢ����֫�ڡ�\n"NOR, me);
     if (me->query_skill("huagong-dafa",1)<450)
        me->start_busy(1);
	 else message_vision(BLU"ֻ��$N������������һ�㱡����ǳ��ɫ��������$N���ƶ�������������Ʈɢ��\n"NOR,me);
     
	 	 
	 me->add_temp("apply/strike", skill/4);
     me->add_temp("apply/attack", skill/4);
	 
	 if (me->query_skill("huagong-dafa")>349) {
	 
	 me->add_temp("apply/damage", skill/6);
	 }
	 //�⿪�������ںϺ����ʱ�	 
	 if (me->query("quest/hgdf/powerup"))
	 {
				 
	    me->add_temp("apply/strength", skill/15);
		me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/attack", skill/6);
		message_vision(HBBLU+HIW"$N������Բ�ڹ�ͨ��������ת������һ���������޵�����ɫ����������$N����\n"NOR, me);

	 }
	 me->add_temp("apply/armor_vs_force", me->query_skill("poison", 1)/3);
   
	 me->add("neili", -400);
      
	  me->set_temp("hgdf_power",skill);
	  me->set("hgdf_power",skill);//������ʱ�ģ������˳��Ͷ�ʧ���޷������� by renlai
     
	 call_out("remove_effect", 1, me, skill/3);
     
	 if (me->query_skill("huagong-dafa",1)<350)
         me->start_exert(1, "����"); 
      
     return 1;
}

void remove_effect(object me, int count)
{
       int skill;
	   if (!me) return;
	   skill=me->query("hgdf_power");
       if( count < 1)
	   {          
			me->add_temp("apply/strike", -skill/4);
			me->add_temp("apply/attack", -skill/4);

			if (me->query_skill("huagong-dafa")>349)
				me->add_temp("apply/damage", -skill/6);
	 	 
			if (me->query("quest/hgdf/powerup"))
			{
				me->add_temp("apply/strength", -skill/15);
				me->add_temp("apply/damage", -skill/6);
				me->add_temp("apply/attack", -skill/6);

			}
			me->delete("hgdf_power");
			me->delete_temp("hgdf_power");

			me->add_temp("apply/armor_vs_force", -me->query_skill("poison", 1)/3);
			message_vision(BLU"$N�˹�������ϣ����������ض����̻����ڡ�\n"NOR, me);
			return;
        }
	   if (me->query("quest/hgdf/powerup"))
	  {
		 if (me->query_condition("xx_poison"))
		  {
			  me->clear_condition("xx_poison");
			  message_vision(BLU"$N����һ�������������촽����ȻЦ���������޶��Ǵ�֮�ﰡ��\n���¹�����ת���������е����޾綾��Ϊ������\n"NOR,me);
			  if (me->query_condition("xx_poison")*100<me->query("max_neili")*2-1)
				me->add("neili",me->query_condition("xx_poison")*100);
			  else me->set("neili",me->query("max_neili")*2-1);
		  }
	  }
       call_out("remove_effect", 1 , me ,count -1);
}
string exert_name(){ return HBBLU+HIW"����"NOR; } 
int help(object me)
{
	write(BLU"\n�����󷨡���������"NOR"\n");
	write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	���������������������쳣���������������޲�̸��ɫ�䡣
	�⻯��һʽ���ǽ�ƽʱ���������ڵľ綾����������߻�����֫
	����Ϊ�������ս���У��𵽸����˵е����ã�350��С�ɣ�450
	���ٴη�Ծ�����ܻ����󷨵İ��غ󣬻�����ռ���Ծ��
	
	���⿪�����󷨵��ռ����ܣ���˹������������ͷţ��������
	����Ĺ����������С�ͬʱ�������Լ����е����޶���ת��Ϊ��
	��������Ч�����Ҷ����ڹ��˺���Ч������Ч��
	
	ע�⣺set ������ ɢ�� Ч����������������öԷ��ж�Ч��

	ָ�yun huadu

Ҫ��:
	������ 200 ����
	�����ȼ� 200 ����
	��ǰ���� 500 �㣻
	������� 1000 �㡣
HELP
);
return 1;
}
