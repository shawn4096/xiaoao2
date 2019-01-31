// Room: /d/shaolin/ting.c
// Date: bren

#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_diao(object me,object wei);
int do_check(object me);
int thinking(object me);


void create()
{
	set("short", HIG"ӭ��ͤ"NOR);
	set("long", 
"������ӳ֮�У�һ��ʯͤ��Ȼ���С�ֻ��ͤ���Ҷ������ɷ�������š�"HIY"ӭ��ͤ"NOR"��\n"
"�������֡���������ʿ���ڴ���������������ı������ſɽ������ڡ�ͤ��������\n"
"֪��ɮ����æµ���д���������͡�\n"
    );

	set("exits", ([
		"northup" : __DIR__"shijie9",
		"southdown" : __DIR__"shijie8",
	]));
	set("outdoors", "shaolin");
	set("objects",([
		CLASS_D("shaolin") + "/xu-tong" : 1,
		CLASS_D("shaolin") + "/xu-ming" : 1,
		CLASS_D("shaolin") + "/weitian" : 1,
	]));
	setup();
}

void init()
{
	object me,wei;
	me=this_player();
	add_action("do_quit","quit");

	if (me->query_temp("qinjian/askhe"))
	{
	
		if (!objectp(wei=present("wei tianwang",environment(me))))
		{
			wei=new("kungfu/class/shaolin/weitian");
			wei->move(environment(me));
		}

		message_vision(HIY"$Nվ������������Σ�һ�Ե��������ȵ������������һ���Ͳ��Ǻö���������\n"NOR,me);
		call_out("do_diao",3+random(3),me,wei);
		me->delete_temp("qinjian/askhe");

	}

}
int do_diao(object me,object wei)
{
	object he;    
	if (!objectp(he=present("he zudao",environment(me))))
	{
		he=new("kungfu/class/kunlun/hezudao");
		he->move(environment(me));
	/*	he->delete("chat_msg_combat");
		he->set("chat_msg_combat", ({
  			(: perform_action, "sword.feihua" :),  		
			//(: exert_function, "qinjian" :),
		}));
		setup();*/

	}
		message_vision(HIC"����￦��һ����ʯͤ�ݶ����ѣ�����һ��������������˶�����һ����\n"NOR,me);
		
		do_check(me);
		he->kill_ob(wei);
		wei->kill_ob(he);
		me->set_temp("qinjian/lookfight",1);
		return 1;
}

int do_check(object me)
{
	object wei,he;
	me=this_player();
	wei=present("wei tianwang",environment(me));
	he=present("he zudao",environment(me));

	if (objectp(wei)) 
	{
		call_out("do_check",1,me);
		return 1;
	}
	
	if (!objectp(he=present("he zudao",environment(me)))) return;
	else {
		message_vision(HIR"\n\n\n\n\n��������˿���$Nһ��˵����������ʩչ���似��ɶ�������ˣ��ܷ����canwu���Ϳ����Լ��ˡ�\n\n\n\n"NOR,me);
		add_action("do_lingwu","canwu");
		destruct(he);
	}
	return 1;
}

int do_lingwu()
{
	object me;
	//int i,j,x;
	
	me = this_player();       
    if (!me->query_temp("qinjian/lookfight"))
    	return notify_fail("�������Զ���ȵ����㱾���Ƿ�֮�ˣ����ʴ�����������\n");
	
	if (!me->query("family")
		|| me->query("family/master_id")!="he zudao"
		|| me->query("family/family_name")!="������")
		return notify_fail("�������Զ���ȵ���������ɵ��ӣ����ʴ�����������\n");

	
    if( me->query_skill("xuantian-wuji", 1) < 350 )
		return notify_fail("��������޼����費��350�����޷������������ǽ����ľ�Ҫ���ڣ�\n");
	
	if( me->query("quest/kl/xtwj/qinjian/pass") )
		return notify_fail("���Ѿ�����������ٽ��������ֺιʿ�����Ц�أ�\n");

	if ((int)me->query("int")<30)
		return notify_fail("��Ѹ�׽����ܿ����ԣ�����������30���������ң�\n");
	
	
	if( time()- me->query("quest/kl/xtwj/qinjian/time")<86400)
		return notify_fail("�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�\n");
  
	call_out("thinking",1,me);
	me->delete_temp("qinjian/lookfight");
	return 1;
 
}

