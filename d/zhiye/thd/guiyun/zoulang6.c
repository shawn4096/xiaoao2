// /u/jpei/guiyun/zoulang6.c

inherit ROOM;

void create()
{
	set("short","����");
	set("long",@LONG
���Ǵ�����ͨ�����䳡�����ȡ������������ۣ����������˻�
����
LONG
);
	set("exits",([
		"north" : __DIR__"zoulang5",
		"south" : __DIR__"lianwuchang",
	]) );
	set("no_clean_up",0);
	set("outdoors", "����ׯ");
	set("objects",([
                __DIR__"npc/zhuangding" : 1,
	]));  
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "south" && me->query("family/family_name") != "�һ���")
		if (present("zhuang ding", this_object()))
			return notify_fail("һλׯ����ס���㣬����������˵������λ����������������Ǳ�ׯ���ӵ����䳡����\n");
/*
		else
			return notify_fail("һλׯ����Ȼ�ӻ��������˳�������ס���㣬����������˵������λ����������������Ǳ�ׯ���ӵ����䳡����\n����ͣ�������ˣ���λׯ��һ���֣����˻�����������\n");
	
*/
	return ::valid_leave(me, dir);
}