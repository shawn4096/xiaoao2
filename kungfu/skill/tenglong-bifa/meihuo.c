//meihuo.c �Ȼ�
//cre by sohu@xojh 
//����ذ�׶�λŮ�Զ�����������Ů�Դ�����ģ��Դ�����ذ�������к�ͻϮ

#include <ansi.h>
#include <combat.h>
//#include <combat_msg.h>

inherit F_SSERVER;

string perform_name() {return HBYEL"�Ȼ�"NOR;}

int perform(object me, object target)
{
	    object weapon;
        int ap,dp,skill; 
		weapon=me->query_temp("weapon");
        skill=me->query_skill("tenglong-bifa",1);

		if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("���Ȼ�ֻ����ս��ʱʹ�ã�\n");

        if( !weapon || weapon->query("skill_type")!="dagger")
                return notify_fail("���������ذ�ײ����á��Ȼ󡿣�\n");
		if( !me->query("quest/sld/tlbf/meihuo/pass"))
                return notify_fail("��ֻ��֪�������ž����������޷����á��Ȼ󡿣�\n");
		if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou" )
                return notify_fail("��û�����ұ����߲�˿�֣������޷�ʹ�á��Ȼ󡿽��й�����\n");  

        if( (int)me->query_skill("chansi-shou", 1) < 350 )
                return notify_fail("��Ĳ�˿�ֻ���������������ʹ�á��Ȼ󡿣�\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("ֻ��ʹ�ò�˿��ʱ����ʹ�á��Ȼ󡿣�\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 350 )
                return notify_fail("��������ȷ�����������������ʹ�á��Ȼ󡿣�\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�á��Ȼ󡿣�\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 350 )
                return notify_fail("�������ذ������������������ʹ�á��Ȼ󡿣�\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á��Ȼ󡿣�\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("��Ķ����󷨹������㣬�����á��Ȼ󡿡�\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á��Ȼ󡿣�\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á��Ȼ󡿣�\n");  
		if( me->query("gender")!="Ů��") 
                return notify_fail("��һ������ү��ɦ��Ū�˵ģ�����ͽ����룡\n");  
        if(me->query("per")<25) 
                return notify_fail("���������òǷ�ѣ��޷�ʩչ���Ȼ��ܣ�\n");  
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á��Ȼ󡿡�\n");
		//if( target->query_temp("tlbf/meiguo"))
              //  return notify_fail("�Է��Ѿ���������ʩչ�ġ��Ȼ󡿾�����\n");

		if( target->is_busy())
                return notify_fail("�Է��Ѿ���æ�����ˣ���Ͻ����ֽ����ɡ�\n");

		message_vision(HIM"$N��"+weapon->query("name")+HIM"������󣬳�$n��ȻһЦ��ɲ�Ǽ�����С¶�������ٻ����ţ�\n"NOR,me,target);
		message_vision(HIY"\b$N�Ჽ���������溬����һ����ҡ��$nɲ�Ǽ����$N����аٺϣ�ҡҷ���ˡ�\n"NOR,me,target);
		
		ap=(int)me->query_per()*me->query("combat_exp")/10000;
		
		if (target->query("family/family_name")=="������"||target->query("family/family_name")=="������")
			dp=(int)me->query("buddhism",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="������")
			dp=(int)me->query("dacheng-fofa",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="������")
			dp=(int)me->query("mizong-fofa",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="Ѫ����")
			dp=(int)me->query("huanxi-chan",1)*me->query("combat_exp")/200000;
		else if (target->query("family/family_name")=="�䵱��"||target->query("family/family_name")=="ȫ���")
			dp=(int)me->query("taoism",1)/10*me->query("combat_exp")/10000;
		else dp=(int)me->query_per()*me->query("combat_exp")/10000;
		
		if (random(ap)>dp/2 
			|| random(me->query_skill("dagger",1))>target->query_skill("parry",1)/2
			|| random(me->query_per())>target->query_per()/2)
		{
			//message_vision(HIR"\n$N�������Ȼ����$n�������ߣ���$nһʱ��Ϊ$N��ɫ�����˲�䣬����Ծ�𣬰γ����вص�"+weapon->query("name")+HIR"����$n!\n"NOR,me,target);
			if (userp(target)) target->add_busy(2);
			else target->add_busy(4);
			//target->set_temp("tlbf/meihuo",skill);
			if (!target->query_temp("tlbf/meihuo")
				&&me->query("gender")=="����")
			{
				target->add_temp("apply/attack",-skill/3);
				target->add_temp("apply/parry",-skill/4);
				target->add_temp("apply/dodge",-skill/4);
				target->set_temp("tlbf/meihuo",skill);
				call_out("remove_effect",1,target);
				message_vision(HIM"$N��ЦٻȻ��Ц�ݶ������ǣ���$n��ǣ���ƣ����ߵ���������ʼ����������\n"NOR,me,target);
			}
			//if (me->is_fighting()&&objectp(target))
				//call_out("remove_effect",5,me,target);
			
		}
		else {
			message_vision(HIC"$Nɦ��Ū�˵���Ū�˰��죬$n��Ц��������û�յ�$N��Ӱ�졣\n"NOR,me,target);
			me->start_busy(1);
		}
		me->add("neili",random(200));
		me->add("jingli",random(200));	
        
		return 1;
}
void remove_effect(object target)
{
      int skill;
	  if (!objectp(target)) return ;
	  skill=target->query_temp("tlbf/meihuo");
	  target->add_temp("apply/attack",skill/3);
	  target->add_temp("apply/parry",skill/4);
	  target->add_temp("apply/dodge",skill/4);

	  tell_object(target,target->query("name")+HIC"��ʶ���Լ�ʧ̬����æ�˹���ǿ��ѹ�������Ȼ�\n"NOR);
	  target->delete_temp("tlbf/meihuo");
	
	  return ; 
}

int help(object me)
{
   write(WHT"\n����ذ����"HBYEL"�Ȼ�"WHT"����"NOR"\n");
   write(@HELP
	����ذ�����������������������Ĳ���֮��
	�仯��ˣ�����ʤ������ν��Ů�˵����Ʒ�
	�ӵ����쾡�¡�
	���������鵺�����ϲ���һ�������ܣ�����
	��������Ů���Ӵ��绨�����Ҷ��Ȼ�֮
	���������Ǿ�ͨ���ö���֮������Ͷ��֮��
	���ܴ����������˾�����������ذ����һ��
	��ɱ�������ܣ�����ò�Լ�ս�������й���
	ע�⣺��Ϊ�����ˡ���ʿ�����������ϰ��
	�ĵķ��ţ����ڴ˾�����һ���Ŀ��ƹ�Ч��
	�����ջ����ں�����ò��Ч���йء���Ů��
	Ч�����ѡ�
	   
	ָ�perform dagger.meihuo

Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	����ذ���ȼ� 350 ���ϣ�
	����ذ���ȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	������òҪ�� 25 ���ϣ�
	�����ȷ������ȷ�
	�����ַ�Ϊ���߲�˿��
	����ذ��Ϊ����ذ����
	�ֳ�ذ����������
	�Ա�����Ů�ԡ�
HELP
   );
   return 1;
}
