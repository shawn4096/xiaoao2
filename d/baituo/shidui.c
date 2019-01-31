#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
����������Χȫ�Ǿ�ʯ���������������ҵ���ʯ�ӣ����Ǳ��˻����
ʯ������������顣����һ��ƽ������ʯ���϶���һֻѩ�׵ĸ�󡡣������
�ڷ���һЩƿƿ�޹�(guan)����ʱ�������ڴ�����������
LONG);        
        set("objects", ([
                    __DIR__"npc/chanchu" : 1,
                    BINGQI_D("gs-zhang") : 1,
                    __DIR__"obj/shentuo_book2" : 1,
			        __DIR__"obj/shebian" : 1,


        ]));
        set("item_desc", ([                    
                "stone": "\n��Щ��ʯ���а��棬���ó��Ǳ��������������õġ�\n",
				"guan": "\n������˰���ɽ���еľ綾����,��������������(xidu)��\n",
        ]));
        set("outdoors", "����ɽ");
        setup(); 
}

void init()
{
       	object me = this_player();       
       	if(!me->query_temp("baituo_yun") 
       	&& me->query("id") != "xuanbing chanchu" 
       	&& me->query("id") != "master"
       	&& !me->query_skill("hamagong", 1) ){
             	message_vision(HIW"�������ͻȻ���𣬶���$Nһ�ڶ��������\n"NOR,this_player()); 
             	tell_object(me, HIB "��е�����һ�����Σ���ʱ���˹�ȥ��\n" NOR ); 
             	me->unconcious();
             	me->move(__DIR__"yuanzi5");
             	tell_room(environment(me), me->name()+"ͻȻ�Ӿ�ʯ֮��ֱ�����������ȡ���һ��ˤ�ڵ��ϣ�\n", ({ me }));
          	if(random(me->query_skill("poison", 1)) < 100 ) {
          		me->set_temp("last_damage_from", "�о綾��");
          		me->die();                   
          	}
          	
          	else me->add("max_neili", -5);
          	}  
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
        add_action("do_strike", "strike");  
		add_action("do_liandu", "xidu");    
}

int do_climb(string arg)
{
        object me = this_player();
        if( !arg || arg=="" ) return 0;
        
        if( (int)me->is_busy() || me->is_fighting()) 
        	return notify_fail("����æ���ء�\n");
        	
        if (arg == "stone" ){   
           	message_vision("$N�ֽŲ��ã������˾�ʯȥ������һ�ݣ��Ѿ����˳�ȥ��\n", me);                      
               	me->move(__DIR__"yuanzi5");
               	message("vision", me->name() + "���������˳�����\n",environment(me), ({me}) );
               	me->start_busy(1);
               	if( !me->query_skill("hamabu", 1) && me->query_skill("hamagong", 1) ){
               		tell_object(me, "���ͷ�������Ծ������ƣ�������˸�󡲽������\n");
               		me->set_skill("hamabu", 1);
               	}
               	
               	return 1;
        }     
        return 0;
}
int do_strike(string arg)
{
        int improve, cost;
        object me = this_player();
        
        improve = me->query_int() / 10 + random(me->query_int() * 5 / 6);
        improve /= 2;
        if( !arg || arg=="" ) return 0;
        
        if( (int)me->is_busy() || me->is_fighting()) 
        	return notify_fail("����æ���ء�\n");
        	
        if (arg == "stone" ){             
            	if(!me->query_skill("hamagong", 1))  
               		return notify_fail("������ָ�����ƾ�ʯ������¶��һ˿�ѿ�����ɫ��\n");
            	/*if( me->query_skill("hamagong", 1) > 64 && me->query("oyf/hamagong") < 2)  
               		return notify_fail("������ָ�����ƾ�ʯ������¶��һ˿�ѿ�����ɫ��\n");
					*/
            	if( me->query_skill("hamagong", 1) > 110 )  
               		return notify_fail("��һ�����ʯ��ȥ��ֻ�����һ������ʯ��������������룡\n");
               		
                if( me->query_skill("hamagong", 1) == 100 && (me->query("oyf/hmg_add") < 1) ) {
                   message_vision(WHT"\n$Nһ�����ʯ��ȥ��ֻ�����һ������ʯ��$P����������룡\n"NOR, me);  
                	tell_object(me, "����һ�ƾ���ʮ�㣬�������Գ����ˣ�\n������ʮ�㣬��������˲��١�\n");
                	me->add("combat_exp", 30000);
                	me->add("max_neili", 300);
                	me->add("max_jingli", 200);
                	me->set_skill("hamagong", 110);
                	me->set_skill("force", me->query_skill("force", 1)+10);
                	log_file("quest/oyf_log", sprintf("%s(%s) �� %s ��ϰHMG��100�������õ�������\n", me->name(1), me->query("id"), ctime(time()) ) );
                	return 1;       
                }
                
        	cost = 600 / (int)me->query("int");
        	cost = 600 / (int)me->query("int");

           	if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
                	message_vision("$N��������, һ�����������������$N���˹�ȥ��\n",me);
                	me->unconcious();
                	return 1;
                } 
                
                message_vision("$NĬ�и�󡹦�ھ���������˫��֮�ϣ�һ�������ʯ��ȥ��\n"NOR, me);  
           	me->improve_skill("hamagong", improve);            
           	me->improve_skill("strike", improve/2); 
           	me->receive_damage("jing", cost, "���Ĺ���");
           	me->receive_damage("neili", cost/2, "���Ĺ���");
           	me->receive_damage("jingli", cost, "���Ĺ���");                        
           	return 1;
        }     
        return 0;
}
int valid_leave(object me, string dir)
{        
       me->delete_temp("baituo_yun");       
       return ::valid_leave(me);
}

