// bishen.c �Ա�֮����ʩ����
// by tiantian@sj
// By Spiderii@ty����
#include <ansi.h>
#include <weapon.h>
#include <combat.h>
string perform_name(){ return HIG"�Ա�֮����ʩ����"NOR; }
inherit F_SSERVER;
string query_pfm(object me,object target);
string query_sk(object me);

mapping tested=([
	    "claw":"צ��",
	    "cuff":"ȭ��",
	    "finger":"ָ��",
	    "strike":"�Ʒ�",
	    "hand":"�ַ�",
	    "leg":"�ȷ�",
      ]);
mapping tested2=([
	    "sword":"����",
	    "blade":"����",
	    "dagger":"ذ��",
	    "brush":"�ʷ�",
	    "spear":"ǹ��",
	    "hook":"����",
	    "stick":"����",
	    "staff":"�ȷ�",
	    "club":"����",
	    "throwing":"����",
	    "whip":"�޷�",
	    "axe":"����",
	    "hammer":"����"
      ]);
 
int perform(object me, object target)
{
	int i,j;
	object weapon,weapon2;
	//string perform,perform_file;
	string skill,kungfu1,kungfu2;

	if( !target )
		target = offensive_target(me);
	if( !target || !me->is_fighting(target) ) 
		return notify_fail("�Ա�֮����ʩ����ֻ����ս����ʹ��!��\n");
//by spiderii@ty
    if(target->query("race") != ("����"))
		return notify_fail("����ɣ���Զ����õ���������\n");
	if(me->query_temp("bishen_target") || me->query_temp("dzxy/bishen") )
		return notify_fail("������ʹ���Ա�֮����ʩ����\n");               
	if(me->query_temp("bishen_target"))
		return notify_fail("������ʹ���Ա�֮����ʩ����\n");
	if(me->query_temp("douzhuan_target")|| me->query_temp("douzhuan_target"))
		return notify_fail("������ʹ�ö�ת���ơ�\n");
    
//	if(me->query("quest/mr/dzxy/bishen/pass"))
 
		//return notify_fail("�Ա�֮����ʩ��������Ľ���Ͼ�ѧ������δ�ڻ��ͨ��\n");
	
	weapon=me->query_temp("weapon");
	weapon2=target->query_temp("weapon");
    if( !me->query("quest/bishen/pass"))
       if ((!weapon&&weapon2) || (weapon&&!weapon2))
         return notify_fail("��ͶԷ��ı�����ͬ������ʹ���Ա�֮����ʩ����\n");
	if( target->query("family/family_name")=="����Ľ��"
		|| target->query_skill("douzhuan-xingyi",1)>0
		|| target->query_temp("bishen_target") )
		return notify_fail("�Է�����ת���ƾ��������޷���Է�ʹ���Ա�֮����ʩ����\n");
    if(me->query_skill_mapped("force") != "shenyuan-gong")
         return notify_fail("����ڹ�������Ԫ�����޷�ʹ���Ա�֮����ʩ����\n");      
    if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
         return notify_fail("���мܹ��򲻶�,�޷�ʹ���Ա�֮����ʩ����\n");     
    if( (int)me->query("max_neili") < 15000 )
		return notify_fail("��������������ߣ�\n");
	if( (int)me->query("neili") < 5000 )
		return notify_fail("�㵱ǰ������������\n");
	if(me->query_skill("douzhuan-xingyi",1)<500 )
		return notify_fail("��Ķ�ת���Ʋ����������������Ա�֮����ʩ����\n");
	if(me->query_skill("shenyuan-gong",1)<500 )
		return notify_fail("�����Ԫ�������������������Ա�֮����ʩ����\n");
	
	if( me->query("combat_exp")<target->query("combat_exp")/3)
		return notify_fail("����书��Ϊ���Է����̫Զ��ǿ�������Ա�֮����ʩ�������������Լ���\n");

	me->set_temp("bishen_target",target);
    me->set_temp("bishen_start",1);
	skill=query_pfm(me,target);
	if (weapon && weapon2) 
      {
		kungfu1=tested2[weapon->query("skill_type")];
		kungfu2=tested2[weapon2->query("skill_type")];
	 }
	if (!weapon && weapon2) 
       {
		kungfu1=tested[query_sk(me)];
		kungfu2=tested2[weapon2->query("skill_type")];
	   }
	if (weapon && !weapon2) 
       {
		kungfu1=tested2[weapon->query("skill_type")];
		kungfu2=tested[query_sk(target)];
	     }
 	if (!weapon && !weapon2) 
       {
		kungfu1=tested[query_sk(me)];
		kungfu2=tested[query_sk(target)];
	   }
	   j = me->query_skill("douzhuan-xingyi", 1);
       i = me->query_skill("douzhuan-xingyi", 1)+me->query_skill("shengyuan-gong", 1)/2;
	if (kungfu1 != kungfu2 )
	   message_vision(HIG"$N�����Ц���ȵ�������ͽ����ʶ���Ա�֮������ʩ��������"+kungfu1+"Ϊ"+kungfu2+"��ʹ��$n�ĳ���������"+to_chinese(skill)+"����\n"NOR,me,target);
	else
	   message_vision(HIG"$N�����Ц���ȵ�������ͽ����ʶ���Ա�֮������ʩ������ʹ��$n�ĳ���������"+to_chinese(skill)+"����\n"NOR,me,target);
         me->add_temp("apply/attack", i/3); 
         me->add_temp("apply/damage",i/4);
		 
		 if (!userp(target)) {
		   if (target->is_busy()) target->add_busy(j/100);
		   else target->start_busy(j/100);
		 }
         else 
         { 
			 if (target->is_busy()) target->add_busy(1+random(1));
		     else target->add_busy(1+random(1));
         }
		 
		 message_vision(MAG"$n����$N��Ȼʩչ���Լ��ĳ�����ʽ������һʱ�䲻�������ð��\n"NOR,me,target);

         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>350)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>450)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>550)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 
	

         me->add_temp("apply/attack", -i/3); 
         me->add_temp("apply/damage",-i/4);
 	   
	   message_vision(HIG"$Nʹ��һ�ס�"+to_chinese(skill)+"������ź���һ��������һ�ߣ����¶��һ˿�����Ц�⡣\n"NOR,me,target);
       
	   if( me->query("quest/bishen/pass") && me->query_skill("douzhuan-xingyi",1) > 450 ){
                tell_object(me, HIY"\n�������㰵���߶���Ϣ,˳��ʹ�������ƶ�ת����������\n"NOR);
                me->start_call_out( (: call_other, __DIR__"xingyi","xingyi_hit", me,target, 1 :), 1 );
        }
    	me->delete_temp("bishen_target",target);
        me->delete_temp("bishen_start",1);
    	me->start_perform(4,"�Ա�֮����ʩ����"); 
    return 1;
}

