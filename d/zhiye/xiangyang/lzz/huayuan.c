//huayuan.c
//Csl 2000.04.26
#include <ansi.h>

inherit ROOM;
string look_gushu();
void create()
{
        set("short", "��԰");
        set("long",@LONG
�����԰��Ȼ���󣬵�����ľ�����������ֲ�Ÿ�ʽ�����Ļ����ݲݣ���
�ĳ��������������һ�����򣬳�����������ɢ�����������������Ļ�������
��ͨ���Ժ��·�����������˴����Ĺ�������ľɭɭ�����Ǹߴ�֦Ҷ��ï��
����дС�
LONG
        );
		set("outdoors", "����");
        set("exits",([
                "south"  :  __DIR__"houyuan",
		]));
		set("item_desc", ([
                "����" : (:look_gushu():),
        ]));

	setup();
}

string look_gushu()
{
	this_player()->set_temp("lookgushu",1);
	return "����һ������деĹ������������ƣ�֦辷�ï������ſ�����Ͽ������ټ���\n";

}

void init()
{
	object me=this_player();
	object huang,lu;
	add_action("do_jump","jump");
    
	if (me->query_temp("bangjue/cang"))
	{	
		if (!objectp(huang=present("huang rong",load_object("d/xiangyang/lzz/huayuan"))))
		{
			huang=new("d/xiangyang/lzz/npc/huangrong");		
			huang->move("d/xiangyang/lzz/huayuan");	
		}
		if (!objectp(lu=present("lu youjiao",load_object("d/xiangyang/lzz/huayuan"))))
		{
			lu=new("d/xiangyang/lzz/npc/lu");
			lu->move("d/xiangyang/lzz/huayuan");	
		}
		//me->start_busy(999);
		call_out("do_tech1",2+random(3),me,huang,lu);
	}
}

int do_jump(string arg)
{
	object me=this_player();
	if (!me->query_temp("lookgushu"))
		return notify_fail("��Ҫ��ʲô��\n");
	if (!arg || arg!="����")
	{
		return notify_fail("����һ������һ��Ҫ����������\n");
	}
	message_vision("$N��������������ȥ��˲��������֦��Ҷï������֮�䡣\n",me);

	me->move("d/xiangyang/lzz/gushu");
	return 1;
}

int do_tech1(object me,object huang,object lu)
{
	
	huang->say_lu1();
	lu->say_huang1();
	call_out("do_tech2",2+random(2),me,huang,lu);
	
}
int do_tech2(object me,object huang,object lu)
{
	
	huang->say_lu2();
	lu->say_huang2();
	call_out("do_tech3",1+random(2),me,huang,lu);
	
}
int do_tech3(object me,object huang,object lu)
{
	message_vision(YEL"\n\n$n����򹷰��İ��־�һһ������$N����������ա�\n"NOR,me,huang);

	huang->fight_ob(lu);
	lu->fight_ob(huang);
	//message_vision(YEL"���ؽ���򹷰��İ��־�һһ������������������ա�\n"NOR);
	add_action("do_guanwu","guanwu");
}