int do_liandu(string arg)
{
        int improve, cost;
        object me = this_player();
        
        if( !arg || arg=="" ) return 0;
        
        if( (int)me->is_busy() || me->is_fighting()) 
        	return notify_fail("����æ���ء�\n");
        
		if (me->query("family/family_name")!="����ɽׯ")
        	return notify_fail("��ǰ���ɽׯһ���������޷��ڴ�������\n");
		if (me->query_temp("xidu_chanchu"))
		{
			return notify_fail("����������ܶ�\n");
		}
		if (me->query_temp("xidu_she"))
		{
			return notify_fail("���������߶�\n");
		}

        if (arg == "chanchu"
			||arg=="���"
			||arg=="�������")
		{             
            	if(me->query_skill("hamagong", 1)<100)  
               		return notify_fail("���󡹦����100�����޷��������ն��ء�\n");
            	if( me->query_skill("poison", 1) <150 )  
               		return notify_fail("�㶾�Ʋ���150���޷�����������¶��һ˿�ѿ�����ɫ��\n");
					
               		
                message_vision(HBBLU+HIW"\n$N��ϥ�����������󡹦��Ȼ���Լ�ʳָ���ڡ�������ܡ������ϣ�\n"NOR, me);  
                	
                
				cost = 600 / (int)me->query_int();
				cost = 600 / (int)me->query_int();

				if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost)
				{
						message_vision("$N��������, һ��������������$N���˹�ȥ��\n",me);
						me->unconcious();
						return 1;
				} 
                
                
           	me->receive_damage("jing", cost, "���Ĺ���");         
           	me->receive_damage("jingli", cost, "���Ĺ���");                        
           	me->set_temp("xidu_chanchu",1);
			call_out("xidu_chanchu",1,me);
			return 1;
        } 
		if (arg == "she"
			||arg=="����"
			||arg=="����"
			||arg=="dushe")
		{             
            	if(me->query_skill("hamagong", 1)<100)  
               		return notify_fail("���󡹦����100�����޷����������߶��ء�\n");
            	if( me->query_skill("poison", 1) <180 )  
               		return notify_fail("�㶾�Ʋ���180���޷����߶�������¶��һ˿�ѿ�����ɫ��\n");
					
               		
                message_vision(HBBLU+HIW"\n$N��ϥ�����������󡹦��Ȼ���Լ�ʳָ���ڡ��綾�ߡ������ϣ�\n"NOR, me);  
                	
                
				cost = 600 / (int)me->query_int();
				cost = 600 / (int)me->query_int();

				if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost)
				{
						message_vision("$N��������, һ��������������$N���˹�ȥ��\n",me);
						me->unconcious();
						return 1;
				} 
                
           	me->receive_damage("jing", cost, "���Ĺ���");         
           	me->receive_damage("jingli", cost, "���Ĺ���");                        
           	me->set_temp("xidu_she",1);
			//remove_call_out("xidu_she");
			call_out("xidu_she",1,me);
			return 1;
        }    
        return 0;
}



