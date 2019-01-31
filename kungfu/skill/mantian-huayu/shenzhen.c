// shenzhen.c ���� 
// By sohu 2014/6
#include <ansi.h>

inherit	F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
void remove_effect(object target);

string *xue_name1 =({
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","�羮Ѩ"});
string *xue_name2 = ({
"�ٻ�Ѩ","����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ"});
string *xue_name3 = ({
"����Ѩ","����Ѩ","�縮Ѩ","����Ѩ","��̨Ѩ","����Ѩ","����Ѩ","��ͻѨ"});

int perform(object me,	object target)
{      object weapon = me->query_temp("weapon");
	int p,i,j,z;
	string name1,name2,name3;
	weapon = me->query_temp("weapon");
	name1 =	xue_name1[random(sizeof(xue_name1))];
	name2 =	xue_name2[random(sizeof(xue_name2))];
	name3 =	xue_name1[random(sizeof(xue_name3))];
	if( !target) target = offensive_target(me);
	if( !target || !me->is_fighting(target)	|| !living(target)
		    || environment(target)!=environment(me))
	   return notify_fail("û��ս��������������˾޴��Ŭ����\n"); 
	//if (!present("heixue shenzhen",me ))
	   //return notify_fail("û�к�Ѫ���룬��ʹ�û�ǧ�����к���?!\n");
	
	if(!weapon || weapon->query("skill_type") != "throwing"	)
	   return notify_fail("�����м�����״�����������ʹ�����Ѫ���������\n");
	
	if( (int)me->query_skill("xinxing-dafa",1) < 150	)
       if( (int)me->query_skill("tianmo-gong",1) < 150	)
	   return notify_fail("��������ڹ���Ϊ���㣬�޷�ʩչ��Ѫ���������\n");
	if( (int)me->query_skill("mantian-huayu",1) < 150 )
	   return notify_fail("������컨��ȼ��������޷�������˸�����似��\n");
	if( (int)me->query_skill("force", 1) < 150 )
	   return notify_fail("��Ļ����ڹ���Ϊ���㣬�������⵽���棡\n");
	if( (int)me->query_skill("throwing", 1)	< 150 )
	   return notify_fail("��Ļ���������Ϊ���㣬���ܼ�����˸��ӵ��ַ���\n");
	if (me->query_skill_mapped("throwing") != "mantian-huayu")
	   return notify_fail("���������컨�����ʹ�ú�Ѫ�����������\n");
	if (me->query_skill_mapped("parry") != "mantian-huayu")
	   return notify_fail("���������컨��������ʹ�ú�Ѫ���룿��\n");
	if( (int)me->query("neili") < 1500 )
	   return notify_fail("����������㣬����ʹ�ú�Ѫ���������\n");
	if( (int)me->query("max_neili") < 1200 )
	   return notify_fail("����������㣬����ʹ�ú�Ѫ���������\n");
	if( (int)me->query("jingli") < 300 )
	   return notify_fail("��ľ������㣬����ʹ�ú�Ѫ���������\n");
	if(target->query_temp("hmy/heixue"))
	   return notify_fail("�Է��Ѿ��������ס������Ѩ�������ٶ���ֽ��ˣ�\n");

    i=me->query_skill("mantian-huayu",1)+me->query_skill("throwing",1)+me->query_skill("force",1);
    j=target->query_skill("parry",1)+target->query_skill("dodge",1)+me->query_skill("force",1);
	p = random(i/3);
	z = (i -j)/3;
	if ( z < 3 ) z = 3;
	if ( z > 12 ) z	=12;
      
     message_vision(HIB"\nͻȻ$Nһ����Х��˫�ִ������ͳ�һ�Ѻ�ɫ�룬����һ�գ���ͬ��Ů�����Ƶ��������ܣ���$n�������ڣ�\n"NOR,me,target);
	 
	 me->add("neili", -500);
	 me->add("jingli", -50);
	 //Ч��һ�����ͶԷ������ͷ���
    if (random((int)me->query("combat_exp",1)) > (int)target->query("combat_exp",1)/2 
		 ||random(me->query_dex(1))>target->query_dex(1)/3)
	{ 
      tell_object(me, MAG"���һ����Ч��ѹ����������²��ٹ��ǣ��������ȣ���\n"NOR);
      tell_object(target, MAG"�����У���ͻ��"RED+name1+MAG"��"RED+name2+MAG"��"RED+name3+MAG"ͬʱһ�飬һ������ɢ����֫Ҳ��ʼ��ľ��ɲʱ�����ң���\n"NOR);
	  target->receive_damage("qi", i/3+p,me);
	 if (weapon->query("id")=="heixue shenzhen")
	   target->add_condition("heixue_poison",4+random(3));
	 target->add_busy(2);
	 if (!userp(target)) target->add_busy(3);

	 target->set_temp("hmy/heixue", 1);
	 target->set_temp("apply/strength", -(target->query("str", 1)/3));    
	 target->set_temp("apply/dexerity", -(target->query("dex", 1)/3));  
	 target->set_temp("apply/intelligence",	-(target->query("int", 1)/3));	  
	 target->set_temp("apply/constitution",	-(target->query("con", 1)/3));	
	 
	 target->apply_condition("no_perform", 1+random(2));
	 tell_object(me,	HIB"���"+target->name()+"˫üͻȻ����һ��������ʹ�������ǳԿ����٣���ʱ�������\n"NOR);
	 tell_object(target, HIB"��ս�У���ͻ��"RED+name1+HIB"��"RED+name2+HIB"ͬʱһ�飬Ѫ����ʱΪ֮һ��������æ����������������죬�����ް���ȴҲ��Ū�Ķ��ϼ�����֪�ǳԿ����١�\n"NOR);

	 target->receive_damage("qi", i/3+p,me);	     
	 target->receive_wound("qi", i/6,me);	     

	 if (objectp(target))
	 	 target->start_call_out((:call_other,__FILE__,"remove_effect",target:),i/6); 
	 return 1;
	 }
	 else {
			message_vision(BLU"ֻ��$p����Ʈ���������ޱȵıܿ���$N����������������⡣\n"NOR,me, target);

			message_vision(HIM"$N����Է���ֻ��΢΢һ��������У��漴���������ϣ�������������Ʒ��������$n��\n"NOR,me,target);
			//tell_object(target, HIM"��ս�У���΢��"RED+name1+HIM"һ�飬֪�ǽ������ˣ�æ������أ����˴�����Щ��ʹ��ȴ���޴󰭡�\n"NOR);
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);			   
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);			   
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);			   

			me->start_busy(1);


		}	

	me->delete_temp("hmy/heixue");
	me->add("neili", -(100+random(50)));	
	me->add("jingli", -100);		
	me->start_perform(2, "����Ѫ���롹");	
	return 1;
	
}

