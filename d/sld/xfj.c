// xfj.c
// �ɸ���
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short","�ɸ���");
	set("long",@long
�����ǽ�������Ͼʱ��Ϣ����֮������ʱҲ�������޿��ˡ�
��������(shelf)�ϰڷ���һ�����鼮����Ϊ�������ɾ�Ҫ������
�����ϰ��鼮��һЩ������ס,�Ա�һ��С�֣���������ѧ��Ҫ��
long);
	set("no_fight", 1);
	set("exits",([
          "out" : __DIR__"pt",
]));
	//set("coor/x",490);
	//set("coor/y",430);
	set("book/dujing",1);
	set("book/yaoli",1);
	setup();
}
	    	
void init()
{
	object me=this_player();
	if (me->query_temp("clgf/suok")&& present("shenlong gou",me))
	{
		message_vision(HIC"$Nƽ�ľ����������Ķ���Զ��ɽ���Х������һƬ���ס�\n"NOR,me);
		message_vision(HIY"\n\n\n$N���պ������˵�İ��壬������ζ(tiwei)��\n"NOR,me);
		me->set_temp("clgf/start1",1);
		me->delete_temp("clgf/suok");
		add_action("do_lw","tiwei");
	}	
	add_action("do_search","search");

}
int do_search(string arg)
{
	object me=this_player();
	
	if (!arg||arg!="shelf")
		return notify_fail("��Ҫ����ʲô��\n");
	if (present("shedu jing",me) || present("shenlong yaoli",me))
		return notify_fail("�����ϴ��д����鼮������̰�����ᡣ\n");
	if (arg=="shelf" && !random(3))
	{
		message_vision("$N˺������ϵķ�����Ȼ���������ó�һ���鷭����\n",me);
		switch (random(2))
		{
			case 0:		
			if (query("book/dujing")>0)
			{
				new("d/sld/obj/shedujing2")->move(me);
				message_vision("$N��������õ�һ�����߶���(��)����\n",me);
				this_object()->add("book/dujing",-1);
			}
			break;
			case 1:

			if( query("book/yaoli")>0)
			{
				new("d/sld/obj/yaoli3")->move(me);
				message_vision("$N��������õ�һ��������ҩ��(��)����\n",me);
				this_object()->add("book/yaoli",-1);			
			}
			break;
			default:break;
		}
	}
	
}
	    	
int do_lw(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="������")
		return notify_fail("��Ҫ����ʲô��\n");
	if (!present("shenlong gou",me))
		return notify_fail("��û�б�������Ҫ����ʲô��\n");

	if (me->query("quest/sld/clgf/canglang/pass"))
		return notify_fail("���Ѿ�ȫ�������˲��˹���������İ��أ�\n");
	if (time()-me->query("quest/sld/clgf/canglang/time")<86400)
		return notify_fail("������̫�ڿ��ˣ�\n");
	//if (me->query("quest/sld/clgf/canglang/pass"))
		//return notify_fail("���Ѿ�ȫ�������˽��߲�˿�ֵİ£�\n");
	if (me->query_temp("clgf/start1")) 
	{
		   message_vision(HIR"��ƽ�ľ�������ϥ�������ó�һ������������������ϣ�����һƬ���顣\n"NOR,me);
		   message_vision(HIR"\nһ�߹۲챦����һ�߿�ʼ����������ᵽ�Ĳ��˹����İ��ء�\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("clgf/start1");
	}
	return;
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //�ž����ԣ��������ף��Ӵ��Ѷ�
  if (me->query("gender")=="����") j=random(200);
  else j=random(10);
  me->set("quest/sld/clgf/canglang/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ���������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_canglang")<(30+random(10)))
   {  
	  me->add_temp("canwu_canglang",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
	  tell_room(environment(me),HIC"\n"+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=25
			&& j==2
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N��Ȼ���������������Ц������˵������ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˽��������ڵĲ�����İ��أ����˹�����Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������˹����İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/clgf/canglang/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/clgf/canglang/time",time());
		 me->set("quest/sld/clgf/canglang/pass",1);
		 me->delete_temp("canwu_canglang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�������⣬��ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/clgf/canglang/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/clgf/canglang/fail",1);
		 me->set("quest/sld/clgf/canglang/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_canglang");
		 return 1;
   }

}