int xidu_chanchu(object me)
{
	if (me->query_temp("xidu_chanchu")<10)
	{
		switch (random(4))
		{
			case 0:
				tell_object(me,CYN+me->query("name")+"����󡹦��תһ�ܣ�Ȼ�����������������ϣ���ʱһ�ɺ���Ϯ����\n"NOR);
				//me->apply_condition("cold_poison",1);
				//me->add_temp("xidu_liandu",1);
				break;
			case 1:
				tell_object(me,WHT+me->query("name")+"�������������������������ת��Ȧ��Ȼ�������³���\n"NOR);
				//me->add_condition("xbcc_poison",1);
				me->add_temp("xidu_chanchu",1);

				break;
			case 2:
				tell_object(me,HIC""+me->query("name")+"��ܶ������壬һ���ȣ�һ���������Ƚ��棬��������\n"NOR);
				//me->add_condition("xbcc_poison",1);

				break;
			case 3:
				tell_object(me,HIC""+me->query("name")+"�������һ�����̣�������ܶ����Ѿ�������ȫ���ա�\n"NOR);
				//me->add_condition("xbcc_poison",1);
			
				break;
		}
		me->add_temp("xidu_chanchu",1);
		me->add_condition("xbcc_poison",1);
		call_out("xidu_chanchu",5+random(5),me);

	}
	else {
		message_vision(HIR"$N�����������������󡶾�������ջ�\n"NOR,me);
		if (me->query_skill("poison",1)>180) return notify_fail("������󡶾��������Ѿ�û��Ч���ˣ�\n");
	
		me->improve_skill("poison",me->query_skill("poison",1)*me->query_int());
		
		if (me->query_skill("poison",1)==160&&me->query_skill("hamagong",1))
		{
			message_vision(HIB"$N������󡶾����ĸ�󡹦�������������棡\n"NOR,me);
			me->add("baituo/poison/chanchu",1);
		}
		if (me->query_skill("poison",1)==170&&me->query_skill("hamagong",1))
		{
			message_vision(HIB"$N������󡶾����ĸ�󡹦�������������棡\n"NOR,me);
			me->add("baituo/poison/chanchu",1);
		}
		if (me->query_skill("poison",1)==180&&me->query_skill("hamagong",1))
		{
			message_vision(HIB"$N������󡶾����ĸ�󡹦�������������棡\n"NOR,me);
			me->add("baituo/poison/chanchu",1);
		}
		me->delete_temp("xidu_chanchu");

		me->start_busy(1);
	}
}

int xidu_she(object me)
{
	if (me->query_temp("xidu_she")<10)
	{
		switch (random(4))
		{
			case 0:
				tell_object(me,CYN""+me->query("name")+"����󡹦��תһ�ܣ�Ȼ��������������ϣ���ʱһ��������Ϯ����\n"NOR);
				//me->apply_condition("cold_poison",1);
				//me->add_temp("xidu_liandu",1);
				break;
			case 1:
				tell_object(me,WHT""+me->query("name")+"���������Ķ�����������ת��Ȧ��Ȼ�������³���\n"NOR);
				//me->add_condition("xbcc_poison",1);
				me->add_temp("xidu_she",1);
				break;
			case 2:
				tell_object(me,HIC""+me->query("name")+"���߶������壬һ���ȣ�һ���������Ƚ��棬��������\n"NOR);
				//me->add_condition("xbcc_poison",1);
				break;
			case 3:
				tell_object(me,HIC""+me->query("name")+"�������һ�����̣����߶����Ѿ�������ȫ���ա�\n"NOR);
				//me->add_condition("xbcc_poison",1);
				break;
		}
		me->add_temp("xidu_she",1);
		//me->add_condition("snake_poison",1);
		call_out("xidu_she",5+random(5),me);

	}
	else {
		message_vision(HIR"$N������������߶��������ջ�\n"NOR,me);
		if (me->query_skill("poison",1)>200) return notify_fail("�߶���������Ѿ�û��Ч���ˣ�\n");
		
		me->improve_skill("poison",me->query_skill("poison",1)*me->query_int());
		
		if (me->query_skill("poison",1)==190&&me->query_skill("hamagong",1))
		{
			message_vision(HIB"$N�߶�����ĸ�󡹦���������棡\n"NOR,me);
			me->add("baituo/poison/gsdu",1);
		}
		
		if (me->query_skill("poison",1)==200&&me->query_skill("hamagong",1))
		{
			message_vision(HIB"$N�߶�����ĸ�󡹦���������棡\n"NOR,me);
			me->add("baituo/poison/gsdu",1);
		}

	
		me->start_busy(1);
		me->delete_temp("xidu_she");
	}
}