// xinjing.c 
// By River
// Modified by darken@SJ

#include <ansi.h>
inherit F_CLEAN_UP;
string *pictures=({
  HIY"��˼��"YEL"���"HIC"������"HIR"���¡�"HIB"���"MAG"��Ц"HIW,
  YEL"�ٳ"CYN"���֡�"HIG"��ϲ��"HIR"��ŭ��"HIY"�ٺá�"RED"�ٶ�"HIW,
  HIC"��˼"HIG"��"HIW"�񵡣�"HIB"����"MAG"��"HIY"��ɢ"HIW,
  HIR"����"YEL"��"BLU"����"MAG"����"RED"��"HIG"��ƣ"HIW,
  HIB"����"CYN"��"RED"���٣�"HIR"��Ц"HIC"��"BLU"����"HIW,
  MAG"���"YEL"��"HIR"���壬"RED"����"BLU"��"HIY"����"HIW,
  HIW"��ϲ"HIG"��"HIY"����"MAG"���ң�"HIC"��ŭ"HIR"��"HIB"����"HIG"����"HIW,
  HIG"���"RED"��"BLU"ר��"HIG"���Σ�"HIW"���"HIB"��"MAG"����"CYN"����"HIW
});
string exert_name(){ return HIW"��Ů�ľ�"NOR; }
int exert(object me)
{
        int skill;
        string picture;

        if((int)me->query("neili") < 500 ) 
                return notify_fail("�������������\n");
		if((int)me->query("max_neili") < 1500 ) 
                return notify_fail("����������������\n");
        if((int)me->query_temp("ynxj/xinjing")) 
                return notify_fail("���Ѿ����˹����ˡ�\n");

        if((int)me->query_skill("yunu-xinjing",1 ) < 100)
                return notify_fail("�����Ů�ľ��ȼ����������������ʮ���ٺ�ʮ����֮���\n");
		if((int)me->query_skill("force",1 ) < 100)
                return notify_fail("��Ļ����ڹ��ȼ����������������ʮ���ٺ�ʮ����֮���\n");
        if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("�����ڲ���ʹ�á��ľ����־���\n");

        if( me->query("gender") == "����" )
                return notify_fail("���޸����ԣ������������Ů�ľ��ġ��ľ����־���\n");
                
        skill = (int)me->query_skill("yunu-xinjing", 1);
        if (me->query("quest/jiuyingm/pass"))
        {
			skill=skill+me->query_skill("jiuyin-zhengong",1);
        }
		//if (skill > 250) skill = 250+ (skill-250)/5;
      
		me->add("neili", -(200+ random(200)));
        picture = pictures[random(sizeof(pictures))];
        message_vision(MAG"$N�������񣬿���Ĭ��"HIW"��"+picture+"��"MAG"����Ů�ľ�����Ҫ����\n" NOR, me);
          
        me->add_temp("apply/intelligence", (int)me->query_skill("yunu-xinjing",1)/10);
        me->add_temp("apply/dexerity", skill/5);

        //350С�ɣ���������
		if (skill > 350) {
          me->add_temp("apply/attack", skill/5);
        }
		if (skill > 450) {
          me->add_temp("apply/defense", skill/10);
        }
		//��Ů�ľ���һ��
		if (me->query("quest/gumu/ynxj/pass") )
		{
			message_vision(HIM"$N��Ů�ľ���ת������������ӿ��,��ɫһƬ�κ�,��������,�����γ�һ��������������\n"NOR,me);
			me->add_temp("apply/dodge", skill/5);
            me->add_temp("apply/parry", skill/5);
            me->add_temp("apply/armor", skill/5);
		}
		//��Ů�ľ��ڶ���
		if (me->query("quest/jiuyingm/pass"))
		{
          
		  me->add_temp("apply/attack", skill/5);
          me->add_temp("apply/damage", skill/8);
		  me->add_temp("apply/whip", skill/5);
		  me->add_temp("apply/sword", skill/5);
		  message_vision(HBMAG+HIW"$N�Ѿ�����Ů�ľ��;����澭�ںϹ�ͨ����Ů�ľ����������˷��ԡ�\n"NOR,me);
		}        

        me->set_temp("ynxj/xinjing", skill);
		call_out("remove_effect",1,me,(int)skill/10);
        
		if( me->is_fighting() 
			&& userp(me)
			&& me->query_skill("yunu-xinjing",1)<500)
			me->start_busy(1+random(2));
        if ( !me->query("quest/gumu/ynxj/pass")) 
			me->start_exert(2,"���ľ����־�");
        return 1;
}

