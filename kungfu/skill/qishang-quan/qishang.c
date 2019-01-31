// qishang.c 
// Update By lsxk@hsbbs 2007/6/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_effect(object me,int count);
int remove_effect(object me,int count);

string *songs = ({"����֮��������","�����˷δݸγ�","���뾫ʧ����","������������Ƿ���"});
string *num_color = ({HIR,HIC,HIG,HIM,HIY,HIB,HBRED});


int perform(object me, object target)
{
	string song,ncolor;
	int skill;

	song = songs[random(sizeof(songs))];
	ncolor=num_color[random(sizeof(num_color))];

	skill=me->query_skill("qishang-quan",1);
	
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) || !living(target) )
		return notify_fail("�������ܾ���ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������ʹ�á������ܾ�����\n");

   if( (int)me->query_skill("qishang-quan",1) < 500 )
		return notify_fail("�������ȭ������죬����ʹ�á������ܾ�����\n");
   if( !me->query("quest/mj/qsq/zongjue/pass"))
		return notify_fail("�������ȭ��δ�ڻ��ͨ������ʹ�á������ܾ�����\n");

   if(!me->query_skill("jiuyang-shengong", 1) || (int)me->query_skill("jiuyang-shengong",1)< 200 )
   if(userp(me) && (int)me->query_skill("force",1) < 500 )
           return notify_fail("��������ڹ��ȼ�����������ʹ�á������ܾ�����\n");
   if( (int)me->query_con(1) < 38 )
		return notify_fail("���������ǲ���ǿ׳������ʹ�á������ܾ�����\n");

   if( (int)me->query("max_neili") < 9000 )
		return notify_fail("�������̫��������ʹ�á������ܾ�����\n");

   if( (int)me->query("neili") < 1500 )
		return notify_fail("�������̫���ˣ��޷�ʹ�ó��������ܾ�����\n");

   if( (int)me->query("jingli") < 1000 )
		return notify_fail("��ľ���̫���ˣ��޷�ʹ�ó��������ܾ�����\n");
	if( me->query_skill_mapped("parry") != "qishang-quan"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("����Ҫ�����м�Ϊ����ȭ������ʹ�á������ܾ������й�����\n");

	if (me->query_skill_prepared("cuff") != "qishang-quan"
	 || me->query_skill_mapped("cuff") != "qishang-quan")
           return notify_fail("�㼤�����ԣ������޷�ʹ�á������ܾ������й�����\n");

    if(me->query_temp("qsq/qishang"))
           return notify_fail("������ʩչ�������ܾ��������÷Ѿ��ˣ�\n");

	message_vision(HIY"\n$N˫�ųʶ��ֲ�վ����������ˮ��ĳ���һ������ʩչ������ȭ����"+HBRED+HIY"�������ܾ���"HIY"��\n"NOR,me);
	message_vision(WHT"$N���侫�⣬����������Ƹ�Ǹ衢��ʫ��ʫ��ȭ������"+ncolor+song+WHT"�������һȭ����$n��ǰ�أ�\n"NOR,me, target);

	if (random(me->query_str())>target->query_dex()/2)
	{
		target->add_busy(1+random(3));
		message_vision(YEL"$n�����߹ɾ������У����ɵ�����һ�ᣬ˲����Щ�ֽ�æ�ң�\n"NOR,me,target);
	}
  
	
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/6);
	me->add_temp("apply/cuff",skill/6);
	me->add_temp("apply/strength", skill/8);
	
	me->set_temp("qsq/qishang",skill);
	
	remove_effect(me,(int)skill/50);
//���ö��⹥��
	
	call_out("qishang_attack",1+random(1),me,target);

    me->add("neili",-400);
	me->add("jingli",-300);
	return 1;
}
//�ܾ�Ч��

int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("qsq/qishang");
	if (!me->is_fighting()
		||count<0
		||me->query_skill_prepared("cuff")!="qishang-quan"
		||me->query_skill_mapped("cuff")!="qishang-quan")
	{
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/cuff",-skill/6);
		me->add_temp("apply/strength", -skill/8);

		me->delete_temp("qsq/qishang");
		message_vision(HIY"$N��ɫ���죬����һ�����������������궯��������\n"NOR,me);
		return 1;
	}

	call_out("remove_effect",1,me,count--);
	
}

