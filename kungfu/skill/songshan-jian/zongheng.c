// �ڰ�·�����·���ܼ�17������Ի�ݺ�17��
// Created by sohu@xojh,2014
// zhengheng.c 
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int is_pfm() { return 1;}
void check_first(object me,object target, int i);
#define PFM_NAME 	"�ݺ�����"
string perform_name(){ return HBYEL+HIR+PFM_NAME+NOR; }

int perform(object me, object target)
{     
      	if( (int)me->query_skill("songshan-jian",1) < 500 )
           	return notify_fail("�����ɽ����������죬����ʹ��" + PFM_NAME + "��\n");
      
      	if( (int)me->query_skill("sword",1) < 500 )
           	return notify_fail("��Ļ��������ȼ�����������ʹ��" + PFM_NAME + "��\n");  
      
      	if( (int)me->query_skill("hanbing-zhenqi", 1) < 500 )
           	return notify_fail("��ĺ��������ȼ�����������ʹ��" + PFM_NAME + "��\n");

      	if (me->query_skill_mapped("sword") != "songshan-jian"
			||me->query_skill_mapped("parry") != "songshan-jian")
            return notify_fail("����ʹ�õĽ�������������ɽ������\n");
		   
	  //�������ʹ�ý����书����
		if (!me->query("quest/ss/ssjf/jueji/pass"))
		    return notify_fail("��û�н⿪��ɽʯ�ڵľ������޷�ʩչ���С�\n");

      	if( (int)me->query("max_neili") < 15000 )
           	return notify_fail("����������̫��������ʹ��" + PFM_NAME + "��\n");
      
      	if( (int)me->query("neili") < 2000 )
           	return notify_fail("��ĵ�ǰ����̫���ˣ��޷�ʹ�ó�" + PFM_NAME + "��\n"); 
        
        if( !target ) target = offensive_target(me);
        
       	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 500 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("��Ŀǰ�޷�ʹ�á�" + PFM_NAME + "����\n");   
                
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	   object weapon;
		int i;
		
      	if( !me->is_fighting() 
        || me->query("neili") < 500 || me->query("jingli") < 100 )
                return notify_fail("��Ŀǰ�޷�ʹ�á�" + PFM_NAME + "����\n");   
                	
	        weapon = me->query_temp("weapon");
      	if (!weapon
       	|| weapon->query("skill_type") != "sword"
       	|| me->query_skill_mapped("sword") != "songshan-jian" )
       		return notify_fail("�������޷�ʹ��" + PFM_NAME + "��\n");      
       	//û��pfmҲ��������	
       
       	message_vision(HBGRN+HIY"\n$N����ɽ����һʮ��·����ʩչ����������ɭ�ϣ��糤ǹ��ꪣ������仯���ݺ�ǧ�\n"
		                      +"������ɽ��������"+ perform_name() +HBGRN+HIY"���ڰ�·���·,�������������Ī�⣬ֱϮ$n��\n"NOR, me, target);
       	if (me->query_temp("ss/hb"))
			i=me->query_skill("songshan-jian",1)+me->query_skill("hanbing-zhenqi",1);//�����мӳ�
		else i=me->query_skill("songshan-jian",1);
		if (me->query_temp("ss/focus"))
				i=i+(int)me->query_temp("ss/focus");//�����мӳ�
		
		me->set_temp("ssj/zhbh",i);
		me->add_temp("apply/attack", i/2);
      	me->add_temp("apply/damage", i/3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
        me->add_temp("apply/damage", -i/3);
      	me->add_temp("apply/attack", -i/2);
      	
        //�ڰ�·��ʽ
        if( me->query_temp("ssj/zhbh")&& objectp(target)&&me->is_fighting() )
       				call_out("second_attack",0,me,target);
        else call_out("check_fight",1,me,3);
		//���·��ʽ

      	me->start_perform(4, PFM_NAME);	
       	return 1;       	
}
//�ڰ�·���ӹ�����

void check_first(object me,object target, int i)
{       
      if( !me ) return; 
        //if( !me->query_temp("ssj/zhbh1") ) return;
        
        i--;       

        if( !me->is_fighting() 
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "songshan-jian"
        ||  me->query_skill_mapped("parry") != "songshan-jian") 
		{
        	me->delete_temp("ssj/zhbh");
			me->delete_temp("ssj/zhbh1");
			me->delete_temp("ssj/zhbh2");
			message_vision(HIY"$N��һ����ɽ������ʹ�꣬������һɢ�������չ�,������Ȼ��\n"NOR,me);
        	return;
        }
        me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/4);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
      	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/4);
          
        call_out("check_first", 1, me, target,i);
}
//���
void check_fight(object me, int i)
{       
        if( !me ) return; 
        if( !me->query_temp("ssj/zhbh") ) return;
        
        i--;       

        if( !me->is_fighting() 
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "songshan-jian"
        ||  me->query_skill_mapped("parry") != "songshan-jian") {
        	me->delete_temp("ssj/zhbh");
			me->delete_temp("ssj/zhbh1");
			me->delete_temp("ssj/zhbh2");
			message_vision(HIY"$N��һ����ɽ������ʹ�꣬������һɢ�������չ�,������Ȼ��\n"NOR,me);
        	return;
        }
      
        call_out("check_fight", 1, me, i);
}
/*
void attacking(object me)
{
	object target = offensive_target(me);
	
       	if( !target 
       	|| !target->is_character() 
       	|| !me->is_fighting(target) 
       	|| !living(target) 
        || environment(target) != environment(me) )
        	return;
        me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/6);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
      	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
        me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/6);
        	
}*/
//�칥���⹥ ���·
int second_attack(object me, object target)
{
	int i = me->query_skill("songshan-jian", 1)/50;
	if( i > 9 ) i = 9;
	i=random(i);
	me->set_temp("ssj/zhbh2",i);
	me->add_temp("apply/attack", me->query_skill("songshan-jian", 1)/2);
    me->add_temp("apply/damage", me->query_skill("songshan-jian", 1)/6);
	
       	message_vision(HIB"\n$N��$n���ڸ����翹��һ����Х�����λö�����$nһ��һ���໥���������Ľ������������\n"
		+"��ʽ��ã��仯Ī�⣬Ѹ�������磬����������������ɽ�������·�Ŀ칥��ʽ��\n"NOR, me, target);
    while( i-- ){
     	if( me->is_fighting() )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

        		
    }
	me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
    me->add_temp("apply/damage", -me->query_skill("songshan-jian", 1)/6);
	
	me->delete_temp("ssj/zhbh2");
    
	me->start_perform(5, PFM_NAME);	
	//�����ڰ�·����	
	if (me->is_fighting()&&objectp(target) && me->query_temp("weapon"))
	    	call_out("first_attack",1,me,target);
	else 
	    {
			remove_call_out("check_fight");
			call_out("check_fight",1,me,5);
	     }
       	return 1;
}
//��������
int first_attack(object me, object target)
{
	    object weapon;
		int i = me->query_skill("songshan-jian", 1)/50;
    	if( i > 8 ) i = 8;	
	    //me->delete_temp("ssj/zhbh2");
		weapon=me->query_temp("weapon");
		me->set_temp("ssj/zhbh1",i);
       	message_vision(HIC"\n$N������"+weapon->query("name")+HIC"�������Σ����Ʊ����ٻ���������ȴ�����������ڰ�·�е���ʽ��\n"NOR, me);
       	
		me->add_temp("apply/attack",me->query_skill("songshan-jian", 1)/2 );
      	me->add_temp("apply/damage",me->query_skill("songshan-jian", 1)/5 );
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	me->add_temp("apply/damage",-me->query_skill("songshan-jian", 1)/5 );
		me->add_temp("apply/attack", -me->query_skill("songshan-jian", 1)/2);
       	//me->start_perform(1, PFM_NAME);	
		if (me->is_fighting()&& objectp(target))
		{
			remove_call_out("check_first");
			call_out("check_first",1,me,target,i);
		} 
       	return 1;
}


