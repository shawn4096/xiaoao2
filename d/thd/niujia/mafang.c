// mafang.c
#include <ansi.h>
inherit ROOM;

string look_daocao();
#define QUESTDIR "quest/���Ӣ�۴�/"

#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"
int do_fail(object me);

void create()
{
	set("short", "��");
	set("long", @LONG
���������ļҵĺ�Ժ���������ǰ���и��ܴ��ˮ�ס�
�����߶����˺ܶൾ�ݣ�ƽʱ�ѵĺ����룬���첻֪����
ô�ˣ�����(Daocao)�ѵ����߰���ġ�
LONG
	);

	set("exits", ([
		"south" : __DIR__"houyuan.c",
	]));
            set("objects",([
              // __DIR__"npc/wanyan": 1,
               	
            ]));
            
       set("item_desc",([
		"daocao"		:	(: look_daocao :),
	]));
		set_temp("available",1);
	setup();
}

void init()
{
	
	add_action("do_move", "move");
}
string look_daocao()
{
	this_player()->set_temp("quest/���Ӣ�۴�/��ѩ����/lookdaocao",1);

	return "����һ��ѵ��ݣ�����ǽ�űߣ���֪����ʲ���ó���\n";
}
int do_move(string arg)
{
//	string dir;
	object me,ob;
	me=this_player();

	if( !arg || arg=="" || !query_temp("available") ) return 0;
	if (arg!="daocao"||!me->query_temp("quest/���Ӣ�۴�/��ѩ����/lookdaocao")) return notify_fail("��ҪŲ��ʲô��\n");

	if( arg=="daocao" 
	&& me->query_temp(QUESTDIR1+"weihebao")	
	&& query_temp("available")) 
	{
		write("�������ѵ��������ƿ���ͻȻ�����������Ÿ��������˵����� !\n\n");
	    delete_temp("available");
		ob = new(__DIR__"npc/wanyan");
		
		
		ob->unconscious();
		ob->set("qi",-1);
		
		ob->move(__DIR__"mafang");
		
		remove_call_out("fainting");

		call_out("fainting", 100+random(20), me, ob);

		me->set_temp(QUESTDIR1+"findwanyan",1);

	}else
	{
		write("�������ѵ��������ƿ������˵����µ�һ̲Ѫ����ʲôҲû����!\n\n");
		
	}

	return 1;
}

void fainting(object me, object ob)
{

		message_vision("�Ǹ����˻��������˹�������$N˵��: �ȡ����ҡ���\n",me,ob);
		//me->dest(ob);
		add_action("do_help","baohu");
		add_action("do_help","jiuzhu");

	    return;
}

int do_help(string arg)
{
	object me,wanyan,bao;
	me=this_player();

	if (!me->query_temp(QUESTDIR1+"answerhelp"))
	{
		return notify_fail("���պ��Ҳ�������!\n");
	}

	if (!arg||arg!="���պ���") return notify_fail("��Ҫ��˭��\n");
	if (me->query("quest/���Ӣ�۴�/��ѩ����/����ү"))
	{
		return notify_fail("���Ѿ��ɹ��������պ�����ү��\n");
	}
	if (time()-me->query("quest/���Ӣ�۴�/time")<86400)
	{
		return notify_fail("�������Ѿ����������պ�����үһ���ˣ�\n");
	}
	wanyan=present("wanyan honglie",this_object());

	if (me->query_temp(QUESTDIR1+"answerhelpwanyan")
		&&me->query(QUESTDIR1+"notongyin"))
	{
		message_vision("���պ����������������ڸ������$N˵��: Ӣ�۾��ң��ز�������\n",me);
		message_vision("\n$N�����պ���˵��������ү����ģ�����Ϳ�ʼ���㣡��\n",me);
		message_vision("\n$N��ʼ�����պ��Ұ����˿ڣ����������˵�ˮ���������ƴ�Ϊ���ͣ�\n",me);
		wanyan->clear_condition("neishang");
		wanyan->clear_condition("liuxue");
		wanyan->add_temp("apply/armor",150);
		wanyan->add_temp("apply/defense",150);
		wanyan->add_temp("apply/parry",200);

		call_out("qiu_attack",3+random(4),me,wanyan);
	}
	return 1;
}
int qiu_attack(object me,object wanyan)
{
	object yang,guo,qiu;
	me=this_player();
	message_vision(HIR"\n\n�����Ȼ�����𴦻���ŭ�����������ϣ�֪��֪�治֪�ģ����Ȼ�Ǽ�϶����Ȼ�ڵ�ү��Ƥ�ӵ��¾���������ү����\n",me);
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		yang=new("d/thd/niujia/npc/yang");
		yang->move("d/thd/niujia/mafang");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		guo=new("d/thd/niujia/npc/guo");
		guo->move("d/thd/niujia/mafang");
	}
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		qiu=new("d/thd/niujia/npc/qiuchuji");
		qiu->move("d/thd/niujia/mafang");
	}
	if (!wanyan)
	{
		return notify_fail("���պ��Ҳ��ڴ˵أ�������ɱ��\n");
	}
	yang->kill_ob(me);
	yang->kill_ob(wanyan);
	guo->kill_ob(me);
	guo->kill_ob(wanyan);
	qiu->kill_ob(me);
	qiu->kill_ob(wanyan);
	me->kill_ob(yang);
	me->kill_ob(guo);
	me->kill_ob(qiu);

	call_out("do_check",20+random(10),me,yang,guo,qiu,wanyan);
	return 1;
}

int do_check(object me,object yang,object guo,object qiu,object wanyan)
{
	if (!me) return 0;
	if (!objectp(wanyan))
	{
		tell_object(me,HBYEL+HIW"���sotry��Ҫ����(���պ���)û�еõ���Ч��������������������ʧ�ܣ�����������\n"NOR);
		do_fail(me);
		return 1;

	}
	if (objectp(yang)||objectp(guo)||objectp(qiu))
	{
		tell_object(me,HBYEL+HIW"�ڹ涨ʱ���ڣ�û�б��������պ��ң���������������ʧ�ܣ�����������\n"NOR);
		wanyan->die();

		do_fail(me);
		return 1;
	}
//	tell_object(me,HIG""NOR);
	tell_object(me,HBYEL+HIW"�����Ӣ�۴����������֮��ѩ����ɹ��������պ��ҵ�һ�����գ����պ��Ҷ����ʾ����֮�⣡\n"NOR);
	tell_object(me,HIG"���պ�����������˵����������һվ;�����˻ع���׳ʿ��һ·���ͣ�������л����\n"NOR);

	me->set_temp("quest/���Ӣ�۴�/��ѩ����/����ү",1);
	me->set("quest/���Ӣ�۴�/��ѩ����/����ү",1);
	destruct(wanyan);

	return 1;
}

int do_fail(object me)
{
	if (!me) return 1;
	
	me->add("quest/���Ӣ�۴�/��ѩ����/fail",1);
	me->set("quest/���Ӣ�۴�/time",time());
	tell_object(me,HBYEL+HIW"\n�����Ӣ�۴����������֮��ѩ��ƪ�Ȼ����պ���ʧ�ܣ����պ��ұ�ɱ��\n"NOR);
	tell_object(me,HBYEL+HIW"��24Сʱ��������\n"NOR);

	return 1;
}