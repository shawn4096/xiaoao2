// douzhuan.c ��ת

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int i;

      //  if (userp(me) && ! me->query("quest/mr/syg/douzhuan/pass"))
        //        return notify_fail("����ʱ������ʹ�ö�ת����\n");

        me->clean_up_enemy();
        
		if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����ת����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (me->query_skill_mapped("force")!="shenyuan-gong")
                return notify_fail("��ļ����ڹ�����Ľ����Ԫ��������ʹ�����ƾ��С�\n");
		if (me->query_skill_mapped("parry")!="douzhuan-xingyi")
                return notify_fail("��ļ����мܲ��Ƕ�ת���ƣ�����ʹ�����ƾ��С�\n");

        if ((int)me->query_skill("douzhuan-xingyi", 1) < 450)
                return notify_fail("��Ķ�ת��������죬����ʹ�þ��С�\n");
        if (!me->query("quest/mr/dzxy/pass"))
                return notify_fail("����ת������Ľ�ݾ����似����ֻ��˵����������Ľ����ү����̣�����ʹ�þ��С�\n");

        if ((int)me->query_skill("shenyuan-gong", 1) < 450)
                return notify_fail("�����Ԫ����Ϊ�������ң�"
                                   "�������á���ת������\n");

        if (me->query("neili") < 5000)
                return notify_fail("�����������������޷�ʹ�á���ת������\n");

        if (!living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
		
		if (me->query("max_neili")<9000)
                return notify_fail("�����������������޷�ʹ�á���ת�������С�\n");
		if (me->query("neili")<5000)
                return notify_fail("��ĵ�ǰ�����������޷�ʹ�á���ת�������С�\n");
		if (me->query("jingli")<1000)
                return notify_fail("��ĵ�ǰ�����������޷�ʹ�á���ת�������С�\n");

		if (me->query_temp("syg/douzhuan"))
                return notify_fail("��������ʹ��ת�����޷�����ʹ�á���ת�������С�\n");

        weapon = target->query_temp("weapon");
        
		if (weapon && weapon->query("id") == "zhen")
                return notify_fail("�Է������õ���һ��СС���룬"
                                   "��û�а취ʩչ����ת������\n");
		
        msg = HIM "$N" HIM "����ת����ת�����ķ�������������Ѩ��������"
              "�ζ����������������γ����������ǣ����$n" HIM "����ʽ��\n";

        ap = me->query("combat_exp")/100000; 
        dp = target->query("combat_exp")/100000;

        der = 0;
        me->add("neili", -500);
		me->add("jingli", -500);
		
		me->set_temp("syg/douzhuan",1);
        if (random(ap) > dp/2)
        {
                // Success to make the target attack hiself
                msg += HIR "���$p" HIR "һ�л��������ô����Լ���"
                       "Ҫ���ϣ�����һ���ҽУ�ˤ����ȥ��\n" NOR;
                damage = target->query("max_qi");
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
        } else
        if (ap * 11 / 20 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "Ȼ��$p" CYN "�ڹ���񣬲�û�б�$P"
                       CYN "������ľ�����������\n" NOR;
				me->add_busy(1);
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "���$p" HIC "����ʽĪ������ı�"
                       "�˷��򣬾�Ȼ���Ʋ�ס���Һ����û�б�"
                       "�ˣ�û����ɴ����\n" NOR;
        } else
        {
                string name;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                name = der->name();
                if (name == target->name()) name = "��һ��" + name;
                msg += HIG "���$p" HIG "��������ʽ��������"
                       "�ı��˷���ͻȻ����" + name + HIG "��������" + 
                       name + HIG "���һ�����мܲ�����\n" NOR;
				//der->add_busy(1);
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                
				for (i = 0; i < 1 + random(3); i++)
                {
                        if (!der->is_busy()) der->add_busy(1);
                        COMBAT_D->do_attack(der, der, der->query_temp("weapon"),3);
                }
        }
		//�⿪��ת���ƾ�������
		if (!me->query("quest/mr/dzxy/pass"))
			me->start_exert(1, "��ת��");
		call_out("xingyi_back",3,me);
        return 1;
}
int xingyi_back(object me)
{
	if (!me) return 1;
	
	me->delete_temp("syg/douzhuan");
	message_vision(HIM"$N����ת������֮��ת�������չ���\n"NOR,me);
	return 1;

}
string exert_name(){ return HIC"��ת��"NOR; }

int help(object me)
{
    write(WHT"\n��ת����֮��"HIC"��ת��"WHT"����"NOR"\n");
         write(@HELP
	����ת���ơ���ΪĽ�����ҼҴ���ѧ���������������ŶԷ�
	����ʽ���������й������������ָ��ĵ��ˡ���ת���Ƕ�ת
	���ƵĻ����ķ������֣���˵�дﲻ�����Ա�֮������ʩ����
	�Ķ��򷴻����������Ե����г��䲻���Ч����������Ҫ��Ľ
	�ݲ���̣����ܶ�ת���ƾ�������ʹ�á�
	ע�⣺�������������޷�ʹ�ô˾���

ָ�exert douzhuan

Ҫ��
	������� 9000 ���ϣ�      
	��ǰ���� 5000 ���ϣ�  
	��ǰ���� 1000 ���ϣ�
	��ת���� 450  ���ϣ�
	��Ԫ���� 450  ���ϣ�
	�����м�Ϊ��ת���ƣ�
	�����ڹ�Ϊ��Ԫ����

HELP
    );
        return 1;
}
