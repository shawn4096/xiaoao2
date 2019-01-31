// Room: /d/tianshan/shishi.c
// By Linux

#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "����ʯ��");
	set("long", @LONG
���������չ�������ʯ�ң�ֻ��ʯ���ı���ʯ��ĥ�����ǹ⻬��ʯ���Ͽ�
�����������������ԲȦ��ÿ��Ȧ�ж����˸��ָ�����ͼ�Σ��е���������
�������Σ��е��ǲ�ȱ��ȫ�����֣�����Щֻ�ǼǺź�������ԲȦ��ע������
һ�������׶���������һ�������Ӷ��������֣�ԲȦ֮��������ǧ������Ҳ��
�˾Űٸ���ǽ���ƺ���һ��С��(Zi)���ϱߵ�ǽ�ϸ�����һ����ı��顣
LONG);   
	 set("item_desc", ([                    
                "zi": HIW"\n��ǽ�������̵�����ɽ������Ҫ�����ұ�����ɽ��÷�ֿھ������ϱ�ǽ\n"+
			"�ϵı���(south bing)���ƿ����뿪ʯ�ҡ�\n\n"+
			"		                        ��ɽͯ����\n\n"NOR,
        ])); 
	setup();
}

void init()
{
	add_action("do_learn", ({"yanxi", "learn"}));    
	add_action("do_break", ({"break", "po"}));
	add_action("do_biguan", ({"biguan", "huantong"}));
}

int do_learn(string arg)
{
	object me;
	int improve, cost;
	
	me = this_player();
	improve = me->query_int() / 10 + random(me->query_int() * 5 / 6);
 
	  
	   if( !arg || arg=="" ) return 0;
    
	
	   if (!me->query("quest/tonglao/pass"))
	      return notify_fail("��û���ܵ�ͯ��ָ�㣬���˰���ʲôҲ���������\n");

	   if (arg == "east wall" ){             
		//if( !me->query("tonglao/ok"))  
		if (!me->query("quest/tonglao/pass"))
			return notify_fail("�㿴��ǽ�ڿ��˰��죬Ҳ����������д����ʲô��\n");
		if(me->query_skill("liuyang-zhang", 1) > 220 )  
			return notify_fail("ǽ�ϵ�������Ҫ��������˵̫ǳ�ˡ�\n");

		cost = 300 / (int)me->query("int");
		cost = 300 / (int)me->query("int");

		if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
			message_vision("$Nר�ĵĿ���ǽ�ϵ�������Ҫ����ͻȻͷ�����͡�\n",me);
			me->unconcious();
			return 1;
		} 
		message_vision("$NĬ��������Ҫ����������ʯ����Ȼ�������\n",me);  
		me->improve_skill("liuyang-zhang", improve);            
		me->add("jing", -cost);
		me->add("jingli", -cost);                        
		return 1;
	}
	if (arg == "west wall" ){             
		if( !me->query("quest/tonglao/pass"))  
			return notify_fail("�㿴��ǽ�ڿ��˰��죬Ҳ����������д����ʲô��\n");
		if(me->query_skill("zhemei-shou", 1) > 220 )  
			return notify_fail("ǽ�ϵ���÷�ֿھ�������˵̫ǳ�ˡ�\n");

		cost = 300 / (int)me->query("int");
		cost = 300 / (int)me->query("int");

		if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
			message_vision("$Nר�ĵĿ���ǽ�ϵ���÷�ֿھ���ͻȻͷ�����͡�\n",me);
			me->unconcious();
			return 1;
		} 
		message_vision("$NĬ����÷�ֿھ���������ʯ����Ȼ�������\n",me);  
		me->improve_skill("zhemei-shou", improve);            
		me->add("jing", -cost);
		me->add("jingli", -cost);                        
		return 1;
	}
	return 0;
}

int do_break(string arg)
{
	object me;
	me = this_player();
	if( !arg || arg=="" ) return 0;
	if (arg == "south bing" ){   
		message_vision("����Ӧ�����飬�ֳ�һ���󶴡�\n", me); 
		message_vision("$N�������ӣ�������Ǹ��󶴣�����һ�󺮷紵�������ֱ���ѩ��ס�ˡ�\n", me);                      
		me->move(__DIR__"shanjin1");
		message("vision", me->name() + "���Ա�һ��������עĿ�Ĵ������˳�����\n",environment(me), ({me}) );
		return 1;
	}
	return 0;
}

