// hebi.c ��Ů����ȫ�潣�ϱ����һ���
//by sdong 07/98

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIG"˫�ֻ���"NOR; }
int perform(object me, object target)
{
	int skill, skill1, skill2;
	
	object weapon,weapon2;
       object *inv;
       int i, count,j;
	string bei_skill;

	if( !target) target= offensive_target(me);
    //&& ! me->query("quest/hubo/pass")
    if(!me->query("quest/gm/ynjf/hubo/pass") )
		return notify_fail("����δ�������һ�������������˫���ϱ����һ�����\n");

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		return notify_fail("˫���ϱ����һ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");


	
	if( (int)me->query_temp("hubo") ) 
	{
		return notify_fail("��������˫���ϱ����һ�����\n");
	}

	if( (int)me->query_temp("hebi") ) 
	{
		return notify_fail("�������˺ϱڣ������ٽ���˫���ϱ����һ�����\n");
	}


    if( me->query_skill_mapped("sword") != "yunu-jianfa" && me->query_skill_mapped("sword") != "quanzhen-jianfa")
		return notify_fail("����ͨ����������Ů������ȫ�潣������˫���ϱ����һ�����\n");


	if(me->query_skill("quanzhen-jianfa",1) <500)
		return notify_fail("���ȫ�潣����������������˫���ϱ����һ�����\n");

	if(me->query_skill("yunu-jianfa",1) <500)
		return notify_fail("�����Ů������������������˫���ϱ����һ�����\n");

	if( me->query_skill_mapped("force") != "yunu-xinjing" )
		return notify_fail("�����õĲ�����Ů�ľ������칦���޷�ʩչ˫���ϱ����һ�����\n");

	if( me->query_skill("yunu-xinjing", 1) < 500)
		return notify_fail("�����Ů�ľ����δ�����޷�ʩչ˫���ϱ����һ�����\n");
	
	if( !objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword" )
		return notify_fail("�������˫�����ܺϱ����һ�����\n");

     inv = all_inventory(me);
     for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   break;
		   }
     }

	if( !objectp(weapon2) )
		return notify_fail("�������˫�����ܺϱ����һ�����\n");
    if( me->query("max_neili") <= 15000 )
		return notify_fail("�����������ʹ��˫���ϱ����һ�����\n");
	if( me->query("neili") <= 2000 )
		return notify_fail("�����������ʹ��˫���ϱ����һ�����\n");
	
	if( me->query("jingli") <= 1000 )
		return notify_fail("��ľ�������ʹ��˫���ϱ����һ�����\n");

	skill =  ( me->query_skill("sword",1) + me->query_skill("yunu-jianfa",1)
		+ me->query_skill("quanzhen-jianfa",1) +me->query_skill("yunu-xinjing",1) 
		+ me->query_skill("force")) / 5; 
	if (me->query("gender")=="Ů��"&&me->query("per")>29)
	{
		skill=skill+me->query_per(1);
	}

	message_vision(
	HIR "$NͻȻ�����ֳ����һ�ѽ���˫��ʹ�����ֽ�Ȼ��ͬ�Ľ������������һ���������\n"
	+HBBLU+HIM"ֻ��$N˫��һ������������Ů������ȫ�潣����ϵ������޷죬���ܻ��̣���������������ֽ���һ�㣬����������\n\n" NOR, me);
    if (me->query("quest/jiuyingm/pass") && me->query("gender")=="Ů��")
	{ 
		me->add_temp("apply/attack", skill/4);
        me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/sword", skill/6);
		message_vision(HIB"\n\n$N���Լ�������ľ����澭����Ů�ľ����һ���书�˴�ӡ֤����Ȼ��ͨ��\n"NOR,me);
	}
	else me->add_temp("apply/attack", skill/7); //������������6��Ϊ7
	
	me->add_temp("apply/sword",  skill/3);
	me->add_temp("apply/damage", skill/4);
	me->add_temp("apply/dodge",  skill/3);
	me->add_temp("apply/parry",  skill/3);
	me->set_temp("hubo", 1);

	bei_skill = me->query_skill_mapped("sword");
    target->start_busy(2+random(2));
 
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(weapon) weapon->unequip();
	weapon2->wield();
                                       }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		if(weapon2) weapon2->unequip();
	   if(weapon)	weapon->wield();
                                    }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon)	weapon->unequip();
	if(weapon2) 	weapon2->wield();
                                   }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon2)	 weapon2->unequip();
	if(weapon)	weapon->wield();
                                 }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon)	weapon->unequip();
	if(weapon2)	 weapon2->wield();
                              }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                             }

    me->map_skill("sword", bei_skill);
   if(weapon2)	 weapon2->unequip();
   if(weapon)  weapon->wield();

	me->add("jingli", -100);
	me->add("jing", -100);
	me->add("neili", -300);
	me->start_busy(2+random(2));
    if(me->is_fighting(target))  target->start_busy(1+random(2));  
    
	if (me->query("quest/jiuyingm/pass")&&me->query("gender")=="Ů��")
    { 
		me->add_temp("apply/attack", -skill/4);
        me->add_temp("apply/damage", -skill/6);
		me->add_temp("apply/sword", -skill/6);
	}
	else me->add_temp("apply/attack", -skill/7);
	
	me->add_temp("apply/damage", -skill/4);
	me->add_temp("apply/dodge",  -skill/3);
	me->add_temp("apply/sword",  -skill/3);
	me->add_temp("apply/parry",  -skill/3);
    me->delete_temp("hubo");
	me->start_perform(5,"�����һ�����");
	if(weapon)
	   message_vision(HIY "\n$N������һ���������ֽ�"+"$n" + HIY "��ؽ��ʣ��������У�\n\n" NOR, me,weapon);
    else 
   	   message_vision(HIY "\n$N������һ�������������У�\n\n" NOR, me);
	return 1;
}
int help(object me)
{
        write(HIM"\n��Ů����֮��˫�ֻ�������"NOR"\n");
        write(@HELP
	��Ů������һ��Ů���ֳ�Ӣ�����Ķ��ؽ���������
	�������������ҽ����������ף���ʽ��ţ�����Ů
	��������ȫ�潣���Ŀ��ǣ�һ��һʽ��ǡ�ð�ȫ��
	��������ʽѹ�Ƶö������ã����������ԣ�����
	�Ƶл��ȣ�ȫ�潣�����������Ų�仯�������Ѳ�
	����Ů���������֡��������������ҽ����������ף�
	��ʽ��š�Ʈ���������̬ƮƮ���ɡ�
	�ֳ�Ӣ����һ������������־����ȫ����˼Ͷ�뵽
	��Ů�����Ĺ���֮�У�һ��һʽ��һЦһ������
	�ϵ�����֮�У�������ζ������˵��������������
	������Ϊ��Ĺ������
	С��Ů�Դ��ܲ�ͨ�Ķ�ϰ�����һ���֮�����ڻ�
	��ͨ�����������˹�Ĺ��Ů�ľ����һ�µ��书Ҫ
	�塣ȫ�潣������Ů����˫��ʹ�ã�����������
	ע�⣺����������ò�ҹ�
		
	perform sword.hubo
		
Ҫ��
	�������Ҫ�� 15000 ���ϣ�      
	��ǰ����Ҫ�� 2000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��Ů�ľ��ȼ� 500 ���ϣ�
	��Ů�����ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	ȫ�潣���ȼ� 500 ���ϣ�
	��Ч���ȼ� 60  ���ϣ�
	�����������м�Ϊ��Ů������
	�����ڹ�Ϊ��Ů�ľ���
	�ֳֽ��������
	��ʾ�����⿪�Ĺ�Ĺ����������������
	            
                
HELP
        );
        return 1;
}
