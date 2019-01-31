// yunu-jianfa ��Ů����
// by dubei
// Modify By River 99.5.26
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name(){ return HBMAG+HIW"��Ů���ľ�"NOR; }
int perform(object me, string arg)
{
      object weapon, target;
      int dex,armor,skill;       
      dex = me->query_dex()*2;
      armor = me->query_int()*3;
      skill = me->query_skill("yunu-jianfa",1)/5;

	  if (me->query("gender") == "Ů��") skill *= 5/4; //Ů�Ի�����������
      weapon = me->query_temp("weapon");

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
               return notify_fail("����Ů���ġ�ֻ����ս���жԶ���ʹ�á�\n");

      if ( !weapon
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa" 
        || me->query_skill_mapped("parry") != "yunu-jianfa")
               return notify_fail("��û����Ů���Ľ���ôʹ������Ů���ġ��أ��������ˣ�\n");

      if((int)me->query_skill("yunu-jianfa", 1) < 350 )
               return notify_fail("�����Ů������Ϊ���� ��\n");

      if((int)me->query_skill("sword", 1) < 350 )
               return notify_fail("��Ļ�������������죬ʹ��������Ů���ġ�������\n");

      if((int)me->query_dex() < 60)
               return notify_fail("�����������Ѹ�ݣ�ʹ��������Ů���ġ�������\n");

      if((int)me->query_skill("yunu-xinjing", 1) < 350 )   
               return notify_fail("�����Ů�ľ���Ϊ�������޷�ʹ�á���Ů���ġ�������\n");  
      if( me->query_skill_mapped("force") != "yunu-xinjing" && userp(me))
                return notify_fail("�������޷�ʹ�á���Ů���ġ���\n");
      if((int)me->query_temp("gumu_suxin")) 
               return notify_fail("����������ʹ�á���Ů���ġ�������\n"); 

      if( me->query_temp("wujian") )
                return notify_fail("������ʹ�á��޽�ʤ�н����أ�\n");
      if(me->query_temp("ynjf/suxin"))
               return notify_fail("������ʹ�á���Ů���ġ�������\n"); 
      if((int)me->query_temp("ynxj/hebi"))
               return notify_fail("������ʩչ˫���ϱڣ��޷�ʹ�á���Ů���ġ�������\n"); 

      if((int)me->query("max_neili") < 5000)
               return notify_fail("���������Ϊ������\n");

      if((int)me->query("neili") < 1500)
               return notify_fail("�������������\n");

      if((int)me->query("jingli") < 1500)
               return notify_fail("��ľ���������\n");

       me->add("neili", -300);
       me->add("jingli", -150);
	   
    
	   if (me->query_temp("ynxj/xinjing")
		&& me->query("gender")=="Ů��"
		&& me->query("env/��Ů����")=="����")
	   {
		   skill=skill+me->query_skill("yunu-xinjing",1)/5;
	   }
 	   
       message_vision(HBMAG+HIW"\n$N����һ����������������֮�����"+weapon->name()+HBMAG+HIW"�û���������â����$n�糸��ȥ��\n"
								+"\n$N����ʽ���䣬����Ȼ�Ѿ�����Ů�ľ������һ�µ��书��ʽ�ˡ�\n"NOR,me,target);
	   
	   me->add_temp("apply/armor", armor);
       me->add_temp("apply/dexerity",dex);
       
	   me->add_temp("apply/attack", skill/4);
	   me->add_temp("apply/sword",skill/6);
	   
	   if (me->query("quest/hubo/pass"))
	   {
		   me->add_temp("apply/sword", skill/6);
		   me->add_temp("apply/damage", skill/6);
		   message_vision(HIW"\n$N�Ѿ�����˫�ֻ����İ����ڻ��ͨ����ͷͨ��������Ķ��У���Ů���Ľ�������������ʱ�����ݺᡣ\n"NOR,me,target);
		   //me->start_perform(1,"����Ů���ġ�");
	   }
	   me->set_temp("ynjf/suxin", skill); 
	

	   if (me->query_skill("yunu-jianfa",1) < 550)
	       me->start_perform(2,"����Ů���ľ���");
       call_out("check_fight", 1, me, dex, armor, skill);
       return 1;
}

void remove_effect(object me, int dex, int armor, object weapon)
{      
       int skill=me->query_temp("ynjf/suxin");
	   me->add_temp("apply/armor", -armor);
       me->add_temp("apply/dexerity",-dex);
	   me->add_temp("apply/attack", -skill/4);
	   me->add_temp("apply/sword",-skill/6);

	   if (me->query("quest/hubo/pass"))
	   {
		   me->add_temp("apply/sword", -skill/6);
		   me->add_temp("apply/damage", -skill/6);
		}
       me->delete_temp("ynjf/suxin");
       tell_object(me, HBMAG+HIW"�㡸��Ů���ġ�ʩչ��ϣ���������һ������\n" NOR); 
}

void check_fight(object me, int dex, int armor, int skill)
{
       object weapon;
       if (!me) return;
       if(!objectp(weapon = me->query_temp("weapon"))
         || me->query_skill_mapped("sword") != "yunu-jianfa"
         || me->query_skill_mapped("parry") != "yunu-jianfa"
         || me->query_skill_mapped("force") != "yunu-xinjing"
         || weapon->query("skill_type") != "sword"){
           remove_effect(me, dex, armor, weapon);
           return;
       }
       if( skill < 1 || !me->is_fighting()) {
           remove_effect(me, dex, armor, weapon);
           return;
       }
       call_out("check_fight", 1, me, dex, armor, skill-1);
}
int help(object me)
{
        write(HIM"\n��Ů����֮"HBMAG+HIW"����Ů���ľ�����"NOR"\n");
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
	������Ϊ��Ĺ����������Ů���ľ�����
	��Ů���ľ�������Ů�ľ���벿�ľ�Ҫ���ڣ��ص�
	�����������ľ���ˮ�����ʱ���ڴ��������Ů
	������������ע�⣺Ů�Ա�����������,550���ɡ�
		
	perform sword.suxin
	ע�⣺set ��Ů���� ���� Ů��������ӳ�
		
Ҫ��
	�������Ҫ�� 5000 ���ϣ�      
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��Ů�ľ��ȼ� 350 ���ϣ�
	��Ů�����ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��Ч���ȼ� 60  ���ϣ�
	�����������м�Ϊ��Ů������
	�ֳֽ��������
	��ʾ���������ܲ�ͨ��˫�ֻ�����
	���ľ������������ͷţ�
                
                
HELP
        );
        return 1;
}