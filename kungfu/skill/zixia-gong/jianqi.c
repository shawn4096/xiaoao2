// jianqi.c ��ϼ����, ������ѧ����Ч��,by server 2007/7/26

#include <ansi.h>

inherit F_CLEAN_UP;

string exert_name() {return HIG"��ϼ����"NOR;}

void remove_effect(object me,object weapon);
string *name1 = ({
"����Ѩ",
"���Ѩ",
"����Ѩ",
"����Ѩ",
"����Ѩ",
"�Ϲ�Ѩ",
"���Ѩ",
"�ٻ�Ѩ",
"̫��Ѩ",
"��ǿѨ",
"��̨Ѩ"
});
int exert(object me, object target)
{
    object weapon = me->query_temp("weapon");
    string s_name,t_name,s_long,t_long;

        if (!me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ������ϼ������\n");

        if(!weapon || weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ����ϼ����?\n");
        if (!me->query("quest/huashan/zixia/pass"))
        {
			if(userp(me) && me->query("quest/huashan")!="����")
                return notify_fail("��ϼ���˻�ɽ���ھ�ѧ����ǻ�ɽ���ڵ��ӣ�����͵ѧ������ϼ�񹦣�\n");
        }
        
        if((int)me->query_skill("zixia-gong",1)<350)
                return notify_fail("�����ϼ�񹦻����ǳ���޷�ʹ�á���ϼ��������\n");

        if((int)me->query_skill("force",1)<350)
                return notify_fail("��Ļ����ڹ������ǳ���޷�ʹ�á���ϼ��������\n");

        if( (int)me->query("neili") < 1200  )
                return notify_fail("�������������\n");

        if( weapon->query("zxg/jianqi") ) 
                return notify_fail("��������Ѿ��޷��ٳ�����ϼ�����������ˡ�\n");

        weapon->set("zxg/jianqi", 1);
        message_vision(HIM"$N����һ������,����������ʢ,������ϼ���ھ���������"+weapon->query("name")+HIM"��,ɲ�Ǽ�,"+
            weapon->query("name")+HIM+"��ʱ��һ�ɽ���������\n" NOR, me);

        s_name = weapon->query("name");
        s_long = weapon->query("long");
        t_name = strip(s_name);
        t_long = strip(s_long);

        weapon->set("name",MAG+t_name+NOR);
        weapon->set("long",MAG+t_long+NOR);
        weapon->set("s_long",s_long);
        weapon->set("s_name",s_name);
        weapon->set("s_rigidity",(int)weapon->query("rigidity"));
        weapon->set("s_sharpness",(int)weapon->query("sharpness"));
        weapon->add("rigidity",10);
        weapon->add("sharpness",10);
        //if((int)me->query("rigidity")>12) weapon->set("rigidity",12);
        //if((int)me->query("sharpness")>12) weapon->set("sharpness",12);

        call_out("remove_effect", 1, me, weapon);
        call_out("zixia_jianqi",1,me,target,weapon);
        if (me->query_skill("zixia-gong",1)<550)
           me->start_exert(2+random(2), "��ϼ����");

        return 1;
}

void remove_effect(object me,object weapon)
{
       string name;
	   if(!objectp(weapon)) return;

       if (!weapon->query("zxg/jianqi")) return;

       if (weapon->query("broken")) return;
       
	   

       if (!me){
           weapon->set("name",weapon->query("s_name"));
           weapon->set("long",weapon->query("s_long"));
//           weapon->set("rigidity",(int)weapon->query("s_rigidity"));
//           weapon->set("sharpness",(int)weapon->query("s_sharpness"));
           weapon->delete("zxg/jianqi");
           return;
       }
		
		//message_vision(HIW"$N��������һ����һ���������ֵĽ�����Ȼ����������$n��"+name+NOR,me,target);
		
       if (me->query_temp("weapon") != weapon
         ||!me->is_fighting()
         ||!living(me)
         ||me->query_skill_mapped("force") != "zixia-gong"
         ||me->query("neili")<200 ){
             message_vision(weapon->query("name")+HIM+"������������ȥ,�����ָֻ���ƽ��!\n"NOR,me);
             weapon->set("name",weapon->query("s_name"));
             weapon->set("long",weapon->query("s_long"));
             weapon->set("rigidity",(int)weapon->query("s_rigidity"));
             weapon->set("sharpness",(int)weapon->query("s_sharpness"));
             weapon->delete("zxg/jianqi");
             return;
         }

         call_out("remove_effect", 1, me, weapon);
}

void zixia_jianqi(object me,object target,object weapon)
{
    int ap, dp;
	string name;
	name = name1[random(sizeof(name1))];
    if(!weapon) return;
    if(!me) return;
    if(!target) return;
    if(!weapon->query("zxg/jianqi")) return;
    ap = me->query("neili");
    dp = target->query("neili");

    if( random(ap + dp) > dp*6/5  && random((int) me->query_skill("zixia-gong",1)) > 450 ) {
                message_vision(HIM"$NͻȻ΢΢һ����,����������ʢ,һ�ɽ�����"+weapon->query("name")+HIM+"�ϼ������,����$n��"+HIR+name+HIM",$nֻ���Լ���Ϣ��Ҳ�޷�����!\n"NOR,me,target);
                if(!target->query_condition("no_exert")) target->add_condition("no_exert",1+random(2));
                target->add_busy(3+random(2));
                me->add("neili", -100);
                call_out("zixia_jianqi",2,me,target,weapon);
    }
    else{
         message_vision(MAG"$N����������������,����"+weapon->query("name")+MAG"�ྐྵ���������Ϲ�!\n"NOR,me,target);
         call_out("zixia_jianqi",2,me,target,weapon);
    }
}
int help(object me)
{
    write(YEL"\n��ϼ�񹦡�"HIM"��ϼ����"YEL"����"NOR"\n");
write(@HELP
   "��ɽ�Ź�����ϼ��һ"����ϼ���˻�ɽ������߾�ѧ��
	������ϼ�����������ڽ�������ϼ�ھ����ڽ�����
	�����������˵У������ǳ���550���ںϺ󳹵׷�Ծ��
	
	ָ�exert jianqi

Ҫ��
	��ϼ�� 150 ����
	�����ڹ� 150 ����
	��ǰ���� 1200 ���ϣ�
	ʹ�ý���������

HELP
   );
   return 1;
}
