// jiangmang.c ��â
//cre buy sohu@xojh 2014/10
//����108���н�����书��д�����뵽ljg����������

#include <ansi.h>
#include <combat.h>     
#include <weapon.h>
inherit F_SSERVER;

string *name1 = ({
        "����Ѩ",
        "���Ѩ",
        "����Ѩ",
        "����Ѩ",
        "����Ѩ",
        "�Ϲ�Ѩ",
        "���Ѩ",
        "�ٻ�Ѩ",
        "̫��Ѩ",
        "��ǿѨ",
        "��̨Ѩ"
});

void check_fight(object me, object target,object weapon, int amount);

int perform(object me, object target)
{       
        string msg, name, name2;
        int ap, dp,skill,amount;
        object weapon = me->query_temp("weapon");
        skill=me->query_skill("tianyu-qijian",1);
		amount=(int)skill/10;
        if (! target) target = offensive_target(me);
 
        if (! target || ! target->is_fighting(me))
                return notify_fail("����â��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        
        if (userp(me) && !me->query("quest/ljg/tyqj/jianmang/pass"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ����â����\n");
	
         if (me->query_temp("tyqj/jianmang"))
                return notify_fail("������ʹ�á���â�����������ˡ�\n");
                
        if (target->query("qi") <= 50)
                return notify_fail("������û�б�Ҫ�á���â�����������ˡ�\n");

        if (! weapon || weapon->query("skill_type") != "sword"
        ||  me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("�������޷�ʹ�á���â���������ˡ�\n");

      

        if ((int)me->query_skill("tianyu-qijian", 1) < 350 
            || (int)me->query_skill("sword", 1) < 350
            || (int)me->query_str() < 50 
            || (int)me->query_dex() < 50)  
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á���â����\n");

        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("��Ļ����ڹ���Ϊ�������޷����򡸽�â���ľ��衣\n");


        if ((int)me->query("max_neili") < 5000)
                return notify_fail("�������̫�����޷�ʹ�ó�����â����\n");
        
        if ((int)me->query("neili") < 1500)
                return notify_fail("�������������\n");
                
        name = name1[random(sizeof(name1))];    
        name2 = weapon->query("name");

        message_vision(HIG "\n$N���ֽ���һת�����ӵ�����Ĵ��˰��Ȧ�ӣ�����" + name2 + HIG "һͦ��������ͻȻ����������²�������â!\n" +
              HIG "�����â���Ƴ��߰�����������$N��¶��Ц����������һ����������âͻʢ����$n�ؿڴ�����\n" NOR,me,target);
        me->add("neili", -200);
		me->add("jingli", -200);
		//weapon->set_temp("tyqj/jianmang",1);

        ap = me->query_skill("sword",1);
        dp = target->query_skill("dodge",1);
                   
       if (random(ap+dp) > dp 
			||random(me->query_skill("force",1))>target->query_skill("force",1)/2 )
        {                
                message_vision(HIR "\n\n�������������"+HIY+name+HIR"��$nֻ����ȫ������ͨ���������������ܸ��ӣ�\n"NOR,me,target);   
                if (!userp(target))
					target->add_busy(2 + random(4));
				else target->add_busy(2);
                
			
                me->set_temp("tyqj/jianmang", 1);
				me->add_temp("apply/sword",skill/5);
				me->add_temp("apply/attack",skill/4);
				me->add_temp("apply/damage",skill/10);
				call_out("check_fight",1,me,target,weapon,amount);
          
        } else 
        {
                me->start_busy(2);
                me->add("neili", -100);
                target->add("neili", -100);
                message_vision(HIY"\n$p���һ�����ã�ȫ������һ�ݣ�˳�����˿�ȥ��\n" NOR,me,target);
        }    
       
        return 1; 
}
void check_fight(object me, object target,object weapon, int amount)
{
        object weapon1;
		int skill,damage;
		
		if (!me) return;
		skill=me->query_skill("tianyu-qijian",1);
		weapon1=me->query_temp("weapon");
		damage=(int)skill*me->query_skill("force",1)/100;
		/*
		if (weapon1->query("id")!=weapon->query("id")
			||weapon1->query("name")!=weapon->query("name")
			||weapon1->query_temp("tyqj/jianmang")
			||weapon->query_temp("tyqj/jianmang"))
		{
			me->add_temp("apply/sword",-skill/5);
			me->add_temp("apply/attack",-skill/4);
			me->add_temp("apply/damage",-skill/10);
			me->delete_temp("tyqj/jianmang");
			weapon->delete_temp("tyqj/jianmang");
			message_vision(HIC"$N�����е�"+weapon->query("name")+HIC"���˸�����������һ����������â����ʧ��",me);
			return;
		}*/

        if ( amount<1 || !me->is_fighting())
        {
			me->add_temp("apply/sword",-skill/5);
			me->add_temp("apply/attack",-skill/4);
			me->add_temp("apply/damage",-skill/10);
			me->delete_temp("tyqj/jianmang");
			//weapon->delete_temp("tyqj/jianmang");
			message_vision(HIG"$N�����е�"+weapon->query("name")+HIG"���˸�����������һ����������â����ʧ��\n"NOR,me);
			return;
                
        }
		if (random(10)>5)
		{
			switch (random(2))
			{
				case 0:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIR"$N��һ������ȫ������;�޷����У�ˢ��һ���죬��������$n���������$n���ۡ���һ������һ����Ѫ��\n"NOR,me,target);
						target->receive_damage("qi",damage,me);
						target->receive_wound("qi",damage/4,me);
					}
					break;
				case 1:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIY"$N"+weapon->query("name")+HIY"������һ�С������®��������һ�С�����ãã�������л�һ����$n��ȥ��Ҫ��$nȦ�ڽ���֮�С�\n"NOR,me,target);
						target->add_busy(2);
					}
					break;
				case 2:
					if (objectp(target)&&me->is_fighting()) {
						message_vision(HIW"$N��$n����Ƭ�̣�����ʮ�ּ����ͻȻ��ˢ��һ�����Ӷ�"+weapon->query("name")+HIW"�����������������ͼ������졣\n"NOR,me,target);
						message_vision(HIW"����һ����֮�䣬$N���������������������Ľ�����$n�Խ�����һ���������֡�\n"NOR,me,target);
						
						COMBAT_D->do_attack(me, target,weapon, 3);
						COMBAT_D->do_attack(me, target,weapon, 3);
						
					}
					break;
				default:break;

			}
		}
		call_out("check_fight",2,me,target,weapon,amount-1);
		return;
}
string perform_name(){ return HIC"��â"NOR; }

int help(object me)
{
    write(WHT"\n�����潣֮��"HIC"��â"WHT"����\n");
         write(@HELP
	�����潣������ɽͯ�Ѿ�ѧ֮һ������ɽ��
	ԨԴ����ң��������أ��������֧֮һ��
	���������潣���⾳������Ȼ�����Ʈ��֮
	�⣬���Ʒ����Ƶ���������ȴ�̲�����ɱ��
		 
	�����潣֮��â��������������һ����˵�
	�����ǵ���˼���룬�ɽ���׿���������ж�
	��ɣ��������潣�Ŀ��顢������֣���Ҫ
	�õ�����׿�����Ĵ��ڷ���ʹ�á�
	
	perform sword.jianmang

Ҫ��
	�����ڹ��ȼ� 350 ����;
	�����潣�ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�����Ṧ�ȼ� 350 ���ϣ�
	����������� 5000 ����
	��ǰ�������� 1500  ����
	��ǰ�������� 1000  ����
	��������Ϊ�����潣��
	�����м�Ϊ�����潣��
	�ֳֽ���������
HELP
    );
        return 1;
}
 