int do_guanwu(string arg)
{
  object me=this_player();
  if(!arg||arg!="�򹷰�") return notify_fail("��Ҫ��Ħʲô��");
  
  if (me->query("family/family_name")!="ؤ��")
	 return notify_fail("�㲻��ؤ���ӵܣ�����Ī�����ɹŹ��ļ�ϸô��\n");
  if (me->query("family/master_name")!="���߹�")
	 return notify_fail("�㲻�Ǻ��߹���ү�ӵ��״����ӣ�����������\n");
  
  if (me->query_skill("dagou-bang",1)< 450)
	 return notify_fail("��򹷰��ȼ�̫�ͣ�����450������������\n");
  if (me->query("quest/gb/dgb/bangjue/pass"))
	 return notify_fail("���Ѿ��⿪�������⣬����������\n");
  if (time()-me->query("quest/gb/dgb/bangjue/time")<86400)
	 return notify_fail("������̫�ڿ��ˣ�\n");
  if (me->is_busy())
	 return notify_fail("������æµ�У�\n");
  if(me->query("quest/gb/dgb/bangjue/fail")>=3 && me->query("registered")<3)
  {
		tell_object(me,"shrug �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		return 1;
  }
  if (me->query_skill("dagou-bang",1)< 450)
	 return notify_fail("��򹷰��ȼ�̫�ͣ�����450������������\n");
  me->start_busy(999);
  remove_call_out("thinking");
  call_out("thinking",1,me);
  return 1;

}
int thinking(object me)
{
   int i,j;
	object huang,lu;
  if(me->query_temp("bangjue/guanwu")<(5+random(5)))
  { 
	  me->add_temp("bangjue/guanwu",1);
      if(random(2)) tell_object(me,HIG"\n����������ŷ��Ż��غ�³�н�ս������չ�ֵ�һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬��Ӱ��˸�����ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("bangjue/guanwu");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
 	
	tell_object(me,HIG"\n�����˻��ص�ָ�㣬�Դ򹷰���ʽ�Ϳھ��ںϵ����������ƺ���Щ�ĵá�\n"NOR);
    tell_object(me, HIW"\n�㰴�ջ������ԣ�ʩչ���������־�������ľ���ٻ�֮����˸������\n"NOR);
    tell_object(me, HIC"\n�㰴�ջ������ԣ�ʩչ�����⡹�־�����Ӱ��ɽ���������ܣ�ˮ�ò�����\n"NOR);
	tell_object(me, HIR"\n�㰴�ջ������ԣ�ʩչ���������־�����ʽѸ���ޱȣ���ʽ����������\n"NOR);
	tell_object(me, HIY"\n�㰴�ջ������ԣ�ʩչ�������־����������ܣ�һ����һ��������\n"NOR);
	tell_object(me, HIG"\n�㰴�ջ������ԣ�ʩչ����ת���־��������γ�һ�����У����Է�Ȧ�ڰ�Ӱ֮�ڡ�\n"NOR);
	tell_object(me, HIB"\n�㰴�ջ������ԣ�ʩչ���������־���ָ��������ָ�ϴ򱱣�ȫ���·����ԣ���ÿһ��ȴ���鶯�쳣��\n"NOR);
	tell_object(me, RED"\n�㰴�ջ������ԣ�ʩչ���������־������йٱʡ��糤ǹ����ذ�ס��������۳������˵����͡�\n"NOR);
	tell_object(me, BLU"\n�㰴�ջ������ԣ�ʩչ���������־������а��ӷ·�������һ�㣬���ƹ�֮������Է���ʽ���ߡ�\n"NOR);
     //����30+300Ϊ����
	if(i<3 
		&& me->query("kar")<31
		&& random(me->query_int())>50
		&& random(me->query("kar"))>27)
	 {
		tell_object(me,HIY"\n\n������ǧ���ڿ࣬���ڵó���Ը�����򹷰��ھ��ڻ��ͨ! \n"NOR);
       	me->set_skill("bangjue", 200);
		me->set("quest/gb/dgb/bangjue/pass",1);

		message_vision(HIC"��Ĵ򹷰����ھ������ˣ�"NOR,me);
		me->start_busy(1);
		log_file("quest/dgbbangjue", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������򹷰��ھ�������iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/gb/dgb/bangjue/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gb/dgb/bangjue/fail",1);
		me->set("quest/gb/dgb/bangjue/time",time());
		
		tell_object(me,HIY"\n\n�����˻��ص�ָ�㣬��Ȼ�����˰����İ��أ����Ƕ԰�����κ���ʽ�ڻ��ͨ����������ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HBBLU+HIW"\n\n���ܰ����ھ�ʧ�ܣ��ٽ�������\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("bangjue");
		log_file("quest/dgbbangjue", sprintf("%8s(%8s) �򹷰���������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/gb/dgb/bangjue/fail"),i,me->query("combat_exp")) );
	  }

	  if (objectp(huang=present("huang rong",environment(me))))
	  {
		  destruct(huang);
	  }
	  if (objectp(lu=present("lu youjiao",environment(me))))
	  {
		  destruct(lu);
	  }
      return 1;
  }

}
