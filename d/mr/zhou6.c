// /u/beyond/mr/zhou6.c
// this is made by beyond
// update 1997.6.20
inherit ROOM;
void create()
{
	set("short", "С��");
	set("long", @LONG
һҶС�ۣ����Ҳ�������ߡ��˸��ˡ�һ����ʮ������������ֳֳ���ݣ�
���ڴ�β�����س��Ŵ���
LONG
	);
	set("outdoors", "Ľ��");
        set("no_fight",1);
	setup();
}

void run(object ob)
{
	if (!ob) return;
	if (environment(ob) == this_object()){
		ob->move(__DIR__"zhou7", 1);
		tell_object(ob,"\n����Ѵ�ʻ����һƬһ���޼ʵĺɻ�����һ����ȥ, ������Ҷ, ��Ҷ, «έ��\n"
				"����, ����һģһ��, ��֮��Ҷ, ��Ҷ��ˮ��Ư��, ��ʱһ�����, �㼴�仯\n"
				"�ٶ�, ����˿̼ǵ��������, ��ʱ������ȫȻ��ͬ��\n\n");
	}
}

void init()
{
	object ob = this_player();
	call_out("run", 5, ob);
}