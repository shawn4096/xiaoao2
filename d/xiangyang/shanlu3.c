// /d/xiangyang/shanlu3.c
// Lklv Modify 2001.9.22
#include <ansi.h>

inherit ROOM;
int nanhai_eshen(object me,object mu);
int do_help(string arg);

void create()
{
	set("short", "ɽ��С·");
	set("long", @LONG
�������һƬСɭ�֣������ּ�С·�ϣ�������������ֵ�ס�����⣬
�����Ե�ʮ����������ľ�����ݺᣬ����û��ʲô��·��.
LONG
	);
        set("outdoors", "����");
        set("xyjob", 1);
	set("exits", ([
		"northeast" : __DIR__"shanlu2",
	]));

	set("objects",([
		__DIR__"npc/dingpopo" : 1,
		__DIR__"npc/pingpopo" : 1,
		__DIR__"npc/ruipopo" : 1,

	]));

	setup();
}

void init()
{
    object yuzhuo;
	object me=this_player();
	yuzhuo=present("yu zhuozi",me);
	if (me->query_temp("yyzhi/muzhuo")
		&& objectp(yuzhuo))
		//&& yuzhuo->query("give_player")==me->query("id") 
	{
		//message_vision("eee",me);
		call_out("help_mu",3+random(3),me);
		me->delete_temp("yyzhi/muzhuo");
	}
  
}
int help_mu(object me)
{
	object mu;
	
	if (!objectp(mu=present("mu wanqing",this_object())))
	{
		tell_object(me,YEL"\n\n\n\n\n\n��Ȼһ����������Զ��������.....\n"NOR);
		tell_object(me,HIB"\n\n\n����һƥ��ɫ���������۶���������һλ��������������쭶�����\n"NOR);
		tell_object(me,HIC"\n\n\nֻ����λС������ɫ������������ɴ��������üĿ����ȴ�о���\n"+
			"��һλ�ټ�����Ů�������Ƕ���ү����ҪѰ�Ҳ�������ľ������\n"NOR);
		mu=new("d/dali/wuliang/npc/mu_wanqing");
		mu->move(this_object());
				
	}
	if (me && mu)
		call_out("nanhai_eshen",4+random(3),me,mu);
	
	return 1;

}
int nanhai_eshen(object me,object mu)
{
		object yue;
       if (!objectp(yue=present("nanhai eshen",this_object())))
       { 
		   tell_object(me,HIR"\n\n\n��ʱ����Ȼ��һ���ֺ������������������Ϻ��������϶����ˣ���\n\n"NOR);
		   yue=new("d/dali/wuliang/npc/eshen");
		   yue->move(this_object());
		   tell_object(me,HIC"�����̵ģ����ӽ������ϲŸ��ϣ���˵�Ǹ�С����Ķ����ԹԵθ�����ү��ȥ��\n"NOR);
       }
	   tell_object(me,HIC"�Ĵ����֮���Ϻ������������Ѿ������ñ�����ľ����"HIR"��baohu ľ���壩"HIC"��������ү������ˡ����\n"NOR);
	   add_action("do_help","baohu");
	   yue->kill_ob(mu);
	   yue->kill_ob(me);
	   return 1;

}

int do_help(string arg)
{
	
	
	object ping,ding,rui,yue,me,mu;
	me=this_player();
	ping=present("ping popo",this_object());
	ding=present("ding popo",this_object());
	rui=present("rui popo",this_object());
	yue=present("nanhai eshen",this_object());	
	mu=present("mu wanqing",this_object());
   
	if (!arg)
		return notify_fail("��Ҫ����˭��\n");
	
	if (!objectp(mu)){
		me->delete_temp("yyzhi");
		tell_object(me,HIW"ľ�����Ѿ�����������ʧ�ܣ�\n"NOR);
		return notify_fail("ľ���ﶼ�Ѿ���ɱ�ˣ������ڲų��֣�����̰��������\n");
	}
	if (!objectp(yue))
	{
		return notify_fail("����Ľ�������ʹ����ã��ٵȻῴ��,�Է��ܵ�����͵Ϯ��\n");
	}
	if (arg=="ľ����"||arg=="ľ����")
	{
		message_vision(HIC"$N����Ц����ľ���ﲻҪ���ģ��������㣡\n"NOR,me,mu);
		if (objectp(ping))
			ping->kill_ob(me);	
		if (objectp(rui))
			rui->kill_ob(me);
		if (objectp(ding))
			ding->kill_ob(me);
		if (objectp(yue))
			yue->kill_ob(me);
    
		call_out("checking",1,me,mu);
		return 1;
	}
}

int checking(object me,object mu)
{
 	object ping,ding,rui,yue;
	ping=present("ping popo",this_object());
	ding=present("ding popo",this_object());
	rui=present("rui popo",this_object());
	yue=present("nanhai eshen",this_object());
   
   if (!mu&&!me->is_fighting()&&!me->query_temp("yyzhi/helpmuover"))
   {
	   tell_object(me,HIW"\n\n\nľ�������䲻��������ľ��������ʧ�ܣ�\n\n\n"NOR);
	   me->delete_temp("yyzhi");
	   return 1;
   }
   if (objectp(mu) && mu->query("qi")< (mu->query("max_qi")/3) &&!me->query_temp("yyzhi/helpmuover"))
   {
	   tell_object(me,HIW"\n\n\nľ���������������أ�����ľ��������ʧ�ܣ�\n\n\n"NOR);
	   me->delete_temp("yyzhi");
	   return 1;
   }
   if (!objectp(rui) && !objectp(ping) && !objectp(ding) && !objectp(yue)&&objectp(mu))
   {
      tell_object(me,HIY"\n\n\n��������ʱ����ԡѪ��ս�������ڽ����е���ȫ��ɱ����\n\n\n"NOR);
	  message_vision(HIC"\n\�ۼ�ǿ���Ѿ����ߣ�$N����ǰȥ���ľ��������ơ�\n\n"NOR,me);

      tell_object(me,HIC"\n\���ľ�������Ʋ���̫�أ��;����ȴ�����ȥ�������ү��\n\n\n"NOR);
	  me->delete_temp("yyzhi/muzhuo");
	  me->set_temp("yyzhi/helpmuover",1);
	  me->set("quest/tls/yyz/start/helpmu",1);
	  if (mu) destruct(mu);
	
	  return 1;

   }    
   
	call_out("checking",3,me,mu);
	return 1;

}