int qishang_attack(object me,object target)
{

	int ap,dp,damage,qi_wound;
	string msg;
	
	if (!me||!target) return 0; 

	ap=me->query_skill("qishang-quan");
	dp=me->query_skill("dodge");
   
    if(target->is_busy()) dp=dp/2;
	if (me->query_skill_prepared("cuff")!="qishang-quan"
		||me->query_skill_mapped("cuff")!="qishang-quan")
	{
			return 0;
	}
	//tell_object(me, num_color[(int)target->query_temp("qishang")]+"�ڸ�һ����"+target->name(1)+"������ʱ����㰵����������������ȭ�ڵĵ�"+HIW+chinese_number(1+(int)target->query_temp("qishang"))+NOR+num_color[(int)target->query_temp("qishang")]+"���ھ����˹�ȥ��\n"NOR);

	tell_object(me, num_color[random(sizeof(num_color))]+"����ȭȭ�����ͣ���������"+target->query("name")+"�����壬��㰵����������������ȭ�ڵĵ�"+HIW+chinese_number(1+(int)target->query_temp("qishang"))+NOR+num_color[random(sizeof(num_color))]+"���ھ����˹�ȥ��\n"NOR);

	
	if ( random(ap + dp ) > dp/2
		||random(me->query_str())>target->query_dex()/2)
	{
        qi_wound = ((int)me->query_skill("cuff",1)+(int)me->query_skill("qishang-quan",1)) ;
        
		if(wizardp(me)) write("damage is :"+qi_wound+"!\n");
		
		target->receive_damage("qi", qi_wound, me);
		target->receive_wound("qi", qi_wound/2, me);
		target->add_busy(1);
        
		if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+qi_wound+ WHT"�㹥���˺���\n"NOR);
		
		if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+qi_wound+ WHT"���˺���\n"NOR);
		if((me->query("neili") + me->query_con(1)*(20+random(40))) < target->query("neili"))
			tell_object(me, HIR"��ֻ��"+target->name()+"����������ǿ���㰵����ȭ�ڵĸ������������Ͳ���ȥ��\n"NOR);
		else{
			damage = target->query_str(1)/2;
			damage += target->query_int(1)/2;
			damage += target->query_con(1)/2;
			damage += target->query_dex(1)/2;
                   damage /= 8;
                   tell_object(target, HIW"��һ���ۣ�ֻ��"+me->name(1)+"��ȭ�Ѿ�����������ϣ�����һ��˵�����İ���˳�ƴ��˹�����\n"NOR);
			me->add("neili", -400);
			me->add("jingli", -50);
			me->start_perform(1, "�������ܾ���");
			target->set("qishang", damage);
            if(!target->query_temp("qishang"))
			{
				target->add_temp("apply/strength", -damage);
				target->add_temp("apply/dexerity", -damage);
				//target->add_temp("apply/intelligence", -damage);
				target->add_temp("apply/constitution", -damage);               
                target->add_condition("no_perform", 6);
				target->set_temp("qishang",damage);
				//������� by renlai
				if (QUEST_D->queryquest(me,"was/save")) 
				{
		              target->set_temp("qszj",1);
					  target->add_condition("qishang_poison", 20);
		              message_vision(RED"$N������������ά�����ش������˾����Բ�ȫ��$n����ɾ������У������ڸ������ܴ���\n"NOR,me,target);
	            }
				else  target->add_condition("qishang_poison", 9);
						
				target->start_call_out( (: call_other, __FILE__, "remove_qishang", target ,damage :), me->query_skill("cuff", 1)/4);
            }
              target->add_temp("qishang", 1);
		}
		
	}
	else {
		me->start_busy(1+random(2));
		me->add("neili", -150);
		me->add("jingli", -200);
		message_vision(YEL"ֻ��$p����һת���Ѿ��Ƶ���$P��󡣶�$Nȴ������ղ��ܿ��ƣ�ͷ��ѣ�Σ�\n"NOR,me,target);
	}
	return 1;


}

void remove_qishang(object target,int damage)
{
	if( !target || !target->query_temp("qishang")) return;
	
	target->add_temp("apply/strength", damage);
	target->add_temp("apply/dexerity", damage);
	//target->add_temp("apply/intelligence", damage);
	target->add_temp("apply/constitution", damage);
	target->clear_condition("no_perform");
	target->delete_temp("qishang");
	tell_object(target, HIW"\n���������Ǽ�������ȭ�İ����ڱ鲼���ȫ��֮�󣬿�ʼ����ɢȥ�ˡ�\n"NOR);
}

string perform_name(){ return HBWHT+HIB"�����ܾ�"NOR; }

int help(object me)
{
	write(HIR"\n����ȭ֮�������ܾ���"NOR"\n");
	write(@HELP
	ԭ��Ϊ����ɴ����书���������̽�ëʨ��лѷ���
	������ȭ�ס��ų������������ɡ���ȭ����ȭʱ����
	�Ӻգ�һȭ�����߹ɲ�ͬ�ľ���������͡������ᡢ
	��������ᣬ�������иգ���������ֱ�ͣ�������
	���˵ֵ���ס��ԴԴ�����ľ���������������ˡ�л
	ѷ���Դ�ȭ����������ɮ�ռ���ʦ����������ȭ����
	����δ�黯���������������Լ����м����˺�������
	����������������ľˮ�������У�һ�����ˣ����߽�
	�ˡ�������ν�����ˡ����������˼��������ˡ�
	�������ܾ���������ȭ���ܸ٣���������ʩչ����
	һ��������˵У���Ч��ѹ�Է��ķ�����ͬʱҲ���
	ʱ���������Լ���ȭ��ս������
	ע�⣺����ȭ�⿪Ǭ����Ų���ںϺ;����񹦺���
	�ұ����书����лѷ͵������似�����豾���ڹ�
	
	ָ�perform cuff.qishang

Ҫ��
	����������� 9000 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 1500 ���ϣ�
	����ȭ���ȼ� 500 ���ϣ�
	�����ڹ��ȼ� 500 ���ϣ�
	������������ 65 ���ϣ�
	����ȭ��Ϊ����ȭ��
	�����м�Ϊ����ȭ��Ǭ����Ų�ƣ�
	��ȭ��Ϊ����ȭ�ҿ��֡�
HELP
        );
        return 1;
}
