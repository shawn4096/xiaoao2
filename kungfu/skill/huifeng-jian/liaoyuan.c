// liaoyuan.c ��ԭ�ٻ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl, skill, skill1,jiali,i;
	object weapon;
	string name;

	weapon = me->query_temp("weapon");
	if (weapon) name = weapon->query("name");

	if( !target ) target = offensive_target(me);
     
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("��ԭ�ٻ�ֻ����ս���жԶ���ʹ�á�\n");

	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("������û�н����޷�ʹ����ԭ�ٻ���\n");             

	if( (int)me->query_skill("huifeng-jian",1) < 450 )
		return notify_fail("��Ļط������������죬����ʹ����ԭ�ٻ���\n");
      
	if( (int)me->query_skill("sword",1) < 450 )
		return notify_fail("��Ļ��������ȼ�����������ʹ����ԭ�ٻ���\n");  

	if( (int)me->query_skill("jieshou-jiushi", 1) < 450 )
		return notify_fail("��Ľ��־�ʽ�ȼ�����������ʹ����ԭ�ٻ���\n");
      
	if( (int)me->query_skill("linji-zhuang", 1) < 450 )
		return notify_fail("����ټ�ʮ��ׯ�ȼ�����������ʹ����ԭ�ٻ���\n");

	if (me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
	
	if( (int)me->query("max_neili") < 8000 )
		return notify_fail("�������̫��������ʹ����ԭ�ٻ���\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("�������̫���ˣ��޷�ʹ�ó���ԭ�ٻ���\n");
	if (me->query_skill_prepared("hand") != "jieshou-jiushi"
	 || me->query_skill_mapped("hand") != "jieshou-jiushi"
	 || me->query_skill_mapped("parry") != "huifeng-jian")
		return notify_fail("��ļ������ܲ��ԣ������޷�ʹ����ԭ�ٻ����й�����\n");
	if (me->query_temp("liaoyuan"))
		return notify_fail("������ʹ����ԭ�ٻ�������\n");
	skill = me->query_skill("huifeng-jian", 1);
	skill1 = me->query_skill("jieshou-jiushi", 1);
    lvl = (skill + skill1) /8; 
	if (me->query_skill("huifeng-jian",1)>450&&me->query("em_powerup")&&!userp(target))
      lvl+=me->query_skill("linji-zhuang",1)/4;//��8 ����5
	else lvl+=me->query_skill("linji-zhuang",1)/8;
	
	jiali = me->query("jiali");

	message_vision(HIW"\n$N��Хһ�����������߿���ȥ��ת��֮��պ���ס$n��ǰ��������"+name+HIW"������磬����է��������ɲ�Ǽ������ռ䡣\n"NOR, me,target);
	message_vision(HIC"����ʹ�����־�ʽ����������С������������Ȼ��ǿ��\n"NOR, me,target);
	me->add("neili", -350); 
	me->add("jingli", -100); 
//500�����Ծ
	if ( skill > 500)
        lvl = to_int(lvl/6.0* skill/500.0);
	if (me->query("quest/emei/hfj/liaoyuan/pass"))
	{
		i=3;
		if ( skill > 500)
        //lvl = to_int(lvl/6.0* skill/300.0);
		lvl=lvl+lvl/5;
		message_vision(HIR"$N������ԭ�����İ����Ѿ��ڻ��ͨ����ʱʩչ�������ǵ���Ӧ�֣�����������\n"NOR,me,target);
	}else {
		i=1;
		if ( jiali > 100)
		{
			me->set("jiali", 100);
			me->set_temp("lyjiali", 1);
		}
	}	
    if(!userp(me)) lvl = lvl / 3;
	if (me->query("class")=="bonze")
	   lvl+=lvl/4; //��6����4,��������������
    if (me->query_skill("jiuyin-zhengong",1)>150)
    {
		message_vision(HBBLU+HIW"$Nʩչ�����Ĺ����н������澭�Ĺ�����Ȼʩչ��������ʽ����������\n"NOR, me);
		lvl +=lvl/6;
    }
	    me->set_temp("liaoyuan", 1);
        me->add_temp("apply/attack", lvl );
        me->add_temp("apply/damage", lvl );
        me->add_temp("apply/sword" , lvl );
        me->add_temp("apply/dexerity",lvl /8);
	    me->add_temp("apply/hand", lvl);


     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);

	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);//��ǰ��random(4) by lsxk@hsbbs
                	
    if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);//��ǰ��random(4) by lsxk@hsbbs
   
         weapon->unequip(); 
		 //�������־�ʽ�����ܳ������У��жϽ���
	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi",1) > 350)
       {                
	           if(me->query("env/���־�ʽ") && me->query("emei/jianjue")) 
			   {
                  target->set_temp("must_be_hit",1);
                  COMBAT_D->do_attack(me, target, 0, i); //��ǰ��random(4)?1:3  by lsxk@hsbbs
                  target->delete_temp("must_be_hit"); 
				}
               COMBAT_D->do_attack(me, target, 0, 3); //��ǰ��random(4)?1:3  by lsxk@hsbbs                                       
       }
	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi", 1) > 450)
      {
              if(me->query("env/���־�ʽ") && me->query("emei/jianjue"))
			  { 
                //target->set_temp("must_be_hit",1);
                COMBAT_D->do_attack(me, target, 0, i);
				//target->delete_temp("must_be_hit") ;
			  }
              COMBAT_D->do_attack(me, target, 0, i); 

      }
      weapon->wield();
	  //�⿪��������������������ͷ�һ�д���
	  
     if (me->query("emjy/pass")&&me->query_skill("jiuyin-zhengong",1)>150)
     {
		 message_vision(HIY"$N��Ȼ�����һ�����Ծ���֮������Ծ��,�����ټ�ׯ�еľ���֮�⣬���������Ļӳ�һ����\n"NOR,me,target);
		 me->set_temp("hfj/ronghe",1);
		 target->set_temp("must_be_hit",1);
		 me->add_temp("apply/damage",lvl/4);
         COMBAT_D->do_attack(me, target, 0, 3);
		 me->add_temp("apply/damage",-lvl/4);
		 target->delete_temp("must_be_hit");
		 me->delete_temp("hfj/ronghe");
     }


	if ( me->query_temp("lyjiali"))
	{
 		me->set("jiali", jiali);
		me->delete_temp("lyjiali");
       }
        me->add_temp("apply/attack", -lvl);
	    me->add_temp("apply/sword", -lvl);
        me->add_temp("apply/damage", -lvl);
        me->add_temp("apply/dexerity", -lvl /8);
	    me->add_temp("apply/hand", -lvl);
        me->start_busy(1);
	    me->delete_temp("liaoyuan");
        me->start_perform(5, "��ԭ�ٻ�");
	
		return 1;
		
}

