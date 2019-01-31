// roar.c for xixin-dafa by sohu@xojh

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
		skill = me->query_skill("yijin-jing",1);
        if( me->query("yjj/powerup") !="pass" )
             return notify_fail("��ֻ����˵���׽,���޷���ʹ����ʨ�Ӻ��񹦡�\n");
        if (me->query_skill_mapped("force") != "yijin-jing" )
             return notify_fail("����ʹ�õ������ڹ����ԣ��޷�ʵ���׽��֮��ʨ�Ӻ𡿡�\n");  
		if( (int)me->query_skill("yijin-jing",1) < 500 )
                return notify_fail("����׽����������\n");
		if( (int)me->query_skill("force",1) < 500 )
                return notify_fail("��Ļ����ڹ�������\n");
		if( (int)me->query("max_neili") < 10000 )
                return notify_fail("����������������\n");
		if( (int)me->query("neili") < 5000 )
                return notify_fail("��ĵ�ǰ����������\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("��ľ���������\n");     
	    if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 190);

        me->start_busy(1+random(4));
        message_vision(HBRED+HIY "$N�������һ�������������ʨ�Ӻ���ų��շ���һ�����춯�صĳ�������ʨХ���֡�\n�����ж�ʱ�������춯�ص����˻���.........\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ||ob[i]->query("no_pk")) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query("con") * 2 ) continue;
                                
				damage = (me->query("neili")-ob[i]->query("neili"))*skill/5;
                if( damage > 0 ) {
					    ob[i]->start_busy(2+random(4));
						ob[i]->apply_condition("no_perform",1+random(2));
						ob[i]->apply_condition("no_exert",1+random(2));
						if (damage>8000) damage=8000+(damage-7000)/10;
					
                        ob[i]->receive_damage("qi", damage);
						ob[i]->receive_damage("jing", damage/3);
                        if( (int)ob[i]->query("neili") < skill * 2 )
                                ob[i]->receive_wound("qi", damage/2,me);
                        tell_object(ob[i],HIR "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n"NOR);
                }
                
                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        }
		me->start_exert(4+random(2));
        return 1;
}

string exert_name(){ return HIR"����ʨ�Ӻ�"NOR; }
int help(object me)
{
        write(HIR"\n�׽��"+HIY+"������ʨ�Ӻ�"NOR"\n");
        write(@HELP
		����ʨ�Ӻ�,�����������ش�ϡ���湦֮һ,�˹�Ϊ���嵤�������ⷢ,��������
		֮����,����֮�����н���,������Х,������Ѷ�׼�к��������֮��,��иε���
		��,�ľ���ս,ë���Ȼ,����һ����Х��ʹ���ֲ�ս���ܡ�
		������ʨ�Ӻ𡿴˹���Դ��<<ʨ�Ӿ�>>,ԭ����ʦ���ȷ���˵����ʨ������������
		�Ĳ���˼��֮����.����������ʦ�ǵĲ�������,���һ�ſ˵о�����
		Ҫ��
			�����ڹ��ȼ� 500 ���ϣ�
			�׽���ȼ� 500 ���ϣ�
			�������     10000 ���ϡ�
			��ǰ����     5000 ���ϡ�
			��ǰ����     3000 ���ϡ�
HELP
        );
        return 1;
}
