// riyue ���±�-����
// campsun

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{

        int i = me->query_skill("riyue-bian", 1) /2;
     
        int j = me->query("jiali") + 20;//ԭ����10
   
        string msg,dodge_skill;

		object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("��������ת��ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "whip")
                return notify_fail("����û������,���ʹ�á�������ת����\n");

        if( (int)me->query_skill("riyue-bian", 1) < 450 )
                return notify_fail("������±޷�������죬����ʹ�á�������ת����\n");

        if( (int)me->query_skill("yijin-jing", 1) < 450 )
                return notify_fail("����׽�ȼ�����������ʹ�á�������ת����\n");

        if( (int)me->query_skill("buddhism", 1) < 200 )
                return notify_fail("��������ķ��ȼ�����������ʹ�á�������ת����\n");
          
        if( (int)me->query("max_neili") < 15000 )
				return notify_fail("������������Ϊ̫��������ʹ�á����¡���\n");
      
        if( (int)me->query("jingli") < 500 )
				return notify_fail("����������̫�٣�����ʹ�á����¡���\n");
        if ( me->query_skill_mapped("whip") != "riyue-bian")
				return notify_fail("�㼤���޷����ԣ�����ʹ�á����¡���\n");

        if ( me->query_skill_mapped("parry") != "riyue-bian")
				return notify_fail("���мܲ��ԣ�����ʹ�á����¡���\n");
    
        if ( me->query_skill_mapped("force") != "yijin-jing")
				return notify_fail("�����ʹ�������ķ����ܴ߶���������ת����\n");
               
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫��������ʹ�á�������ת����\n");

        msg = HIC "$N���и�����ţ�ʹ�����±��С�������ת�����������г����������裬���������Ҳ������϶�������$n,\n" NOR;
        msg += HIC "����$N����һ��������������צ��ī�����ƣ��������ϣ�����$n�˵���\n"NOR;
        message_vision(msg, me, target);
   
        me->set_temp("ryb/riyue", 1);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", j);
  //��һ��
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
   //�ڶ���
		if( me->is_fighting(target) ) 
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //������
		if( me->is_fighting(target) && (int)me->query_skill("riyue-bian", 1) > 220)  
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -i);
		
		if(me->is_fighting(target) )
		{
 	
			if(random(10)<5)
			{          
				msg = HIY"\n������$N�����������ӷ𣡡���ʹ��"HIR"���� �� ��"HIY"�־������г���һ���$n���ʺ��ȥ����ͷδ����������Ю\n"
                 + "����������յ��գ���Է�һ�����ϣ�ֻ������žž���������죬��ͷ���𣬱���һ�������Ķ��ߺ��ط�\n"
                 + "�ɻӶ�������������ɳ����Х������\n"NOR; 
				message_vision(msg, me, target);
				
				me->set_temp("ryb/rilun",1);

				if( me->is_fighting(target) ) 
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				if( me->is_fighting(target) ) 
  					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				if( me->is_fighting(target) ) 
  					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

				me->delete_temp("ryb/rilun");      
				me->add("neili", -400);
				me->add_busy(2+random(2));

			} 
			else{ 
				msg = HIC "\n������$N�������ҷ�ȱ�������ʹ��"HIB"���� ת��"HIC"�־����������տ�����������������¶��ǣ����г����趯ʱ\n"
                     +"�Ʋ������Ӱ��������Ϣ���ƻ�ʵ����ȴ���ް�������������ȣ�˵�����Ĺ���Ī����\n"NOR;
				
				message_vision(msg,me,target);
      
				
					msg=HIR"���$nһ��С�ģ���ʱ��û�������Ӱ֮�С�\n"NOR;
					me->delete_temp("ryb/riyue");      
					target->addt_busy(2+random(2));
					msg+=HIG"���ͷ��Ȼ��������֮��ͻϮ������ֱ�Ӵ���$n��ǰ�أ���Ѫ�Ž���\n"NOR;
					//msg+=HIY"���ͷ��Ȼ��������֮��ͻϮ������ֱ�Ӵ���$n��ǰ�أ���Ѫ�Ž���\n"NOR;

					target->receive_damage("qi",5000+random(2000),me);
					target->receive_wound("qi",2000+random(2000),me);
					target->recieve_damage("jing",1000+random(1000),me);

					message_vision(msg,me,target);        
					target->set_temp("must_be_hit",1);
					me->add_temp("apply/damage",i/2);
					me->add_temp("apply/whip",i/2);
					//msg+=HIY"���ͷ��Ȼ��������֮��ͻϮ������ֱ�Ӵ���$n��ǰ�أ���Ѫ�Ž���\n"NOR;
					me->set_temp("ryb/yuelun",1);
					if( me->is_fighting(target) ) 
  						COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					me->add_temp("apply/damage",-i/2);
					me->add_temp("apply/whip",-i/2);
					target->delete_temp("must_be_hit");
					
					me->delete_temp("ryb/yuelun");
					
					
					me->add("neili",-400);

           /*      }
				else {
					dodge_skill = target->query_skill_mapped("dodge");
					if( !dodge_skill ) dodge_skill = "dodge";
                    msg=HIR"$N���Ʋ��ã������ˣ�����������Ӱ��\n"NOR;
					message_vision(msg,target);
					me->delete_temp("ryb/riyue");      
					me->add("neili",-200);
                }*/
			}
       		if (me->query("quest/em/zzr/pass"))
			{
						message_vision(HIB"�ۼ�$n�����糱��ȫ��ѹ��$N��ǰ�����±��鶯����ɥʧ��$N���һ����ʩչ�������澭�е�"HIR"����������"HIB"��ʽ˳�ֶ�����\n"NOR,me,target);
						message_vision(HIW"\n$N����һ��һ�Σ�����"+weapon->name()+HIW"�͵�˦������������������������磬ʸ�ö�����\n"NOR, me,target);

						call_out("jiuyin_feilong",1,me,target);
			}

	} 
	me->start_perform(5, "��������ת��");
	me->add("neili",-200);

    me->delete_temp("ryb/riyue");      
	return 1;

}
int jiuyin_feilong(object me,object target)
{
	
	int lvl;
	object weapon;
	weapon=me->query_temp("weapon");

	lvl=me->query_skill("yinlong-bian",1)/3;
	me->set_skill_mapped("whip","yinlong-bian");

	me->add_temp("apply/attack", lvl);
	me->add_temp("apply/damage", lvl/2);
//	me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", lvl);
//��һ��
	me->set_temp("feilong", 1);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

//�ڶ���
	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
     if(objectp(weapon)) weapon->unequip(); 
//������ ���ֿ��ֻ�����׹�ץ����
	if (objectp(target)&&me->is_fighting()&&me->query("env/�������")=="�����׹�ץ")
	{
	
		if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-baiguzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-baiguzhua" )
		{
        
              	message_vision(HIM"\n$N��ʹ�����׹�צ��ָצ�Ӷ����������˻˻���죬����������������������������ޱȣ�\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
               	message_vision(HIM"\n$N���ָ���ǰ̽�������׹�צ��ָ��ץ��$n�ؿ�,�ۼ���һץ֮�£���ʱ���ǿ�������֮����\n"NOR, me,target);               
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit") ; 
          }

	}
	if (objectp(target)&&me->is_fighting()&&me->query("env/�������")=="�����似")
	{
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit") ; 

	}
	if (objectp(target)&&me->is_fighting()&&me->query("env/�������")=="����")
	{
                message_vision(HIG"\n$N����һ����״�綾�ߣ�˲��ʩչ����������������ʽ�����޳ɻ�����$n��\n"NOR, me,target);
                message_vision(HIR"\$n�پ������޷��ƶ��ֺ����ؿ�����ѹ��һ���ʯ��ȫ������й�糱��\n"NOR, me,target);

                target->add_condition("no_exert",2);
				target->add_condition("no_perform",2);
				target->recieve_damage("jing",1000+random(1000),me);
				target->recieve_damage("jingLI",2000+random(2000),me);
				message_vision(RED"\$N������ӿ����Ȼ��ͷ����һ�С�ֱ�̾�������$n���ؿڴ�Ѩ��\n"NOR, me,target);
				call_out("attack_zhici",1,me,target);
                
	}

    if(objectp(weapon)) weapon->wield(); 
	me->add_temp("apply/attack", -lvl);
	me->add_temp("apply/damage", -lvl/2);
	//me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", -lvl);
	message_vision(HIB"$N����һ����������Ϊ����������һ�����󣬻������±޵���ʽ���ľ�Ҳ�ص��˱���ׯ�ϣ�\n"NOR,me);

	me->set_skill_mapped("whip","riyue-bian");
	me->start_perform(5, "��������ת��");
	me->delete_temp("feilong");

	return 1;
}

int attack_zhici(object me, object target)
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

string perform_name(){ return HIY"��"HIW"��"HIC"��ת"NOR; }
int help(object me)
{
	write(HIC"\n���±ޡ�������ת����"NOR"\n");
	write(@HELP
	���±���������������֮һ��������������������֮�����ɸջ�����书
	��ʱ�����ڹ��Դ��������տ�����������������¶��ǵľ��硣Խ��Խ����
	����Խ�̹���Խǿ�����������������շ����ġ����޼ɾ�лѷ�������գ�
	��һ�ֿ�������ɮ����һս��Ȼ�ɾ������޼ɵ���������ͬʱ���������ϵ�
	���±�Ҳ�������¡�
	��ת��������֮����ֱ�ӽ����ӻ�����ǹ��ꪣ��̴��Է���������ת������
	���ӵ�����֮����ס���ĵ��Է��ľ�����������ת�����������±޵�������
	����Ĵ��֮��������ǿ�����������ֱȽ����ᣬ������⿪������������
	�����������ָ�㣬��ô��õ������޵��似�ںϣ������־����д�������
	����ʽ��
			
	ע�⣺
		set ������� �����׹�ץ  ���뱸����ץ�ܳ����Ǿ����׹�ץ��ʽ
		set ������� �����似    �������Լ����������ֿ���
		set ������� ����        Ȧ�޳ɻ�������������æµ���Һľ�
	
	ָ�perform whip.riyue

Ҫ��	
	������� 15000 ���ϣ�      
	��ǰ���� 1000 ���ϣ� 
	��ǰ���� 500 ���ϣ� 
	�׽�ȼ� 450 ���ϣ�
	���±޷��ȼ� 450 ���ϣ�
	�����ķ��ȼ� 450 ���ϣ�
	�����޷�Ϊ���±޷���
	�������±޷�Ϊ�мܣ�
	�����׽Ϊ�ڹ���
	װ�������������     
HELP
	);
	return 1;
}

