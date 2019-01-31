// trees2.c
// ������2
//add by sohu, chansishou quest
#include <ansi.h>

inherit ROOM;
int do_guancha(string arg);

void create()
{
	set("short","����");
	set("long",@long
����������ö��ָ��д󣬴ִ����֦��������ཻ����һ����ס��
���⣬������ï�ܵ��Ӳݣ���������಻֪����Ұ����ɢ��������ܺ���
�������������Ϻ��Ӳ�����������ڷ���˻˻����������������ԼԼ�غ�
���м������ݡ�
long);
	set("exits",([
		 "north" : __DIR__"kongdi",
          "northeast" : __DIR__"treee1",
          "northwest" : __DIR__"treew1",
          "south" : __DIR__"trees1",
	]));
	set("objects",([
			__DIR__"snake/dushe2" : 2,
	]));
	set("outdoors", "������");
    set("canfindsnake",1);
    set("coor/x",490);
    set("coor/y",400);
    set("coor/z",0);
    setup();
}
void init()
{
	object me=this_player();
	if (me->query_temp("chansi/asksu"))
	{
		message_vision(HIC"$Nվ�����ּ䣬���������Ľ̵���˿�ֵİ��أ���Լ���ƺ�ץ����һ˿����\n"NOR,me);
		message_vision(HIY"\n\n\n$N˼ǰ���ܾã�Ȼ������������й۲��£����Ƿ������ĵá�\n"NOR,me);
		me->set_temp("chansi/dunwu1",1);
		me->delete_temp("chansi/asksu");
		add_action("do_guancha","guancha");
	}	

}
	    	
int do_guancha(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="��")
		return notify_fail("��Ҫ�۲�ʲô��\n");
	if (me->query("quest/sld/chss/pass"))
		return notify_fail("���Ѿ�ȫ�������˽��߲�˿�ֵİ£�\n");
	if (time()-me->query("quest/sld/chss/time")<86400)
		return notify_fail("������̫�ڿ��ˣ�\n");
	if (me->query_temp("chansi/dunwu1")) 
	{
		   message_vision(HIR"��ƽ�ľ����������ڲݴ��У���ʼ�۲��������ߵĶ�����\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("chansi/dunwu1");
	}
	return;
}

int thinking(object me)
{
  int i,j,k; 
  if(!me) return 0;
  k=random(me->query("kar"));
  //�ž����ԣ��������ף��Ӵ��Ѷ�
  
  if (me->query("gender")=="����") j=100+random(200);
  if(me->query("m-card-vip")) j =  17;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
	  i=random(j);
  me->set("quest/sld/chss/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ����ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_chansi")<(10+random(5)))
   {  
	  me->add_temp("canwu_chansi",1);
      if(random(1)) tell_object(me,HIG"\n��Ȼ��һ���ߴܵ����ϣ�����ǰ�С�������ּ����к����������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
      else tell_object(me,HIY"\n\n\n��һ�����ںͷ�ӥ�ڲ���..��������Ȼ����ӥ׽ס��������Ȼһ�ܽ�����ӥ���һ�ţ�...\n"
							+"\n��ӥ�޷�չ�ᣬ��������ڵ��ϡ�����Ȼ��Ѫ����ȴ����������\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (k>=22
			&& i<5
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˽������������ڵĽ��߲�˿�ֵİ��أ���˿�ֻ�Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������߲�˿�ֵĲ�˿���أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail"),
		 k,
		 i,
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
		 k,
		 i,
         me->query("combat_exp")));
        
		 me->add("quest/sld/chss/fail",1);
		 me->set("quest/sld/chss/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chansi");
		 return 1;
   }

}