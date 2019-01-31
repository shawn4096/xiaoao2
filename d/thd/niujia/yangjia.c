//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"
void create()
{
	set("short", "���С��");
	set("long", @LONG
����һ��ʮ����ˬ���񷿣��Ҿ߰���һӦ��ȫ��ֻ�Ƕ�����һ���������
���м���һ��С�������ϵı��뻹��û�г�ȥ����������ȥ�ĺܴ�æ��ǽ�Ϲ�
��һ�˶̱����������ǹ(Tieqiang)��
LONG
	);

	set("item_desc", ([
		"tieqiang" : "һ���þ��˵���ǹ��������ԭ��Ӧ����һ�Եģ���֪Ϊ��ֻʣ��һ�ˡ�\n",
	]) );

	set("exits", ([
		"north" : __DIR__"houyuan.c",
		"south" : __DIR__"qianyuan.c",
	]));
    set("objects",([
               __DIR__"npc/yang": 1,
            //   __DIR__"npc/bao": 1,
     ]));

	setup();
}
//�𴦻��ߺ����Ը�Ᵽ��������,��ϧ��������պ���
//���ѡ��ȥ�������պ��ң�����а�ߣ����𴦻����˴�ս��


void init()
{
  object me,obj,yang,guo,qiu;
  me = this_player();
  add_action("do_jiejiao","jiejiao");

  //ʹ��

  if (me->query(QUESTDIR1+"start") 
	 &&objectp(present("yang tiexin",this_object()))
	 &&!me->query_condition("killer")
	 &&!me->query(QUESTDIR1+"over")
	 && me->query_temp(QUESTDIR1+"xiangzhi"))
  {
		
	  message_vision(HIC"�������ۼ��������������Ц����$N˵�����������þ��ˣ���л��λӢ�۵����ƣ���������������\n"NOR,me);
	  if (!objectp(guo=present("guo xiaotian",this_object())))
	  {
			guo=new("d/thd/niujia/npc/guo");
			guo->move("d/thd/niujia/yangjia");
	  }
	  if (!objectp(qiu=present("qiu chuji",this_object())))
	  {
			guo=new("d/thd/niujia/npc/qiuchuji");
			guo->move("d/thd/niujia/yangjia");
	  }
	  call_out("say_baby",3+random(4),me);
	  me->delete_temp(QUESTDIR1+"xiangzhi");
	  me->set_temp(QUESTDIR1+"saybaby",1);
	  return;
  }
//����������ɱ��
  if (me->query(QUESTDIR+"start")
 	 &&!me->query_condition("killer")
	 &&!me->query(QUESTDIR1+"over")
	 && me->query(QUESTDIR+"tongyin")
	 && me->query_temp(QUESTDIR1+"helpyangtiexin") )
  {
     tell_object(me,HIC"������ŭ�����ߣ������߳��������ȵ������Ҿ��������ģ����Ǹ���ô����������������һ�������»��ת���˿�����\n" 
                       "�����һ����������߽����е������ã����������ģ����Ҽ���ȥ�������ˣ�������������һӵ���ϡ������ĵ�תǹ����\n"NOR+
                    RED"һ�С��׺羭�족������������ɨ���ڵأ�����һ�С�������ŭ����ǹ������һ�����������˶ѣ��ȵ�����Ҫ���ˣ��ȵ�˵˵�ҷ�����ô���\n"NOR); 
     message_vision(HIR"\n���ͻȻ����$N��������ȫ��һ㶣�ͻȻһ�������˵�������ҵ���ү׽��Ҫ��������ɱ�ˡ���\n"NOR, me);
     me->delete_temp(QUESTDIR1+"helpyangtiexin");
     me->set_temp(QUESTDIR1+"fightjinbing",1);
/*	 
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
*/
	 obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(environment(me));  
	 obj->kill_ob(me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
  //   remove_call_out("killme");
     call_out("check_kill", 5, me);        
  }      
}
int check_kill(object me)
{
	object bing;
	if (!me) return 0;
	
	if (file_name(this_object())!="/d/thd/niujia/yangjia")
	{
		me->set("quest/���Ӣ�۴�/time",time());
		me->add("quest/���Ӣ�۴�/fail",1);
		me->delete_temp("quest/���Ӣ�۴�");
		message_vision(HIY"�������뿪ս���������������ӣ�����ʧ�ܣ������ټ���!\n"NOR,me);
		return 1;
	}
	if (!me->is_fighting()
		&& present("yang tiexin",this_object())
		&& !present("jin bing",this_object()))
	{
		me->set("quest/���Ӣ�۴�/��ѩ����/�ɹ�����������",1);
	    return 1;
	}
	call_out("check_kill",1,me);
}
//�𻰣�
int say_baby(object me)
{
	
	message_vision(HIY"\n���˺��žƣ��˴�������Ͷ����֪�����䶼�ȵĲ���ˣ�\n"NOR, me);
	message_vision(CYN"\n�����Ĵ�ʱ˵�������Һ͹����Ļ�Ҷ��ѻ��У�������Ĳ��Ȼ��Ҫ�������ǂz�������������Ρ���\n"NOR, me);
	message_vision(CYN"\n�𴦻���������˵�����������ܣ���δѩ�����Ӻ޺�ʱ���ҿ��ͽ���͹�����Ρ���\n"NOR, me);
	message_vision(CYN"\n������˵�������������к����ͽ��Ϊ�ֵܣ�����Ů��Ϊ���ã���Ů���Ƿ��ޡ���\n"NOR, me);
	message_vision(CYN"\n�𴦻�˵�����������ҽ��յõ�����ذ�ף���Ϊ��λ�ֵ����õļ����Ҳ���ϵ��ҵ�һ�����⡱��\n"NOR, me);
	message_vision(YEL"\n�𴦻��ӿڴ����ͳ�����ذ�ף��˹��ڽ��Ͽ��¡��������͡���������������������ĺ͹�Х�죿\n"NOR, me);

	message_vision(CYN"\n��һ���飬���˶��Ǿ����˷ܣ����ʼ��δ���������ڴ���\n"NOR, me);
	message_vision(HIG"\n������������������մ�ѩ�׷ף����ǽ�������β�ʹ��һ����Ҳ���������õ�ʱ�⡱��\n"NOR, me);
	message_vision(HIR"\n��Ը����������ĵ�ʹ����tongyin yes||no������ô?��ע�⣬ֻ��һ��ѡ�����!\n"NOR, me);

	add_action("do_tongyin","tongyin");
	
}
//tongyin
int do_tongyin(string arg)
{
	object me,yang,guo,qiu;
	int i;
	
	me=this_player();
	i=me->query_temp("quest/���Ӣ�۴�/��ѩ����/hejiutime");
	message_vision(HIY"\n�����ĺ�������ϧ�����Ͼƣ���\n�ڴ��ڼ䣬$N���������ĵķ��˰�ϧ���ϾƵ�ʱ���е�ã�\n"NOR, me);
	message_vision(HIC"\n��ĿǰΪֹ�Ѿ�����"+chinese_number(i)+"��ƣ��˴˼�Խ��Խ��Ͷ���������������֮�⣡\n"NOR, me);
	
	if (me->query("quest/���Ӣ�۴�/tongyin"))
	{
		return notify_fail("���Ѿ�ѡ����ʹ����һ���ݣ�\n");
	}
	if (me->query("quest/���Ӣ�۴�/��ѩ����/notongyin"))
	{
		return notify_fail("��û��ѡ���һȺɽҰ���ʹ�����Լ����µ�ѡ��\n");
	}
	if (time()-me->query("quest/���Ӣ�۴�/time")<86400)
	{
		return notify_fail("�����Ѿ��ȹ����ˣ���û���������������\n");
	}
	if (arg=="yes")
	{
		message_vision(HIG"\n�ڴ������£�����һ��ʹ����$N��ϸ�緢��������䷢�������ķ��˰�ϧ���ڼ��뿪�ܳ�һ��ʱ�䣬\n����������ʱ��ɫ��΢��Щ���ң�\n"NOR, me);
		message_vision(HIC"\n�������¶Ǻ�$N������ǳ������˵�š��ɣ��ɣ������𽥻�˯��ȥ��\n"NOR, me);
		//me->apply_condition("drunk",100);
		message_vision(HIR"\n�����Ժ������ƺ�����Զ�������ڴ��������������������\n"NOR, me);

		me->unconcious();
		me->set_temp("quest/���Ӣ�۴�/��ѩ����/yestongyin",1);
		me->set("quest/���Ӣ�۴�/��ѩ����/yestongyin",1);
		me->set("quest/���Ӣ�۴�/tongyin",1);
		
	}
	if (arg=="no")
	{
		message_vision(HIG"\n��������ٺ��ˣ�˵������ʱ��Ҵң���Ȼ��Ҷ��ȵþ��ˣ��ҿ��͵���Ϊֹ���ðɣ���\n"NOR, me);
		message_vision(HIG"\n�����ĺ͹�Х���Լ��𴦻��˴˿��˿����׷׵�ͷ����������κȾơ�\n"NOR, me);
		me->set("quest/���Ӣ�۴�/��ѩ����/notongyin",1);
		me->set("quest/���Ӣ�۴�/bad",1);

		me->set_temp("quest/���Ӣ�۴�/��ѩ����/notongyin",1);
		//me->set("quest/���Ӣ�۴�/��ѩ����/yestongyin",1);
	}
	if (objectp(qiu=present("qiu chuji",this_object())))
	{
		destruct(qiu);
	}
	if (objectp(guo=present("guo xiaotian",this_object())))
	{
		destruct(guo);
	}
	me->add_temp("quest/���Ӣ�۴�/��ѩ����/hejiutime",1);
	return 1;

}	


int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n��������ȵ��������ߡ�һ����ס�㣬�㾹Ȼ�޷��뿪��\n"NOR);
       if (present("jin bing",this_object()))

		   return notify_fail(RED"\n��������ȵ��������ߡ�һ����ס�㣬�㾹Ȼ�޷��뿪��\n"NOR);
   		if(me->query_condition("killer")) 
   		          return notify_fail(RED"\n��ô�����ģ��������wiz�ɡ�\n"NOR);
        return ::valid_leave(me, dir);
}

