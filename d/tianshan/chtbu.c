// Room: /d/tianshan/chtbu.c
// By Linux

#include <ansi.h>
inherit ROOM;
string look_deng1();
string look_deng2();
string look_deng3();
string look_deng4();

void create()
{
	set("short", "���첿");
	set("long", @LONG
��ǰ��һ�������������˵Ĵ������ǳ��첿�����ڵأ�����ǽ���ϻ�����
�����춥�ϻ�����һ���������ӣ�ͷ���нǣ����ֳֳ����������ս�������
��һֻ������������𡣵�������ɫ��ʯĥ�ͣ��ֺ��޷죬��Ȼ��ɡ�������
�ǵ�����յ���ƣ������ڴ����������������Ǵӵ��﷢����
LONG);

	set("exits", ([
                "eastdown" : __DIR__"dadao9",
        ]));       

        set("objects", ([
                __DIR__"npc/f-dizi" : 1,
        ]));    

	set("item_desc", ([
		"east deng" : (: look_deng1 :),
		"south deng" : (: look_deng2 :),
		"west deng" : (: look_deng3 :),
		"north deng" : (: look_deng4 :),
	]));
	set("zhbfang", 1);
	setup();	
}

void init()
{
	add_action("do_smell", ({"smell", "wen"}));
	add_action("do_move", ({"move", "yi"}));
	//add_action("do_dunwu","dunwu");
}

void reset()
{
	set("zhbfang", 1);
}

string look_deng1()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "ʲô��\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ�����û��ʲô������\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ����ڷ�������һյ�ĵ������ƺ������ƶ���\n";
	}
}

string look_deng2()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "ʲô��\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "����ϸ���ŵ�ȼ�ڴ����Ͻǵ�ͭ�ƣ�����û��ʲô������\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "����ϸ���ŵ�ȼ�ڴ����Ͻǵ�ͭ�ƣ����ڷ�������һյ�ĵ������ƺ������ƶ���\n";
	}
}

string look_deng3()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "ʲô��\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ�����û��ʲô������\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ����ڷ�������һյ�ĵ������ƺ������ƶ���\n";
	}
}

string look_deng4()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "ʲô��\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ�����û��ʲô������\n";
	}
	else {
		me->set_temp("ts/smell2",1);		
		return "����ϸ���ŵ�ȼ�ڴ������ǵ�ͭ�ƣ����ڷ�������һյ�ĵ������ƺ������ƶ���\n";
	}
}

int do_smell(string arg)
{
	object me=this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���أ�\n");
	tell_object(me,"����ϸ���ſ�������������ƺ�������������������ζ��ͬ�����ɵİ�������!\n");
	me->set_temp("ts/smell",1);
	me->add_busy(2);
	return 1;
}

int do_move(string arg)
{
	object ob, *ob2;
	object here = this_object();
	object me = this_player();
	int i;

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	if (!me->query_temp("ts/smell2"))
		return notify_fail("ʲô��\n");
	if( (!arg) || !((arg == "deng") || (arg == "��") || (arg == "tong deng") || (arg == "ͭ��")))
		return notify_fail("��Ҫ�ƶ�ʲô��\n");
	if (query("zhbfang") < 1)
		return notify_fail ("���ͭ�����Ա������ƣ���û�����κζ�����\n");

	ob=new(__DIR__"npc/zhbfan");
	ob->move(environment(me));
	message_vision(HIW"$N��ͭ�����Ա������ơ�\n"NOR, me);
	message_vision(HIW"ͻȻһ����Ӱ��$N���˹�����\n"NOR, me);
	message_vision(HIR"׿������$N���һ������Ȼ���ϵ�ɽ��������Ҫ��������Щ��ν���ӣ�ƴ�������һ\n"+
			"��Ȼ�����" + RANK_D->query_rude(me) + "�����ˣ��������������һ\n"NOR, me);
	here->add("zhbfang",-1);
	ob2 = all_inventory(here);
	for(i=0; i<sizeof(ob2); i++) {
		if(!ob2[i]->is_character()) continue;
		if( ob2[i]->is_corpse()) continue;
		//if(ob2[i]!=me) continue;
		ob->kill_ob(ob2[i]);
		ob2[i]->kill_ob(ob);
	}
	if (me->is_fighting(ob)&&objectp(ob))
	{
		call_out("check_zhuo",1,me,ob);
	}
	me->delete_temp("ts/smell1");
	me->delete_temp("ts/smell2");
	return 1;
}

int valid_leave(object me,string dir)
{
	me->delete_temp("ts/smell");
	me->delete_temp("ts/smell2");
	return ::valid_leave(me);
}
//ս�����ж�

