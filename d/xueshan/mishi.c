// Room: mishi.c
// sohu@xojh 2014

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_open(string arg);
void create()
{
	set("short", HIC"��¥����"NOR);
	set("long", @LONG
����һ��С�ݣ�������һ�����������������ޱȣ�
������Ӧ�����ڸ߿�֮�С�����ǽ���ϻ����˴�����
��̱ڻ���������������������������������ľ�
����������ô�������������������������ܡ�
һ�������Ϸ���һ�����裬��������������ׯ�����¡�
����ǰ������һ������(jingshu)��
LONG
	);
	//set("down", (["south" : __DIR__"fatang2",]));
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  me->start_busy(1);
  if (me->query_temp("lxbr/start"))
  {
   		tell_object(me,WHT"\n\n����һ��ɾ����������������������Ǹɾ���������飬��Ծ����̲�ס�뷭����fankan����\n"NOR);
		add_action("do_fan","fankan");
		add_action("do_open", "open");
   }      
   
}
//��������

int do_fan(string arg)
{
    object me=this_player();
	if (!arg)
	{
		return notify_fail("��Ҫ����ʲô��\n");

	}
	if (arg !="jingshu" && arg !="����")
		return notify_fail("��û�±��Ҷ�������\n");
	
	if (me->query_temp("lxbr/start"))
	{
		tell_object(me,WHT"\n\n����һ��"HIY"�������������"WHT"����Ƥ�ȽϾ�Զ�������Ѿ���źܾ��ˡ�\n"NOR);
		tell_object(me,HIC"\n\n��С������ķ���һҳ��֮����ҳ����һ��С�֣�������Դ�Դ˾�---���ַ�����\n"NOR);
		tell_object(me,HIY"\n\n�⹦��ѭ�򽥽����������޲�������֮�������˵�����ǧ����䣬���ձ����ʮ���㾳�磬��\n"NOR);
		tell_object(me,HIY"ֻ�������ޣ��������еĸ�ɮ��ʿ������������֮ǰ�������߲㡢�ڰ˲㣬��ǵ�������ɡ�\n"NOR);
		tell_object(me,HIY"�������ʼǼ��أ�������䣬�·�����һλ��ɮ�����˵ھŲ㣬�������;�������������ʮ��ʱ����ħ����\n"NOR);
		tell_object(me,HIY"�޷����ƣ����ڿ���������ҹ���Ծ��������������������������˵��Դ�Ϊ����\n"NOR);
		tell_object(me,HIY"\n\n�д˾��飬���Ծ������������ˣ�Ǳ�޿�ѧ���������٣��������ƵھŲ��ѹأ���ʱ�ѵ���ʮ��ľ��磬\n"NOR);
		tell_object(me,HIY"���ǡ�������������Ե�����ʱÿһ�ƻ���������ʮ��ʮ��Ĵ���������֪�����������������������\n"NOR);
		tell_object(me,HIY"���������������޵��֣�����������ʮһ�㣬Ҳ�Ѷ��ࡣ���ԴӰ�����Ů������򸾺����Դ�Ϊ��ܴ��衣\n"NOR);
		tell_object(me,HIY"��ȥ��ԭ����֪�����ܹ飬��������֮�ĵü�¼�ڴˣ�����С����ͻ�������ߵľ��硣\n"NOR);
        tell_object(me,HIY"\n\n��С�ӵ����ڴ˲���(canwu)�˾�����������������µ�һ�񹦡�\n"NOR);
		
		me->set_temp("quest/lx/fan",1);
		//me->delete_temp("lxbr/start");
		add_action("do_canwu", "canwu");
		return 1;
	}
    else tell_object(me,HIC"����һ���������������,��Ϊ���֮�������㷭����\n"NOR);
	return 1;

}



