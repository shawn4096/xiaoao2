inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "ƽ��");
        set("long", @LONG
�����Ǻ�ɽ�ϵ�һ��ƽ�ء����ƽ�غ�����������Ϊ����ɹ���ֹ���֮��
����ƽ�������ƽ�ص����ܴ��˺ܶ�ľ�ܣ��Ҳ���һ�Ÿ��ʵ���������һ�ô�
������֦込���һ��Сľ�ݡ�
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "west" : __DIR__"xiaolu3",
               // "enter" : __DIR__"shandong",
        ]));
		set("item_desc", ([
        "Сľ��": CYN"����һ��Сľ�ݣ��ƺ��ܾ�û������ס�����ӣ����������˺��Ļ�ѩ��\n"NOR,
	    //"����":HIC"������ƺ����������½�룬�粻��ϸ�۲죬����û����ʲô�쳣��\n"NOR,
        ]) );
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
int init()
{
	object qiu,yang,xiao,duan;
	object me=this_player();
	
	add_action("do_jump","jump");

	if (me->query_temp("tzjj/tingover"))
	{
		if (!objectp(qiu=present("qiu qianzhang",environment(me))))
		{
			qiu=new("kungfu/class/tiezhang/qqren");
			qiu->move("d/quanzhen/pingdi");
			qiu->set("name",HIC"�ȶ�"NOR);

		}
		if (!objectp(duan=present("yideng dashi",environment(me))))
		{
			duan=new("d/dali/yideng/npc/yideng");
			duan->move("d/quanzhen/pingdi");
		}
		
		//yang=new("kungfu/class/gumu/yang");
		//yang->move("d/quanzhen/pingdi");
		//xiao=new("kungfu/class/gumu/xln");
		//xiao->move("d/quanzhen/pingdi");
		//qiu->kill_ob(duan);
		message_vision(HIR"\n\n$N��$n�ȵ�����������ƭ�ң������ң�ʲô�����ް��������һ�����ԡ�˵��һ������$n��\n��"NOR,qiu,duan);
		message_vision(HIY"\n\n$N�����ƹ������Ϭ����Ϊ$Nһ�������ؿڣ��۵�ͻ��һ����Ѫ��������ˣ���$nȴû��˿������֮�⡣\n"NOR,qiu,duan);
		message_vision(CYN"$N��ü�ʹ���ֻ�ǵ����������а����ӷ�\n"NOR,duan);
		duan->add("qi",-3000);
		call_out("qiu_kill",3+random(2),me,duan,qiu);
		me->delete_temp("tzjj/tingover");

	}
	


}
int do_jump(string arg)
{
	object me=this_player();
	if (!arg || arg!="Сľ��")
	{
		return notify_fail("��Ҫ���Ķ�����\n");
	}
	if (me->query_skill("dodge",1)<350)
	{
		return notify_fail("����������������350����ȥ�ú���ϰ�ɡ�\n");
	}
	message_vision(HIC"������һԾ��������辣�һ��������Сľ��֮�С�\n"NOR,me);
	me->move("d/quanzhen/xiaomuwu");
	return 1;

}
int qiu_kill(object me,object duan,object qiu)
{
	
	message_vision(HIR"��ǧ���ۼ�$Nվ��һ�ԣ�˫Ŀ��ʱ����׺ݣ���$N�ȵ����Ҽ���Խ��Խ��˳���ˣ�"NOR,me);
	qiu->kill_ob(me);
	me->kill_ob(qiu);
	me->set_temp("tzjj/qiukill",time());
	me->delete_temp("tzjj/tingover");
	call_out("check",1,me,duan,qiu);
	return 1;
}
int check(object me,object duan,object qiu)
{
	if (!me) return 1;
	
	if (!present("qiu qianren",environment(me)) && !me->is_fighting())
	{
		message_vision(HIC"$Nͣ�����������뷽�Ŵȶ���һ��һʽ���˵��Ǿ����쳣����������������\n"NOR,me);
		message_vision(HIY"\n\n\n�������Ǻ��б�Ҫ��ȥ���Լ���ʦ��̽���������Ʒ��ľ�����ʽ�����ˡ�\n"NOR,me);
		//message_vision(YEL"\n\n$Nɲ�Ǽ�������������е�����������������һ������Ķ���(dunwu)״̬��"NOR,me);
		//add_condition("do_dunwu","dunwu");
		destruct(duan);
		//destruct(qiu);
		me->set_temp("tzjj/killover",1);
		return 1;
	}
	if (time()-me->query_temp("tzjj/qiukill")>30)
	{
		message_vision(HIY"��̫����ˣ�ɱһ����ɮ��������ô��ʱ�䣬����ʧ�ܡ�\n"NOR,me);
		if (objectp(qiu=present("qiu qianren",environment(me))))
			destruct(qiu);
		if (objectp(duan=present("yideng dashi",environment(me))))
			destruct(duan);
		me->set("quest/tz/tzzf/tiezhang/time",time());

		return 1;
	}
	call_out("check",2,me,duan,qiu);

}

//������ܣ�����������

/*	    	
int do_dunwu(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="���ƾ���")
		return notify_fail("��Ҫ����ʲô��\n");
	if (me->query("quest/tz/tzzf/tiezhang/pass"))
		return notify_fail("���Ѿ�ȫ�����������ƾ����似��\n");
	if (time()-me->query("quest/tz/tzzf/tiezhang/time")<86400)
		return notify_fail("������̫�ڿ��ˣ�\n");
	
	if (me->query_temp("tzzf/dunwu1")) 
	{
		   message_vision(HIC"��վ���Ƕ���ɲ�Ǽ����һ�ֶ���״̬��������˿������ʵ������е���������\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("tzzf/dunwu1");
	}
	return 1;
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(15);

  me->set("quest/tz/tzzf/tiezhang/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) �������ƾ���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_tiezhang")<(15+random(10)))
   {  
	  me->add_temp("canwu_tiezhang",1);

	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
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
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));
	
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	  return 1;

   } 
   else if (i>=28
			&& j==2
			&& random(me->query("str"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˽������������ڵĽ��߲�˿�ֵİ��أ���˿�ֻ�Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������߲�˿�ֵĲ�˿���أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/chss/time",time());
		 me->set("quest/sld/chss/pass",1);
		 me->delete_temp("canwu_chansi");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n������߲�˿�ֽ���ʧ�ܣ�\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�����߲�˿�֣���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/chss/fail",1);
		 me->set("quest/sld/chss/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chansi");
		 return 1;
   }

}*/