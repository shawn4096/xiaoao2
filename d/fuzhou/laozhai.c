// room: laozhai.c
// modify by Lklv 2001.9.6

#include <room.h>
#include <ansi.h>

inherit ROOM;
int check_fight(object me);

void create()
{
    set("short", "������լ");
    set("long", @LONG
������һ���ưܵ���լԺ��ƽ��û��ʲô�˻���������Ϻ������˵ض�
�ż����Ҿߡ����ߵ�ǽ�ǽ���һ��֩���������ﵽ���ǳ�������Ȼ���Ѿ��ܾ�
û����ס�ˡ�����ľ�ͷ��һ����(men)�����ѱ�̮����ש�ߵ�ס�ˡ�
LONG
    );

    	set("exits", ([
        	"west" : __DIR__"xyxiang2",
    	]));

    	set("item_desc", ([
        	"men" : "�������ѱ���ס�޷�ͨ�У����������(break)����\n",
    	]) );
	setup();
}

void init()
{
	object book, me,yue;
	me = this_player();
	add_action("do_break", "break");	
	
	if (objectp(book=present("zijin jiasha",me))) {
		//remove_call_out("buqun_rob");
		//call_out("buqun_rob", 0, me, book);
		if (!objectp(yue=present("yue buqun",environment(me))))
		{
			yue=new("/d/fuzhou/npc/yuebuqun");
			yue->move(this_object());
		}
		message_vision(HIR "��Ȼ��һ�������˴Ӻ�Ӱ�����˳�����һ�С��з����ǡ���"
        "���г�����˸\n����������$N���ʺ�\n" NOR,  me);
		yue->kill_ob(me);
		me->start_busy(1);
		call_out("check_fight",1,me);	
	}
}

int do_break(string arg)
{
	int n;
	n = this_player()->query("neili");
	if( !arg || arg!="men" ) {
		write("��Ҫ����������ұ��˵Ķ�����\n"); // by pishou
		return 1;
	}
	message_vision("$N�ߵ�����ǰ���ݳ��������ʽ������һ������˫��ͬʱ�ĳ���\n", this_player());

	if (n>=500 && this_player()->query("quest/pixie/pxj_passwd")) {
		message_vision("$Nֻ��һ�����죬$N�������ˣ�\n", this_player());
		set("exits/south", __DIR__"houyuan");
		this_player()->set("neili",n-500);
		remove_call_out("close");
		call_out("close", 5, this_object());
	}
	else {
		message_vision("$N���һ���������������ʲôҲû����������$N����������ǿ��\n", this_player());
		this_player()->set("neili",0);
	}
	return 1;
}

void close(object room)
{
	message("vision","���ϵ�שͷ�߿�ϡ�ﻩ��̮���������ֵ�ס�˺��š�\n", room);
	room->delete("exits/south");
}

int check_fight(object me)
{
	object book,yue;
	if (!me) return 1;
	yue=present("yue buqun",this_object());
	if (!objectp(book=present("zijin jiasha",me)))
	{
		tell_object(me,HIY"����Ͻ������Ѿ�Ϊ�����������ˣ�\n"NOR);
		return 1;
	}	
	if (!living(me))
	{
		message_vision(HIR"$Nһ�֮�䣬�ѱ������˴����ʺ���ʱ��Ѫ��ע��\n"NOR, me);
		book->move(this_object());
		destruct(book);
		me->unconcious();
		return 1;
	}
	if (!yue || yue->query("qi")<yue->query("max_qi")/2)
	{	
		message_vision(HIC"$N��������ս�����ڽ��������˴��ܡ�\n"NOR, me);	
		write(HIR"������˫���أ�Խǽ���ߡ�\n��о������˵��������ǻ�ɽ�ɵġ�\n"NOR);
		destruct(yue);
		return 1;
	}
	call_out("check_fight",1,me);
	return 1;

}
