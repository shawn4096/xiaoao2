#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
      object ob;
      string msg, *limbs;
      int i, neili, ap, dp, damage, p;
        
      i = (int)me->query_skill("chousui-zhang", 1);
      neili = (int)me->query("neili");   
        if( !target ) target = offensive_target(me);
    if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) 
        || !living(target)
        || environment(me)!=environment(target) )
                return notify_fail("�����桹����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á����桹��\n");        
        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("û�л����ô���������桹���й�����\n");
        if(me->query_temp("pfm_chousui"))
                return notify_fail("������������ѽ��й�����\n");
        if( i < 350 )
                return notify_fail("�㷢���Լ������޶��ƻ�������죬�޷�ʹ�á����桹���й�����\n");

        if( (int)me->query_skill("huagong-dafa",1) < 350 )
                return notify_fail("�㷢���Լ��Ļ�������Ϊ�������޷�ʹ�á����桹���й�����\n");
        
		if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("�㷢���Լ��Ļ����ڹ���Ϊ�������޷�ʹ�á����桹���й�����\n");
		if( (int)me->query_skill("strike",1) < 350 )
                return notify_fail("�㷢���Լ��Ļ����Ʒ���Ϊ�������޷�ʹ�á����桹���й�����\n");
        if((int)me->query_skill("poison",1) < 180)
                return notify_fail("�㷢���Լ����ھ۶��������޷�ʹ�á����桹���й�����\n");         

        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                return notify_fail("������ó����Ʋ���ʹ�á����桹���й�����\n"); 
                                                                              
        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("�㷢���Լ����õ��ڹ��޷����С����桹������\n");

        if( (int)me->query("max_neili") < 5000) 
                return notify_fail("�㷢���Լ�����̫�����޷����������桹���й�����\n");

        if(neili < 2500)
                return notify_fail("�㷢���Լ���������̫����ʹ���������桹���й�����\n");           
    
        if(target->query_condition("xx_poison") > 200)
                return notify_fail("�Է��Ѿ����������綾���㲻���ٽ��С����桹�����ˡ�\n");           

        message_vision(HIC"\n$N����ָ��"HIR"���"HIC"��Ĭ��������ע���Ż��棬���ư��أ������૵Ĳ�֪˵Щʲô��\n"NOR,me);
                 
        ap = me->query("combat_exp")/100000 * me->query_str();
        dp = target->query("combat_exp")/100000 * target->query_dex();
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -100);
        me->add("jingli", -25);
        
		message_vision(HIG"\n$NͻȻ���Լ�������һҧ,������ھ�Ѫ������"RED"����"HIG"֮�ϣ���ʱֻ��������Ѫ���������ȳ��ޱȣ�\n"NOR,me);  
		me->receive_damage("qi",random(200),me);
		if (!me->query_temp("csz/biyan"))
		{
			message_vision(HBWHT+HIB"$N�⼸�ھ�Ѫ�̺��綾���ڻ����ж���һ�������"HIG"����"HBWHT+HIB"����ʹ�ó���������������\n"NOR,me);  
		
			
			me->add_temp("apply/attack",i/4);
			me->add_temp("apply/strike",i/6);
			me->add_temp("apply/damage",i/6);
			me->set_temp("csz/biyan",i);
			call_out("remove_effect",1,me,i/50);
		}
		
        
		message_vision(HIG"\nȻ��$NͻȻ˫����ǰƽƽ�Ƴ�������"RED"����"HIG"΢΢���������£����һ��"GRN"����"HIG"������$n��\n"NOR,me,target);        

		
		if(random(ap+dp) > dp
			||random(me->query_skill("chousui-zhang",1))>target->query_skill("parry",1)/2)
		{
        	damage = (i+me->query("jiali"))*4;
          	if(neili > target->query("neili")*2) damage *= 2;
            if( damage > 6500) damage = 6500+random(damage-6500)/10;
          	
			target->receive_damage("qi", damage, me);
          	target->receive_wound("qi", random(damage), me);
          	
			target->apply_condition("xx_poison",  1+random(2));
		    
			if (userp(me) && userp(target) && me->query_condition("killer") < 15)
				me->apply_condition("killer", 15);
          	p = (int)target->query("qi")*100/(int)target->query("max_qi");
          	msg = damage_msg(damage, "����");
          	msg += "( $n"+eff_status_msg(p)+" )\n";
            if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
			
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
			
			if (me->query_skill("chousui-zhang",1)<350)
			   me->start_busy(1);
          	if(!target->is_busy())
          		target->start_busy(3);
			message_vision(msg, me, target);

        }
        else{
          	if (!me->query("hgdf/powerup"))
				me->start_busy(1);
          	message_vision( HIY"\n$pȫ�����һ��һ����������ֵرܿ����Ǽ��ٶ����ı��棡\n" NOR,me,target);
        }  
             
      // limbs = target->query("limbs");
    //   msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
    //   msg = replace_string(msg, "$w", GRN"����"NOR);
   //    message_vision(msg, me, target);
       if (me->query_skill("chousui-zhang",1)<450)
       {
		   me->start_perform(2,"����");
       }
       return 1;
}

int remove_effect(object me,int count)
{
	int i;
	if (!me) return 0;
	i=me->query_temp("csz/biyan");
	
	if (!me->is_fighting()
		||count<0
		||me->query_skill_mapped("strike")!="chousui-zhang"
		||me->query_skill_mapped("parry")!="chousui-zhang"
		||me->query_skill_prepared("strike")!="chousui-zhang")
	{
		
			me->add_temp("apply/attack",-i/4);
			me->add_temp("apply/strike",-i/6);
			me->add_temp("apply/damage",-i/6);
			me->delete_temp("csz/biyan");
			message_vision(WHT"$N�����³�һ����������ɫ��Щ�Ұ���ƣ̬���ԣ���Ȼ�������Ĳ��پ�����\n"NOR,me);  
			return 1;

	}
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return HIC"����"NOR; }
int help(object me)
{
        write(HIB"\n������֮�����桹��"NOR"\n\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	������������ս���У�ƾ������ڹ������ڴ涾�Ƴ������˵е�
	һ�Ź��򡣡����桹һʽ����ͨ���ۻ��ڹ��������ƶ�������֣�
	�������Ź��򾭹��������ɲ����Ż������ݣ���������������
	�Գ����Ƶĸ�����������ǿ��450���󳹵״�ɡ�
	
	ָ�perform strike.biyan

Ҫ��
	��ǰ�������� 2500 ����;
	����������� 5000 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ����;
	�������Ƶȼ� 180 ���ϣ�
	�������ޱ�����

        
HELP
        );
        return 1;
}

