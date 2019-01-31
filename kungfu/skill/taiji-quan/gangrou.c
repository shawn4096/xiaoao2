// gangrou.c ̫��ȭ�����������
// by snowman@SJ 26/11/1999
// Modified by snowman@SJ 08/05/2001


inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI	"/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
string perform_name(){ return RED"�����"NOR; }

int perform(object me, object target)
{ 
	    if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	    if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("�����������������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("����ڹ���ȭ�����ԣ��������ܷ��ӳ���������������ơ�\n");  
        if(me->query_skill("taiji-quan", 1) < 350 )
                return notify_fail("̫��ȭ��Ҫ���������׼�����糵�֣�̫��ȭ�����������������ʹ�á����������\n");
		if(me->query_skill("yinyun-ziqi", 1) < 350 )
                return notify_fail("�����������������������ʩչ�����\n");
        if( (int)me->query("neili", 1) < 2500 )
                return notify_fail("����������������ǿ��ʹ�á���������Ƿ��Ӳ������������ģ�\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     
         if( target->query_temp("tjq/gangrou"))
                return notify_fail("�Է��Ѿ�������ĸ��������\n");     

        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
    int damage = 1, j, ap, dp;
        string msg, str;

    if( !target ) target = offensive_target(me);


    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 1000 || me->query("jingli") < 200 || me->query_temp("weapon")){
        	write("��Ŀǰ�ò��ˡ����������\n");
		return 1;
        }                

	if( target->query_condition("neishang") ){
		write("�Է��Ѿ��������ˣ��㲻�����á���������ˡ�\n");
		return 1;
	 }
	if(intp(me->query_temp("tjq/"+target->query("id")) > 4))
		me->add_temp("tjq/"+target->query("id"), -4);
	else me->delete_temp("tjq/"+target->query("id"));
	              
    str = (string)me->query("env/���Ͼ�"); 
    if(str != "�귭" && str != "����" && str != "����" && str != "����" && str != "����" && str != "����")
        	str = "��";
        	
    msg = HIB"\n$Nʹ��̫��ȭ��"RED"���������"HIB"�Ĺ���";
        
    if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 350){
        	msg += "����һ��������$n��\n"NOR;
        	str = "��";
     }  
     else msg += "����һ������$n���к�Ԫ����ȭ·������֮����֮���򣬱仯������\n"
		+"��Ī�ܲ⣬�������ģ�����̫�������\n"NOR;
        
    if( TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350 )
        	damage = 2;
       
    if (me->query_skill("taiji-quan",1)<450)
    {
	   me->start_perform(2, "���������");
	   me->start_busy(1);
     } 
	me->add("neili", -100);
	me->add("jingli", -50);
	
	if(!target->is_busy()) target->start_busy(1+random(1));

	ap = me->query("combat_exp")/ 1000000 ;
	dp = target->query("combat_exp")/1000000 ;
    //����̫����������˺�
	if (me->query("taiji/pass"))
    {
		ap *=2;
		damage *=2;
    }
	if( random(ap + dp) > dp ||random(me->query_str(1))>target->query_con(1)/2){
		msg += HIY"$n�ۼ�$P�������ٺ�һЦ��̧�־ͷ�ס��$N��һ�ƣ�\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -50);
		target->set_temp("tjq/gangrou",1);
		call_out("hurt", 0, me, target, damage);	
	}
	else if( random(ap) > dp/3 ){
		damage *= (me->query_skill("cuff") + me->query("jiali")) * 2;
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/2, me);
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += damage_msg(damage, "����")+"( $n"+eff_status_msg(j)+" )\n"; 
        if(userp(me) && me->query("env/damage"))
		   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
	
    if(userp(target)&& target->query("env/damage"))
		   tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); 
	    me->add("neili", -150);
		me->add("jingli", -50);
	}
        else {
		msg += HIY"����$p�����ϵ�������һ�ˣ������ˡ����������\n"NOR;
	}
        message_vision(msg, me, target);
        return 1;
}

int hurt(object me,object target, int damage)
{
        string msg;

		if ( ! me) return 0;

        if( !target || !target->is_character() )
                return 0;
                
        msg = HIR"\nͻȻ$Nȫ��һ����Ϣ���ڣ�ԭ���Ǳ�������������ֵ��ᾢ�����ˣ�\n"NOR;
        if( target->query("neili") <= 1000 || target->query("qi") <= 1000 ){
		tell_object(target, "����Ȼ�����Լ�������Ȼ�ݽߺľ����޷��˾��࿹�ˣ�\n");
		msg += RED"���ֻ��$N�͵ؿ�����Ѫ���磬ȫ��������ѣ��ۼ��ǻ���ˣ���\n"NOR;
		target->receive_damage("qi", (int)target->query("qi")+1, me);
		target->set("eff_qi", 10);
                msg += "( $N"+eff_status_msg(1)+" )\n";   
	}
	
	else if( target->query_skill("force") > 450 ) 
		target->apply_condition("neishang", 5+random(3));
	else target->apply_condition("neishang", 1);
	target->delete_temp("tjq/gangrou");
	message_vision(msg, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n̫��ȭ֮"RED"�����������"NOR"\n");
	write(@HELP
	ʹ̫��ȭ�������������Ϊ��Ҳ���������գ�ֱ���޺�
	������أ�������������ɼ��壬������У���Ȼһ��
	������������ʯ���������ͣ�ӥ��ȼ�����ͬ��ˮ
	����ֹ���ɽ�����˵����ڣ����ƺ���������֮���֡�
	�����������̫��ȭ�������仯����Ҫ�ھ���350������
	С�ɣ�450���ɡ��Ҹü��ܻ��Ϊ̫��ȭ��Ҫ�ĸ�����
	�����ܡ�ע�⣺�����Ͼ����õõ���̫��ȭ����������
	
	ָ�perform cuff.gangrou

Ҫ��	
	��ǰ���� 2500 ���ϣ�
	̫��ȭ�� 350  ���ϣ�
	������ 350  ���ϣ�
	���پ��� 200 ���ϣ�      
	����̫��ȭ�����ޱ�����
HELP
	);
	return 1;
}
