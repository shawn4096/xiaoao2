// tougu.c ͸����
// by snowman

#include <ansi.h>
//#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int exert(object me, object target)
{        
        object weapon;
        int damage,p;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("͸����ֻ����ս���жԶ���ʹ�á�\n");
        if(!weapon)
                return notify_fail("�����ʹ������������͸�����ھ���\n");        
       // if (me->query_temp("shenghuo/tougu"))
         //       return notify_fail("������ʩչ͸�����ھ���\n");
		if( (int)me->query_skill("shenghuo-shengong",1) < 200 )
                return notify_fail("���ʥ���񹦵ȼ�����������ʩչ͸�����ھ���\n");
        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʩչ͸�����ھ���\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������㣬����ʩչ͸�����ھ���\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("����������㣬����ʩչ͸�����ھ���\n");
        if( (int)me->query("max_jingli") < 2000 )
                return notify_fail("��ľ������㣬����ʩչ͸�����ھ���\n");
        //if( target->is_busy()) 
                //return notify_fail("�Է����Թ˲�Ͼ�أ��㲻æʩչ͸�����ھ���\n");
        me->start_exert(4,"͸����");         
        message_vision(HIW"$N��������"+HIB+"͸����"+HIW+"����һ�ɼ�����������������һ�㣬��"+weapon->query("name")+HIW"�ϴ�����ֱ��"+target->name()+HIW"��\n"NOR,me,target);       
        //me->set_temp("shenghuo/tougu",1); 
		if(random(me->query_skill("force",1)) > target->query_skill("force",1)/3){           
           damage = me->query_skill("force",1)+me->query_skill("shenghuo-shengong",1);
           damage = damage*2 + random(damage);
		 
        if(target->query("neili") > me->query("neili")*2)
             damage = random(10);
		if(target->query("neili")< me->query("neili")/2)
             damage =damage+ me->query("neili")-target->query("neili");        
       
        if (me->query("mjqkdny/pass"))
             damage=damage*2;
		if(damage > 3000){
		   damage=3000+(damage-3000)/10;
           tell_object(target,HBRED"\nͻȻ֮�䣬���ؿ�һʹ���ƺ���һö��ϸ�ļ������һ�¡���һ�´�ʹ\n"+
		   "ͻ�������������Σ�ʵ���ʣ�һ�ɺ���ͻ����Ļ���������ֱ���ķΣ�ʹ����ǣ�\n"NOR);
		}
        else if(damage <= 1000){
              damage = 1000;
              tell_object(target, HIY"\nͻȻ֮�䣬���ؿ�һʹ���ƺ���һö��ϸ�ļ������һ�¡��Һ��㻤���񹦱�\n"+
"��ȫ������������������˿��֮ϸ��ٿ�궸�����ѷ��ѵ���ȴҲ���㲻�ã�\n"NOR);
              tell_object(me, HIY"�����ˡ�͸���롱���ھ��������Է����Ǻ��������ĵֵ���������\n"NOR);
              }
        else tell_object(target, HIB"\nͻȻ֮�䣬���ؿڱ��������һ�¡���ʹ�����Σ�ʵ���ʣ�һ�ɺ���ͻ�����\n"+
"�����񹦣�ֱ�����࣡�������壬������ʧ������һ�̿ɵ�����ʹ��ǣ�\n"NOR);
           target->receive_damage("qi", damage,me);
          // target->receive_wound("qi", damage/2);
           target->receive_damage("neili", damage); 
		   if (target->query("neili")<0) target->set("neili",1);
		 
           limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"ͻȻȫ��һ������ͬ���������һ�£�\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
           if(userp(me) && me->query("env/damage")) 
			   tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+damage+ WHT"�㹥���˺���\n"NOR);
		   
if(userp(target)&& target->query("env/damage"))
			   tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR);
		   me->start_busy(1);
           me->add("neili", -150);
           me->add("jingli", -20);
		   if (me->query("mjqkdny/pass")&&objectp(target))
		   {
			   target->apply_condition("no_exert",1);
			   target->add("max_neili",-1-random(5));
		   }
           target->add_busy(1);
           return 1;
       } else {
          me->add("neili", -50);
          me->add("jingli", -5);
          tell_object(me, HIY"���͸�����ھ���������û����"+target->name()+"���Ѿ�ɢ�ˡ�\n"NOR);
          me->start_busy(1);         
          }
        // me->delete_temp("shenghuo/tougu");  
         
		 return 1;   
}
string exert_name(){ return BLU"��͸���롹"NOR; }

int help(object me)
{
        write(RED"\nʥ����"+BLU"��͸���롹"NOR"\n");
        write(@HELP
	���������ɽ���˵ľ���͸���룬ͨ�������������ۼ�
	�ڱ����ϲ�ͨ������͸���������������˷���ʤ����
	�ü������⿪Ǭ����Ų���ؼ���֮�ںϺ�͸��������
	�������Ե�����������˺���
	���⣺�⿪Ǭ����Ų�ơ��ںϡ����⣬�����׺�Ǭ����
	Ų���ںϱ��죬��������������ſ�,�𵽺���Ҫ�ĸ���
	��Ч��
	
	ָ��;exert tougu

Ҫ��
	��ǰ���� 3500 ���ϣ�
	����� 2000 ���ϣ�
	ʥ���񹦵ȼ� 200 ���ϣ�
	�����ڹ�Ϊʥ���񹦡�        

HELP
        );
        return 1;
}