// tisha.c ��ɳ
// Update By lsxk@hsbbs 2007/6/11 

#include <ansi.h>
inherit F_SSERVER;
int nuoyi_ob(object me,object victim,int damage);
int perform(object me, object target)
{
	object weapon=me->query_temp("weapon");
	int j, f, flag;
    flag=0;

	if( !target ) target = offensive_target(me);

    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
		return notify_fail("��ʥ���ѧ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

   if(me->query_skill("shenghuo-lingfa", 1) < 450 )
		return notify_fail("���ʥ�������̫ǳ������ʹ�á�\n");

   if(!me->query_skill("jiuyang-shengong", 1)||(int)me->query_skill("jiuyang-shengong",1)<450)
   if(me->query_skill("shenghuo-shengong", 1) < 450 )
           return notify_fail("��������ڹ�����̫ǳ������ʹ�á�\n");


   if(me->query_skill("dagger", 1) < 450 )
		return notify_fail("��Ļ���ذ������̫ǳ������ʹ�á�\n");

   if(me->query_skill("cuff", 1) < 450)
		return notify_fail("��Ļ���ȭ������̫ǳ������ʹ�á�\n");

   if(me->query_skill("qiankun-danuoyi", 1) < 450 )
		return notify_fail("���Ǭ����Ų�ƹ���̫ǳ������ʹ�á�\n");

   if(me->query("max_neili") < 3000 )
		return notify_fail("�������̫ǳ������ʹ�á�\n");

	if(me->query("neili") < 1000 )
		return notify_fail("�����������������ʹ�á�\n");

	if(me->query("jingli") < 1000)
		return notify_fail("��ľ�������������ʹ�á�\n");

	if( me->query_temp("tisha") )
		return notify_fail("������ʩչ��ɳ�����أ�\n");

	/*if( me->query_temp("qkdny/hua") )
		return notify_fail("������ʩչǬ����Ų�ơ������־��أ�\n");*/

    if( me->query_skill_mapped("parry") != "shenghuo-lingfa" 
        && me->query_skill_mapped("parry") != "qiankun-danuoyi" )
                return notify_fail("����Ҫ�����м�Ϊʥ���������ʹ�ô˾�����\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "dagger"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 || me->query_skill_mapped("dagger") != "shenghuo-lingfa"
    || me->query_skill_mapped("cuff") != "shenghuo-lingfa" 
    || (me->query_skill_mapped("force") != "shenghuo-shengong" && me->query_skill_mapped("force") != "jiuyang-shengong") )
		return notify_fail("�㲻��ʹ��������У�\n");


    if ( !me->query_skill("jiuyang-shengong", 1)&&me->query_skill("qiankun-danuoyi", 1)<350||(!userp(me) && userp(target)))
	  {
	   flag = 3;
	   f = (int)me->query_skill("shenghuo-lingfa", 1)+ (int)me->query_skill("shenghuo-shengong", 1)/3;
	   }
	 else
	   {
		flag = 4;
        f = (int)me->query_skill("shenghuo-lingfa", 1) + (int)me->query_skill("force", 1)/3+(int)me->query_skill("jiuyang-shengong", 1)/3;
		}
    if (me->query("mjqkdny/pass")||me->query("quest/jiuyang/pass"))
	    {
		 flag=5;  		 
         f = (int)me->query_skill("shenghuo-lingfa", 1) + (int)me->query_skill("qiankun-danuoyi", 1)/5+(int)me->query_skill("jiuyang-shengong", 1)/5;
		}
  
     j = f / (8-flag);//��ԭ���ĵ���8����ֹ���
/*
	if ( f > 500 )
		j = to_int(f/��7-flag�� * f/ 250.0);
*/

	message_vision(HBBLU+HIY"\n$NͻȻ���ȼ�ɨ��������´�Ƭɳʯ������һ��Ϊ"+chinese_number(flag)+"��ǰ��л�������"+chinese_number(flag)+"�У�\n" NOR, me);
    //�ֳ�ʥ�����������
	if (weapon->query("id")=="shenghuo ling")
         me->add_temp("apply/damage", j/5);
	     me->set_temp("tisha", 5);
   if(userp(me))
      me->add_temp("apply/damage", j);
      me->add_temp("apply/attack", j);
      //target->set_temp("must_be_hit",1);

	  weapon->unequip();
	  me->set_temp("type", 1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(flag>=4)?3:1);          //��һ�п���
	  me->delete_temp("type");
      //target->delete_temp("must_be_hit",1);

	  weapon->wield();
	if (present(target,environment(me)) && me->is_fighting(target))
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (flag>=4)?3:1); //��2�б���
//������Ϊ��ͨ������
	   weapon->unequip();
	  me->set_temp("type", 1);
	if (present(target,environment(me)) && me->is_fighting(target))
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (flag>=4)?3:1);//��3�п���
	   weapon->wield();
	   me->delete_temp("type");
        
	if (present(target,environment(me)) && me->is_fighting(target) && flag >=4 )   //��4�б���
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       
  
   // call_out("nuoyi_ob",0,me,target);
	if (present(target,environment(me)) && me->is_fighting(target) && me->query("mjqkdny/pass"))
	  { 
	   //me->add_temp("apply/damage",j);
	   message_vision(HBRED"\n$N��������б�ȣ�������ϵ���ɳ������ʱ֮�䣬$n������ɳ���棬˫�۲��ܼ��ãȻ��֪���룬\n"NOR+HIR"$N���ƴӱ���һԾ������$n�ĺ󾱲�ȥ��\n"NOR,me,target);
       target->add_busy(2);
	   target->set_temp("must_be_hit",1);
	   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
	   //me->add_temp("apply/damage",-j);
	   target->delete_temp("must_be_hit");
	 }
	if(userp(me))
      me->add_temp("apply/damage", -j);
      me->add_temp("apply/attack", -j);
	  me->delete_temp("tisha");
   if (weapon->query("id")=="shenghuo ling")
         me->add_temp("apply/damage", -j/5);
   me->add("neili", -600);
   me->add("jingli", -300);
   me->start_perform(4, "��ɳ");
   me->start_busy(2);
   return 1;
}