string query_pfm(object me, object target)
{
	object weapon=target->query_temp("weapon");
	//string skill,perform;
	string skill;
	int i;
	string *base_skill=({ "cuff","strike","hand","leg","claw","finger" });
    skill="none";
	if(weapon)
	{
		skill=target->query_skill_mapped(weapon->query("skill_type"));
	}
	else
	{
		for(i=0;i<6;i++)
		{
			if( (skill=target->query_skill_prepared(base_skill[i]) ) ) break;
				
		}
	}
	return skill;
}

string query_sk(object me)
{
	//string skill;
	mapping pmap;
	int i;
	string *base_skill=({ "cuff","strike","hand","leg","claw","finger" });
  
  pmap = me->query_skill_prepare();
  
  if (!pmap) pmap = ([]);
  
  if (!sizeof(pmap))
      return "none";

		for(i=0;i<6;i++)
		{
			if( me->query_skill_prepared(base_skill[i]) ) return base_skill[i];				
		}
		return "none";
}



int help(object me)
{
    write(WHT"\n��ת����֮��"HIG"�Ա�֮������ʩ����"WHT"����"NOR"\n");
         write(@HELP
	���Ա�֮������ʩ������ΪĽ�����ҼҴ���ѧ���ö���
	�ĳ���������������ת���ƴﵽһ���ȼ�ʱ��˳��ʹ����
	һ���������ƶ�ת�������书��Ľ���϶�ת�������߾�ѧ
	��Ҫ��������Ĺ�������ʩչ����Ե�ɺ�֮�£�ͨ����
	�ܷ�����ϰ��

ָ�perform parry.bishen

Ҫ��
	������� 15000 ���ϣ�      
	��ǰ���� 5000  ���ϣ�
	��ת���� 500   ������
	��Ԫ���� 500   ������
	�����ڹ�Ϊ��Ԫ����
	�����м�Ϊ��ת���ƣ�
	δ���侫Ҫʱ��������Է�ͬʱ���ֻ�ͬ��������
	��ѧ��Ϊ��Է�����С�ڶԷ�1/3��
	���ܶ�Ľ�ݵ���ʹ�á�       
HELP
    );
        return 1;
}