int do_canwu(string arg)
{
	object me;
	int i,count,ht;

	me = this_player();

	ht=(int)me->query("lx/gree");
	if (!me->query_temp("quest/lx/fan") || !arg ||arg !="���������")
	{
		return notify_fail("��Ҫ����ʲô��\n");

	}
	if (me->query("family/family_name")!="������")
	    return notify_fail("����Ҵ����µ��ӣ���Ϊ������\n");
	if( time()-me->query("quest/dls/longxiang/time")<86400 )
		return notify_fail("������Ҳ̫�ڿ��˵㣿\n");
    if( ht==13 )
		return notify_fail("Ӣ�ۣ����Ѿ���������񹦵�"+ht+"��������������һ�٣�\n");
	  

	if (me->query_skill("longxiang-boruo",1)<500)
	      return notify_fail("�����������̫��������Ҳû�á�\n");

	if (ht==10 ) {
		   message_vision(HIC"��ƽ�ľ�������ʼ���Ϸ��ġ�����������������վ������ط��ſ�ʼ�����ʮһ������\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	}
	else if (ht==11 )
	{
		   message_vision(HIY"��ƽ�ľ�������ʼ���ġ�����������������վ������ط��ſ�ʼ�����ʮ��������\n"NOR,me);           
		   //me->set("title",HIY"������"HIM"�������������"NOR);
		   //me->set("mytitle/quest/banruo1title",HIY"������"HIM"�������������"NOR);
		   me->start_busy(999);
		   remove_call_out("thinking2");
		   call_out("thinking2",1,me);
	}
	else if (ht==12)
	{
		  message_vision(HIR"��ƽ�ľ�������ʼ���ġ�����������������վ������ط��ſ�ʼ�����ʮ��������\n"NOR,me);

		  me->start_busy(999);
		  remove_call_out("thinking3");
		  call_out("thinking3",1,me); 
	 }
	return 1;

}

//��ʮһ��
int thinking(object me)
{
  int i,j,x,lx; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);

  me->set("quest/dls/longxiang/time",time());
  x=random(me->query("int"));
  lx=(int)me->query("lx/gree");
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) �������������11��ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n����š�����������������ݺͷ��������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧʵս�������뵽����������У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң���Ȼ���⣬һ����ɮ���̬֮���ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if ( me->query("lx/gree")==10
	   && i>=20
	   && j<6
	   && x>32
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�������ϲ�����������������������ĵ�ʮһ���������������������һ��¥������ʮһ����֮������\n"NOR,me); 
         log_file("quest/longxiang11", sprintf("%s(%s) ��%d�β���ʧ�ܺ󣬻�Ե�ɺ��£��ɹ���������������ĵ�11��������ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail1"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",11);
		 me->set("lx/gree",11);
		 me->set("title",HIY"������"HIM"�������������"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"������"HIM"�������������"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N������죬����ȫ�����������������ӿ����ʱ�����߻���ħ̬֮����\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"�߻���ħ��");
		 me->apply_condition("hot_poison",2);

		 log_file("quest/longxiang11", sprintf("%s(%s) �����11�����ʧ�ܵ�%d�Σ�ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail1"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail1",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}
//����2��

int thinking2(object me)
{
  int i,j,x; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);

  x=random(me->query("int"));
  me->set("quest/dls/longxiang/time",time());
  
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) �������������12��ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n����š�����������������ݺͷ��������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧʵս�������뵽����������У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң���Ȼ���⣬һ����ɮ���̬֮���ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking2");
	  call_out("thinking2",3+random(3), me);

   } 
   else if ((int)me->query("lx/gree",1)==11
	   && i>=25
	   && j<5
	   && x>35
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�������ϲ�����������������������ĵ�ʮ�����������������������һ��¥������ʮ������֮������\n"NOR,me); 
         log_file("quest/longxiang12", sprintf("%s(%s) ��%d�β���ʧ�ܺ󣬻�Ե�ɺ��£��ɹ���������������ĵ�12��������ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail2"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",12);
		 me->set("lx/gree",12);
		 me->set("title",HIY"������"HIM"����������н�"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"������"HIM"����������н�"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N������죬����ȫ�����������������ӿ����ʱ�����߻���ħ̬֮����\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"�߻���ħ��");
		 me->apply_condition("hot_poison",4);

		 log_file("quest/longxiang11", sprintf("%s(%s) �����12�����ʧ�ܵ�%d�Σ�ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail2"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail2",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}
//��ʮ����
int thinking3(object me)
{
  int i,j,x; 
  if(!me) return 0;
  i=random(me->query("kar"));
   j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);
  x=random(me->query("int"));
  me->set("quest/dls/longxiang/time",time());
  
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) �������������13��ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n����š�����������������ݺͷ��������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧʵս�������뵽����������У�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң���Ȼ���⣬һ����ɮ���̬֮���ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking3");
	  call_out("thinking3",3+random(3), me);

   } 
   else if ((int)me->query("lx/gree",1)==12
	   && i>=27
	   && j==4
	   && x>=38
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�������ϲ�����������������������ĵ�ʮ�����������������������һ��¥������ʮ������֮������\n"NOR,me); 
         log_file("quest/longxiang12", sprintf("%s(%s) ��%d�β���ʧ�ܺ󣬻�Ե�ɺ��£��ɹ���������������ĵ�13��������ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail3"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",13);
		 me->set("lx/gree",13);
		 me->set("title",HIY"������"HIM"ʮ�������洫"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"������"HIM"ʮ�������洫"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIY"\n$N������죬����ȫ�����������������ӿ����ʱ�����߻���ħ̬֮����\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"�߻���ħ��");
		 me->apply_condition("hot_poison",6);

		 log_file("quest/longxiang11", sprintf("%s(%s) �����13�����ʧ�ܵ�%d�Σ�ȡֵ����ֵi��%d,��ǰ���ֵj��%d,��ǰ���飺%d����ǰ��Դkar��%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail3"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail3",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}


int do_open(string arg)
{
       object gkey;
		object me=this_player();
		if (!me->query_temp("lxbr/start"))
			return notify_fail("������ô������\n");
		
		 if (!objectp(gkey=present("jin yaoshi",me)))
		{
			return notify_fail("������Ÿ�����ô��Ҫ��Կ�׶�Ū���ˣ�������Űɡ�\n");
		}
		if( arg == "door"||arg == "men" || arg == "��" || arg == "��")
        {
			
			message_vision("$N����Կ���ó������������У�֨֨����ƿ����ǽ���򿪳��ڡ�\n",me);
			if( !query("exits/down") ) 
			{
				set("exits/down", "/d/xueshan/jingtang");
				remove_call_out("close_path");
				message_vision(HIR"\n\n���Կ��һ��С�ı�$N�����ˡ�\n",me);
				destruct(gkey);
				call_out("close_path", 15);
			}
		}else return notify_fail("��Ҫ��ʲô��\n");

		
      
}
void close_path()
{
        if( !query("exits/down") ) return;
		message("vision","һ��ᣬ�̵�һ����ǽ�ָֻ�ԭ����\n", this_object() );
		delete("exits/down");
}
