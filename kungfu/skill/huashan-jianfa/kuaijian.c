// kuaijian.c ���콣
// by darken@SJ
// modified olives@SJ
// Update By lsxk@hsbbs 2007/6/14
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name() {return HIG"���콣"NOR;}

int perform(object me, object target)
{
        object wp;
		wp=me->query_temp("weapon");
		if( !target || target == me) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���콣ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    	
		if (me->query("huashan/quest") == "����")
        {
           if (me->query_skill_mapped("force") != "zixia-gong"
             &&me->query_skill_mapped("force") != "huashan-qigong" )
                return notify_fail("����ڹ������޷�ʹ�á����콣����\n");
        } 

        if( (int)me->query_dex() < 70 )
                return notify_fail("�������������������㣬����ʹ�ÿ��콣��\n");
        
        if( (int)me->query_skill("zixia-gong", 1) < 400
          &&(int)me->query_skill("huashan-qigong", 1) < 400)
                return notify_fail("��Ļ�ɽ�����ڹ����δ�����޷�ʩչ���콣��\n");

        if( (int)me->query_skill("dodge",1) < 400 )
                return notify_fail("���콣��Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( (int)me->query_skill("sword",1) < 400 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ�ÿ��콣��\n");

        if( (int)me->query("neili") <= 5000 )
                return notify_fail("�����������ʹ�ÿ��콣��\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�ÿ��콣��\n");

        if( me->query_temp("hsj_kf",))
                return notify_fail("���������ÿ��콣��\n");

        if(!me->query_temp("weapon") || wp->query("skill_type") != "sword" 
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޽�����ʹ�ÿ��콣����\n");

        message_vision(HBGRN+HIW"$N����һ����Х��б�ж�ǰ����������ֱ����Ѹ���ޱȣ�δ�������У��������ѷ�������������$N������磬���糱ˮ�㹥��$n��\n"NOR
		               +HBGRN+HIW"Խ��Խ�죬����Ҳ�ǽ��졣����һ������һ����������ķ���ҲԽ��Խǿ��һ�����ʽ�����콣����̼�ȫ��$n�����к���\n"NOR, me, target);
        me->set_temp("hsj_kf",1);
        me->add("neili",-1000);
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/6);
        me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/10);
		//���Ը�������
		if(me->query("gender")=="����")
		{
          me->add_temp("apply/sword",me->query_skill("huashan-jianfa",1)/6);
		  me->add_temp("apply/strength",me->query_skill("huashan-jianfa",1)/6);
		}
		//���������˺�������
		if (me->query("quest/huashan")=="����")
		{
          me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/7);
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/5);
		}
        call_out("kuangfeng", 0, me, target);
        me->start_perform(999,"�����콣��");
        return 1;
}

void kuangfeng(object me, object target)
{
        int i;
        object weapon;
        
        if (!me) return;
        weapon= me->query_temp("weapon");
        //��busy������ֹͣ��磬�����ڻ����
        if(me->is_busy() && me->query("quest/huashan") != "����"){
            message_vision(HIG"$N�ġ����콣��ίʵ�켫��һ�������Ƭ�̼����ʹ�ꡣ\n"NOR, me);
            me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
            me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
			if(me->query("gender")=="����")
		    {
				me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
				me->add_temp("apply/strength",-me->query_skill("huashan-jianfa",1)/6);
	     	}
            me->delete_temp("hsj_kf");
            me->start_busy(3+random(3));
            me->start_perform(2+random(3),"�����콣��");
            return;
        }
        if (me->is_fighting(target) &&
    //       !me->is_busy()          &&
            (int)me->query("jingli") > 1000 &&
            (int)me->query("neili") > 2000 &&
           objectp(target) && 
           !target->is_ghost() &&
           !me->is_ghost() && 
           me->query_temp("hsj_kf")<37 &&
           environment(me) == environment(target) &&
           weapon &&
           weapon->query("skill_type") == "sword"  
            ) {
               message_vision(HIG"�Թ�����ֻ���������ˣ����ϡ����ϱ�$N����������ļ���ε��������ۣ����������ĺ��ˡ�\n"NOR, me);
               if((int)me->query_temp("hsj_kf")%3==0 && me->query("quest/huashan") == "����" && random(2)){
                  message_vision(HBRED"$n���������˿�Ľ��У����°����Ծ���ȫ�����ػ���$N���������ƣ�\n"NOR, me, target);
                  target->add_temp("lost_attack",3+random(3)); 
			      target->add_busy(1);
             }
            for (i = 0; i < 4; i++) {
              if (me->is_fighting(target)) {
               if (me->query("quest/huashan") == "����"){
					me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/3);
					me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/5);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(5)?3:1);
					me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/3);
					me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/5);
			  
               } else COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           }
          } 
          me->add("neili", -100-random(50));
          me->add("jingli", -80-random(30));
          me->add_temp("hsj_kf",1);
          call_out("kuangfeng", 1, me, target);
          return;
        }
        message_vision(HIG"$N�ġ����콣��ίʵ�켫��һ�������Ƭ�̼����ʹ�ꡣ\n"NOR, me);
        me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
		if (me->query("quest/huashan")=="����")
		{
          me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/7);
          me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/5);
		}
		if(me->query("gender")=="����")
		{
          me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
		  me->add_temp("apply/strength",-me->query_skill("huashan-jianfa",1)/6);
		}
        me->delete_temp("hsj_kf");
        if(me->query("gender")!="����")
             me->start_busy(3+random(3));
        else me->start_busy(1+random(2));
        me->start_perform(2+random(3),"�����콣��");
}

int help(object me)
{
	write(WHT"\n��ɽ������"HIG"���콣"WHT"����"NOR"\n");
	write(@HELP
    ���콣�����б�������������֮�죬����֮�Ͽ������κ��书����
    ����ϸ��£����˻�ɽ���ھ��������־�ѧ����ɽ���ڵ����ռ�����
    ���й���һ������У�һ���ǳɣ�����������ˮ���ʹ���������Թ�
    ��Ҳ��Ϊ�佣��֮��������Ȼ�����ж�ʹ���ߵĽ����������ڹ�Ҫ
    ���ĸߡ���ɽ���ڵ���Ҳ��ʹ�ã�������ȴ��������֮�����ĳɡ�
	��Ҫע����ǣ������˽��ھ����������������������ǿ�������ڹ�
	Ҫ��Ҳû��������ô�ϸ�
    
	ָ�perform sword.kuaijian

Ҫ��
	��ɽ���� ���� ��ϼ�� 400��
	���������� 70  ����
	���������ȼ� 400 ����
	�����Ṧ�ȼ� 400 ����
	��ǰ�������� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϡ�
HELP
	);
	return 1;
}
