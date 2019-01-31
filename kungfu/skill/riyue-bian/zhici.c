// This program is a part of XOJH MudLIB
// zhici.c ֱ�̾����������������Ϊǹ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

    //    if (userp(me) && ! me->query("can_perform/riyue-bian/shang"))
      //          return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ��ֱ�̾�����\n");
                 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֱ�̾���ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force",1) < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("riyue-bian", 1) < 200)
                return notify_fail("������±޷���Ϊ������Ŀǰ����ʹ��ֱ�̾���\n");
        if (me->query_skill("buddhism", 1) < 150)
                return notify_fail("������±޷���Ϊ����150��Ŀǰ����ʹ��ֱ�̾���\n");

        if (me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ��ֱ�̾���\n");
        if (me->query("jingli") < 500)
                return notify_fail("��ľ����������޷�ʹ��ֱ�̾���\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷�������ʹ��ֱ�̾���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
		message_vision(HIY "$N" HIY "��Ȼ��Ц�����е�" + weapon->query("name") +
              HIY "һ����ʱ��ñ�ֱ����ͬ����һ��ɴ���$n" + HIY "��\n"
				+"��" + weapon->query("name") +HIY "����һ����ֱ�ı��У��糤ì����˰������̶���!\n" NOR,me,target);


        ap = me->query_skill("whip",1)+me->query_skill("riyue-bian",1);

        dp = me->query_skill("parry",1)+me->query_skill("dodge",1);

		me->add("jingli", -200); 

        if (random(ap)>dp / 3
			||random(me->query_skill("force",1))>target->query_skill("force",1)/2)
        {
               damage = ap+me->query_skill("force",1);
                damage=me->query_str()*damage/20;
				
				me->add("neili", -300); 

				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage/2,me);

				if (me->query("env/damage"))
				{
					tell_object(me,WHT"���"+target->query("name")+"���"+damage+"��ɱ��ֵ!\n");
					tell_object(me,WHT"���"+target->query("name")+"���"+damage/2+"���˺�ֵ!\n");
				}
                message_vision(HIR "ֻ��$p" HIR "һ���ҽУ�" + weapon->query("name") + HIR "��Ȼ����$p" + HIR "�����ϣ�ֱ�ӶԴ���������Ѫ�ɽ����ߣ��Ҳ����ԣ�\n" NOR,me,target);
                                         
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
				message_vision( CYN "����$p" CYN "����������������ס��$P" CYN "�����Ī���һ����\n"NOR,me,target);
                me->start_busy(1 + random(2));

        }
		me->start_perform(3,"ֱ�̾�");

        return 1;
}
string perform_name(){ return HIR"ֱ�̾�"NOR; }

int help(object me)
{
	write(HIC"\n���±ޡ�ֱ�̾�����"NOR"\n");
	write(@HELP
	���±���������������֮һ��������������������֮�����ɸջ�����书
	��ʱ�����ڹ��Դ��������տ�����������������¶��ǵľ��硣Խ��Խ����
	����Խ�̹���Խǿ�����������������շ����ġ����޼ɾ�лѷ�������գ�
	��һ�ֿ�������ɮ����һս��Ȼ�ɾ������޼ɵ���������ͬʱ���������ϵ�
	���±�Ҳ�������¡�
	ֱ�̾�������ǿ���ڹ����˾��ڱޣ���ע���У��п�ɽ��ʯ֮��������Խǿ
	������Խ��,һ�беС�
	
	ָ�perform whip.zhici

Ҫ��	
	��ǰ���� 500 ���ϣ� 
	��ǰ���� 500 ���ϣ� 
	�׽�ȼ� 200 ���ϣ�
	���±޷��ȼ� 200 ���ϣ�
	�����ķ��ȼ� 150 ���ϣ�
	�����޷�Ϊ���±޷���
	�������±޷�Ϊ�мܣ�
	�����׽Ϊ�ڹ���
	װ�������������     
HELP
	);
	return 1;
}



