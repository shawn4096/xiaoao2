// roar.c for xixin-dafa by sohu@xojh

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
		skill = me->query_skill("xixing-dafa",1);
        if( me->query("quest/xxdf/pass") <2 )
              return notify_fail("�㵱ǰ�Ĺ����޷���ʹʨ�Ӻ���������û�����������Դ��ڷ��ɡ�\n");
        if (me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԣ��޷�ʵ�����Ǵ�֮��ʨ�Ӻ𡿡�\n");  
		if( (int)me->query("max_neili") < 10000 )
                return notify_fail("����������������\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("��ľ���������\n");     
        if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        me->add("neili", -300);
        me->receive_damage("qi", 190);

        me->start_busy(5+random(2));
        message_vision(HIY "$N�������һ�������������Ǵ󷨶���$n���һ����\n��ʱһ���춯�صľ޺�����$n�о������ܵ�����̼���\n" NOR, me,target);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ||ob[i]->query("no_pk")) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query_con(1) * 2 ) continue;
                                
				damage = (me->query("neili")-ob[i]->query("neili"))*skill/10;
                if( damage > 0 ) {
					    ob[i]->start_busy(1+random(2));
						if (damage>4000) damage=4000+(damage-4000)/100;
					
                        ob[i]->receive_damage("qi", damage,me);
                        if( (int)ob[i]->query("neili")*3/2 < (int)me->query("neili")  )
                             ob[i]->receive_wound("jing", damage/8,me);
                        tell_object(ob[i],HIR "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n"NOR);
                }
                
                if( userp(ob[i]) ) 
			    {
					ob[i]->fight_ob(me);
					me->kill_ob(ob[i]);
				}
                else if( !userp(ob[i])&&!ob[i]->is_killing(me) ) ob[i]->kill_ob(me);

        }
        return 1;
}

string exert_name(){ return HIY"��ʨ�Ӻ�"NOR; }
int help(object me)
{
        write(HIR"\n���Ǵ�"+HIY+"��ʨ�Ӻ�"NOR"\n");
        write(@HELP
		���Ǵ������������ǰ���������е��ش��似���뵱����������������񼼣�
		��һΪ�������䣬���Ϊ���Ǵ󷨣�ǰ������������λʱѡ����ϰ���Ǵ󷨡�
		��Ȼ�����ݺ��������ܵ����ɣ������Ǵ󷨵Ĺ����ǿ��Ҳ����ѡ�����Ҫԭ��
		�����ڣ�������Ϊ̸֮��ɫ�䡣����������������һս�������Ǵ��س�����
		�ɼ�������������
		��ʨ�Ӻ𡿾���������Դ����������÷ׯ������ƾ��һ����ȫ��һ��������
		�����������˵��似���ǹ�������߲���ʹ�á�
		Ҫ��
			�����ڹ��ȼ� 450 ���ϣ�
			���Ǵ󷨵ȼ� 450 ���ϣ�
			�������     8000 ���ϡ�
			��ǰ����     10000 ���ϡ�
			�����     5000 ���ϡ�
			��ǰ����     3000 ���ϡ�
HELP
        );
        return 1;
}
