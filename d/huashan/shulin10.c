// Room: /d/huashan/shulin.c
// Date: Look 99/03/25

inherit ROOM;
#include <get_place.h>
#include <ansi.h>
int check(object ob);
//string get_place(string str);

string* msg1 = ({"��Ȼ","ͻȻ",	"�͵�",	"�䲻��",});
string* msg2 = ({"��������","�������",});
string* msg3 = ({"�ܳ�","ɱ��",});
string* msg4 = ({"һ�Ѷ���","����","һ����ȥ","��ȥ",});
string* msg5 = ({"��",	"����",	"����·","�����·",});

string* names = ({
"/d/village/caidi",	"/d/village/shilu1",	"/d/village/shilu2",
"/d/village/shilu3",	"/d/village/shilu4",	"/d/village/shilu5",
"/d/village/shilu6",	__DIR__"canglong",	__DIR__"celang1",
__DIR__"celang2",	__DIR__"chaoyang",	__DIR__"husun",
__DIR__"pubu",		__DIR__"qianchi",	__DIR__"qingke",
__DIR__"shaluo",	__DIR__"sheshen",	__DIR__"shulin1",
__DIR__"shulin2",	__DIR__"shulin3",	__DIR__"shulin4",
__DIR__"yuquan",	__DIR__"yunu",		__DIR__"zhenyue",
__DIR__"shanlu1",	__DIR__"xiaolu2",	__DIR__"siguoya",
__DIR__"baichi",	__DIR__"laojun",	__DIR__"houtang",
__DIR__"celang3",	__DIR__"celang4",
});

void create()
{
        set("short", "����");
        set("long",@long
�����ǻ�ɽ�����һƬ�����֣������û�к����֣���ǧ��Ҫ�ڴ˵ؾ�
������˵����ǿ����û�����١�ɱ�˵����龭��������
long);
        set("exits",([
		"west" : __DIR__"shulin3",
	        "north" : __DIR__"shulin2",
		"east" : __DIR__"shulin1",
	]));
	setup();
}

void init(object me)
{
	object target, *living, ob, name1, ling;
	string objwhere, str;
	int i, j;

	me = this_player();
	name1 = me->query("id");
	ling = present("ling pai", me);

        if( ! (present("mengmian ren", environment(me)) ) 
	 && (int)me->query_temp("hs/jobji", 1)==1 
	 && (int)me->query_temp("hs/have", 1)==0
	 && ling
	 && (int)ling->query_temp("done", 1) < 2
	 && !(ling->query_temp("hsjob") != name1 )
	 &&  random(10) > 3 ) {

		living = livings();
		for (i=0;i < sizeof(living);i++){
			j = random(sizeof(living));
			if (j <= 1 || j == sizeof(living)-1) continue;
			if(check(living[j]) ){
				target = living[j];
				str = environment(target)->query("short");
				if( str == "��ɮ��"
			 || str == HIR"������"NOR
			 || str == "��շ�ħȦ"
			 || str == HIB"����Ժ"NOR) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
			}
		}

		ob=new(__DIR__"npc/mmr");
		ob->set("long", ob->query("long")+ "�������Ǹղ�����"+me->query("name")+"("+capitalize(me->query("id"))+")���Ƶ��ˡ�\n");
		ling->move(ob);
		me->set_temp("hs/have", 1);
		ling->set_temp("mmr", name1);
		ob->set_temp("mmr", name1);

		if (me->query("combat_exp", 1) > 2000000
		 && ling->query_temp("done", 1) > 0
		 && target ) {
			ob->move(environment(target));
			me->set_temp("hs/power", 1);
			message_vision(HIW "\n" + msg1[random(sizeof(msg1))] +
				msg2[random(sizeof(msg2))] + 
				msg3[random(sizeof(msg3))] + "һ��������" +
				msg4[random(sizeof(msg4))] + 
				"$N�����ƣ���" HIY +get_place(base_name(environment(target)))+ str +
				HIW + msg5[random(sizeof(msg5))] + "��ȥ��\n\n" NOR, me);
			return;
		}
		else {
			objwhere = names[random(sizeof(names))];
			ob->move(objwhere);
			message_vision(HIW "\n" + msg1[random(sizeof(msg1))] +
				msg2[random(sizeof(msg2))] + 
				msg3[random(sizeof(msg3))] + "һ��������" +
				msg4[random(sizeof(msg4))] + 
				"$N�����ƣ���" HIY + objwhere->query("short") + 
				HIW + msg5[random(sizeof(msg5))] + "��ȥ��\n\n" NOR, me);
		}
	}
}

string *no_kill_list = ({
	"mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")	 
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("sleep_room")     //add by renlai for no fight sleep room
	 || room->query("quest")          //add by renlai for not enter room
	 || room->query("outdoors") == "���ش��"
	 || room->query("outdoors") == "������"   //add by renlai for not enter zone
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/xueshan/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
	 return 0;
	return 1;
}

