//dingyang.c ������;
//Modify By jpei
//��һ�ƴ�ѧ�ö��������Ҫ������ϰ���ܻ�Ȼ��ͨ
//������Ϊtry,��������
 
#include <ansi.h>
inherit F_SSERVER;
 
string exert_name() {return HBWHT+HIR"������"NOR;}

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, p, force, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("xiantian-gong",1);
		//count=skill/2;
        if( !(me->is_fighting() ))
                return notify_fail("�������롹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((string)me->query_skill_mapped("force") != "xiantian-gong" )
		  return notify_fail("���������롹���ǵ������칦�ľ�ѧ��\n");

        if( skill < 450)
                return notify_fail("������칦��������, ����ʹ�á������롹��\n");

        if( me->query("neili") < 2000 )
                return notify_fail("��������������޷����á������롹��\n");
		//����ͯ�����޷���ʹ������
		if( me->query("marry"))
                return notify_fail("���Ѿ�����ͯ�����޷��������칦�����������롹��\n");
       if( !me->query("quanzhen/force")  )
                return notify_fail("����Ȼ��˵���������롹�����ǲ�֪��������á�\n");     

       if( me->query("max_neili") < 15000 )
                return notify_fail("��������������޷����á������롹��\n");
 
       msg = HIY"\n$NĬ�����칦����������������һ��ָָ����ӭ��һָ����ֱ����$nü�ģ����ǵ���һָ���Ƹ�󡹦������������"HIR"������"HIY"������\n"NOR;

         ap = me->query_skill("force",1) + skill;
         dp = target->query_skill("force",1)+ target->query_skill("parry",1);

	   if( dp < 1 ) dp = 1;
  	
       if( me->query("quanzhen/force")=="try" )
        {        ap = ap/4;
    	         msg += HIY"ֻ��$N��ѧէ��֮�£������ܺܺõķ��Ӷ������������\n"NOR;

         if( me->query("kar")<31 && random(me->query("kar"))>28 && random(50)==5 && me->query_skill("xiantian-gong",1)>=450 ){

		      	msg += HBBLU"$N��Ȼ�������飬���칦���������У���ȱ�裬��������أ���������������֮���������������Ȼ��ͨ��\n"NOR;	     
	           me->set("quanzhen/force","pass");
	          }

        }         
       message_vision(msg, me, target);
      //||random( me->query_skill("force",1)) > target->query_skill("dodge",1)/2 
       if((random(ap) >dp/2)		    
		   ||( me->query("str")>40 && random( me->query("combat_exp",1)) > target->query("combat_exp",1)/2 ) 
		   ||(!userp(target) && me->query("str") >=45) 
		   )
		{

		  if(userp(me))
              me->add("neili",-(500+random(500)));
           msg = HIM"\n$n������������$Nһָ���У�ֻ������������͸����룬��Ȼ��嫣�Ī��֮�С�ȫ�����������⣬���º��Ļ����ɢ��\n" NOR;   
           message_vision(msg, me, target);
      
           p = (int)me->query_skill("force") + random(me->query_skill("force")*3);
   
           force = target->query_skill_mapped("force");
 	     switch(force) {
		    case "huntian-qigong":
			if( intp(p = target->query_temp("htqg/powerup")) ){
				target->add_temp("apply/armor", - p*2);
				target->add_temp("apply/dodge", - p);
				target->delete_temp("htqg/powerup");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ�����������Ч����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "xixing-dafa":
			if( intp(p = target->query_temp("xxdf/xixing")) ){
				target->add_temp("apply/attack", - p);
				target->add_temp("apply/dexerity", - p/10);
				target->delete_temp("xxdf/xixing");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ����Ǵ󷨵�Ч����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}

		case "xiantian-gong":
			if( intp(p = target->query_temp("xtg/wuqi")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/strike", - p/10);
                                target->add_temp("apply/attack", - p /10);
				target->delete_temp("xtg/wuqi");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ�������Ԫ��Ч����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "bahuang-gong":
			if( intp(p = target->query_temp("bhg/duzun")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/hand", - p/10);
				target->add_temp("apply/attack", - p*5 /10);
				target->delete_temp("bhg/duzun");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ��˻Ĺ�Ψ�Ҷ���Ч����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "beiming-shengong":
			if( intp(p = target->query_temp("bmsg/bm")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/attack", - p/5);
				target->add_temp("apply/intelligence", - p/10);
				target->add_temp("apply/dexerity", - p /10);
				target->delete_temp("bmsg/bm");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ���ڤ������Ч����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "huashan-qigong":
			if( intp(p = target->query_temp("hsqg/yjs")) ){
				target->add_temp("apply/attack", - p/2);
				target->delete_temp("double_attack");
				target->delete_temp("hsqg/yjs");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ��������㣬Ԧ��ʽЧ����Ȼ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "zixia-gong":
			if( target->query_temp("zxg/zixia") ){
				target->delete_temp("double_attack");
				target->delete_temp("zxg/zixia");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱����ƣ��������㣬��ϼ����Ч����ʧ�ˣ�\n"NOR);
				break;
			}

		case "yijin-jing":
			if( intp(p = target->query_temp("fanzhen")) ){
				target->add_temp("apply/armor", - p);
				target->add_temp("apply/parry", - p);
				target->add_temp("apply/attack", - p);
				target->delete_temp("fanzhen");
				target->delete_temp("no_skill_hit_ob");
				                                                      target->add("neili", -p*100);
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,����ղ������񹦡���ЧӦҲ��Ӧ����ʧ�ˣ�\n"NOR);
				break;
			}
		case "jiuyang-gong":
			if( intp(p = target->query_temp("jiuyang/powerup")) ){
	                                        target->add_temp("apply/attack", - p);
	                                        target->add_temp("apply/dexerity", - p/10);
                                                      target->add_temp("apply/armor", - p/4);
                                                      target->delete_temp("fanzhen");  
                                                      target->add("neili", -p*100);
	                                        target->delete_temp("jiuyang/powerup");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,�������񹦡���ЧӦҲ��Ӧ����ʧ�ˣ�\n"NOR);
				break;
			}
		case "linji-zhuang":
			if( target->query_temp("ljz/riyue") ){
				target->delete_temp("ljz/riyue");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,�����¡�ׯ�������֮������ɢ������֮�䣡\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/yinyang")) ){
				target->add("max_qi", - p);
				target->receive_wound("qi", p, "��������ׯ���ƣ�������");
				target->delete_temp("ljz/yinyang");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,��������ׯ������ЧӦҲ��ʧ�ˣ�\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/fengyun")) ){
				target->add_temp("apply/dexerity", - p);        
				target->delete_temp("ljz/fengyun");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,�����ơ�ׯЧ����ʧ���Ծ����ĳ�����һЩ��\n"NOR);
				break;
			}
			if( target->query_temp("ljz/wuwo")){
				target->delete_temp("ljz/wuwo");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,�����ҡ��ķ����ƣ��ָֻ���ԭ�����㣡\n"NOR);
				break;
			}
		case "yinyun-ziqi":
			if( target->query_temp("tj/̫��") ){
				target->delete_temp("tj/̫��");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,��æ֮�У�̫������������У�ЧӦҲ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "dulong-dafa":
			if( intp(p = target->query_temp("sld/wudi2") ) ){
				target->add_temp("apply/strength", -p/20);  
				target->add_temp("apply/attack", -p/3);
				target->delete_temp("double_attack");
				target->delete_temp("sld/wudi2");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi", target->query("max_qi"));
				tell_object(target, HIR"������һ�ɣ���Ҳ֧�ֲ�ס�ˣ���\n"NOR);
				break;
			}
		           if( intp(p = target->query_temp("sld/wudi1")) ){
				target->add_temp("apply/strength", -p/20);
				target->add_temp("apply/attack", -p/4);
				target->delete_temp("sld/wudi");
				target->delete_temp("sld/wudi1");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi",target->query("max_qi"));
				tell_object(target, HIR"������һ�ɣ�����������һ����ͻȻ������������\n"NOR);
				break;
			}
		case "hanbing-zhenqi":
			if ( intp(p = target->query_temp("hbzq/huti")) ){
				target->add_temp("apply/parry", -p);
				target->add_temp("apply/dodge", -p);
				target->delete_temp("hbzq/huti");
				tell_object(target, HIR"������ĺ���ɢ�����������𵽱����������ˡ�\n"NOR);
				break;
			}
			if( target->query_temp("ss/focus")){
				target->delete_temp("ss/focus");
				tell_object(target, HIR"�㻤����������������ƣ�����ĺ���������ɢȥ�ˡ�\n"NOR);
				break;
			}
			if( target->query_temp("ss/hb")){
				target->delete_temp("ss/hb");
				tell_object(target, HIR"�㻤����������������ƣ����ϵĺ���������ɢȥ�ˡ�\n"NOR);
				break;
			}
		case "huagong-dafa":
			if( intp(p = target->query_temp("hgdf/judu")) ){
				target->add_temp("apply/armor", -p);
				target->delete_temp("hgdf/judu");
				tell_object(target, HIR"�㻤����������������ƣ�����һ�ɣ����۶���ȫ�����ˣ���\n"NOR);
				break;
			}
			else if( intp(p = target->query_temp("hgdf/huadu")) ){
				target->add_temp("apply/dodge", -p); 
				target->add_temp("apply/armor_vs_force", -p/2);           
				target->delete_temp("hgdf/huadu");
				tell_object(target, HIR"�㻤����������������ƣ�����һ�ɣ��������۶���ȫ�����ˣ���\n"NOR);
				break;
			}
		case "yunu-xinjing":
			if( target->query_temp("gm/xinjing") ){
				p  = target->query_temp("gm/xinjing");
				target->add_temp("apply/intelligence", -p/10);
				target->add_temp("apply/dexerity", -p/10);
				if ( target->query_skill("yunu-xinjing", 1) > 200 ){
					target->add_temp("apply/attack", -p/5);
                                                                      target->add_temp("apply/damage", -p/8);
					if ( target->query("gender") == "Ů��") {
						target->add_temp("apply/dodge", -p/10);
						target->add_temp("apply/parry", -p/10);
						target->add_temp("apply/armor", -p/10);
					}
					if ( target->query("gender") == "����") {
						target->add_temp("apply/strike", -p/10);
						target->add_temp("apply/parry", -p/10);
						target->add_temp("apply/armor", -p/10);
					}
				}
				target->delete_temp("gm/xinjing");
				tell_object(target, HIR"�㱻������ָ�����У������񹦱�����,���ľ����־�ЧӦҲ��ʧ�ˣ�\n"NOR);
				break;
			}
		case "shenyuan-gong":
			if ( intp(p = target->query_temp("shenyuan")) ){
				target->add_temp("apply/parry", -p/3);
				target->add_temp("apply/dexerity", -p/20);
				target->delete_temp("shenyuan");
				tell_object(target, HIR"�㻤����������������ƣ�������ʽ�Ѿ������ˡ�\n"NOR);
				break;
			}
		case "xuantian-wuji":
			if ( intp(p = target->query_temp("kl/riyue")) ){
				target->add_temp("apply/parry", -p/2);
				target->add_temp("apply/armor", -p/2);
				target->delete_temp("kl/riyue");
				tell_object(target, HIR"�㻤����������������ƣ��޼������޷��𵽱��������ˡ�\n"NOR);
				break;
			}
			if ( intp( p = target->query_temp("kl/taxue")) ) {
				target->add_temp("apply/dodge", -p);
                                                        target->add_temp("apply/dexerity", -p);
				target->delete_temp("kl/taxue");
				tell_object(target, HIR"�����˽Ų������ظ���������\n"NOR);
				break;
			}
		case "longxiang-boruo":
			if ( intp(p = target->query_temp("xs/shield")) ) {
				target->add_temp("apply/dodge", -p);
				target->add_temp("apply/armor", -p*2);
				target->delete_temp("xs/shield");
				tell_object(target, HIR"�㻤����������������ƣ����Ϻ��һ�����ǽ�žž���켸����ɢȥ�˻���������\n" NOR);
				break;
			}
			if ( intp(p = target->query_temp("xs/longxiang")) ) {
				target->add_temp("apply/attack", -p);
				target->delete_temp("xs/longxiang");
				tell_object(target, HIR"�㻤����������������ƣ���������һ�����ָֻ��糣��\n" NOR);
				break;
			}
		case "qiantian-yiyang":
			if( intp(p = target->query_temp("dali_jing")) ){
				target->add_temp("apply/intelligence", -p);
				target->delete_temp("dali_jing");
				tell_object(target, HIR"�㻤����������������ƣ��޷�����Ǳ���ˡ�\n" NOR);
				break;
			}
		case "guiyuan-tunafa":
			if ( intp(p = target->query_temp("tz/focus")) ){
				target->add_temp("apply/attack", p);
				target->add_temp("apply/strength", p);
				target->delete_temp("tz/focus");
				tell_object(target, HIR"�㻤����������������ƣ�������Щί�٣������漴�ָ���̬��\n"NOR);
				break;
			}
		case "kurong-changong":
			if( intp(p = target->query_temp("krcg_kurong")) ){
				target->delete_temp("krcg_kurong");
				target->add_temp("apply/armor", -p);
				target->add_temp("apply/parry", -p);
				tell_object(target, HIR"�㻤����������������ƣ������١���������ɢ�ˣ�\n" NOR);
				break;
			}	

			case "hamagong":
             if( intp(p = target->query_skill("hamagong",1)) && target->query("oyf/hamagong",1)<3 ){

				target->start_busy(p/10);
				target->add_temp("apply/force", -p);
				target->add_temp("apply/damage", -p);
								target->add_temp("apply/attack", -p);
								target->add_temp("apply/dodge", -p);
								target->add_temp("apply/parry", -p);
							   target->add("neili", -p*200);
				tell_object(target, HIR"�������˸�󡹦���ǣ���ȫ������ʱ��ʧ��\n" NOR);
				break;
		      }
              if( target->query_temp("hmg_nizhuan") && target->query("oyf/hamagong",1)==3 ){

                 message_vision(HIW "\n$n��Ȼ�������澭�����ɹ���ȫ������ת����������$Nһָ��ȥ��ֻ�������аܸ\n"
				  +"���е�λ����ȷ������$n�������ң�������������ţ�뺣��˿���������á�\n" NOR, me,target);
				break;
		       	}
				
		case "bihai-chaosheng":
			if( intp(p = target->query_temp("thd/maze")) ){
				target->delete_temp("thd/maze");
				target->add_temp("apply/dexerity", -p/10);
				target->add_temp("apply/parry", -p /2);
				target->add_temp("apply/dodge", -p /2);

              target->delete_temp("thd/mazed");
				tell_object(target, HIR"�㻤����������������ƣ���Ͼ�˼��������󣬽���������¾ͱ���ɢ�ˣ�\n" NOR);
				break;
			}
          }
                
				qi_wound = ap * 4 +random(ap*2) ;

				neili_wound = ap * 3 +random(ap*3);
                
                if(neili_wound > target->query("neili"))
                   neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                   qi_wound = target->query("qi");
                //��󡹦3ʧЧ
				if( target->query_temp("hmg_nizhuan") && target->query("oyf/hamagong",1)==3 ){
                    target->add_busy(2+random(1));
					return 1;
				}
        	                       
                else if(random(3)== 1){
                    target->apply_condition("no_perform", 3+ random(3));
					target->apply_condition("no_force", 3+ random(3));
				}
				message_vision(WHT"$nֻ��һ��������$N����������һ�����Ƶ���ȫ���ʹ�������Ҵܣ��޷���Ϣ��\n"NOR,me,target);
				target->apply_condition("no_exert", 3+ random(3));

                target->set("neili", 0);
                target->add("qi", -qi_wound);
                target->add("eff_qi", -qi_wound*2/3);
                
				message_vision(HIR"��������ʩչ������������$n���澭����,�����ڼ��Ȼ���״̬��������ʹ�ޱȣ�˿���������ã�\n"NOR,me,target);

				if (!userp(target)) target->add_busy(skill/50);
                else target->add_busy(skill/100);
				//�Ʒ���
				message_vision(HBYEL+HIR"$n���ÿ�Ҫ���˰�ļ�����������ڵش�����\n"NOR,me,target);

				target->set_temp("xtg/dingyang",skill);
				target->add_temp("apply/attack",-skill);
				target->add_temp("apply/parry",-skill);
				target->add_temp("apply/dodge",-skill);
				target->add_temp("apply/defense",-skill);
				call_out("dy_recover",(int)skill/10,me,target);
                
				me->start_exert(5,"������");
				//me->start_perform(1,"������");

		   } else
              { 
                msg = YEL"\n$nֻ����$Nָ��͸����룬����������Ȼ��嫣�Ī��֮�С�����ֻ�÷�����ˣ�\n" NOR;
                message_vision(msg, me, target);
                if (me->query("quanzhen/force") =="pass" )
			       target->add_busy(2);
		        me->add_busy(1);
		        me->start_exert(3+random(2),"������");

			 }

        return 1;

}
int dy_recover(object me,object target)
{
	int skill;
	if (!target) return 0;
	//if (!me) return 0;
	skill=target->query_temp("xtg/dingyang");
	
	target->add_temp("apply/attack",skill);
	target->add_temp("apply/parry",skill);
	target->add_temp("apply/dodge",skill);
	target->add_temp("apply/defense",skill);
	return 1;
}
int help(object me)
{
	write(HIC"\n���칦֮�������롹������"NOR"\n");
	write(@HELP
	��������֮�������롹������
	ȫ����������ų�����С�����ͨ����һ��������������
	ƾ��ľ��������������һΪȫ�����ǽ��������Ϊ����
	�����������칦���������𵽾����Ե����ã������ɽ��
	������а���������ϵۡ���ؤ���������������칦�����
	����Ͷ�ء������Ƕ�������ŷ����ĸ�󡹦���������Ե�
	���ƹ�Ч���������˵���һָ��������ŷ�����󡹦����
	����������������������һ��ָָ�������Ƶ��˻���������
	�˵��������ǳ����ųƿ������������ڹ�������������ŷ
	�������������澭�����칦�Ŀ������ò���ʧЧ��

	ע�⣺���칦�������롹������ͯ��֮������ϰ��

	ָ�exert dingyang
	
Ҫ��	
	��ǰ�������� 2000  ���ϣ�
	����������� 15000 ���ϣ�
	���칦�ĵȼ� 450   ���ϣ�
	�õ����������칦�洫�ĵ��ӿ���ʹ�á�
	��Ҫ������ͯ��֮��
	�ߵı������ڹ��ȼ��ж����Ч���� 

HELP
	);
	return 1;
}