int thinking(object me)
{
  int i,j;
  if(!me) return 0;
  if(me->query_temp("qinjian/canwu")<(3+random(3)))
    { me->add_temp("qinjian/canwu",1);
          if(random(2)) tell_object(me,HIG"\n����������Ÿղź��������������ʱ��һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬�����һ��������������һ�ָ��٣�һ�ֻӽ��Ĺ��̣��ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
 
  else
   {  
	  me->delete_temp("qinjian/canwu");
  
	  i=random(10);
	  j=random(me->query("kar"));
      if (i == 3 
		// && random(total) >= 80 
	     && me->query("kar") <= 30
		 && j > 27  )
	  {
       
          tell_object(me,HIM"\n�������޼������������У���ȱ�裬��������أ���������������֮����һ��һ����������������������ת���ݣ�\n"NOR);
          message_vision(HIC"\n$N�����ʹ�������޼�����ͬʱ�����������ټ�ͬʱʹ�õļ����ƺ���Щ�˽��ˡ���\n"NOR,me); 
          tell_object(me,HIR"������ʹ�������޼�����������ʵʩ�ٽ�˫���ƺ���Щ�˽��ˣ�ʣ�µľ����ڼ���ϰ�ˣ�\n"NOR);
          me->set("quest/kl/xtwj/qinjian/pass",1);
          //me->set("title",HIC"ȫ������칦����"NOR);
          log_file("quest/xtwjqinjian", sprintf("%s(%s) ʧ��%d�γɹ��⿪�ٽ�˫������Դj��%d�������i��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/kl/xtwj/qinjian/fail"),
          j,
		  i,
          me->query("combat_exp")) );
          me->start_busy(1);
       }
      else
       {
          tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
          message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
          tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ����ٽ�˫������ʧ�ܣ�\n"NOR);
          tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
          tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		  log_file("quest/xtwjqinjian", sprintf("%s(%s) ���������޼��ٽ�˫��ʧ��%d�Ρ���Դj��%d�������i��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/kl/xtwj/qinjian/fail"),
          j,
		  i,
          me->query("combat_exp")) );
          me->add("quest/kl/xtwj/qinjian/fail",1);
          me->set("quest/kl/xtwj/qinjian/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/kl/xtwj/qinjian/time",time());
        } 

     }

}


int do_quit()
{
        object ob = this_player();
	if (ob->query_condition("sl_lunzhi") > 0){
		write("��������ֵ�������˳���Ϸ��\n");
                return 1;
        }
        return 0;
}

int valid_leave(object me, string dir)
{
	object *inv;
	mapping myfam;
	int i;

	myfam = (mapping)me->query("family");
  	if (!me->query("luohan_winner") && !present("yingxiong ling", me))
		if (me->query("gender") == "Ů��" && dir == "northup" ) {
			if(objectp(present("xu tong", environment(me))))
				return notify_fail("��ͨ������ס�����һ��˵����ǧ����������������Ů�����롣\n"
				 + RANK_D->query_respect(me) +"����ɽȥ�ɣ��������ûȤ��\n");
			if(objectp(present("xu ming", environment(me))))
				return notify_fail("����������������ǰ��˫�ֺ�ʲ˵���������ӷ�"
					"��λ" + RANK_D->query_respect(me) + "��������\nˡС�²��Ӵ�Ů"
                			"�͡�Ůʩ������һ����𣬺η�ȥ��üɽ��ϲ��\n");
		}
	if ((!myfam || myfam["family_name"] != "������" ) && dir == "northup") {
        	inv = all_inventory(me);
        	for(i=sizeof(inv)-1; i>=0; i--)
            	if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped"))) {
                	if(objectp(present("xu tong", environment(me))))
                    		return notify_fail("��ͨ��ס��˵������λ" +
                        RANK_D->query_respect(me) + "����±��С�����ǧ���"
                        "��أ���Ͳ��óֱ�����ɽ��\n");
                	if(objectp(present("xu ming", environment(me))))
                    		return notify_fail("����������������ǰ��˫�ֺ�ʲ˵������"
                        "���ӷ���λ" + RANK_D->query_respect(me) + "������"
                        "���С�\n�����徲֮�أ����������赶Ū��������ʩ����"
                        "�¡�\n");
		}
	}

	if (!me->query("muren_winner")
	 && mapp(myfam)
	 && myfam["family_name"]== "������" 
	 && me->query("class") == "bonze" 
	 && dir == "southdown" ) {
		if(objectp(present("xu tong", environment(me))))
			return notify_fail("��ͨ������ס�㹪��˵������λʦ���书��δ���ã�����"
                              "��ɽ����������������ֵ�������\n");
		if(objectp(present("xu ming", environment(me))))
			return notify_fail("����������ס�㹪��˵������λʦ���书��δ���ã�����"
                              "��ɽ����������������ֵ�������\n");
	}

	if (me->query_condition("sl_lunzhi") > 0)
		return notify_fail("��������ֵ�������뿪��\n");

	if(me->query("no_quest") && dir == "northup")
		return notify_fail("\n");

	return ::valid_leave(me, dir);
}
