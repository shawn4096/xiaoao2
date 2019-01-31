//liangyi.c ���������ǽ���������ѧ
//cre by sohu@xojh 2014
// Դ������������ǽ��뷴���ǵ��ںϡ�
// ���ǽ��� 

#include <ansi.h>
inherit F_SSERVER;
void finish();
void check_fight(object me, int count);

int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��"HIG"���ǽ���"NOR"��\n");
        weapon = me->query_temp("weapon");
        if( !me->query("quest/kl/lyj/liangyi/pass"))
                return notify_fail("��ֻ�����������ž������޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
		if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("parry") != "liangyi-jian"
            || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("������û�н����޷�ʹ��"HIG"���ǽ���"NOR"��\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 500 )
                return notify_fail("��������ǽ���������죬�޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("��Ļ�������������죬�޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("��������޼���������죬�޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
		if( me->query_temp("xtwj/qinjian") )
			return notify_fail("������ʹ���ٽ�˫��������ͬʱʹ�á����Ǿ�����\n");
		if( me->query_skill_mapped("force")!="xuantian-wuji")
                return notify_fail("�㼤�����ڹ��������޼������޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
         
		if ( (int)me->query("max_neili") <15000)
                return notify_fail("�����������������޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
        if ( (int)me->query("neili") < 1500)
                return notify_fail("��������������޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
        if ((int)me->query("jingli") < 1000)
                return notify_fail("��ľ����������޷�ʩչ��"HIG"���ǽ���"NOR"��\n");
		if ( me->query_temp("lyj/liangyi"))
                return notify_fail("������ʩչ"HIG"���ǽ���"NOR"��\n");
    
        me->add("neili", -random(1500));
        me->add("jingli", -200);
        
		message_vision(HIC"$N���е�"+weapon->query("name")+HIC"����һ�䣬��Ȼʩչ�������Ǻͷ����ǵ�Ҫ������ʱ���ƺ���ǰ��Ȼ��ͬ��\n"NOR,me, target);
 		message_vision(BLU"�������似�ɱ�ͬ���书���죬����ʽһ����ȴ��ϵ������޷죬����һ����į֮�˺���֪�����ϲ����\n"NOR,me, target);

		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/4);
		me->add_temp("apply/sword",i/4);
		me->add_temp("apply/parry",i/4);
		me->add_temp("apply/defense",i/4);

        me->set_temp("lyj/liangyi",i);
		call_out("check_fight",1,me,i/20);
		
		return 1; 
}

void check_fight(object me,int count)
{
    object weapon, target;

    if (!me ) return;
    
    target = offensive_target(me);
    
	if (!target) 
	{		
	  call_out("finish",1);
	  return;
	}
	
    if( !me->is_fighting(target) 
		|| count < 0
        || environment(target)!=environment(me)
        || !me->query_temp("lyj/liangyi")) {
              call_out("finish",1);
			  return;
	}
    else if(me->query_skill_mapped("sword") != "liangyi-jian"||me->query_skill_mapped("parry") != "liangyi-jian"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á����ǽ�����������\n");
                call_out("finish",1);
				return;
    }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á����ǽ�����������\n");
                call_out("finish",1);
				return;
    }
    else if ((int)me->query("neili") < 1500 ){
                tell_object(me, HIR"���������ã�ֻ�û����ջء����ǽ�������\n");
                call_out("finish",1);
				return;
    }				
    else if ((int)me->query("jingli") < 1000 ){
                tell_object(me, HIR"��������֧��ֻ�û����ջء����ǽ�������\n");
                call_out("finish",1);
				return;
    }
    count=count-1;
	call_out("check_fight",1, me, count);
	return; 
    
}

void finish()
{
       int i;
	   object me = this_player();
       if (!me||!me->query_temp("lyj/liangyi")) return;
     
	   i=me->query_skill("liangyi-jian",1);
	   
	   
	   me->add_temp("apply/attack",-i/4);
	   me->add_temp("apply/damage",-i/4);
	   me->add_temp("apply/sword",-i/4);  
	   me->add_temp("apply/parry",-i/4);
	   me->add_temp("apply/defense",-i/4);
       me->delete_temp("lyj/liangyi"); 
       message_vision(HIC"$N����һ�󼲹��������ĺ�����������һ���������ƻع���Ȼ��\n"NOR, me);
	   return;

}

string perform_name(){ return HIY"����"HIC"����"NOR; }
int help(object me)
{
write(HIW"\n���ǽ���֮"HIC"�����ǽ�������"NOR"\n\n");
write(@HELP
	���ǽ����ǽ������ǽ��ͷ����ǵ�����ʽ�����ںϺ�
	�����������Ĺ������������ں������ǽ��ľ�����ʽ
	�����������׾����ǻ����֡�
	ע�⣺���ܺ󷽿���ϰ����Ϊ�����Ǿ��кͷ����ǵ���
	���ϵ����ʣ����Բ��ܺ��ٽ�˫�����á�
	
	ָ�perform sword.liangyi

Ҫ��
	�������Ҫ�� 15000 �����ϣ�
	��ǰ����Ҫ�� 1500 �����ϣ�
	��ǰ����Ҫ�� 1000 �����ϣ�
	���ǽ����ȼ� 500 ���ϣ�
	�����޼��ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	��������Ϊ���ǽ�����
	�����м�Ϊ���ǽ�����
	�����ڹ�Ϊ�����޼�����
	���ý��������
HELP
	);
	return 1;
}






















/*
#include <ansi.h>
inherit F_SSERVER;
//int remove_effect(object me);
int perform(object me, string arg)
{
    object weapon, weapon1, target;
    int skill, skill1;
    string msg;
	skill = me->query_skill("liangyi-jian", 1);
    skill1 = target->query_skill("liangyi-jian", 1);

    if(!arg) return notify_fail("�����˭һ���赣�\n");
    if(!objectp(target = present(arg, environment(me))))
             return notify_fail("����û������ˡ�\n");

	if( !target->is_fighting() || !target->is_character() || !me->is_fighting())
                return notify_fail("���ֻ����ս����ʹ�á�\n");
    if(!living(target))
                return notify_fail(target->name()+"�Ѿ��޷�ս���ˡ�\n"); 
    if(target==me) return notify_fail("���Լ���赣�\n"); 
    if(me->is_fighting(target))
                return notify_fail("�����ں�"+target->name()+"����ء�\n");            

    weapon = me->query_temp("weapon");  
    weapon1 = target->query_temp("weapon");  

    if(!weapon || weapon->query("skill_type") != "sword"
      || me->query_skill_mapped("sword") != "liangyi-jian"
      || me->query_skill_mapped("parry") != "liangyi-jian")
        return notify_fail("�������޷�ʹ�á�˫����赡���\n");

    if(!weapon1 || weapon1->query("skill_type") != "sword"
      || target->query_skill_mapped("sword") != "liangyi-jian"
      || target->query_skill_mapped("parry") != "liangyi-jian")
        return notify_fail(target->name()+"�����޷�ʹ�á�˫����赡���\n");

   
    if(skill < 100 )
        return notify_fail("������ǽ����ȼ�����������ʹ�á�˫����赡���\n");
    
    if((int)me->query_skill("xuantian-wuji", 1) < 100 )
        return notify_fail("��������޼����ȼ�����������ʹ�á�˫����赡���\n");       
    
    if((int)me->query("neili") < 500 )
        return notify_fail("����������̫��������ʹ�á�˫����赡���\n");
    if((int)me->query("max_neili") < 1000 )
        return notify_fail("����������̫��������ʹ�á�˫����赡���\n");

    if(me->query_temp("ly_hebi")) 
        return notify_fail("���Ѿ���ʹ�á�˫����赡��ˡ�\n");

   if(target->query_temp("ly_hebi")) 
        return notify_fail(target->name()+"�Ѿ��ں�����ʹ�á�˫����赡��ˡ�\n");

          
    if(me->query_temp("lyhebi_target")){
          if(me->query_temp("lyhebi_target")==target)
                return notify_fail("���Ѿ����ú�"+target->name()+"˫����赵�׼���ˡ�\n");
          else{
               tell_object(me->query_temp("hebi_target"), YEL+me->name()+"������������˫������ˡ�\n"NOR); 
                me->delete_temp("lyprepare_hebi");
                me->delete_temp("lyhebi_target");
               }
          }
     if(target->query_temp("lyprepare_hebi") && target->query_temp("lyhebi_target") ==me){
        message_vision(MAG"\n $N��$nʹ����ɫ,����"+weapon->name()+MAG+"��$n��"+weapon1->name()+MAG+"���������˫�����ϣ���ʱֻ����������������������\n"NOR, me, target);
       me->delete_temp("lyprepare_hebi");
       me->delete_temp("lyhebi_target");
       target->delete_temp("lyprepare_hebi");
        target->delete_temp("lyhebi_target");
        me->set_temp("ly_hebi", 1); 
        target->set_temp("ly_hebi", 1); 
        me->add("neili", -300);
        target->add("neili", -300);
        me->add("jingli", -50);
        target->add("jingli", -50);
        remove_call_out("check_reply");
        me->start_call_out( (: call_other, __FILE__, "check_fight", me, target :), 1);
        target->start_call_out( (: call_other, __FILE__, "check_fight", target, me :), 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), (skill+skill1)/2);
        target->start_call_out( (: call_other, __FILE__, "remove_effect", target :), (skill+skill1)/2);
        return 1;
        }
    message_vision(HIC"\n $N������"+weapon->name()+HIC"һ�ᣬ��ʾ$n��$Pһ������˫����赡�\n"NOR, me, target);
    tell_object(target, YEL"�����Ը���"+me->name()+"����˫���ͱڣ���Ҳ��"+me->name()+"��һ�� ( perform hebi <player's id> ) �����\n"NOR); 
    me->set_temp("lyprepare_hebi", 1);     
    me->set_temp("lyhebi_target", target);
      call_out("check_reply", 15, me); 
    return 1;
}

void check_fight(object me, object target)
{
    object weapon,weapon1;  
    
 	weapon = me->query_temp("weapon");  
      weapon1 = target->query_temp("weapon");  

    if(!weapon || weapon->query("skill_type") != "sword"
      || me->query_skill_mapped("sword") != "liangyi-jian"
      || me->query_skill_mapped("parry") != "liangyi-jian")
         call_out("remove_effect", 0, me);

    if(!weapon1 || weapon1->query("skill_type") != "sword"
      || target->query_skill_mapped("sword") != "liangyi-jian"
      || target->query_skill_mapped("parry") != "liangyi-jian")
		  call_out("remove_effect", 0, me);

     else if((!present(target->query("id"), environment(me))) ||
            !me->is_fighting() || !living(target) || !target->is_fighting()
            || target->is_ghost() || me->is_ghost() || !living(me)
            || !target->query_temp("ly_hebi"))
         call_out("remove_effect", 0, me);

    else call_out("check_fight", 1, me, target);
}
void check_reply(object me)
{
if (me->query_temp("lyprepare_hebi", 1)) {     
        me->delete_temp("lyprepare_hebi");     
        me->delete_temp("lyhebi_target");
            return notify_fail("�ƺ��Է�����İ�ʾû�з�Ӧ������ֻ��ȡ����˫���ϱڵ�����\n");
}   
}
void remove_effect(object me)
{
  if(me->query_temp("ly_hebi")){
    me->delete_temp("ly_hebi");
	return notify_fail(HIR"��˫�������ᣬ����Ҳ�ָ������ˡ�\n"NOR);
       }
}

*/