void remove_effect(object target)
{
      if(!target) return;

      target->set_temp("apply/strength", target->query("str", 1)/3);    
	  target->set_temp("apply/dexerity", target->query("dex", 1)/3);  
	  target->set_temp("apply/intelligence",target->query("int", 1)/3);	  
	  target->set_temp("apply/constitution",target->query("con", 1)/3);	
      target->clear_condition("no_perform");
      target->delete_temp("qianshou");
      message_vision(WHT"ֻ��$P����һ�����������ۡ������ϱƳ���ö���룬����֮��������\n"NOR,target);
      tell_object(target,WHT"��پ�Ѩ������֮��ȫ�������а������泩�ޱȡ�\n"NOR);
	  return;
}
string perform_name(){ return HBBLU"��Ѫ����"NOR; }

int help(object me)
{
        write(HBBLU"\n���컨��֮����Ѫ���롹��"NOR"\n\n");
        write(@HELP
	ħ�̴��Ƶ�һ�־綾������ʩ��ʱһ�Ժ�����������������߱�����
	����������֮���ġ�ħ�̳�������Ϊ�������磬��������δι����
	��Ѫ�����˵У�
	��Ҫע����ǣ���������״��������ʩչ���С���Ѫ��������Ч��
	
	ָ��;perform throwing.shenzhen

Ҫ��
	��ǰ���� 1500 ����;
	����� 1200 ���ϣ�
	���컨��ȼ� 150 ���ϣ�
	��ħ�������Ǵ󷨵ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	�����ڹ��ȼ� 150 ����;
	�����������м�Ϊ���컨�������
	�����г�����״������

        
HELP
        );
        return 1;
}