void remove_effect(object me, int count)
{       
    int skill;
	if(!me || !objectp(me)) return;
	skill = me->query_temp("ynxj/xinjing");
    
    if (count < 1 || me->query_skill_mapped("force")!="yunu-xinjing")
    {	    
        me->add_temp("apply/intelligence", -(int)me->query_skill("yunu-xinjing",1)/10);
        me->add_temp("apply/dexerity", -skill/5);
        if (skill > 350)
        {
            me->add_temp("apply/attack", -skill/5);
        }
		if (skill > 450)
        {
            me->add_temp("apply/defense", -skill/10);
        }
		if (me->query("quest/gumu/ynxj/pass"))
		{
			me->add_temp("apply/dodge", -skill/5);
            me->add_temp("apply/parry", -skill/5);
            me->add_temp("apply/armor", -skill/5);
		}
        if (me->query("quest/jiuyingm/pass"))
		{
			me->add_temp("apply/attack", -skill/5);
			me->add_temp("apply/damage", -skill/8);
			me->add_temp("apply/whip", -skill/5);
			me->add_temp("apply/sword", -skill/5);
			
		}
        me->delete_temp("ynxj/xinjing");
        if (me->query("quest/jiuyingm/pass"))
			tell_object(me, HBMAG+HIW"�����Ů�ľ����ľ����־��˹���ϣ��������ջص��\n"NOR);
		else tell_object(me, HIM"�����Ů�ľ����ľ����־��˹���ϣ��������ջص��\n"NOR);
		return;
    }
	count=count-1;
	call_out("remove_effect", 2, me, count);
	return;
}

int help(object me)
{
        write(HIW"\n��Ů�ľ�֮"HIY"���ľ�����"NOR"\n");
        write(@HELP
	�ֳ�Ӣ�������������߾����ǣ��о����˿���
	ȫ�����书�ġ���Ů�ľ����������������һ
	�����������˲�����У�Ҫ�������һ������
	���˷�ʹȫ�潣������Ů�����໥ӦԮ���ֽ�
	�ϻ������ն�����߰���Ⱥ���Ը�δ�ܳ�����
	�أ������ֳ�Ӣ���ս�ΪŮͽ����Ҫ��������
	��������Ĺ��������һ���Ӹ�ԸΪ���׳���
	�������Է��ơ���ˣ���Ĺ�����书��ǿ��ȴ
	δ���������֣��������ס��Ĺ����Ī������
	�����Գ�ʦ��Ϊ��Ĺ�ɡ�
		
	��Ĺ����Ů����������֮��ʮ���٣�ʮ���ࡱ��
	��Ҫ��������˼��������������¡������
	Ц���ٳ���֡���ϲ����ŭ���ٺá��ٶ�
	�д�ʮ���٣�������֮����Ҳ����˼���񵡣�
	������ɢ�����������𣬶�������ƣ����
	�������٣���Ц����ˣ���������壬����
	�����磬��ϲ��������ң���ŭ�����������
	�����ר�Բ��Σ�����򽹼���������ʮ��
	�಻����ɥ��֮��Ҳ��
	
	��Ĺ����ȫ���书ϵ���ڹ�����Ů�ľ��ܹ�
	��Ϊ���䣬���ڼ�����С�ɺʹ�ɲ�����ǿ
	���кͷ������ڶ��俪ʼ��Ů�ľ�Ů�Ե���
	�Ƶ��Է��ӣ������������Ů�ľ���������
	�����ͷš�500�����״�ɣ��⿪�ڶ��䣬ȡ
	������busy��
	
	ָ�yun xinjing
	
Ҫ��
	��Ů�ľ��ȼ� 100 �����ϣ�
	�����ڹ��ȼ� 100 �����ϣ�
	�������Ҫ�� 1500 ���ϣ�      
	��ǰ����Ҫ�� 500  ���ϣ�
			    
                
HELP
        );
        return 1;
}