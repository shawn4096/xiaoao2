// rong.c ��λ�����˹�Ч����������
// By Spiderii@ty �Ӹ�����,��ֹǿ��Ϊ����yun liao.��ɶԷ�busy
// edit by sohu@xojh 2014
#include <ansi.h>

string exert_name() {return HIG"���־�"NOR;}

int exert(object me, object target)
{
        int i,m,j,z;
		i=me->query_skill("kurong-changong",1)+me->query_skill("yiyang-zhi",1);
		m=me->query_skill("medicine",1);
		j=me->query_skill("jingmai-xue",1);
		z=i+m+j;
		if( !objectp(target) )
                return notify_fail("��Ҫ��һ��ָΪ˭���ˣ�\n");

        if(!present(target,environment(me)) )
                return notify_fail("��Ҫ��һ��ָΪ˭���ˣ�\n");

        if (target->is_corpse() || !target->is_character())
                return notify_fail("�ǲ��ǻ���Ү��\n");

        if((int)me->query_skill("force",1) < 150 )
              return notify_fail("���Ǭ��һ����������죬�޷��������ˣ�\n");

        if( me->is_fighting()&& target != me)
                return notify_fail("ս�����޷���������ˣ�\n");

        if( target->is_fighting()&&target != me)
                return notify_fail("�Է�����ս�����޷��������ˣ�\n");
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("���������Ϊ������\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query_skill("medicine", 1) < 80 )
               return notify_fail("���������ҽ��֪ʶ��֪���٣���֪�������? \n");

        if( (int)target->query("eff_qi") >= (int)target->query("max_qi") )
                return notify_fail( target->name() + "��û�����ˣ�\n");
        // By Spiderii@ty �Ӹ�����
        if( target->query("env/no_lifeheal"))
                return notify_fail( target->name()+"�ܾ���������ˡ�\n");
        if (me->is_fighting() && (target==me))
        {
          message_vision(HIY"\n$N�ֱ۲������������ѵ�ˮ��һ����������Լ��ؿڵ�ʮ������Ѩ��������������͸�롣����\n\n"
                         HIM"ֻ��Ƭ��֮�䣬$N��ɫ�����˺���,���ƺö��ˡ�\n" NOR,me);
          me->add("neili",-random(200));
          me->receive_curing("qi",z/10);
          me->add("qi", z/10);
          if( (int)me->query("qi") > (int)me->query("eff_qi") )
			me->set("qi", (int)target->query("eff_qi"));
          if (me->query_skill("kurong-changong",1)<450)
          {
			  me->start_exert(2,"����");
          }
        }
        else
        {
          if (target != me)
            message_vision(HIY"\n$N�������ʳָ��΢һ������������������, ʳָ���Ρ���������Ѩ���˵���������$n�ؿڵ����д�Ѩ�ϣ���������ԴԴ͸�롣����\n\n"
                           HIM"\n$Nͷ��ð��˿˿������$n�о�һ������ƽ�͵�����������ѭ������������һյ��ʱ�֣�$N�ŷſ���ָ��ֻ��Ƭ��֮�䣬$n˫��\n"
                           HIM"�����˺��Σ���ɫ������Ҳ�ö��ˡ�\n" NOR,me,target);
          else
           message_vision(HIY"\n$N�������£�΢һ������ʳָ���Ρ���������Ѩ���˵����ʳָһ�գ����ư����ؿ����д�Ѩ����������ԴԴ͸�롣����\n\n"
                          HIM"$Nͷ��ð��˿˿����������һյ��ʱ�֣��ŷſ���ָ,$N����ɫ������Ҳ�ö��ˡ�\n" NOR,me);
           if(target != me
           && userp(target)
           &&(int)target->query("eff_qi") < (int)target->query("max_qi")/5)
           {
             if(!random(4))
             	me->add("max_neili",-1);
             me->add("yyz_cure",1);
           }
           me->add("neili",-random(400));
           target->receive_curing("qi", z/10);
           target->add("qi", z/10);
           if((int)target->query("qi")>(int)target->query("eff_qi"))
           	target->set("qi", (int)target->query("eff_qi"));
           if(target!=me)
           	me->start_busy(3);
           target->start_busy(3);
        }
        return 1;
}


int help(object me)
{
        write(WHT"\n��������"HIG"�����־�����"NOR"\n");
        write(@HELP
	�����������Ǵ����������Ժ--���������ֿ��ٳ��ϵ��ڹ��ķ�
	�ഫ�����������ڰ˿���֮�䡣��˿����ֶ����ϱ��������÷�
	�У����Ƿֱ���һ��һ�٣������ϱ��ֱ��ǣ������޳���������
	�֣��������ң������޾��� ���������޿����ٷ��Ǵ�ɡ�����
	�������������������һ����ֻ�εð�ݰ��١�
	
	����������������������֮��ת����һ�ŷ��Ÿ߼����������־�
	�ǽ�����������ת������������������Ч�����õ�һ���ڹ���
	���޵�һ��ָ��ѧ��Ч�����ѡ�

Ҫ��:
	�������� 150 �����ϣ�
	������� 2000 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	����ҩ�� 80 �����ϣ�Խ��Ч��Խ�ã�
	�輤���ڹ�Ϊ����������

HELP
        );
        return 1;
}