string perform_name(){ return HBRED+HIW"��ɳ"NOR; }

int help(object me)
{
	write(YEL"\nʥ���֮����ɳ����"NOR"\n\n");
	write(@HELP
	ʥ��������������������֮һ����˵���Բ�˹��ɽ����
	�󾭰ݻ�̴�����ԭ���Բ�˹��ʹ�����ߵ������޼�һս����
	�������޵��ֵ��Ž��������ܴ죬���˲��ٿ�ͷ������ԭ���
	����������ѵ��������������ϱ��ѱ棬�����Ϸ���
	����ɳ����������ͨ��������ת����·�ߵ�ɳ�ӷɽ����赲��
	�˵����߲�ͬʱ�õ����Ի�֮�ʣ���Ȼ�������С���Ȼ������
	��Ǭ����Ų�������⣬����н��ٴη�Ծ��ʵ��ʥ�����
	Ϊ������һ��ɱ����
	
ָ�perform dagger.tisha

Ҫ��
	��ǰ���������� 5000 ���ϣ�
	������������� 9000 ���ϣ�
	��ǰ���������� 2000 ���ϣ�
	ʥ����ĵȼ� 450 ���ϣ�
	Ǭ����Ų�Ƶȼ� 450 ���ϣ�
	ʥ���񹦵ĵȼ� 450 ���� ���� ���̾������ȼ� 450 ���ϣ�
	������ĵȼ� 450 ���ϣ�
	����ȭ���ĵȼ� 450 ���ϣ�
	�����Ϊʥ�����
	����ȭ��Ϊʥ�����
	�����м�Ϊʥ�����
	��ȭ��Ϊʥ�����
	���ֱֳ���,���ֳ�ʥ����似����������

HELP
        );
        return 1;
}
