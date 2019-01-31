// jianqi.c ��Ѫ��, ������ѧ����Ч��,by server 2007/7/26

#include <ansi.h>
//#include <combat_msg.h>
#include <combat.h>

inherit F_CLEAN_UP;


void remove_effect(object me,object weapon);

string *name1 = ({
				"�ؿ�",
				"����",
				"���ϱ�",
				"���ϱ�",
				"��",
				"С��",
				"��ָ",
				"ͷƤ",
				"ǰ��",
				"С��",
				"�β�",
});
int perform(object me, object target)
{
		object weapon;
		string s_name,t_name,s_long,t_long;
		string msg;
		int skill,damage;
		
		skill=me->query_skill("xuedao-daofa",1);
		weapon= me->query_temp("weapon");
        
		if (!me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ���û�Ѫ����\n");

        if(!weapon || weapon->query("skill_type") != "blade")
                return notify_fail("�������޵������ʹ�á���Ѫ����?\n");
        if (!me->query("quest/xd/xddf/huaxue/pass"))
        {
                return notify_fail("��Ѫ������Ѫ���Ų�����ѧ����δѧ�᲻��ʹ�ã�\n");
        }
        
        if((int)me->query_skill("xuedao-jing",1)<350)
                return notify_fail("���Ѫ���������ǳ���޷�ʹ�á���Ѫ������\n");
        if((int)me->query_skill("xuedao-daofa",1)<350)
                return notify_fail("���Ѫ�����������ǳ���޷�ʹ�á���Ѫ������\n");
		if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ������������ʹ�á����ĵ����ľ�����\n");

		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");

        if((int)me->query_skill("force",1)<350)
                return notify_fail("��Ļ����ڹ������ǳ���޷�ʹ�á���Ѫ������\n");
        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ����������ִ�������ʹ������Ѫ�����ľ�����\n");

        if( (int)me->query("neili") < 1200  )
                return notify_fail("�������������\n");

        if( weapon->query("xddf/huaxue") ) 
                return notify_fail("��������Ѿ��޷��ٳ��ܻ�Ѫ���ĵ��������ˡ�\n");

		if( me->query_temp("xddf/huaxue") ) 
                return notify_fail("���Ѿ���ʩչ��Ѫ���������ˡ�\n");

		msg = HBRED+HIW "\n$N����Ѫ�����С���Ѫ��������������"NOR+weapon->query("name")+HBRED+HIW"��˸һƬ����ɫ�ĵ�Ӱ������������������ȥ��\n"NOR;
        msg+=weapon->query("name")+RED"�ϵ�Ѫ�ۺ�Ȼ����һ����а�İ���֮ɫ����Ϊ����,���˵�����\n"NOR;
		message_vision(msg, me);
		weapon->set("xddf/huaxue", 1);

//ԡѪ���ҵ���
        if(me->query_temp("xdj/yuxue")&& weapon->query("xddf/huaxue"))
		{
                damage = me->query_skill("xuedao-jing",1)/8;
                me->add_temp("apply/damage", damage);
				me->set_temp("xddf/hxyxadd",damage);
                message_vision(RED"$N����Ѫ�����ľ������ڱ���֮�ϣ�"NOR+weapon->query("name")+RED"��˸��������Ѫ���â��\n"NOR, me,target);
				call_out("xddf_hxyxadd",1,me,skill/30);
        }

        s_name = weapon->query("name");
        s_long = weapon->query("long");
        t_name = strip(s_name);
        t_long = strip(s_long);

        weapon->set("name",RED+t_name+NOR);
        weapon->set("long",RED+t_long+NOR);
        weapon->set("s_long",s_long);
        weapon->set("s_name",s_name);
        weapon->set("s_rigidity",(int)weapon->query("rigidity"));
        weapon->set("s_sharpness",(int)weapon->query("sharpness"));
        
		weapon->add("rigidity",10);
        weapon->add("sharpness",10);
        

        call_out("remove_effect", 1, me, weapon);
        call_out("xddf_huaxue",1,me,target,weapon);
      //����500��perform busy  
		if (me->query_skill("xuedao-jing",1)<500&&me->query_skill("xuedao-daofa",1))
           me->start_perform(1, "��Ѫ��");

        return 1;
}
//�ͷ������ϱ��������ĸ����˺�
void xddf_hxyxadd(object me,int count)
{
	int damage;
	object weapon;
	if (!me) return;
	damage=me->query_temp("xddf/hxyxadd");
	weapon=me->query_temp("weapon");

	if (!me->is_fighting()
		||!weapon
		||me->query_skill_mapped("blade")!="xuedao-daofa"
		||me->query_skill_mapped("parry")!="xuedao-daofa"
		||weapon->query("skill_type")!="blade"
		||count<0)
	{
		me->add_temp("apply/damage", -damage);
		me->delete_temp("xddf/hxyxadd");
		message_vision(RED"$N�澭����һ���ɶ��������ڱ����ϵ��������������ˣ�\n"NOR,me);
		return;
	}
	call_out("xddf_hxyxadd",1,me,count--);
	
}
//��Ҫ�жϱ�������

void remove_effect(object me,object weapon)
{
       string name;
	   if(!objectp(weapon)) return;
		
		
       if (!weapon->query("xddf/huaxue")) return;

       if (weapon->query("broken")) return;
       
	   
	   //����������

       if (!me){
           weapon->set("name",weapon->query("s_name"));
           weapon->set("long",weapon->query("s_long"));
//           weapon->set("rigidity",(int)weapon->query("s_rigidity"));
//           weapon->set("sharpness",(int)weapon->query("s_sharpness"));
           weapon->delete("xddf/huaxue");
           return;
       }
		
		//message_vision(HIW"$N��������һ����һ���������ֵĽ�����Ȼ����������$n��"+name+NOR,me,target);
		
       if (me->query_temp("weapon") != weapon
         ||!me->is_fighting()
         ||!living(me)
         ||me->query_skill_mapped("force") != "xuedao-jing"
         ||me->query("neili")<200 )
		{
             message_vision(weapon->query("name")+RED+"�ϵİ���Ѫɫ������ȥ,�����ָֻ���ԭ��!\n"NOR,me);
             weapon->set("name",weapon->query("s_name"));
             weapon->set("long",weapon->query("s_long"));
             weapon->set("rigidity",(int)weapon->query("s_rigidity"));
             weapon->set("sharpness",(int)weapon->query("s_sharpness"));
             weapon->delete("xddf/huaxue");
             return;
         }

         call_out("remove_effect", 1, me, weapon);
		 return;
}

void xddf_huaxue(object me,object target,object weapon)
{
    int ap, dp;
	string name;
    object tweapon;
	name = name1[random(sizeof(name1))];

	if(!weapon) return;
    if(!me) return;
    if(!target) return;
    
	tweapon=target->query_temp("weapon");

	if(!weapon->query("xddf/huaxue")) return;
    
	ap = me->query_skill("blade",1);
    dp = target->query_skill("parry",1);

    if(me->query("env/��Ѫ��")=="��Ѫ") {
                message_vision(RED"$Nһ���ӳ�,����"NOR+weapon->query("name")+RED+"һƬ����ѪӰ������$n��"+HIY+name+RED",��ʱ��Ѫ�Ľ�!\n"NOR,me,target);
                target->receive_damage("qi",ap*3,me);			
                if(random(ap)>dp*2/3) target->add_condition("no_exert",1);

				me->add("neili", -100);	
    }
    if(me->query("env/��Ѫ��")=="ѣ��"){
         message_vision(RED"$N����"+weapon->query("name")+RED"�ϰ���ɫ����һ��,$nΪ�������㣬�ƺ���Щѣ��!\n"NOR,me,target);
         target->add_busy(1+random(2));
		 target->receive_damage("jing",ap,me);
    }
	if(objectp(tweapon) && me->query("env/��Ѫ��")=="ն��")
	{

		if( random(ap + dp) > dp && tweapon->query("imbued") < 4 && weapon->query("sharpness") > 3)
		{
			message_vision(RED"$NǱ��Ѫ�����ھ������ǡ���һ�����죬$n���е�"+tweapon->name()+RED"�Ѿ���"+weapon->name()+RED"ն�ϣ�\n"NOR, me, target );
            tweapon->broken("���ϵ�");
			return ;
        }
		else if (random(ap)>dp/3) {
		
			message_vision(CYN "$N�ص�б�����ã�$n����ס�����е�"+tweapon->name()+CYN"���ֶ��ɣ�\n"NOR, me, target );
			target->add_busy(random(2)+1);
			tweapon->move(environment(target));
			target->reset_action();
		}


    }
	call_out("xddf_huaxue",2,me,target,weapon);
	return;
}

string perform_name() {return HBWHT+HIR"��Ѫ��"NOR;}

int help(object me)
{
    write(YEL"\nѪ������"HIM"��Ѫ��"YEL"����"NOR"\n");
	write(@HELP
	��Ѫ�����ǻ�Ѫ���ĵ����ܸ٣�Ϊ�������쵶��
	�ĸ�Ҫ�ļ���Ѫ�������б��Ī��ĵ���������
	�ɴ˶�����Ѫ�����ǽ�ƽʱ�̲��ڵ����е�Ѫ��
	�������ڹ�������ɢ�������˵�ɱ�������޵ĺ�
	�⣬�����Ի���֣�Ҳͬʱ������б���������
	��ս���л����������϶Է������Ĺ�Ч
	
	set ��Ѫ�� ն�� ������϶Է�����
	set ��Ѫ�� ��Ѫ ������õ��ϰ��۸��Է���Ѫ
	set ��Ѫ�� ѣ�� ����߶��������Ѫ��ѣ��

	ָ��: perform blade.huaxue

Ҫ��
	�������  1200 ���ϣ�
	��ǰ����  1000  ���ϣ�
	Ѫ����  450  �����ϣ�
	350����С�ɣ�
	500���Ϊ����ʽ��
	��������Ѫ��������
	�����м�ΪѪ���������ջ�������
	�ֳֵ���������

HELP
   );
   return 1;
}
