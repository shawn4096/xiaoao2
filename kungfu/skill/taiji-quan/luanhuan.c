// luanhuan.c ̫��ȭ���һ�������
// by snowman@SJ 26/11/1999
// Modified by snowman@SJ 24/05/2001
// Update By lsxk@hsbbs 2007/5/28

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
int hurt(object,object,int,string,string);

string perform_name(){ return HIC"�һ���"NOR; }

int perform(object me, object target)
{ 
        int damage = 1, ap, dp;
        string msg, force, str, tmpTJstr;

	    if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("���һ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	    if( userp(me) 
          &&( me->query_skill_mapped("parry") != "taiji-quan" && me->query_skill_mapped("parry") != "taiji-jian") )
          return notify_fail("���һ�������������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");
        if( me->query_skill_prepared("cuff") != "taiji-quan" )
                return notify_fail("����ڹ���ȭ�����ԣ��������ܷ��ӳ����һ����������ơ�\n");  
        if( me->query_skill("taiji-quan", 1) < 450 )
                return notify_fail("̫��ȭ��Ҫ���������׼�����糵�֣�̫��ȭ�����������������ʹ�á��һ�������\n");
		 if( me->query_skill("yinyun-ziqi", 1) < 450 )
                return notify_fail("̫��ȭ��Ҫ�����ڹ��������������������������ʹ�á��һ�������\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������ǿ��ʹ�á��һ������Ƿ��Ӳ������������ģ�\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     
        

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 1000 || me->query("jingli") < 200 || me->query_temp("weapon"))
        	return 0;                    

	    if(intp(me->query_temp("tjq/"+target->query("id")) > 5))
		    me->add_temp("tjq/"+target->query("id"), -5);
	    else me->delete_temp("tjq/"+target->query("id"));
	              
        tmpTJstr = (string)me->query("env/���Ͼ�"); 
        if(str != "�귭" && str != "����" && str != "����" && str != "����" && str != "����" && str != "����")
        	str = "��";
        	
        msg = HIC"\n$Nʹ��̫��ȭ��"RED"���һ�����"HIC"�Ĺ���";
        
        if(me->query_skill("force", 1) < 100){
        	msg += "�����˼���Ȧ�ӣ���ס��$n��\n"NOR;
        	str = "��";
        }        
        
        else msg += "�������������Ҽ�б��������ƾ�ջ��˼���Ȧ�ӣ���ס$n��\n"+"�������������������ң�"+
        "Ȼ��һ����̫��ԲȦ������������΢��������$pǧ�������\n"NOR;
        
        if((int)me->query_skill("taiji-quan",1)>350)
           damage = 2;
//550�����super�������������
        if((int)me->query_skill("taiji-quan",1)>550){ 
            me->set("env/���Ͼ�",TAIJI->check_force(target)); 
            str = me->query("env/���Ͼ�");
            me->set_temp("tjq/super_lh",1);
        }

        if(TAIJI->check_force(target) == str )
        	damage = 3;
       
        me->start_perform(2, "���һ�����");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
        	force = "�ڹ�";

        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
		tell_object(me, "Str = "+str+"��Force = "+force+"��Damage = "+damage+"\n");

	    ap = me->query("combat_exp")/ 100000 * me->query_int(1);
	    dp = target->query("combat_exp")/100000 * target->query_int(1);

	    if ( target->is_busy())
		 dp -= dp/2;

	    if( random(ap + dp) > dp ){
           msg += HIC"���$n���ɼ������ƽ���$P������Ȧ�ڣ�\n"NOR;
           target->add_busy(2+random(2));
		   me->start_perform(2, "���һ�����");
           message_vision(msg, me, target);
           hurt(me, target, damage, str, force);
	     }
	
        else{
		msg += HIY"����$p�������Ƿ���һ������Ȼ�ѳ��ˡ��һ������İ�Χ��\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -50);
         message_vision(msg, me, target);
	    }


      if (me->query_temp("tjq/super_lh") ){
            me->add_temp("apply/attack", (int)me->query_skill("taiji-quan",1)/4);
			me->add_temp("apply/damage", (int)me->query_skill("taiji-quan",1)/6);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack", -(int)me->query_skill("taiji-quan",1)/4);
			me->add_temp("apply/damage", -(int)me->query_skill("taiji-quan",1)/6);
            if( (int)me->query("neili",1)> 800 ) me->add("neili",-800);
            else me->set("neili",0);
            me->delete_temp("tjq/super_lh");
            me->start_busy(1);
            me->start_perform(3, "���һ�����");
        }

        return 1;
}


