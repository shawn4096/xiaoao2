// chaozong.c ��ɽ���� ��������
// modified by sohu@xojh 2013
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);
      
         if( !target
         || !target->is_character()
	     || !living(target)
         || !me->is_fighting(target) )
                return notify_fail("���������ڡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		

        if( me->query("family/family_name") !="��ɽ��" || !me->query("quest/ss/ssj/chaozong/pass") )
                return notify_fail("��û�еõ���ɽ�����洫���޷�ʹ��������ʽ���������ڡ���\n");
        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽�������ܹ�ʹ�����������ڡ�����\n");

        if( (int)me->query_skill("songshan-jian", 1) < 350 )
                return notify_fail("�����ɽ����������죬�޷�ʹ�����������ڡ���\n");
                
        if( me->query_temp("ssj/chaozong"))
                return notify_fail("������ʹ�á��������ڡ���\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 350 )
			if( (int)me->query_skill("lengquan-shengong", 1) < 350 )
            return notify_fail("��ĺ�����������Ȫ�񹦻�򲻹����޷�ʹ�����������ڡ���\n");

        if( me->query_skill_mapped("force") != "hanbing-zhenqi")
			if( me->query_skill_mapped("force") != "lengquan-shengong")
            return notify_fail("�������ʹ�õ��ڹ����ԣ��޷�ʹ�����������ڡ���\n");    

        if (me->query_skill_mapped("sword") != "songshan-jian"
         || me->query_skill_mapped("parry") != "songshan-jian")
                return notify_fail("�������޷�ʹ�á��������ڡ����й�����\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ���������ڡ���\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("�����������������������ʩչ���������ڡ���\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ������ޣ�������ʩչ���������ڡ���\n");

        message_vision(HBYEL+HIG"$N�������أ�˫��ִ����"NOR+weapon->name()+HBYEL+HIG+"���⳯�£��������ϣ�״������\n"+
		        "���������г������һ�㣬��������ɽ�����������ڵ�����ʽ"+NOR+HIR+"���������ڡ���״��ǫ����\n"NOR, me);
		if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("hanbing-zhenqi")/2+me->query_skill("songshan-jian");
      	improve = skill/5 + random(skill/5);//ԭ����5
      	if ( improve > 100 ) improve = 100 + random(improve-100) / 5;

        me->set_temp("ssj/chaozong", improve);
		me->set_temp("ssj/chaozong1",1);
        me->add_temp("apply/parry", improve);
        //me->add_temp("apply/sword", improve);
        me->add_temp("apply/defense", improve);
        call_out("remove_effect", 1,  me, weapon, improve);
		//һ���Զ��������ơ���
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("ssj/chaozong1");

        if (me->query_skill("songshan-jian",1)<450) me->start_perform(2, "���������ڡ�");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(!me->is_fighting()
         ||!weapon
		 ||weapon->query("skill_type")!="sword"
         || me->query_skill_mapped("sword") != "songshan-jian"
         || me->query_skill_mapped("parry") != "songshan-jian"
         || count < 1 ){
          i = me->query_temp("ssj/chaozong");
          me->add_temp("apply/parry", -i);

          me->add_temp("apply/defense", -i);
          me->delete_temp("ssj/chaozong");
          message_vision(HIW"$Nʹ��"NOR"��"HIR"��������"NOR+HIW"������ɽ�����ķ�����Ч����ʧ��\n"NOR, me);
		  me->start_perform(3,"���������ڡ�");
		
  return;
        }
        else {
           call_out("remove_effect", 1, me, weapon, count -1);
        }
}              
string perform_name(){ return HIC"��������"NOR; }

int help(object me)
{
        write(HIG"\n��ɽ����֮"+HIY"���������ڡ���"NOR"\n\n");
        write(@HELP
	���������ڡ��ǵ�ϵ���ڵ���ɽ��������һ�к������ǹ�����
	��ɽ���Ӻͱ��ɳ������У�������ʹ�ô��У���˼��˵��
	�ǸҺ�ǰ�����֣�ֻ���������˼�ָ�̵���˼������ʩչ
	����ɽ�����ķ��������������
	
	ָ�perform sword.chaozong

Ҫ��
	��ǰ�������� 1500 ���ϣ�
	����������� 3500 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ɽ�����ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	���ֳֽ���������
	�����ڹ�Ϊ����������450���ɡ�
HELP
        );
        return 1;
}
