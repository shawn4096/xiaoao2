//sanjue.c 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
  	string msg;
    int i,ap,dp,damage;
    object weapon;
	if( !target ) target = offensive_target(me);
	if( !target || !me->is_fighting(target) )
		return notify_fail("������������ֻ����ս���жԶ���ʹ�á�\n");
    weapon = me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="blade")
        return notify_fail("�����ʹ�õ�ʱ����ʹ����������������\n");
    if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ�������죬����ʹ�á�������������\n");
	if( (int)me->query_skill("dodge", 1) < 100 )
		return notify_fail("��Ļ����Ṧ������죬����ʹ�á�������������\n");
	if( (int)me->query_skill("xiuluo-dao", 1) < 100 )
		return notify_fail("������޵���������죬����ʹ�á�������������\n");
    if(me->query_skill_mapped("blade")!="xiuluo-dao"||me->query_skill_mapped("parry")!="xiuluo-dao")
        return notify_fail("��û�м������޵�������ʹ�á�������������\n");
	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ���Ϊ����������ʹ�á�������������\n");
    if( me->query_temp("sl/xiuluo"))
		return notify_fail("������ʹ�á���������������\n");
	if( (int)me->query("max_neili", 1) < 1400 )
		return notify_fail("����������̫��������ʹ�á�������������\n");
	if( (int)me->query("neili", 1) < 400 )
		return notify_fail("����������̫��������ʹ�á�������������\n");
    if((int)me->query("jingli",1)< 200)
        return notify_fail("�����ھ���̫�٣�����ʹ�á�������������\n");
        i = me->query_skill("xiuluo-dao", 1);
        
       
		//�����˺�,350ǰ������
        if (userp(me) && me->query_skill("xiuluo-dao",1)<350)
        {
          me->add_temp("apply/damage", i/4);
        }
		//���Ϊ������������
		if (userp(me)&&me->query("class")=="bonze")
		{
          me->add_temp("apply/damage", i/6);
          me->add_temp("apply/attack", i/3);
		  message_vision(YEL"$N���з�ţ��ȵ����������ӷ�������������ͬʱ���ϵ��������Լ�ǿ���١�\n"NOR,me,target);
		}		
        //me->add_temp("apply/attack", i); 	    
        msg = HIY "$N" HIY "����ɱ����ʢ��һ�����е�" + weapon->query("name")+HIY "����������ͼ��$n" + HIY "���Ź�ס��\n" NOR;
        ap = me->query_skill("blade",1);
		if (me->query("class")=="bonze")
		   ap=ap+me->query_skill("huddhism",1);
        dp = target->query_skill("parry",1);
        damage = ap*4+ random(ap);
		damage=damage*2;
	  if (damage>4000) damage=4000+(damage-4000)/100;
	
      if (ap / 2 + random(ap) > dp || random(me->query_str())>target->query_con()/2)
        {
               
				msg+=HIC"$nһ��С��Ϊ$N�ĵ�����������ʱ��æ����������\n"NOR;				
                target->start_busy(2+random(2));
				if (me->query_skill("buddhism")>=200&&me->query("class")=="bone"&&me->query_skill("xiuluo-dao")>150)
				{
					 msg+= HIR "$N���ĳ�ħ��������˸��������$n" HIR "�ҽ�������һ����Ѫ����" HIR"���׵ĵ����н�����\n" NOR;
					 target->receive_damage("qi",damage,me);
					 message_vision(msg,me,target);
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				}
        } else
        {               
                me->start_busy(1);
                msg += CYN "����$p" CYN "�����ֿ죬ֻ����������������һ��"
                       CYN "������$p" CYN "��$P" CYN "����ʽȫ��������\n" NOR;
        }
	    message_vision(msg, me, target);
        me->add("neili", -100);
        me->add("jingli",-50);
		me->set_temp("sl/xiuluo",1);
        
		if (me->is_fighting()&&objectp(target)&&me->query("class")=="bonze")
        {
            message_vision(YEL"$N���ٴθ��з�ţ��ȵ�������Ȼ�������ڤ�����������Ҿ������˳�ħ������\n"+HIC"$N����һ���ӳ���ֱ��$n���ؿ���ȥ��\n"NOR,me,target);
			target->receive_damage("qi",damage,me);
            target->receive_wound("qi",damage/3,me);
	        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        }
		me->start_busy(1);
            
       // me->add_temp("apply/attack", -i); 
		if (userp(me)&&me->query_skill("xiuluo-dao",1)<350)
        {
          me->add_temp("apply/damage", -i/4);
        }
		if (userp(me)&&me->query("class")=="bonze")
		{
          me->add_temp("apply/damage", -i/6);
          me->add_temp("apply/attack", -i/3);
		}
		me->delete_temp("sl/xiuluo");
        me->start_perform(3,"��������");
        
      return 1;
}
string perform_name(){ return HIB"��������"NOR; }
int help(object me)
{
         write(HIB"\n���޵���֮��������������"NOR"\n");
        write(@HELP
	��������������������Ϊ�˳�ħ�������������������������似��
	�����������ڳ�������˵���������������ޣ����Զ���ǣ��Ϊ��
	�����������������ޣ�����ʩչ�������У����Է����ѣ�Ϊ����
	һ����·����ʵ����ڤ�����������һ����������������������
	�����޵ķ𷨹�����
	
	perform blade.xiuluo

Ҫ��
	�����ڹ���100
	�����Ṧ��100
	���޵�����100
	�����ڹ���100
	���������1400
	��ǰ������500
	��ǰ������200
	�輤�����޵���       
HELP
        );
        return 1;
}