int hurt(object me, object target, int damage, string str, string force)
{
        int p, j, m;
        float at;
        string msg;

	    if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
        if( !target || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me) )
                return 0;        
        switch(str){
           case "�귭": msg = HIC"$N˫������������һ����ԲȦ�������ѽ�$n��"+force+"������̫��ȭ��"HIW"��"+str+"����"HIC"�漴ʹ����\n"NOR;break;
           case "����": msg = HIC"����$N˫��һȦһת��ʹ�������Ͼ����е�"HIY"��"+str+"����"HIC"���ѽ�$n�Ļ���"+force+"��㲦����\n"NOR;break;
           case "����": msg = HIC"$N˫������������$n��ǰ�������գ�"HIM"��"+str+"����"HIC"ʹ������������ˮ�������ޱȵش�$p"+force+"�Ŀ�Ϯ�䴩����\n"NOR;break;
           case "����": msg = HIC"ֻ��$N����������������Ŀ�����������ֱۣ���Ȼ��$n��"+force+"��������һ��ȱ�ڣ����ֺ�£����������ɽ��"HIB"��"+str+"����"HIC"��\n"NOR;break;
           case "����": msg = HIC"$N��������˫�ְ뻡��ס��$nֻ��ȫ��"+force+"����$P˫�Ƶ�"MAG"��"+str+"����"HIC"����֮��ɢ�����Ѿ��޿����ܣ��޿ɵ�����\n"NOR;break;
           case "����": msg = HIC"$N˫������ԲȦ�����鶥�������������ƫ���У��������֣�"HIG"��"+str+"����"HIC"Ǳ��$n��"+force+"�ڲ��޼�������\n"NOR;break;
           default: msg = HIC"$N��Ȧ��Ȧ��һ��ԲȦ����һ��̫��ԲȦ��������ʱ����ס$n��\n"NOR;break;
        }        
        
        if (target->query("neili") <= 1200){
			tell_object(target, "����Ȼ�����Լ�������Ȼ�ݽߺľ����޷��˾��࿹�ˣ�\n");
			msg += RED"���ֻ��һ�����죬$n����ÿ�����Ѫ���磬ȫ��������ѣ��ۼ��ǻ���ˣ���\n"NOR;
			target->receive_damage("qi", (int)target->query("qi")+1, me);
			msg += "( $n"+eff_status_msg(1)+" )\n";   
			message_vision(msg, me, target);
        return 1;
	}	
	
	else if(me->query("neili")*3 < target->query("neili")) {
		   me->start_busy(random(2));
           damage = (int)target->query_skill("force",1);
           damage = damage + random(damage);
                
		   me->receive_damage("qi", damage, me);
		   me->receive_wound("qi", damage/3, me);
		   target->add("neili", -damage/10);
                
     if( damage < 1000 ) msg += HIY"����$P�ܵ�$p�����������ƺ�һ����\n"NOR;
          else if( damage < 2000 ) msg += HIY"����$P��$p���������𣬡��١���һ������������\n"NOR;
          else if( damage < 4000 ) msg += RED"����$P��$p�����������ؿ������ܵ�һ���ش�����������������\n"NOR;
          else    msg += HIR"����$P��$p������������ǰһ�ڣ��������ɳ�������\n"NOR;
          message_vision(msg, me, target);
          p = (int)me->query("qi")*100/(int)me->query("max_qi");
          msg += damage_msg(damage, "����") + "( $N"+eff_status_msg(p)+" )\n";    
          message_vision(msg, me, target);
		  me->start_perform(1, "���һ�����");
     if( !me->is_killing(target->query("id"))
		   && !target->is_killing(me->query("id"))
		   && !target->query("have_master")   // added by snowman
		   && me->query("qi")*2 <= me->query("max_qi")) 
			COMBAT_D->end_fight(target, me);
        	return 1;
	}        
	p = me->query_skill("force",1)*4;
	at = me->query("neili") / (target->query("neili")+1);

	if(at < 1){
        	if(at < 0.5) p /= 2;
            	p /= 2;
	}
	else p *= at;
	p *= damage;

	if( me->query_skill("taiji-quan", 1) > 400 ) 
		m = 5000 + ( me->query_skill("taiji-quan", 1) - 300 ) * 10 + random(500);
	else m = 5000;

	if( !userp(me) ) m = 5000;

	if( p > m ) p = m + (p-m)/15;
    if( p > 10000 ) p = p*2/3 + random(p/3) + 1;
    if( wizardp(me) ) tell_object(me, "��ġ�"HIC"�һ���"NOR"������Ϊ�� "+p+"��\n"NOR);

	target->receive_damage("qi", p, me);
	target->receive_wound("qi", p/2, me);

	if( target->query("neili") >= p/5 )
        	target->receive_damage("neili", p/5);
        else target->set("neili", 0);

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 120);
        
	if( p >= me->query_skill("taiji-quan", 1) * 10 )
           msg += HIR"̫��֮�����಻�ϣ�������ȥ�пգ�һ��ԲȦδ�꣬�ڶ���ԲȦ����������һ�죬$pһ����ͷ���ʶϣ�\n"NOR;
        	
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += damage_msg(p, "����")+"( $n"+eff_status_msg(j)+" )\n"; 
        
        message_vision(msg, me, target);

        if (me->query_temp("tjq/super_lh") ){
          me->add_temp("apply/attack", (int)me->query_skill("taiji-quan",1)/4);
		  me->add_temp("apply/damage", (int)me->query_skill("taiji-quan",1)/6);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          if (userp(me)&&me->is_fighting())
          {
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          }
		  
          me->add_temp("apply/attack", -(int)me->query_skill("taiji-quan",1)/4);
		  me->add_temp("apply/damage", -(int)me->query_skill("taiji-quan",1)/6);
          if( (int)me->query("neili",1)> 800 ) me->add("neili",-800);
          else me->set("neili",0);
          me->delete_temp("tjq/super_lh");
        }

        me->start_perform(2+random(3), "���һ�����");
        
        if( !me->is_killing(target->query("id"))
	       && !target->is_killing(me->query("id"))
	       && !me->query("have_master")   // added by snowman
	       && target->query("qi")*2 <= target->query("max_qi")) 
		   COMBAT_D->end_fight(me, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n̫��ȭ��֮���һ�������"NOR"\n");
	write(@HELP
	ʹ̫��ȭ��˫��ƾ�ջ�Ȧ���ྡྷ���һ����ס����˫�ۣ������������Ͼ�
	���˶Է�����������ֱ̫����ʦ�����ᣬҪּ�������������ļ���ԲȦ����
	����������Ķ������Ǻ��ʲ����ˡ��һ�����ҪҪ��˫��������ˮƽ������
	�߳�֮���Ὣ����ʩչ��������ˮ����ע�⣬�һ������������ش������
	ע�⣺�����Ͼ����õõ���̫��ȭ����������

	ָ�perform cuff.luanhuan

Ҫ��
	��ǰ���� 2000 ���ϣ�      
	��ǰ���� 1000 ���ϣ�
	̫��ȭ�� 450  ���ϣ�
	������ 450  ���ϣ�
	����̫��ȭ�����ޱ�����
HELP
	);
	return 1;
}
