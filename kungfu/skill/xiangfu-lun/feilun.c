// feilun.c ���֣��ɳ�ȥ��������������2��
// Ϊ����˥��by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_DBASE;
inherit F_SSERVER;
void feilun_finish(object me);
void checking(object me, object target, int num);

string perform_name(){ return HBYEL+HIW"���־���"NOR; }

//string *falun=({ "����","����","ͭ��","Ǧ��","����"});
string *falun=({HIY"����"NOR,HIW"����"NOR,YEL"ͭ��"NOR,WHT"Ǧ��"NOR,BLU"����"NOR});
string fl;

int perform(object me, object target)
{
        object weapon, ob;
        int lv, damage,num;

        lv = (int)me->query_skill("xiangfu-lun", 1); 
        damage = lv + random(lv/2) + (int)me->query_skill("hammer",1);

		num=2+random(4);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                       return notify_fail("�����־�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("xfl/feilun"))
                       return notify_fail("������ʹ�á����־�������\n");
 
        if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "hammer"
          || me->query_skill_mapped("hammer") != "xiangfu-lun"
          || me->query_skill_mapped("parry") != "xiangfu-lun")
                 return notify_fail("���������֣����ʹ�á����־�������\n");
                 
        if((int)me->query("max_neili") < 5000 )
 
			return notify_fail("���������Ϊ�������޷�ʹ�á����־�������\n");
        if( (int)me->query("neili") < 1000 )
 
			return notify_fail("�������������\n");
		if( (int)me->query("jingli") < 1000 ) 
			return notify_fail("��ľ���������\n");
        if( me->query_skill("xiangfu-lun", 1) < 400 )

			return notify_fail("��ġ������֡��ȼ��������޷�ʹ�á����־�������\n");
		if( me->query_skill("longxiang-boruo", 1) < 400 )
			return notify_fail("��ġ�������������ȼ��������޷�ʹ�á����־�������\n");
        if( me->query_skill_mapped("force") !="longxiang-boruo" )
			return notify_fail("�㼤�����ڹ����ԣ��޷�ʹ�á����־�������\n");
        if( me->query_skill("hammer", 1) < 400 )
            return notify_fail("��ġ������������ȼ��������޷�ʹ�á����־�������\n");
                 
        if( (int)me->query_str() < 70 )
            return notify_fail("�������������㣬�����־���������������˵������̫���ˡ�\n");

        message_vision(HBYEL+HIW "\n$N�����е�"NOR+weapon->name()+HBYEL+HIW"�ɳ�ȥ"+num+"��������ת״�Ի��η���$n��ʹ�������־�������"NOR"\n" NOR, me,target);
		message_vision(YEL "\n$N�����µ�����ִ�����У�������ϣ��趯���������ɵ����ң��ֿɵ����ƣ�ͬʱ�������ֳ����絶ذ��"NOR"\n" NOR, me,target);
        //me->start_perform(3+random(3), "�����־�����");
        ob = me->select_opponent();
        me->set_temp("xfl/feilun",lv);
		if (me->query_skill("xiangfu-lun",1)<450)
		{
			me->start_perform(1,"���־���");
		}
		me->add_temp("apply/attack",lv/4);
		me->add_temp("apply/hammer",lv/6);
		me->add_temp("apply/damage",lv/6);
	

		call_out("checking", 1, me, target,num);
		
        return 1;
}

void checking(object me, object target, int num)
{

       object weapon;
		int lvl;
		string *falun=({HIY"����"NOR,HIW"����"NOR,YEL"ͭ��"NOR,WHT"Ǧ��"NOR,BLU"����"NOR});
		
		if (!me) return;
		
		lvl=me->query_skill("xiangfu-lun",1)+me->query_skill("longxiang-boruo",1)/2;

		fl=falun[random(sizeof(falun))];
		
	
		if (num < 0 ||!objectp(target) || !me->is_fighting())
		{
		    feilun_finish(me);
			me->delete_temp("xfl/feilun");
			//message_vision(HIM"\n$N����һ���������ɳ�ȥ��"NOR+fl+HIM"½���ջ����У����־����չ���ϣ�\n" NOR, me,target);
			return;
		}
        if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "hammer") {
                     //  tell_object(me, "\n���������֣�����ֹͣ�ˡ����־���������ʹ��\n" NOR);
                       
					   feilun_finish(me);
                       me->delete_temp("xfl/feilun");
                       return;
        }
	    if (me->query_temp("xfl/feilun"))
	    {
	    
           message_vision(HIM"\nֻ��$N������һ���Ϻȣ����������������������ȻһȭӲ����������"NOR+fl+HIM"�ϣ����ַ����͵�һת��ֱ׷��$n��\n" NOR, me,target);
           {             
				if (me->is_fighting(target))

					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                 me->add("neili", -random(400));

			}
		  }
 		   call_out("checking", 2, me,target,num-1); 
                                 
 }


void feilun_finish(object me)
{
        int lv;
		object weapon=me->query_temp("weapon");
        if ( !objectp( me ) ) return;
	//    lv=me->query_temp("xlf/feilun");
		lv = (int)me->query_skill("xiangfu-lun", 1); 
		me->add_temp("apply/attack",-lv/4);
		me->add_temp("apply/hammer",-lv/6);
		me->add_temp("apply/damage",-lv/6);
		me->delete_temp("xfl/feilun");
		if (weapon)
        		message_vision(HIM"\n$Nһ�ס����־�����ʹ�꣬"+weapon->query("name")+HIM"���ֻص����С�\n"NOR, me);
		else  message_vision(HIM"\n$Nһ�ס����־�����ʹ�꣬���ɳ�ȥ������ȴ��֪�����ںδ���\n"NOR, me);

	
        //me->start_busy(2);
        me->start_perform(2,"���־���");
		return;
} 

int help(object me)
{
   write(YEL"\n������֮��"HBYEL+HIW"���־���"YEL"����"NOR"\n");
   write(@HELP
	�������ڽ��ַ�����ɨ���������ԭ��һ�ֲ��ܽ�ս�����
	ʹ�ó����뻭���ˡ�������˥�������˷�������֮����ȫ����
	��֮�����������������ַ�����ת���������������տ�ɽ��
	�����ɵ�֮�������޼���һ�мȳ�������������
	���־������ǽ��ַ�����������֮�أ����������ӷɳ�ȥ����
	Ȼ���ֳּ��������ٽ�������Զ��������ң���Ӧ������Զ
	�����ֿɽ����ս�������а������ص㣬�־��д��Ӻ͵�����
	�㡣ʵ�˽����־�������Ҫ�������ܡ�

	ָ��;perform hammer.feilun

Ҫ��
	�����ַ��ȼ� 400 ����
	���������ȼ� 400 ����
	��������ȼ� 400 ����
	����������� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	�������Ҫ�� 70  ����
	�����м�Ϊ������
	��������Ϊ������
	�����ڹ�Ϊ�������
	
HELP
   );
   return 1;
}
/**/