int do_biguan()
{
	object me;
	int i,count,ht;
	me = this_player();
	count=me->query("age");
	ht=(int)me->query("bhg/biguan");
	if (me->query("family/family_name")!="���չ�"||me->query("family/master_name")!="����")
	    return notify_fail("����Ϊ������\n");
	
	if( time()-me->query("bhg/flhttime")<86400 )
		return notify_fail("������Ҳ̫�ڿ��˵㣿\n");
    if( ht==3 )
		return notify_fail("Ӣ�ۣ����Ѿ���ɷ��ϻ�ͯ����"+ht+"��������һ�٣�\n");
	if (me->is_busy())
	{
		return notify_fail("������æµ��....\n");
	}
	if (!me->query("quest/tonglao/pass"))
	      return notify_fail("��û���ܵ�ͯ��ָ�㣬��ʲô�أ���ʲôͯ��\n");
	if (me->query("age")<20)
	      return notify_fail("���꼶���ᣬ����20�꣬Ϲ����ʲô��\n");
	    //30����ǰ����չ�һ�Σ�������Զʧȥ����
	//message_vision(HIR"biguan="+ht+"\n"NOR,me);
	if (ht<1 && me->query("age")<60) {
		   message_vision(HIR"����ת�˻�����Ψ�Ҷ��𹦣���ʼ���е�һ�η��ϻ�ͯ������\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	}
	else if (me->query("bhg/biguan")==1 )
	{
           if (me->query("age")<30)
              return notify_fail("���Ѿ���ɵ�һ�η��ϻ�ͯ������30��󷽿��Խ��еڶ���������\n");
		   message_vision(HIR"����ת�˻�����Ψ�Ҷ��𹦣���ʼ���еڶ��η��ϻ�ͯ������\n"NOR,me);
           if (me->query("int")<35)
           {
			   return notify_fail("����������Բ���35����Ŭ������\n");
           }
		   me->start_busy(999);
		   remove_call_out("thinking2");
		   call_out("thinking2",1,me);
	}
	else if (me->query("bhg/biguan")==2)
	{
           message_vision(HIR"����ת�˻�����Ψ�Ҷ��𹦣���ʼ���е����η��ϻ�ͯ������\n"NOR,me);
			if (me->query("int")<40)
           {
			   return notify_fail("����������Բ���40����Ŭ������\n");
           }
		   
		   me->set("mytitle/quest/bahuang1title",HIC"��ɽͯ�Ѵ���"NOR);
           me->set("mytitle/quest/bahuang2title",HIG"���չ�����"NOR);			   
		 
		   me->start_busy(999);
		   remove_call_out("thinking3");
		   call_out("thinking3",1,me);
	 }
	
}


int thinking(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
  t = 18;
  if(me->query("m-card-vip")) t =  16;
  if(me->query("y-card-vip")) t =  12;
  if(me->query("buyvip"))     t =  8;
  j=random(t);

  me->set("bhg/flhttime",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ����˻�����Ψ�Ҷ���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(10+random(10)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(1)) tell_object(me,HIG"\n�����ǽ�ڵ����ݺ�ͯ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧ���뵽�˻�����Ψ�Ҷ����У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if ((int)me->query("bhg/biguan",1)< 1 
	   && i>=26
	   && j<3
	   && me->query("kar")<31)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIC"\n$N���������������������˰˻�����Ψ�Ҷ��𹦵ĵ�һ�η��ϻ�ͯ�������似����һ��¥����\n"NOR,me); 
         log_file("quest/bhgbiguan1", sprintf("%s(%s) ��%d�β��򣬻�Ե�ɺ��£��ɹ�����˻�����Ψ�Ҷ��𹦵ĵ�һ�η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail1"),
		 i,
         me->query("combat_exp"),
		 me->query("age")));

		 me->set("bhg/flhttime",time());
		 me->set("bhg/biguan",1);
		 me->set("title",HIC"��ɽͯ�Ѵ���"NOR);
		 me->set("mytitle/quest/bahuang1title",HIC"��ɽͯ�Ѵ���"NOR);	
		 
		 me->delete_temp("canwu_huantong");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n����˻�����Ψ�Ҷ����һ�η��ϻ�ͯʧ�ܡ�\n"NOR,me); 
         log_file("quest/bhgbiguan1", sprintf("%s(%s) ��%d��ʧ�ܲ���˻�����Ψ�Ҷ��𹦵ĵ�һ�η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail1",1),
		 i,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail1",1);
		 me->set("bhg/flhttime",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huantong");
		 return 1;
   }


}
//����2��
int thinking2(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  t = 20;
  if(me->query("m-card-vip")) t =  18;
  if(me->query("y-card-vip")) t =  15;
  if(me->query("buyvip"))     t =  10;
  j=random(t);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ����˻�����Ψ�Ҷ���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),         
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(20+random(20)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(2)) tell_object(me,HIG"\n�����ǽ�ڵ����ݺ�ͯ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧ���뵽�˻�����Ψ�Ҷ����У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking2");
	  call_out("thinking2",3+random(3), me);

   } 
   else if (me->query("bhg/biguan")==1 && i>26 && j<3)
 	  { 
         me->delete_temp("canwu_biguan");
         me->start_busy(1);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         tell_object(me,HIR"\n��ͨ�����β����ϻ�ͯ���ɹ�����ɵڶ��η��ϻ�ͯ��\n"NOR);
         log_file("quest/bhgbiguan2", sprintf("%s(%s) ��%d�β��򣬻�Ե�ɺ��£��ɹ�����˻�����Ψ�Ҷ��𹦵ĵڶ��η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ�����:%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail2",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
		 me->set("bhg/flhttime",time());
		 me->set("title",HIG"���չ�����"NOR);
		 me->set("mytitle/quest/bahuang2title",HIG"���չ�����"NOR);	

		  me->delete_temp("canwu_huantong");
		 me->set("bhg/biguan",2);
		 return 1;
      }
	 else {
	     message_vision(HIC"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n����˻�����Ψ�Ҷ���ڶ��η��ϻ�ͯʧ�ܡ�\n"NOR,me); 
         log_file("quest/bhgbiguan2", sprintf("%s(%s) ��%d��ʧ�ܲ���˻�����Ψ�Ҷ��𹦵ĵڶ��η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail2",1),
		 i,
	     j,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail2",1);
		 me->set("bhg/flhttime",time());

		 me->start_busy(2);
		  me->delete_temp("canwu_huantong");
		 return 1;
   }


}

int thinking3(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  t = 25;
  if(me->query("m-card-vip")) t =  24;
  if(me->query("y-card-vip")) t =  20;
  if(me->query("buyvip"))     t =  15;
  j=random(t);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ����˻�����Ψ�Ҷ���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),        
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(10+random(10)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(2)) tell_object(me,HIG"\n�����ǽ�ڵ����ݺ�ͯ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧ���뵽�˻�����Ψ�Ҷ����У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking3");
	  call_out("thinking3",3+random(3), me);

   } 
   else if (me->query("bhg/biguan")==2 
	   && i>27
	   && me->query("kar")<30
	   && j<2)
 	  { 
         me->delete_temp("canwu_biguan");
         me->start_busy(1);     
         message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         tell_object(me,HIR"\n��ͨ�����β����ϻ�ͯ���ɹ�����ɵ����η��ϻ�ͯ��\n"NOR);
         log_file("quest/bhgbiguan3", sprintf("%s(%s)��Ե�ɺ��£��ڵ�%d�β��򣬳ɹ�����˻�����Ψ�Ҷ��𹦵ĵ����η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ�������%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail3",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
		 me->set("bhg/flhttime",time());
		  me->delete_temp("canwu_huantong");
		  me->set("bhg/biguan",3);
		//  me->set("title",HIR"��ɽͯ�Ѵ���"NOR);

		  me->set("title",HIY"�˻�����"HIR"Ψ�Ҷ���"NOR);
		  me->set("mytitle/quest/bahuang3title",HIY"�˻�����"HIR"Ψ�Ҷ���"NOR);
		 return 1;
      }
	 else {
	     message_vision(HIC"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n����˻�����Ψ�Ҷ�������η��ϻ�ͯʧ�ܡ�\n"NOR,me); 
         log_file("quest/bhgbiguan3", sprintf("%s(%s) ��%d��ʧ�ܲ���˻�����Ψ�Ҷ��𹦵ĵ����η��ϻ�ͯ����ǰ����ֵ��%d,��ǰ�����:%d,��ǰ���飺%d�����䣺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail3",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail3",1);
		 me->set("bhg/flhttime",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huantong");
		 return 1;
   }


}