string perform_name(){ return HIR"��ԭ�ٻ�"NOR; }

int help(object me)
{
	write(HIR"\n�ط������֮����ԭ�ٻ�����"NOR"\n\n");
	write(@HELP
	�ط���������Ƕ�ü����֮�أ���ɽ��ʦ����������ʱ�ھ���
	��Ϊ�ḻ�������ǳ�������һ���������ϣ���ϼҴ���ѧ��
	�书���輫Ϊ��񡣺�������������ã�������������ʮ��
	��󳹴��򣬳���Ϊ�ᣬ������ü��ѧ--�ط���������⿪��
	���������ԭ�ٻ�����������

ָ�perform sword.liaoyuan

Ҫ��
	��ǰ���������� 1500 ���ϣ�
	������������� 8000 ���ϣ�
	��ǰ���������� 2000 ���ϣ�
	�ط�������ȼ� 450 ���ϣ�
	���־�ʽ�ĵȼ� 450 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 450 ���ϣ�
	���������ĵȼ� 450 ���ϣ�
	�����ڹ�Ϊ�ټ�ʮ��ׯ��
	��������Ϊ�ط��������
	�����ַ�Ϊ���־�ʽ��
	���ַ�Ϊ���־�ʽ��
	���ֱֳ�����
HELP
        );
        return 1;
}
