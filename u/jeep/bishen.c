// bishen.c �Ա�֮����ʩ����
// by tiantian@sj
// By Spiderii@ty����
#include <ansi.h>
#include <weapon.h>
#include <combat.h>
string perform_name(){ return HIR"�Ա�֮����ʩ����"NOR; }
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
	/*
       
	if((int)me->query_temp("lianhuan"))

		return notify_fail("������ʹ���߽�����ָ��\n");
	*/

	
	weapon=me->query_temp("weapon");
	weapon2=target->query_temp("weapon");

	if( !me->query("quest/bishen/pass"))
		if ((!weapon&&weapon2) || (weapon&&!weapon2))
		return notify_fail("��ͶԷ��ı�����ͬ������ʹ���Ա�֮����ʩ����\n");
	if( target->query("family/family_name") == "����Ľ��"
	|| target->query_skill("douzhuan-xingyi",1) > 0
	|| target->query_temp("bishen_target"))
		return notify_fail("�㲻����Է�ʹ���Ա�֮����ʩ����\n");
	if(me->query_skill_mapped("force") != "shenyuan-gong")
		return notify_fail("����ڹ�������Ԫ�����޷�ʹ���Ա�֮����ʩ����\n");      
	if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("���мܹ��򲻶�,�޷�ʹ���Ա�֮����ʩ����\n");     
	if((int)me->query("max_neili") < 2500 )
		return notify_fail("��������������ߣ�\n");
	if((int)me->query("neili") < 2500 )
		return notify_fail("�㵱ǰ������������\n");
	if(me->query_skill("douzhuan-xingyi",1)<180 )
		return notify_fail("��Ķ�ת���Ʋ����������������Ա�֮����ʩ����\n");
	if( me->query("combat_exp")<target->query("combat_exp")/2)
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
	me->set_temp("dzxy/bishen", 1);

	if (!userp(target)) {
		if (target->is_busy()) target->add_busy(j/100);
		else target->start_busy(j/100);
	}
	else 
	{ 
		if (target->is_busy()) target->add_busy(1+random(1));
		else target->add_busy(1+random(1));
	}

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	if(objectp(target) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	if(objectp(target) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	if(objectp(target) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	if (me->query("shenyuan/super") && me->query_skill("douzhuan-xingyi", 1) > 449)
	{
		target->set_temp("must_be_hit",1);
		message_vision(MAG"$N���Լ�������ת���Ƶľ���ʩչ����������������ˮ��$n��Ȼ�Է�ʩչ���Լ�����ʽ�������󺧣�"NOR,me,target);
		if(objectp(target) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		target->delete_temp("must_be_hit",1);
	}

	me->add_temp("apply/attack", -i/3); 
	me->add_temp("apply/damage", -i/4);
	me->delete_temp("dzxy/bishen");

	message_vision(HIG"$Nʹ��һ�ס�"+to_chinese(skill)+"������ź���һ��������һ�ߣ����¶��һ˿�����Ц�⡣\n"NOR,me,target);
	if( me->query("quest/bishen/pass") && me->query_skill("douzhuan-xingyi",1) > 450 ){
		tell_object(me, HIY"\n�������㰵���߶���Ϣ,˳��ʹ�������ƶ�ת����������\n"NOR);
		me->start_call_out( (: call_other, __DIR__"xingyi","xingyi_hit", me, 3 :), 1 );
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

	if(weapon)
	{
		skill=target->query_skill_mapped(weapon->query("skill_type"));
	}
	else
	{
		for(i=0;i<6;i++)
			if( (skill=target->query_skill_prepared(base_skill[i]) ) )
				break;
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
		if( me->query_skill_prepared(base_skill[i]) )
			break;

	return base_skill[i];
}

int help(object me)
{
    write(WHT"\n��ת����֮��"HIG"��ʩ����"WHT"����"NOR"\n");
         write(@HELP
        ���Ա�֮������ʩ������ΪĽ�����ҼҴ���ѧ���ö���
        �ĳ���������������ת���ƴﵽһ���ȼ�ʱ��˳��ʹ����
        һ���������ƶ�ת����
             
Ҫ��  ������� 2500 ���ϣ�      
        ��ǰ���� 2500  ���ϣ�  
        �����м�Ϊ��ת���ƣ�
        δ���侫Ҫʱ��������Է�ͬʱ���ֻ�ͬ��������
        ��ѧ��Ϊ��Է�����̫Զ��    
        ���ܶ�Ľ�ݵ���ʹ�á�       
HELP
    );
        return 1;
}

