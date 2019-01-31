// Room: /u/numa/thd/shanding.c
// Modified by Numa 19980903

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"�Խ��嶥"NOR);
        set("long",@LONG
��������Խ���ķ嶥��������ʯ����������֮����Ҫ���ȥ����
���Ѷ�֮����������������ȥ�������һ���һ�����ࡣ
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","�һ���");

        setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_jump","yue");
	add_action("do_sit","sit");
	//add_action("do_biguan","lingwu");
	add_action("do_biguan","biguan");
}

int do_jump(string arg)
{
	object me = this_player();
	
	if (me->is_fighting() || me->is_busy())
		return notify_fail("����æ���أ�\n");
	if (arg!="ya") return 0;
	if(me->query_encumbrance() * 100 / me->query_max_encumbrance() > 20)
	        return notify_fail("�㸺�ع��࣬��������Ծ��ȥ��\n");
        if (me->query_skill("dodge") < 100)
                return notify_fail("�㳢��Ծ��԰��Ķ��£���ȴ�����Լ��޷�Ծ��ȥ��\n");
        tell_room(environment(me), HIC+me->name()+"���˽�������Ʒ���漴һ�С��沨������Ծ��԰����£����ȵ����ڶ��档\n" NOR, ({me}));
        write("����Ϣһ�ᣬ����Ծ�����¡�\n");
        me->move(__DIR__"shanya");
        return 1;
}
int do_sit()
{
	object me=this_player();
	if (!me->query_temp("quest/thd/biguan/askhuang"))
	{
		return notify_fail("����ϥ����������ֻ������ɽ���Х����ɫ������\n");

	}
	if (me->query_temp("quest/thd/biguan/start"))
	{
		return notify_fail("���Ѿ���ϥ����������\n");

	}
	write(HIC"����ϥ����������Զ��Զ������һɫ���پ��Ŀ�������\n");
	me->set_temp("quest/thd/biguan/start",1);
	return 1;

}

int do_biguan()
{
	int i,count,ht;

	object me=this_player();
	
	if (!me->query_temp("quest/thd/biguan/start"))
	{
		return notify_fail("����˼����������չ�Ҳ���������ʲô���춯�ص��书��\n");

	}

	if (me->query("family/family_name")!="�һ���"||me->query("family/master_name")!="��ҩʦ")
	    return notify_fail("�㲻���һ�������������Ϊ������\n");
	
	if( time()-me->query("quest/thd/biguan/time")<86400 )
		return notify_fail("������Ҳ̫�ڿ��˵㣿\n");
    
	if (me->is_busy())
	{
		return notify_fail("������æµ��....\n");
	}
	if (me->query("int")<50 || me->query("con")<50)
	      return notify_fail("��������ǻ��������Բ���50������չ�Ҳ��û���ջ�\n");

	if (me->query_skill("qimen-bagua",1)<200 )
	      return notify_fail("�����Ű��Բ���200������չ�Ҳ���������ְ��\n");
	
	message_vision(HIG"��̺���������Ĭ���һ������Ű��Եİ��壬��ʼ�չ�������\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	return 1;

	
}
int thinking(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
  t = 25;
  if(me->query("m-card-vip")) t =  20;
  if(me->query("y-card-vip")) t =  18;
  if(me->query("buyvip"))     t =  15;
  t=random(t);
  j=me->query("int")+me->query("con");
  j=random(j);
  me->set("quest/thd/biguan/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) �һ����չ�ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("thd_biguan")<(10+random(10)))
  {  
	  me->add_temp("thd_biguan",1);
      if(random(3)==2) tell_object(me,HIG"\n����Դ󺣣���ϻ�ҩʦ�����ڵ��ķ��˴�ӡ֤��ֻ�����Ժ���һƬ����\n"NOR);
      else if (random(3)==1) tell_object(me,HIC"\n���һ������Ȼ������ǰ����һƬ���Ű��������ֵ��¸�֣���ǰ��û����ľ���\n"NOR);
      else tell_object(me,HIY"\n�㽫�Լ�һ����ѧ���뵽�̺��������У���ʱ��������...\n"NOR);  
	  
	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>26
			&& t<3
			&& j>85
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIC"\n$N���������������ڳ��׽��һ��������似���ķ���Ϊһ�壬�似����һ��¥����\n"NOR,me); 
		 message_vision(HIC"\n$N�̲�ס���쳤Х���پ����¾�Ӣ��������˶��ѵĸо���\n"NOR,me); 
		 message_vision(HBWHT+HIR"\n��ϲ�㣬�һ����չز���һ��ͻ�ƣ���ʱ��ǰһƬ̹;��������󣬾���ȥ�ã�\n"NOR,me); 

         log_file("quest/thdbiguan", sprintf("%s(%s) ��%d�β��򣬻�Ե�ɺ��£��ɹ��չز����һ����ռ��似����ǰ����ֵ��%d����ǰ�������%d,��ǰ�������Ժ͸��ǣ�%d����ǰ���飺%d\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/thd/biguan/fail"),
		 i,
		 t,
		 j,
         me->query("combat_exp")));

		 //me->set("bhg/flhttime",time());
		 //me->set("bhg/biguan",1);
		 me->set("title",HBWHT+HIG"��а"NOR);
		 me->set_skill("qimen-bagua",300);
		 me->set("quest/thd/biguan/pass",1);

		 me->delete_temp("thd_biguan");
		 me->delete_temp("quest/thd");
		 return 1;
     }
	 else {
	     message_vision(WHT"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n�һ����չ�ʧ��!\n�ٳ߸�ͷ�ٽ�һ����ʵ���ף���һ��Ҫ��ֲ�и��\n"NOR,me); 
         log_file("quest/thdbiguan", sprintf("%s(%s) ��%d�αչز����һ����似ʧ�ܣ���ǰ����ֵ��%d����ǰ�������%d,��ǰ�������Ժ͸��ǣ�%d����ǰ���飺%d\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/thd/biguan/fail"),
		 i,
		 t,
		 j,
         me->query("combat_exp")));

        
		 me->add("quest/thd/biguan/fail",1);
		 me->set("quest/thd/biguan/time",time());
		 me->start_busy(1);
		 me->delete_temp("thd_biguan");
		 me->delete_temp("quest/thd");
		 return 1;
   }


}	