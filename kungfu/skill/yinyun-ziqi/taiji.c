// ������ ̫���� PFM
// by sohu@xojh 2014.1

#include <ansi.h>

string exert_name(){ return HBMAG+HIW"̫����"NOR; }

int check_fight(object me);
int exert(object me)
{
		object weapon;
		int skill;
  		skill=me->query_skill("yinyun-ziqi",1);
	    
        if (!me->query("quest/wd/yyzq/taiji/pass"))
        		return notify_fail("����δ����͸��̫�������⣬ʩչ����̫������\n");
		
        if( !me->is_fighting() || 
			!living(me))
                return notify_fail("��̫����ֻ����ս���е�ʹ�á�\n");
        if( me->query_temp("yyzq/taiji")) 
                return notify_fail("��̫����֮�����಻�������Ѿ��ڷ������������ˡ�\n");  
        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("������������Ϊ̫�������Ӳ�����̫���������ơ�\n");                
        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("�������������������Ӳ�����̫������������\n");
        if( (int)me->query_skill("yinyun-ziqi", 1) < 500 )
                return notify_fail("����������ȼ������ߣ����Ӳ�����̫������������\n");
        if( (int)me->query_skill("taiji-jian", 1) < 500 )
                return notify_fail("���̫������������죬��������ᡸ̫����֮���ϡ�\n");
        if( (int)me->query_skill("taiji-quan", 1) < 500 )
               	return notify_fail("����δ��ȫ����̫��ȭ���޷���ʹ�á�̫���������ˡ�\n");
		if((int)me->query_skill("taoism", 1) < 200 )
                return notify_fail("��Ե�ѧ�ķ������򲻹������Ӳ�����̫������Բת���ϵ����⡣\n");
        if( me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("����ڹ����ԣ��������ܷ��ӳ���̫���������ơ�\n");                                                                                     
        if( userp(me) 
           &&( me->query_skill_mapped("parry") != "taiji-quan"&& me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("��̫�������ϱ�������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");
        if( me->query_skill_prepared("cuff") != "taiji-quan"
           || me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("����붮��̫��ȭ������ʩչ��̫������\n");  
        if( me->query_skill_mapped("sword") != "taiji-jian" )
                return notify_fail("����붮��̫������������ʩչ��̫������\n"); 
              
        if( objectp(weapon = me->query_temp("weapon")) ){
        	    if( weapon->query("skill_type") != "sword" )
                	return notify_fail("�����ʹ�ý��������á�̫����ʩչ��̫�����⣡\n");           
              
         message_vision(HIC"\n$P�����ƶ���һ�ֳֽ���һ�ֻ��˸���ָ������ֿ�ƽ�У���������������������ǰ��\n����$P�������أ�ÿһ�ж�����̫��ʽ�������仯����΢���\n",me);
         tell_object(me, CYN"\n��Ĭ��̫���񹦣����Լ��ͽ��������һ����̫��"RED"�����⡹"CYN"���ӵ����쾡�£�\n"NOR);
        }
        else {                  
        	message_vision(HIC"\n$P�����ƶ���˫���´����ֱ����⣬��ָ΢�棬����ֿ�ƽ�У���������������������ǰ����۰뻷��\n"
+"������Գ����ƣ����Ʒ��������ƣ�����$P˫��Բת��ÿһ�ж�����̫��ʽ�������仯����΢���\n",me);
        	tell_object(me, HIW"\n��Ĭ���񹦣�˫����Ȼ�Ӷ����������һ������̫����"RED"��ȭ�⡹"HIW"���ӵ����쾡�£�\n"NOR);
        }
		
		me->set_temp("yyzq/taijiing",1);//����ֹͣ���
		
        //if (me->query_skill("yinyun-ziqi",1) < 450 ) me->start_busy(1+random(2)); //�з�ȡ��busy
		if (skill > 549 ) //�����ǿ����
		{
			
			//�������ͨ��buff���� 
		//������Ŀ�� buff�� buffֵ buffʱ�� ��ʱ���,ɢ������,ս��ֹͣ���
			
		 //CHAR_D->addbuff(me,"armor",skill/3,3,"yyzq/armor",0,1); 
		// CHAR_D->addbuff(me,"defense",skill/3,3,"yyzq/defense",0,1);
		// CHAR_D->addbuff(me,"parry",skill/3,3,"yyzq/parry",0,1);
		// CHAR_D->addbuff(me,"dodge",skill/3,3,"yyzq/dodge",0,1);
			 
			
			/*me->set_temp("apply/armor",0);
			me->set_temp("apply/defense",0);
            me->set_temp("apply/parry",0);
			me->set_temp("apply/dodge",0);*/
			
			me->add_temp("apply/armor",skill/3);
			me->add_temp("apply/defense",skill/3);
            me->add_temp("apply/parry",skill/3);
			me->add_temp("apply/dodge",skill/3);
			me->set_temp("yyzq/dafei",skill);
			
			
			
			//me->add_temp("apply/strength",(int)me->query_skill("yinyuan-ziqi",1)/10);
		}
		
      
		me->set_temp("yyzq/taiji",skill);
        check_fight(me);
        return 1;
}

string check_force(object ob)
{
	string force;
	
	if(!stringp(force = ob->query_skill_mapped("force")))
       		force = "�ڹ�";
        
        switch(force){
        	case "yinyun-ziqi": break;
        	case "huntian-qigong":
        	case "hamagong":
        	case "longxiang-boruo": force = "�귭"; break;
        	case "huagong-dafa":
        	case "guiyuan-tunafa":
        	case "dulong-dafa": force = "����"; break;
        	case "yijin-jing":
        	case "bihai-chaoshen":
        	case "qiantian-yiyang":
        	case "kurong-changong": force = "����"; break;        	
        	case "shenyuan-gong":
        	case "zixia-gong":
        	case "shenghuo-shengong": force = "����"; break;        	
        	case "lingji-zhuang":
        	case "yunu-xinjing":
        	case "shenzhao-jing": force = "����"; break;
        	default: force = "����"; break;
        } 
        return force;
}
        
int check_fight(object me)
{    
	object ob, weapon;
	string force;
	int skill;
	if (!me) return 0;
	
	skill=me->query_skill("yinyun-ziqi",1);
	
	if( !me || !me->query_temp("yyzq/taiji") ) return 0;
	weapon = me->query_temp("weapon");
	    if (!me->is_fighting() || me->query("neili") <= 100 || !living(me) || !me->query_temp("yyzq/taijiing"))
	    {
			
			if( !weapon )  	message_vision(CYN "\n$Nʹ�������ơ�����̫������ǰ������ǰ�죬���ҷֿ�����΢���������ƽ���������������䣬�����е�վ�ڵ��ء�\n\n"NOR, me);
		    else 	message_vision(CYN "\n$N��������ֹ��˫�ֱ�������ǰ���������䣬�����е�վ�ڵ��ء�\n\n"NOR, me);
			message_vision(HIW"$N��̫���񹦻����չ������ض������������ӡ�\n"NOR,me);
			if (me->query_temp("yyzq/dafei")) 
		    {
				skill=me->query_temp("yyzq/dafei");
				// me->set_temp("apply/armor",0);
              //  me->set_temp("apply/parry",0);
		    //	me->set_temp("apply/dodge",0);
			//	me->set_temp("apply/defense",0);	
				
			    me->add_temp("apply/armor",-skill/3);
                me->add_temp("apply/parry",-skill/3);
		    	me->add_temp("apply/dodge",-skill/3);
				me->add_temp("apply/defense",-skill/3);	
				
				me->delete_temp("yyzq/dafei");
				
				
		     }
			 //ȡ��̫��ϵ��super����
				me->delete_temp("tjq/super_hit");
				me->delete_temp("tjj/super_hit");
				
			 me->delete_temp("yyzq/taiji");
			 me->delete_temp("yyzq/taijiing");
			return 1;
		}
		else
		{
			if( weapon ){
        	if( weapon->query("skill_type") != "sword" ){
        		write(HIY"�����зǽ���̫�������ʱ�㲻����ͨ�ˣ�\n"NOR);
        		me->delete_temp("yyzq/taijiing");
				
        	}
        	else if( me->query_skill_mapped("sword") != "taiji-jian" ){
                	message_vision(CYN"$NͻȻ��̫������һ�գ���һһ�ֽ���������̫�������ʧ!\n"NOR, me);
                	me->delete_temp("yyzq/taijiing");
					
                }
                
            else if( (int)me->query_skill("taiji-jian", 1) < 500 ){
                	write(HIY"���̫������������죬��᲻�ˡ�̫����֮���ϣ�\n"NOR);
                	me->delete_temp("yyzq/taijiing");
					
        	}
			else if( me->query_skill_mapped("parry") != "taiji-jian" )
			{
				    message_vision(CYN"$NͻȻ��̫������һ�գ���һһ�ֽ���������̫�������ʧ!\n"NOR, me);
                	me->delete_temp("yyzq/taijiing");				
			}
            else me->set_temp("tjj/super_hit",1);
        		//me->map_skill("parry", "taiji-jian");
			
			
        }        
        else {
        	if ( me->query_skill_mapped("cuff") != "taiji-quan" 
        		|| me->query_skill_prepared("cuff") != "taiji-quan" ){
                	message_vision(HIY"$Nʹ��һʽ̫��ȭ��ͻȻ���У���Ȼ����ȫ��ͬ��������̫����Բ֮���ʧ��\n"NOR,me);
                	me->delete_temp("yyzq/taijiing");
                	me->start_busy(1);
        	}
            else if( me->query_skill_mapped("parry") != "taiji-quan" )
			{
				message_vision(HIY"$Nʹ��һʽ̫��ȭ��ͻȻ���У���Ȼ����ȫ��ͬ��������̫����Բ֮���ʧ��\n"NOR,me);
                	me->delete_temp("yyzq/taijiing");
                	me->start_busy(1);				
			}			
       		else{      
       			if( me->query_skill("taiji-quan", 1) > 450
       			&& objectp(ob = me->select_opponent()) 
       			&& random(me->query_int()) > ob->query_int()
       			&& !me->query_temp("tjq/"+ob->query("id"))
       			&& stringp(force = check_force(ob)) 
       			&& force != "yinyun-ziqi"){
        			tell_object(me, HIC"����һϸ�Ĺ۲죬������"+ob->name()+"�����ڹ�����ʵ������һת���˳�����"+force+"������\n"NOR);
        			me->set("env/���Ͼ�", force);
        			me->set_temp("tjq/"+ob->query("id"), random(me->query_int(1))+1);
				me->set_temp("tjq/super_hit",1);
        		}        		
        	}
			
        }
		call_out("check_fight",1, me);	
         return 0;		
		}        
       	return 1;
}       

int help(object me)
{
	write(HIM"\n������"HIW"��̫���񹦡���"NOR"\n");
	write(@HELP
	̫��֮�⣬��仯��ˣ�����Ϊһ�ᡣ������
	�����򶮾��ɶ������׼�������Ȼ�������վã�
	���ܻ�Ȼ��ͨ�ɡ�����������̫��ȭ�����ж�
	���Դ�����ϡ�ÿ�����괿���������˻��ߣ�
	�ʽ���Ϊ���ƣ�˫��֮��δ�����ѭ�������
	�ȼ�������ʮ�Ժ�������ã���Ϊ��������
	���󣬷�������������̫������������������
	���Լ�һ����ѧ�ڻ��ͨ��������ã����ڱ�
	�������ѧ��ͨ�������������������̡�
	ע�⣺̫���ھ������������������������ⲻ
	�������糤����ӣ����಻����̫���ڹ���λ
	�ɱ������о����ڹ����ã��Ѷ�ϵ���ϸߣ���
	���˺�����Ҳֵ���ڴ����м�̫�������ں�
	��������550�������������ԡ�
	
	ʹ��ָ�yun taiji

Ҫ��
	̫��ȭ���ȼ� 500 ���ϣ�
	̫�������ȼ� 500 ����)
	�������ȼ� 500 ���ϣ�
	��ѧ�ķ��ȼ� 200 ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 1000 ���ϡ�
HELP
	);
	return 1;
}
