//daojian.c ���ҵ�������ҽ������ں�
//by sohu@xojh 12/10/2013

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HBBLU+HIW"����˫��"NOR; }
int perform(object me, object target)
{
	
	int skill, skill1, skill2;
	object weapon,weapon2;
    object *inv;
    int i, count;
	string bei_skill;
	if( !target) target= offensive_target(me);
    //&& ! me->query("quest/hubo/pass")
    
	if(!me->query("quest/ѩɽ�ɺ�/�书/ronghe"))
		return notify_fail("����δ���򵶽��ںϣ�����ʹ�����о�����\n");

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
		 || !living(target)
         || environment(target)!= environment(me))
		return notify_fail("ѩɽ�ɺ��似�����ں�˫��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	
    if( me->query_skill_mapped("sword") != "miaojia-jianfa" || me->query_skill_mapped("blade") != "hujia-daofa")
		return notify_fail("����ͨ�������к��ҵ�������ҽ�������ʹ�õ���˫����\n");

     
    if(me->query_skill("miaojia-jianfa",1) <500)
		return notify_fail("�����ҽ�����������������ʹ�õ���˫����\n");

	if(me->query_skill("hujia-daofa",1) <500)
		return notify_fail("��ĺ��ҵ�����������������ʹ�õ���˫����\n");
/*
	if( me->query_skill_mapped("force") != "lengquan-shengong" )
		return notify_fail("�����õĲ�����Ȫ���ķ����޷�ʩչ����˫����\n");

	if( me->query_skill("lengquan-shengong", 1) < 500 )
		return notify_fail("�����Ȫ�񹦻��δ�����޷�ʩչ����˫����\n");
	*/	
	if( !objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "blade" )
		return notify_fail("������е�����ʹ�õ���˫����\n");

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
		return notify_fail("������е�������ʹ�õ���˫����\n");

	if( me->query("neili") <= 1500 )
		return notify_fail("�����������ʹ�õ���˫����\n");
	if( me->query("jingli") <= 1500 )
		return notify_fail("��ľ�������ʹ�õ���˫����\n");
	if( me->query("max_neili") <= 15000 )
		return notify_fail("��������������ʹ�õ���˫����\n");

	skill =  ( me->query_skill("sword",1) + me->query_skill("miaojia-jianfa",1)
		+ me->query_skill("hujia-daofa",1) +me->query_skill("blade",1) 
		+ me->query_skill("force",1)) / 5; 

	if (me->query_skill("lengquan-shengong",1))
	{	
		message_vision(HIC"$N"+HIC"����Ȫ���������׷��ӳ���������"HIG"��ҽ���"+HIC"����"+HIR"���ҵ���"HIC"���ڻ��ͨ��\n"+
		"����Ʈ�����ѣ�����Ȫ�񹦵ļ����£�����˫������������\n" NOR, me);		
		skill+=me->query_skill("lengquan-shengong",1)/4;
		me->add_temp("apply/strength",  skill/15);

	}else {
		message_vision(HIW"$N"+HIW"��������������������ӿ������"HIG"��ҽ���"+HIW"����"+HIR"���ҵ���"HIW"���ڻ��ͨ��\n"+
		"����Ʈ�����ѣ��������ܣ��������ã������ںϺ��˫��������Ȼ������\n" NOR, me);

	}
    me->set_temp("feihu/ronghe", 1);

	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage", skill/4);
	me->add_temp("apply/dodge",  skill/2);
	me->add_temp("apply/sword",  skill/4);
	me->add_temp("apply/blade",  skill/4);
	me->add_temp("apply/parry",  skill/4);

    bei_skill = me->query_skill_mapped("blade");

    if (skill>=500 && !userp(target) ) target->set_temp("must_be_hit",1);
	  //weapon->unequip();
	  weapon2->unequip();
	  me->map_skill("blade", "hujia-daofa");
	  weapon->wield();
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  //���ҵ��� 

   if(me->is_fighting(target)) {
     me->map_skill("sword", "miaojia-jianfa");

	  weapon->unequip();
	  weapon2->wield();
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  //��ҽ���
	
     }                               

   if(me->is_fighting(target)) {
      weapon2->unequip();
	  weapon->wield();
	  me->map_skill("blade", "hujia-daofa");

      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);  //���ҵ��� 
      
	 }

   if(me->is_fighting(target)) {
	  weapon->unequip();
	  weapon2->wield();
      me->map_skill("sword", "miaojia-jianfa");         

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);   //��ҽ���
	}

//-------------------��Ȫ450��------------------//
    if(me->query_skill("lengquan-shengong",1) >= 500)
     {

       if(me->is_fighting(target)) {
         weapon2->unequip();
	     weapon->wield();
		 me->map_skill("blade", "hujia-daofa");
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);         //��ҽ���
	   }
  
     if(me->is_fighting(target)) {
	     weapon->unequip();
	     weapon2->wield();
         me->map_skill("sword", "miaojia-jianfa");         

	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);   //���ҵ���
	    }
      }

      me->map_skill("blade", bei_skill);
	  weapon2->unequip();
	  weapon->wield();

	me->add("jingli", -random(400));
	me->add("jing", -100);
	me->add("neili", -random(1000));
	me->start_busy(1+random(2));
    
	if(target){
       target->start_busy(1+random(2));  
       target->delete_temp("must_be_hit");
	  }
	   me->add_temp("apply/attack", -skill/2);
	   me->add_temp("apply/damage", -skill/4);
	   me->add_temp("apply/dodge",  -skill/2);
	   me->add_temp("apply/sword",  -skill/4);
	   me->add_temp("apply/blade",  -skill/4);
	   me->add_temp("apply/parry",  -skill/4);
	   if (me->query_skill("lengquan-shengong"))
	   {
		   me->add_temp("apply/strength",  -skill/15);
	   }
	   
       me->delete_temp("feihu/ronghe");
       me->start_perform(6, "������˫����");

	   message_vision(HIY "\n$N���������������뵤�����˫�����У�\n\n" NOR, me);

	return 1;
}

int help(object me)
{
        write(HIB"\n��ҽ���֮������˫������"NOR"\n");
        write(@HELP
		
	��ҽ����ͺ��ҵ������Գ��������֣����ҵ����Ը������ƣ�
	��ҽ���ȴ���������������������������书�����������
	Ѱ��ɱ�����˵Ĺ����У����Ϻ����˷�����д裬ȴ������
	�����񹦵Ĺ����л���֮�ƣ����������˷�ĵ㲦�»�Ȼ��
	�����ࡣ���ŵ���˫����ֻ����������Ȫ��֧��֮��
	���ܷ��ӳ������������
		
	ָ��;perform sword.daojian

Ҫ��  
	������� 15000 ���ϣ�      
	��ǰ���� 1500  ���ϣ�
	��ǰ���� 1500  ���ϣ�
	���ҵ����ȼ� 500 ���ϣ�
	��ҽ����ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	��������Ϊ��ҽ�����
	��������Ϊ���ҵ�����
	�ֳֽ�������������ϴ�����
	�ڹ����ޣ�
                
HELP
        );
        return 1;
}