int help(object me)
{
	write(HBYEL+RED"\n��ɽ������"NOR + perform_name() + HBYEL+RED"����"NOR"\n");
	write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ�17·���̿����Ľ���Ӧ�о��С�
	��������������ħ��ʮ�������Ȼ�ս��ɽ���������ɵĺ������˴�����
	���ɽ�������ྪ�����������ɸ��ֶ����š���ɽ�������������Ἧ
	���ɲд�����ϣ����������ǵõĽ��в��۴־�������¼����������
	��һ�����ס���ʮ��������ȥ�ߴ�ݼ�������ɽ��������ֲ���������
	�����������ûʵ����ƣ�һһ�޸ģ�ʹ�ñ��ɵ�ʮ��·����������ȱ��
	����δ�����µĽ�·��ȴ�����������ɽ�����Ĵ󹦳���
	������ɽ�������ܲ���͸��ɽʯ�ڵ���ɽ�似����ô��ɽ�����Ĵ���
	���������ͷš�
	
	ָ�perform sword.zongheng

Ҫ��	
	��ɽ�����ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	����������� 15000 ���ϣ� 
	��ǰ�������� 2000 ���ϡ�
	��������Ϊ��ɽ����
	�����м�Ϊ��ɽ����
	���輤�������ڹ�
	�ֳֽ�������
HELP
	);
	return 1;
}