//lingwu
int check_zhuo(object me,object ob)
{

	if (me->is_fighting(ob)&&objectp(ob))
	{
		call_out("check_zhuo",3,me,ob);
		return 1;
	}
	if (!present("zhuo bufan",environment(me)))
	{
		message_vision(HIC"\n\n$N�������գ���׿�����ò�����ɱ����������ȴ������������,�⽣��׿�����Ľ�����Ȼ��ɡ�\n"NOR,me);
		message_vision(HIC"\n\n$N���𷽲�׿����ͻȻ��������ʩɱ�֣��͵�һ�������д��Լ�Ҹ�´����������ۻ����˳������ӡ�\n"NOR,me);
		message_vision(HIC"\n\n��׿�����ڶ������У���־���֮�⣬��������־��£����ӵ�����Ĵ��˰��Ȧ�ӣ�����һͦ��\n"NOR,me);
		message_vision(HIC"\n\n������ͻȻ����������²�������â���ǽ�â���Ƴ��߰�������������Ȼ�Ǵ�˵�еġ���â������\n"NOR,me);
		message_vision(HIC"\n\n��ʱ׿������¶��Ц����������һ����������âͻʢ�����Լ��ؿڴ�������׿�����Ľ�����Ȼ��˹��\n"NOR,me);
		message_vision(HIC"\n\n���δ�������˵ı�������������â��������һ�������书���Լ���Ȼ�Ը����ˣ��Ų�һ�����˿�ȥ��\n"NOR,me);
		message_vision(HIC"\n\n׿������һ������ȫ������;�޷����У�ˢ��һ���죬���������˴�ʯ���У�����������ʯ���˼�\n"
							+"\n\n��Ӳ�Ļ���ʯ���ƣ�����ĳ�����Ȼ����һ�����࣬�ɼ������ڽ����ϵ�����ʵ�Ƿ�ͬС�ɡ�\n"NOR,me);
		message_vision(HIY"\n\n\n\n���н�â������һ��ʲô������ʽ�����˷��ŵ�һ��ս����ʹ���㲻����ʼ���ж���(dunwu)״̬��\n"NOR,me);	
		add_action("do_dunwu","dunwu");
		me->set_temp("tyqj/startdw",1);
		return 1;
	}

}


int do_dunwu()
{	
	object me = this_player();
	//int i=3+random(3);
//	me->start_busy(2);
	if (me->query("family/family_name") != "���չ�" )
		return notify_fail("�㲻�����չ���������������\n");
		
	
	if (me->query("family/master_id")!="xu zhu"||me->query("family/master_name")!="����")
			return notify_fail("��ʦ��������������������\n");

	if (!me->query_temp("tyqj/startdw"))
			return notify_fail("��û���������أ�\n");

    if (me->query("quest/ljg/tyqj/jianmang/pass"))	
			return notify_fail("���Ѿ��⿪�����ˣ�\n");
//	if (me->is_busy())	
//			return notify_fail("������æµ�У�\n");
	if (time()-me->query("quest/ljg/tyqj/jianmang/time")<86400)
			return notify_fail("��Ҳ̫�ڿ����Ү��\n");

		  
		//me->set_temp("tyqj/dwjm",1);
			
		message_vision(HIR"\n\n$N��ϥ������ͷ�������뵣��ƺ����ڲ���ʲô������\n"NOR,me);
		me->start_busy(999);
		remove_call_out("thinking");
		call_out("thinking",1,me);
		me->delete_temp("tyqj/startdw");
		return 1;
			
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);
  me->set("quest/ljg/tyqj/jianmang/time",time());
// if (!me->query_temp("tyqj/dwjm"))
	//return notify_fail("��Ҫ��ʲô�ء�\n");
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ���򻯹�����ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_jianmang")<(30+random(10)))
   {  
	  me->add_temp("canwu_jianmang",1);
	  switch (random(7))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ���䷽�ŵ�ս�����̣�ֻ���ö�Ŀһ��...\n"NOR);
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
	  //ȥ�����
     // me->delete_temp("tyqj/dwjm");


	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=26
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�����������������������⽣â�İ��أ����������潣��һ�е������Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/tyqj_jianmang", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ����������潣��â�İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ljg/tyqj/jianmang/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/ljg/tyqj/jianmang/time",time());
		 me->set("quest/ljg/tyqj/jianmang/pass",1);
		 me->start_busy(1);
		 me->delete_temp("canwu_jianmang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n���������潣��â��������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tyqj_jianmang", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ��������潣��â����ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ljg/tyqj/jianmang/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ljg/tyqj/jianmang/fail",1);
		 me->set("quest/ljg/tyqj/jianmang/time",time());
		 me->start_busy(1);
		 me->delete_temp("canwu_jianmang");
		 return 1;
   }

}