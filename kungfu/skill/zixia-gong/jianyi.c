//Create By lsxk@hsbbs 2007/6/14

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIM"��ϼ����"NOR;}

int exert(object me, object target)
{
        object weapon = me->query_temp("weapon");  
        int skill=me->query_skill("zixia-gong",1);
        string jianyi_set;
        
        if( !target ) target = offensive_target(me);

        if(!me->is_fighting() )
                return notify_fail("����ϼ���⡹ֻ����ս����ʹ�á�\n");

        if(userp(me) && !me->query("quest/huashan/zixia/pass"))
          if(me->query("quest/huashan")!="����")
                return notify_fail("��ϼ���˻�ɽ���ھ�ѧ����ǻ�ɽ���ڵ��ӣ�����͵ѧ������ϼ�񹦣�\n");

        if((int)me->query_skill("zixia-gong", 1) < 450 )
                return notify_fail("�����ϼ�񹦲���������ʹ�á���ϼ���⡹��\n");
    
        if((int)me->query_skill("force", 1) < 450 )
                return notify_fail("��Ļ����ڹ�����������ʹ�á���ϼ���⡹��\n");

        if ((int)me->query_skill("huashan-jianfa", 1) < 450 )
                return notify_fail("��Ļ�ɽ����������죬�����������ӡ���ϼ���⡹��\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword")
                return notify_fail("�����������޽����޷�ʹ�á���ϼ���⡹��\n");
    
        if ((int)me->query("neili") < 1000 )
                return notify_fail("����������̫��������ʹ�á���ϼ���⡹��\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á���ϼ���⡹��\n");

        if ((int)me->query_temp("zxg/jianyi/����"))
                return notify_fail("������ʹ�á����ӽ�����������\n"); 

        if ((int)me->query_temp("zxg/jianyi/��Ů"))
                return notify_fail("������ʹ�á���Ů������������\n"); 
   
        if ( (int)me->query_temp("zxg/jianyi/ϣ��") ) 
                return notify_fail("������ʹ�á�ϣ�Ľ�������\n");
        if ( (int)me->query_temp(" zxg/jianyi/�ں�") ) 
                return notify_fail("������ʹ�á������ںϡ���\n");
        if ( (int)me->query_temp("zxg/jianyi") ) 
                return notify_fail("������ʹ�á���ϼ���⡹��\n");

        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("����ڹ������޷�ʹ�á���ϼ���⡹��\n");

        if(me->query("env/��ϼ����")) jianyi_set = me->query("env/��ϼ����");
	    // else return 0;
		//��û�趨����Ĭ���ں�
        if(jianyi_set!="����"
        && jianyi_set!="��Ů"
        && jianyi_set!="ϣ��"
        && jianyi_set!="�ں�") jianyi_set = "�ں�";

        if( jianyi_set=="����"){
            message_vision(HIM"$N������ϼ���ھ���������"+weapon->name()+HIM"�ϣ�"+HIC"���ӽ���"+HIM"���Ķ��������������ˣ�\n"+
            HIC"$Nɲ�Ǽ����������Ԧ��֮��Ҫ�������"+HIC"���ӽ���"+HIM"���ӵ����쾡�£���������������\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"����ϼ���⡹");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(6+random(3));
            me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/strength",skill/15);
			
			me->set_temp("zxg/jianyi/����",1);
            me->add("neili", -400);
            me->add("jingli", -200);              

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="��Ů"){
            message_vision(HIM"$N������ϼ���⣬����"+weapon->name()+HIM"����һ�䣬������ӯ����֮��,����"+HIG"��Ů����"+HIM"��\n"+
            "$N����"+weapon->name()+HIM"������У����н���һһչ����������ˮ������֮���ɣ�ʵ��������\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"����ϼ���⡹");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(1,"����ϼ���⡹");
            me->add("neili", -300);
            me->add("jingli", -100);
            me->set_temp("zxg/jianyi/��Ů",1);

            skill = (int)me->query_skill("huashan-jianfa", 1);
            me->add_temp("apply/dexerity",  skill/5);            
            me->add_temp("apply/dodge",  skill/4);
			me->add_temp("apply/attack",  skill/15);
            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="ϣ��"){
            message_vision(HIM"����$NͻȻһ�����У�������죬ȴ������֮�ƣ�ʵ�˷�����˼�����ǻ�ɽ������"+HIW"ϣ�Ľ���"+
            HIY"\n$N��ϼ���ⲻ�������о������һ��ͭǽ���ڣ�����֮����ʱ������$n���а��ɳ�֮������\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"����ϼ���⡹");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(2,"����ϼ���⡹");
            me->add("neili", -300);
            me->add("jingli", -100);
            me->set_temp("zxg/jianyi/ϣ��",1);

           
            me->add_temp("apply/armor",  skill/2);
            me->add_temp("apply/parry",  skill/4*3);
            me->add_temp("apply/dodge",  skill/4*3);
            me->add_temp("apply/attack",  -skill/4);

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="�ں�"&&(int)me->query_skill("huashan-jianfa", 1) > 550){
            message_vision(HIM"$N������ϼ�񹦣�������ϼ���⳹���ں������ڽ���֮�У�����ʹ�ô���֮����"+
            HIW"\n$N������ɽ����֮���ӣ���Ů��ϣ����ʽ�����ں�һ������ʽ�ֺ�������⽥���ۻ�֮�ƣ�"+
			HIR"\n$N��ϼ���������Ƿ��켫�ĵز�������Ԧ��֮��Ҫ���ӵ����쾡�£���������������\n"NOR,me,target);
            //me->start_exert(1+random(2),"����ϼ���⡹");
            //me->start_perform(3+random(3),"����ϼ���⡹");
            me->add("neili", -1000);
            me->add("jingli", -600);
            me->set_temp("zxg/jianyi/�ں�",1);

            skill = (int)me->query_skill("huashan-jianfa", 1);
            me->add_temp("apply/damage",  skill/4);
            me->add_temp("apply/armor",  skill/6);
            me->add_temp("apply/parry",  skill/4);
            me->add_temp("apply/dodge",  skill/4);
			me->add_temp("apply/strength",  skill/25);
            me->add_temp("apply/dexerity",  skill/15);
			me->add_temp("apply/sword",  skill/10);

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }


}

void check_fight(object me, object weapon,int skill)
{  
        object wep;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         //|| me->query_skill_mapped("parry") != "huashan-jianfa"
         //|| me->query_skill_mapped("sword") != "huashan-jianfa"
         || weapon != wep ){
             if(me->query_temp("zxg/jianyi/����")){
                 me->add_temp("apply/damage",-skill/6);
				 me->add_temp("apply/strength",-skill/15);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/��Ů")){
                 me->add_temp("apply/dexerity", -skill/5);            
                 me->add_temp("apply/dodge",  -skill/4);
			     me->add_temp("apply/attack",  -skill/15);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/ϣ��")){
                 me->add_temp("apply/armor",  -skill/2);
			     me->add_temp("apply/parry",  -skill/4*3);
                 me->add_temp("apply/dodge",  -skill/4*3);
                 me->add_temp("apply/attack",  skill/4);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/�ں�")){
                 me->add_temp("apply/damage",  -skill/4);
                 me->add_temp("apply/armor",  -skill/6);
                 me->add_temp("apply/parry",  -skill/4);
                 me->add_temp("apply/dodge",  -skill/4);
			     me->add_temp("apply/strength",  -skill/25);
                 me->add_temp("apply/dexerity",  -skill/15);
			     me->add_temp("apply/sword",  -skill/10);
                 me->delete_temp("zxg/jianyi");
             }
             else{
                 message_vision(HIR"�������������֪ͨ����wiz!\n"NOR, me);
             }
           if(living(me) && !me->is_ghost())
              message_vision(HIM"$N������ʽ����ϼ���⻺���չ������������Ľ���������ʧ��\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon, skill);
        return ;
}

int help(object me)
{
    write(YEL"\n��ϼ�񹦡�"HIM"��ϼ����"YEL"����"NOR"\n");
    write(@HELP
	��ϼ���˻�ɽ���ڵĸ������ڣ���ν����ɽ�Ź�����ϼ��һ��
	��Ϊ�˹������ע�⣬ϰ����ϼ����������ɽ�似���������
	����������ϼ��������󣬽���ɽ�����Ľ����̺�����ϼ����ʩ
	չ������������ͬ���졣
	��ϼ�����Ϊ���ֲ�ͬ���ã�ʹ��Ϊ ��set ��ϼ���� xx��
	���У�
	�����ӡ������Ƿ�������ϼ�ھ��������ӽ��⣬���Զ�ʱ��
		�ڴ�������˺�����������ڹ��������
	����Ů����������Ů���⣬�ɶ�ʱ�ڴ�����������Ṧ��
		����Ůʮ��ʽ���Ч�����ѡ�
	��ϣ�ġ�������ɽ������ϣ�Ľ���ʩչ��������ʱ���ڴ��
		��������,����һ�����˺���
	���ںϡ�������ʽ�ں�Ϊһ�塣�͵�����Ƚ����������幥
		��Ч�����ԡ�
	˵����350��С�ɣ�450����ɣ�550����ϼ����ɿ�ʹ���ں�
	Ҫ��
		��ϼ�񹦵ȼ� 450 ���ϣ�
		�����ڹ��ȼ� 450 ���ϣ�
		��ɽ�����ȼ� 450 ���ϣ�
		��ǰ����Ҫ�� 1000 ���ϣ�
		��ǰ����Ҫ�� 500 ���ϡ�

HELP
    );
    return 1;
}
